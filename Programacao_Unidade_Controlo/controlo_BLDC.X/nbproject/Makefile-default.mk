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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/controlo_BLDC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/controlo_BLDC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c ../biblio_BLDC/controlLoop.c ../biblio_BLDC/initMeu.c ../biblio_BLDC/interrupt.c ../biblio_BLDC/measuresPlate.c ../biblio_BLDC/motor_control.c ../biblio_BLDC/sine_control.c ../biblio_BLDC/CAN/easy_can1.c ../biblio_BLDC/CAN/can_carro_eletrico_impl.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/387062786/controlLoop.o ${OBJECTDIR}/_ext/387062786/initMeu.o ${OBJECTDIR}/_ext/387062786/interrupt.o ${OBJECTDIR}/_ext/387062786/measuresPlate.o ${OBJECTDIR}/_ext/387062786/motor_control.o ${OBJECTDIR}/_ext/387062786/sine_control.o ${OBJECTDIR}/_ext/925455325/easy_can1.o ${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/_ext/387062786/controlLoop.o.d ${OBJECTDIR}/_ext/387062786/initMeu.o.d ${OBJECTDIR}/_ext/387062786/interrupt.o.d ${OBJECTDIR}/_ext/387062786/measuresPlate.o.d ${OBJECTDIR}/_ext/387062786/motor_control.o.d ${OBJECTDIR}/_ext/387062786/sine_control.o.d ${OBJECTDIR}/_ext/925455325/easy_can1.o.d ${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/387062786/controlLoop.o ${OBJECTDIR}/_ext/387062786/initMeu.o ${OBJECTDIR}/_ext/387062786/interrupt.o ${OBJECTDIR}/_ext/387062786/measuresPlate.o ${OBJECTDIR}/_ext/387062786/motor_control.o ${OBJECTDIR}/_ext/387062786/sine_control.o ${OBJECTDIR}/_ext/925455325/easy_can1.o ${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o

# Source Files
SOURCEFILES=main.c ../biblio_BLDC/controlLoop.c ../biblio_BLDC/initMeu.c ../biblio_BLDC/interrupt.c ../biblio_BLDC/measuresPlate.c ../biblio_BLDC/motor_control.c ../biblio_BLDC/sine_control.c ../biblio_BLDC/CAN/easy_can1.c ../biblio_BLDC/CAN/can_carro_eletrico_impl.c


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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/controlo_BLDC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ64GS606
MP_LINKER_FILE_OPTION=,--script=p33FJ64GS606.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG     -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/387062786/controlLoop.o: ../biblio_BLDC/controlLoop.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/387062786 
	@${RM} ${OBJECTDIR}/_ext/387062786/controlLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/387062786/controlLoop.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/controlLoop.c  -o ${OBJECTDIR}/_ext/387062786/controlLoop.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/387062786/controlLoop.o.d"      -g -D__DEBUG     -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/387062786/controlLoop.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/387062786/initMeu.o: ../biblio_BLDC/initMeu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/387062786 
	@${RM} ${OBJECTDIR}/_ext/387062786/initMeu.o.d 
	@${RM} ${OBJECTDIR}/_ext/387062786/initMeu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/initMeu.c  -o ${OBJECTDIR}/_ext/387062786/initMeu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/387062786/initMeu.o.d"      -g -D__DEBUG     -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/387062786/initMeu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/387062786/interrupt.o: ../biblio_BLDC/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/387062786 
	@${RM} ${OBJECTDIR}/_ext/387062786/interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/387062786/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/interrupt.c  -o ${OBJECTDIR}/_ext/387062786/interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/387062786/interrupt.o.d"      -g -D__DEBUG     -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/387062786/interrupt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/387062786/measuresPlate.o: ../biblio_BLDC/measuresPlate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/387062786 
	@${RM} ${OBJECTDIR}/_ext/387062786/measuresPlate.o.d 
	@${RM} ${OBJECTDIR}/_ext/387062786/measuresPlate.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/measuresPlate.c  -o ${OBJECTDIR}/_ext/387062786/measuresPlate.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/387062786/measuresPlate.o.d"      -g -D__DEBUG     -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/387062786/measuresPlate.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/387062786/motor_control.o: ../biblio_BLDC/motor_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/387062786 
	@${RM} ${OBJECTDIR}/_ext/387062786/motor_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/387062786/motor_control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/motor_control.c  -o ${OBJECTDIR}/_ext/387062786/motor_control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/387062786/motor_control.o.d"      -g -D__DEBUG     -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/387062786/motor_control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/387062786/sine_control.o: ../biblio_BLDC/sine_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/387062786 
	@${RM} ${OBJECTDIR}/_ext/387062786/sine_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/387062786/sine_control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/sine_control.c  -o ${OBJECTDIR}/_ext/387062786/sine_control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/387062786/sine_control.o.d"      -g -D__DEBUG     -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/387062786/sine_control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/925455325/easy_can1.o: ../biblio_BLDC/CAN/easy_can1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/925455325 
	@${RM} ${OBJECTDIR}/_ext/925455325/easy_can1.o.d 
	@${RM} ${OBJECTDIR}/_ext/925455325/easy_can1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/CAN/easy_can1.c  -o ${OBJECTDIR}/_ext/925455325/easy_can1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/925455325/easy_can1.o.d"      -g -D__DEBUG     -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/925455325/easy_can1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o: ../biblio_BLDC/CAN/can_carro_eletrico_impl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/925455325 
	@${RM} ${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o.d 
	@${RM} ${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/CAN/can_carro_eletrico_impl.c  -o ${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o.d"      -g -D__DEBUG     -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/387062786/controlLoop.o: ../biblio_BLDC/controlLoop.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/387062786 
	@${RM} ${OBJECTDIR}/_ext/387062786/controlLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/387062786/controlLoop.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/controlLoop.c  -o ${OBJECTDIR}/_ext/387062786/controlLoop.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/387062786/controlLoop.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/387062786/controlLoop.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/387062786/initMeu.o: ../biblio_BLDC/initMeu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/387062786 
	@${RM} ${OBJECTDIR}/_ext/387062786/initMeu.o.d 
	@${RM} ${OBJECTDIR}/_ext/387062786/initMeu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/initMeu.c  -o ${OBJECTDIR}/_ext/387062786/initMeu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/387062786/initMeu.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/387062786/initMeu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/387062786/interrupt.o: ../biblio_BLDC/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/387062786 
	@${RM} ${OBJECTDIR}/_ext/387062786/interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/387062786/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/interrupt.c  -o ${OBJECTDIR}/_ext/387062786/interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/387062786/interrupt.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/387062786/interrupt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/387062786/measuresPlate.o: ../biblio_BLDC/measuresPlate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/387062786 
	@${RM} ${OBJECTDIR}/_ext/387062786/measuresPlate.o.d 
	@${RM} ${OBJECTDIR}/_ext/387062786/measuresPlate.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/measuresPlate.c  -o ${OBJECTDIR}/_ext/387062786/measuresPlate.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/387062786/measuresPlate.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/387062786/measuresPlate.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/387062786/motor_control.o: ../biblio_BLDC/motor_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/387062786 
	@${RM} ${OBJECTDIR}/_ext/387062786/motor_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/387062786/motor_control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/motor_control.c  -o ${OBJECTDIR}/_ext/387062786/motor_control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/387062786/motor_control.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/387062786/motor_control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/387062786/sine_control.o: ../biblio_BLDC/sine_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/387062786 
	@${RM} ${OBJECTDIR}/_ext/387062786/sine_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/387062786/sine_control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/sine_control.c  -o ${OBJECTDIR}/_ext/387062786/sine_control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/387062786/sine_control.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/387062786/sine_control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/925455325/easy_can1.o: ../biblio_BLDC/CAN/easy_can1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/925455325 
	@${RM} ${OBJECTDIR}/_ext/925455325/easy_can1.o.d 
	@${RM} ${OBJECTDIR}/_ext/925455325/easy_can1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/CAN/easy_can1.c  -o ${OBJECTDIR}/_ext/925455325/easy_can1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/925455325/easy_can1.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/925455325/easy_can1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o: ../biblio_BLDC/CAN/can_carro_eletrico_impl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/925455325 
	@${RM} ${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o.d 
	@${RM} ${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../biblio_BLDC/CAN/can_carro_eletrico_impl.c  -o ${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/925455325/can_carro_eletrico_impl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/controlo_BLDC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/controlo_BLDC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG   -omf=elf     -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/controlo_BLDC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/controlo_BLDC.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/controlo_BLDC.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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
