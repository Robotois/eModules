#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AccelGyroModule.o \
	${OBJECTDIR}/Kalman.o \
	${OBJECTDIR}/Libraries/ADS1015/ADS1015.o \
	${OBJECTDIR}/Libraries/BCMSetup/BCMSetup.o \
	${OBJECTDIR}/Libraries/MCP23008/MCP23008.o \
	${OBJECTDIR}/Libraries/PCA9685/PCA9685.o \
	${OBJECTDIR}/Libraries/Timer/AccurateTiming.o \
	${OBJECTDIR}/LineFinder.o \
	${OBJECTDIR}/Modules/AnalogModules/LightSensor.o \
	${OBJECTDIR}/Modules/AnalogModules/OpticalDistanceSensor.o \
	${OBJECTDIR}/Modules/AnalogModules/RotarySensor.o \
	${OBJECTDIR}/Modules/AnalogModules/TemperatureSensor.o \
	${OBJECTDIR}/Modules/DigitalIO/DigitalHeader.o \
	${OBJECTDIR}/Modules/DigitalIO/DigitalIO.o \
	${OBJECTDIR}/Modules/LCD/LCDModule.o \
	${OBJECTDIR}/Modules/LineSensors/LineSensors.o \
	${OBJECTDIR}/Modules/Motors/Motors.o \
	${OBJECTDIR}/Modules/RGBLEDs/RGBLEDs.o \
	${OBJECTDIR}/Modules/Servos/Servos.o \
	${OBJECTDIR}/Modules/Ultrasonic/UltrasonicSensor.o \
	${OBJECTDIR}/Robert.o \
	${OBJECTDIR}/Robotina.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-l bcm2835 -l rt

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pimodules

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pimodules: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pimodules ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/AccelGyroModule.o: AccelGyroModule.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AccelGyroModule.o AccelGyroModule.cpp

${OBJECTDIR}/Kalman.o: Kalman.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Kalman.o Kalman.cpp

${OBJECTDIR}/Libraries/ADS1015/ADS1015.o: Libraries/ADS1015/ADS1015.cpp 
	${MKDIR} -p ${OBJECTDIR}/Libraries/ADS1015
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libraries/ADS1015/ADS1015.o Libraries/ADS1015/ADS1015.cpp

${OBJECTDIR}/Libraries/BCMSetup/BCMSetup.o: Libraries/BCMSetup/BCMSetup.cpp 
	${MKDIR} -p ${OBJECTDIR}/Libraries/BCMSetup
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libraries/BCMSetup/BCMSetup.o Libraries/BCMSetup/BCMSetup.cpp

${OBJECTDIR}/Libraries/MCP23008/MCP23008.o: Libraries/MCP23008/MCP23008.cpp 
	${MKDIR} -p ${OBJECTDIR}/Libraries/MCP23008
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libraries/MCP23008/MCP23008.o Libraries/MCP23008/MCP23008.cpp

${OBJECTDIR}/Libraries/PCA9685/PCA9685.o: Libraries/PCA9685/PCA9685.cpp 
	${MKDIR} -p ${OBJECTDIR}/Libraries/PCA9685
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libraries/PCA9685/PCA9685.o Libraries/PCA9685/PCA9685.cpp

${OBJECTDIR}/Libraries/Timer/AccurateTiming.o: Libraries/Timer/AccurateTiming.cpp 
	${MKDIR} -p ${OBJECTDIR}/Libraries/Timer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libraries/Timer/AccurateTiming.o Libraries/Timer/AccurateTiming.cpp

${OBJECTDIR}/LineFinder.o: LineFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LineFinder.o LineFinder.cpp

${OBJECTDIR}/Modules/AnalogModules/LightSensor.o: Modules/AnalogModules/LightSensor.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modules/AnalogModules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Modules/AnalogModules/LightSensor.o Modules/AnalogModules/LightSensor.cpp

${OBJECTDIR}/Modules/AnalogModules/OpticalDistanceSensor.o: Modules/AnalogModules/OpticalDistanceSensor.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modules/AnalogModules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Modules/AnalogModules/OpticalDistanceSensor.o Modules/AnalogModules/OpticalDistanceSensor.cpp

${OBJECTDIR}/Modules/AnalogModules/RotarySensor.o: Modules/AnalogModules/RotarySensor.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modules/AnalogModules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Modules/AnalogModules/RotarySensor.o Modules/AnalogModules/RotarySensor.cpp

${OBJECTDIR}/Modules/AnalogModules/TemperatureSensor.o: Modules/AnalogModules/TemperatureSensor.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modules/AnalogModules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Modules/AnalogModules/TemperatureSensor.o Modules/AnalogModules/TemperatureSensor.cpp

${OBJECTDIR}/Modules/DigitalIO/DigitalHeader.o: Modules/DigitalIO/DigitalHeader.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modules/DigitalIO
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Modules/DigitalIO/DigitalHeader.o Modules/DigitalIO/DigitalHeader.cpp

${OBJECTDIR}/Modules/DigitalIO/DigitalIO.o: Modules/DigitalIO/DigitalIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modules/DigitalIO
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Modules/DigitalIO/DigitalIO.o Modules/DigitalIO/DigitalIO.cpp

${OBJECTDIR}/Modules/LCD/LCDModule.o: Modules/LCD/LCDModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modules/LCD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Modules/LCD/LCDModule.o Modules/LCD/LCDModule.cpp

${OBJECTDIR}/Modules/LineSensors/LineSensors.o: Modules/LineSensors/LineSensors.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modules/LineSensors
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Modules/LineSensors/LineSensors.o Modules/LineSensors/LineSensors.cpp

${OBJECTDIR}/Modules/Motors/Motors.o: Modules/Motors/Motors.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modules/Motors
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Modules/Motors/Motors.o Modules/Motors/Motors.cpp

${OBJECTDIR}/Modules/RGBLEDs/RGBLEDs.o: Modules/RGBLEDs/RGBLEDs.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modules/RGBLEDs
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Modules/RGBLEDs/RGBLEDs.o Modules/RGBLEDs/RGBLEDs.cpp

${OBJECTDIR}/Modules/Servos/Servos.o: Modules/Servos/Servos.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modules/Servos
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Modules/Servos/Servos.o Modules/Servos/Servos.cpp

${OBJECTDIR}/Modules/Ultrasonic/UltrasonicSensor.o: Modules/Ultrasonic/UltrasonicSensor.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modules/Ultrasonic
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Modules/Ultrasonic/UltrasonicSensor.o Modules/Ultrasonic/UltrasonicSensor.cpp

${OBJECTDIR}/Robert.o: Robert.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Robert.o Robert.cpp

${OBJECTDIR}/Robotina.o: Robotina.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Robotina.o Robotina.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pimodules

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
