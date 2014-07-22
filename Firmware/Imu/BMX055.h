/*
 * File:   BMX055.h
 * Author: Seb Madgwick
 *
 * Definitions for Bosch BMX055 gyroscope and accelerometer register addresses
 * and values.  Magnetometer may be interfaced to using the Bosch BMM Linux
 * Driver (BMM_Linux_Android_rls_v2.5.6_20131217).
 */

#ifndef BMX055_H
#define BMX055_H

//------------------------------------------------------------------------------
// Definitions (accelerometer)

#define BMX055_ACC_ADDRESS  0x18 // I2C address (SD01 = GND)

#define ACC_BGW_CHIPID      0x00 // accelerometer registers
#define ACC_ACCD_X_LSB      0x02
#define ACC_ACCD_X_MSB      0x03
#define ACC_ACCD_Y_LSB      0x04
#define ACC_ACCD_Y_MSB      0x05
#define ACC_ACCD_Z_LSB      0x06
#define ACC_ACCD_Z_MSB      0x07
#define ACC_ACCD_TEMP       0x08
#define ACC_INT_STATUS_0    0x09
#define ACC_INT_STATUS_1    0x0A
#define ACC_INT_STATUS_2    0x0B
#define ACC_INT_STATUS_3    0x0C
#define ACC_FIFO_STATUS     0x0E
#define ACC_PMU_RANGE       0x0F
#define ACC_PMU_BW          0x10
#define ACC_PMU_LPW         0x11
#define ACC_PMU_LOW_POWER   0x12
#define ACC_ACCD_HBW        0x13
#define ACC_BGW_SOFTRESET   0x14
#define ACC_INT_EN_0        0x16
#define ACC_INT_EN_1        0x17
#define ACC_INT_EN_2        0x18
#define ACC_INT_MAP0        0x19
#define ACC_INT_MAP1        0x1A
#define ACC_INT_MAP2        0x1B
#define ACC_INT_SRC         0x1E
#define ACC_INT_OUT_CTRL    0x20
#define ACC_INT_RST_LATCH   0x21
#define ACC_INT_0           0x22
#define ACC_INT_1           0x23
#define ACC_INT_2           0x24
#define ACC_INT_3           0x25
#define ACC_INT_4           0x26
#define ACC_INT_5           0x27
#define ACC_INT_6           0x28
#define ACC_INT_7           0x29
#define ACC_INT_8           0x2A
#define ACC_INT_9           0x2B
#define ACC_INT_A           0x2C
#define ACC_INT_B           0x2D
#define ACC_INT_C           0x2E
#define ACC_INT_D           0x2F
#define ACC_FIFO_CONFIG_0   0x30
#define ACC_PMU_SELF_TEST   0x32
#define ACC_TRIM_NVM_CTRL   0x33
#define ACC_BGW_SPI3_WDT    0x34
#define ACC_OFC_CTRL        0x36
#define ACC_OFC_SETTING     0x37
#define ACC_OFC_OFFSET_X    0x38
#define ACC_OFC_OFFSET_Y    0x39
#define ACC_OFC_OFFSET_Z    0x3A
#define ACC_TRIM_GP0        0x3B
#define ACC_TRIM_GP1        0x3C
#define ACC_FIFO_CONFIG_1   0x3E
#define ACC_FIFO_DATA       0x3F

#define ACC_RANGE_16G       0b00001100 // ACC_PMU_RANGE

#define ACC_UPDATE_64MS     0b00001000 // ACC_PMU_BW
#define ACC_UPDATE_32MS     0b00001001
#define ACC_UPDATE_16MS     0b00001010
#define ACC_UPDATE_8MS      0b00001011
#define ACC_UPDATE_4MS      0b00001100
#define ACC_UPDATE_2MS      0b00001101
#define ACC_UPDATE_1MS      0b00001110
#define ACC_UPDATE_0_5MS    0b00001111

//------------------------------------------------------------------------------
// Definitions (gyroscope)

#define BMX055_GYR_ADDRESS  0x68 // I2C address (SD02 = GND)

#define GYR_CHIPID          0x00 // gyroscope registers
#define GYR_RATE_X_LSB      0x02
#define GYR_RATE_X_MSB      0x03
#define GYR_RATE_Y_LSB      0x04
#define GYR_RATE_Y_MSB      0x05
#define GYR_RATE_Z_LSB      0x06
#define GYR_RATE_Z_MSB      0x07
#define GYR_INT_STATUS_0    0x09
#define GYR_INT_STATUS_1    0x0A
#define GYR_INT_STATUS_2    0x0B
#define GYR_INT_STATUS_3    0x0C
#define GYR_FIFO_STATUS     0x0E
#define GYR_RANGE           0x0F
#define GYR_BW              0x10
#define GYR_LPM1            0x11
#define GYR_LPM2            0x12
#define GYR_RATE_HBW        0x13
#define GYR_BGW_SOFTRESET   0x14
#define GYR_INT_EN_0        0x15
#define GYR_INT_EN_1        0x16
#define GYR_INT_MAP0        0x17
#define GYR_INT_MAP1        0x18
#define GYR_INT_MAP2        0x19
#define GYR_INT_RST_LATCH   0x21
#define GYR_HIGH_TH_X       0x22
#define GYR_HIGH_DUR_X      0x23
#define GYR_HIGH_TH_Y       0x24
#define GYR_HIGH_DUR_Y      0x25
#define GYR_HIGH_TH_Z       0x26
#define GYR_HIGH_DUR_Z      0x27
#define GYR_SOC             0x31
#define GYR_A_FOC           0x32
#define GYR_TRIM_NVM_CTRL   0x33
#define GYR_BGW_SPI3_WDT    0x34
#define GYR_OFC1            0x36
#define GYR_OFC2            0x37
#define GYR_OFC3            0x38
#define GYR_OFC4            0x39
#define GYR_TRIM_GP0        0x3A
#define GYR_TRIM_GP1        0x3B
#define GYR_BIST1           0x3C
#define GYR_FIFO_CONFIG_1   0x3D
#define GYR_FIFO_CONFIG_2   0x3E

#define GYR_ODR100_FB32     0b00000111 // GYR_BW
#define GYR_ODR200_FB64     0b00000110
#define GYR_ODR100_FB12     0b00000101
#define GYR_ODR200_FB23     0b00000100
#define GYR_ODR400_FB47     0b00000011
#define GYR_ODR1000_FB116   0b00000010
#define GYR_ODR2000_FB230   0b00000001
#define GYR_ODR2000_FB523   0b00000000

#define GYR_DATA_EN         0b10000000 // GYR_INT_EN_0

#define GYR_INT1_LVL        0b00000001 // GYR_INT_EN_1

#define GYR_INT1_DATA       0b00000001 // GYR_INT_MAP1

#endif

//------------------------------------------------------------------------------
// End of file
