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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AccelGyroModule.o \
	${OBJECTDIR}/AccurateTiming.o \
	${OBJECTDIR}/Kalman.o \
	${OBJECTDIR}/LineFinder.o \
	${OBJECTDIR}/LineSensorModule.o \
	${OBJECTDIR}/Motors.o \
	${OBJECTDIR}/Robert.o \
	${OBJECTDIR}/Robotina.o \
	${OBJECTDIR}/ServoModule.o \
	${OBJECTDIR}/UltrasonicSensor.o \
	${OBJECTDIR}/libraries/ADS1015/ADS1015.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-larmadillo
CXXFLAGS=-larmadillo

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-l bcm2835

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pimodules

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pimodules: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pimodules ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/AccelGyroModule.o: AccelGyroModule.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AccelGyroModule.o AccelGyroModule.cpp

${OBJECTDIR}/AccurateTiming.o: AccurateTiming.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AccurateTiming.o AccurateTiming.cpp

${OBJECTDIR}/Kalman.o: Kalman.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Kalman.o Kalman.cpp

${OBJECTDIR}/LineFinder.o: LineFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LineFinder.o LineFinder.cpp

${OBJECTDIR}/LineSensorModule.o: LineSensorModule.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LineSensorModule.o LineSensorModule.cpp

${OBJECTDIR}/Motors.o: Motors.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Motors.o Motors.cpp

${OBJECTDIR}/Robert.o: Robert.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Robert.o Robert.cpp

${OBJECTDIR}/Robotina.o: Robotina.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Robotina.o Robotina.cpp

${OBJECTDIR}/ServoModule.o: ServoModule.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ServoModule.o ServoModule.cpp

${OBJECTDIR}/UltrasonicSensor.o: UltrasonicSensor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/UltrasonicSensor.o UltrasonicSensor.cpp

${OBJECTDIR}/libraries/ADS1015/ADS1015.o: libraries/ADS1015/ADS1015.cpp 
	${MKDIR} -p ${OBJECTDIR}/libraries/ADS1015
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/ADS1015/ADS1015.o libraries/ADS1015/ADS1015.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
