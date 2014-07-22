#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Human_Harp_Player_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Human_Harp_Player_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../main.c ../Uart/Uart1.c ../Send/Send.c ../Encoder/Encoder.c ../I2C/I2C1.c ../Imu/Imu.c ../Delay/Delay.c ../SleepTimer/SleepTimer.c ../Button/Button.c ../Led/Led.c ../BatteryLevel/BatteryLevel.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/761528099/Uart1.o ${OBJECTDIR}/_ext/761583977/Send.o ${OBJECTDIR}/_ext/1623220307/Encoder.o ${OBJECTDIR}/_ext/1360894859/I2C1.o ${OBJECTDIR}/_ext/1360896738/Imu.o ${OBJECTDIR}/_ext/2146845780/Delay.o ${OBJECTDIR}/_ext/222419331/SleepTimer.o ${OBJECTDIR}/_ext/2085484161/Button.o ${OBJECTDIR}/_ext/1360899356/Led.o ${OBJECTDIR}/_ext/692688262/BatteryLevel.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/761528099/Uart1.o.d ${OBJECTDIR}/_ext/761583977/Send.o.d ${OBJECTDIR}/_ext/1623220307/Encoder.o.d ${OBJECTDIR}/_ext/1360894859/I2C1.o.d ${OBJECTDIR}/_ext/1360896738/Imu.o.d ${OBJECTDIR}/_ext/2146845780/Delay.o.d ${OBJECTDIR}/_ext/222419331/SleepTimer.o.d ${OBJECTDIR}/_ext/2085484161/Button.o.d ${OBJECTDIR}/_ext/1360899356/Led.o.d ${OBJECTDIR}/_ext/692688262/BatteryLevel.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/761528099/Uart1.o ${OBJECTDIR}/_ext/761583977/Send.o ${OBJECTDIR}/_ext/1623220307/Encoder.o ${OBJECTDIR}/_ext/1360894859/I2C1.o ${OBJECTDIR}/_ext/1360896738/Imu.o ${OBJECTDIR}/_ext/2146845780/Delay.o ${OBJECTDIR}/_ext/222419331/SleepTimer.o ${OBJECTDIR}/_ext/2085484161/Button.o ${OBJECTDIR}/_ext/1360899356/Led.o ${OBJECTDIR}/_ext/692688262/BatteryLevel.o

# Source Files
SOURCEFILES=../main.c ../Uart/Uart1.c ../Send/Send.c ../Encoder/Encoder.c ../I2C/I2C1.c ../Imu/Imu.c ../Delay/Delay.c ../SleepTimer/SleepTimer.c ../Button/Button.c ../Led/Led.c ../BatteryLevel/BatteryLevel.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Human_Harp_Player_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512GM604
MP_LINKER_FILE_OPTION=,--script=p33EP512GM604.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761528099/Uart1.o: ../Uart/Uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761528099 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Uart/Uart1.c  -o ${OBJECTDIR}/_ext/761528099/Uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761528099/Uart1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761528099/Uart1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761583977/Send.o: ../Send/Send.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761583977 
	@${RM} ${OBJECTDIR}/_ext/761583977/Send.o.d 
	@${RM} ${OBJECTDIR}/_ext/761583977/Send.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Send/Send.c  -o ${OBJECTDIR}/_ext/761583977/Send.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761583977/Send.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761583977/Send.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1623220307/Encoder.o: ../Encoder/Encoder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1623220307 
	@${RM} ${OBJECTDIR}/_ext/1623220307/Encoder.o.d 
	@${RM} ${OBJECTDIR}/_ext/1623220307/Encoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Encoder/Encoder.c  -o ${OBJECTDIR}/_ext/1623220307/Encoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1623220307/Encoder.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1623220307/Encoder.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360894859/I2C1.o: ../I2C/I2C1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360894859 
	@${RM} ${OBJECTDIR}/_ext/1360894859/I2C1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360894859/I2C1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../I2C/I2C1.c  -o ${OBJECTDIR}/_ext/1360894859/I2C1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360894859/I2C1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360894859/I2C1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360896738/Imu.o: ../Imu/Imu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360896738 
	@${RM} ${OBJECTDIR}/_ext/1360896738/Imu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360896738/Imu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Imu/Imu.c  -o ${OBJECTDIR}/_ext/1360896738/Imu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360896738/Imu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360896738/Imu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2146845780/Delay.o: ../Delay/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2146845780 
	@${RM} ${OBJECTDIR}/_ext/2146845780/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/2146845780/Delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Delay/Delay.c  -o ${OBJECTDIR}/_ext/2146845780/Delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2146845780/Delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2146845780/Delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/222419331/SleepTimer.o: ../SleepTimer/SleepTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/222419331 
	@${RM} ${OBJECTDIR}/_ext/222419331/SleepTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/222419331/SleepTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SleepTimer/SleepTimer.c  -o ${OBJECTDIR}/_ext/222419331/SleepTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/222419331/SleepTimer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/222419331/SleepTimer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2085484161/Button.o: ../Button/Button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2085484161 
	@${RM} ${OBJECTDIR}/_ext/2085484161/Button.o.d 
	@${RM} ${OBJECTDIR}/_ext/2085484161/Button.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Button/Button.c  -o ${OBJECTDIR}/_ext/2085484161/Button.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2085484161/Button.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2085484161/Button.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360899356/Led.o: ../Led/Led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360899356 
	@${RM} ${OBJECTDIR}/_ext/1360899356/Led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360899356/Led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Led/Led.c  -o ${OBJECTDIR}/_ext/1360899356/Led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360899356/Led.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360899356/Led.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/692688262/BatteryLevel.o: ../BatteryLevel/BatteryLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/692688262 
	@${RM} ${OBJECTDIR}/_ext/692688262/BatteryLevel.o.d 
	@${RM} ${OBJECTDIR}/_ext/692688262/BatteryLevel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../BatteryLevel/BatteryLevel.c  -o ${OBJECTDIR}/_ext/692688262/BatteryLevel.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/692688262/BatteryLevel.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/692688262/BatteryLevel.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761528099/Uart1.o: ../Uart/Uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761528099 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Uart/Uart1.c  -o ${OBJECTDIR}/_ext/761528099/Uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761528099/Uart1.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761528099/Uart1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761583977/Send.o: ../Send/Send.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761583977 
	@${RM} ${OBJECTDIR}/_ext/761583977/Send.o.d 
	@${RM} ${OBJECTDIR}/_ext/761583977/Send.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Send/Send.c  -o ${OBJECTDIR}/_ext/761583977/Send.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761583977/Send.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761583977/Send.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1623220307/Encoder.o: ../Encoder/Encoder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1623220307 
	@${RM} ${OBJECTDIR}/_ext/1623220307/Encoder.o.d 
	@${RM} ${OBJECTDIR}/_ext/1623220307/Encoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Encoder/Encoder.c  -o ${OBJECTDIR}/_ext/1623220307/Encoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1623220307/Encoder.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1623220307/Encoder.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360894859/I2C1.o: ../I2C/I2C1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360894859 
	@${RM} ${OBJECTDIR}/_ext/1360894859/I2C1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360894859/I2C1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../I2C/I2C1.c  -o ${OBJECTDIR}/_ext/1360894859/I2C1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360894859/I2C1.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360894859/I2C1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360896738/Imu.o: ../Imu/Imu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360896738 
	@${RM} ${OBJECTDIR}/_ext/1360896738/Imu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360896738/Imu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Imu/Imu.c  -o ${OBJECTDIR}/_ext/1360896738/Imu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360896738/Imu.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360896738/Imu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2146845780/Delay.o: ../Delay/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2146845780 
	@${RM} ${OBJECTDIR}/_ext/2146845780/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/2146845780/Delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Delay/Delay.c  -o ${OBJECTDIR}/_ext/2146845780/Delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2146845780/Delay.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2146845780/Delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/222419331/SleepTimer.o: ../SleepTimer/SleepTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/222419331 
	@${RM} ${OBJECTDIR}/_ext/222419331/SleepTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/222419331/SleepTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SleepTimer/SleepTimer.c  -o ${OBJECTDIR}/_ext/222419331/SleepTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/222419331/SleepTimer.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/222419331/SleepTimer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2085484161/Button.o: ../Button/Button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2085484161 
	@${RM} ${OBJECTDIR}/_ext/2085484161/Button.o.d 
	@${RM} ${OBJECTDIR}/_ext/2085484161/Button.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Button/Button.c  -o ${OBJECTDIR}/_ext/2085484161/Button.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2085484161/Button.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2085484161/Button.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360899356/Led.o: ../Led/Led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360899356 
	@${RM} ${OBJECTDIR}/_ext/1360899356/Led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360899356/Led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Led/Led.c  -o ${OBJECTDIR}/_ext/1360899356/Led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360899356/Led.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360899356/Led.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/692688262/BatteryLevel.o: ../BatteryLevel/BatteryLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/692688262 
	@${RM} ${OBJECTDIR}/_ext/692688262/BatteryLevel.o.d 
	@${RM} ${OBJECTDIR}/_ext/692688262/BatteryLevel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../BatteryLevel/BatteryLevel.c  -o ${OBJECTDIR}/_ext/692688262/BatteryLevel.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/692688262/BatteryLevel.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/692688262/BatteryLevel.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Human_Harp_Player_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Human_Harp_Player_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Human_Harp_Player_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Human_Harp_Player_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Human_Harp_Player_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
