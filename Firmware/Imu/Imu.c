/*
 * File:   Imu.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include "BMX055.h"
#include "I2C\I2C1.h"
#include "Imu.h"
#include <math.h>
#include "SystemDefinitions.h"
#include "Timer/Timer.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Definitions

#define HIGH_PASS_FILTER_GAIN 0.05f

typedef union {
    int value;

    struct {
        char lsb;
        char msb;
    };
} INT_UNION;

typedef union {
    unsigned long Val;

    struct {
        int LW;
        int HW;
    };
} DWORD_VAL;

typedef struct {
    INT_UNION x;
    INT_UNION y;
    INT_UNION z;
} GYRO_ADC;

typedef struct {
    float x;
    float y;
    float z;
} GYRO_CALIBRATED;

typedef struct {
    float w;
    float x;
    float y;
    float z;
} QUATERNION;

//------------------------------------------------------------------------------
// Macros

#define DEG_TO_RAD(DEGREES) (0.01745329252f * DEGREES)
#define RAD_TO_DEG(RADIANS) (57.29577951308f * RADIANS)

//------------------------------------------------------------------------------
// Variables

static I2CScript i2cScript;
static void ScriptCompleteTasks();
static Ticks64 adcTimestamp;

static volatile GYRO_ADC gyroAdc;
static volatile GYRO_CALIBRATED gyroDps;
static volatile QUATERNION quaternion = {1.0f, 0.0f, 0.0f, 0.0f};

static volatile bool highPassFilterDisabled = false;

//------------------------------------------------------------------------------
// Function prototypes

static float InvSqrt(float x);

//------------------------------------------------------------------------------
// Functions

void ImuInitialise() {

    // Power cycle BMX055
    IMU_VDD_LAT = 0;
    TimerDelay(50);
    IMU_VDD_LAT = 1;

    // Initialise I2C module
    I2C1Initialise(400000);
    TimerDelay(10);

    // Setup BMX055 gyroscope
    I2C1Start();
    I2C1Send(I2C_WRITE_ADDRESS(BMX055_GYR_ADDRESS));
    I2C1Send(BMX055_GYR_BW);
    I2C1Send(BMX055_GYR_ODR400_FB47);
    I2C1Restart();
    I2C1Send(I2C_WRITE_ADDRESS(BMX055_GYR_ADDRESS));
    I2C1Send(BMX055_GYR_INT_EN_0);
    I2C1Send(BMX055_GYR_DATA_EN);
    I2C1Restart();
    I2C1Send(I2C_WRITE_ADDRESS(BMX055_GYR_ADDRESS));
    I2C1Send(BMX055_GYR_INT_EN_1);
    I2C1Send(BMX055_GYR_INT1_LVL);
    I2C1Restart();
    I2C1Send(I2C_WRITE_ADDRESS(BMX055_GYR_ADDRESS));
    I2C1Send(BMX055_GYR_INT_MAP1);
    I2C1Send(BMX055_GYR_INT1_DATA);
    I2C1Stop();

    // Compose I2C script
    I2CScriptInitialise(&i2cScript);
    I2CScriptAddStart(&i2cScript);
    I2CScriptAddSend(&i2cScript, I2C_WRITE_ADDRESS(BMX055_GYR_ADDRESS));
    I2CScriptAddSend(&i2cScript, BMX055_GYR_RATE_X_LSB);
    I2CScriptAddRestart(&i2cScript);
    I2CScriptAddSend(&i2cScript, I2C_READ_ADDRESS(BMX055_GYR_ADDRESS));
    I2CScriptAddReceive(&i2cScript);
    I2CScriptAddAck(&i2cScript, (char*) &gyroAdc.x.lsb);
    I2CScriptAddReceive(&i2cScript);
    I2CScriptAddAck(&i2cScript, (char*) &gyroAdc.x.msb);
    I2CScriptAddReceive(&i2cScript);
    I2CScriptAddAck(&i2cScript, (char*) &gyroAdc.y.lsb);
    I2CScriptAddReceive(&i2cScript);
    I2CScriptAddAck(&i2cScript, (char*) &gyroAdc.y.msb);
    I2CScriptAddReceive(&i2cScript);
    I2CScriptAddAck(&i2cScript, (char*) &gyroAdc.z.lsb);
    I2CScriptAddReceive(&i2cScript);
    I2CScriptAddNack(&i2cScript, (char*) &gyroAdc.z.msb);
    I2CScriptAddStop(&i2cScript);
    i2cScript.scriptCompleteTasks = ScriptCompleteTasks;

    // Setup INT1
    _INT1IP = 3; // set interrupt priority
    _INT1IF = 0; // clear interrupt flag
    _INT1IE = 1; // enable interrupt
}

static void ScriptCompleteTasks() {

    // Calculate sample period
    static Ticks32 previousTicks;
    float samplePeriod = (float) (adcTimestamp.ticks32.value - previousTicks.value) * (1.0f / (float) TIMER_TICKS_PER_SECOND);
    previousTicks = adcTimestamp.ticks32;

    // Calculate degrees per second
    gyroDps.x = (float) gyroAdc.y.value * (1.0f / 16.4f); // swap x and y axis
    gyroDps.y = (float) gyroAdc.x.value * (1.0f / 16.4f);
    gyroDps.z = (float) -gyroAdc.z.value * (1.0f / 16.4f);

    // Calculate radians per second
    GYRO_CALIBRATED g = {DEG_TO_RAD(gyroDps.x), DEG_TO_RAD(gyroDps.y), DEG_TO_RAD(gyroDps.z)};

    // Adjust for convergence to alignment
    if (!highPassFilterDisabled) {
        g.y -= 2.0f * (quaternion.x * quaternion.z + quaternion.w * quaternion.y) * HIGH_PASS_FILTER_GAIN;
        g.z += 2.0f * (quaternion.x * quaternion.y - quaternion.w * quaternion.z) * HIGH_PASS_FILTER_GAIN;
    }

    // Integrate to yield quaternion
    QUATERNION q = quaternion;
    g.x *= (0.5f * samplePeriod); // pre-multiply common factors
    g.y *= (0.5f * samplePeriod);
    g.z *= (0.5f * samplePeriod);
    quaternion.w += (-q.x * g.x - q.y * g.y - q.z * g.z);
    quaternion.x += (q.w * g.x + q.y * g.z - q.z * g.y);
    quaternion.y += (q.w * g.y - q.x * g.z + q.z * g.x);
    quaternion.z += (q.w * g.z + q.x * g.y - q.y * g.x);

    // Normalise quaternion
    float reciprocalNorm = InvSqrt(quaternion.w * quaternion.w + quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z);
    quaternion.w *= reciprocalNorm;
    quaternion.x *= reciprocalNorm;
    quaternion.y *= reciprocalNorm;
    quaternion.z *= reciprocalNorm;
}

static float InvSqrt(float x) { // fast inverse square-root. See: http://en.wikipedia.org/wiki/Fast_inverse_square_root
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*) &i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

void ImuGetDirection(DIRECTION * const direction) {
    float x = 2.0f * quaternion.w * quaternion.w - 1.0f + 2.0f * quaternion.x * quaternion.x;
    float y = 2.0f * (quaternion.x * quaternion.y - quaternion.w * quaternion.z);
    float z = 2.0f * (quaternion.x * quaternion.z + quaternion.w * quaternion.y);
    direction->azimuth = RAD_TO_DEG(atan2(y, x));
    direction->elevation = RAD_TO_DEG(atan2(x, z)) - 90.0f;
}

float ImuGetAngularRate() {
    return sqrt(gyroDps.x * gyroDps.x + gyroDps.y * gyroDps.y + gyroDps.z * gyroDps.z);
}

void ImuZero() {
    quaternion.w = 1.0f;
    quaternion.x = 0.0f;
    quaternion.y = 0.0f;
    quaternion.z = 0.0f;
}

//------------------------------------------------------------------------------
// Functions - ISRs

void __attribute__((interrupt, auto_psv))_INT1Interrupt(void) {
    adcTimestamp = TimerGetTicks64();
    I2C1RunScript(&i2cScript); // read sensor data
    _INT1IF = 0; // clear interrupt flag
}

void ImuDisableHighPassFilter() {
    highPassFilterDisabled = true;
}

//------------------------------------------------------------------------------
// End of file
