CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(CMAKE_SYSTEM_NAME  Generic)

SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(TOOLCHAIN d:/toolchain/avr8-gnu-toolchain)

SET(CMAKE_ASM_COMPILER ${TOOLCHAIN}/bin/avr-as.exe)
SET(CMAKE_C_COMPILER ${TOOLCHAIN}/bin/avr-gcc.exe)
#SET(CMAKE_CXX_COMPILER ${TOOLCHAIN}/bin/avr-g++.exe)
SET(AVRSTRIP ${TOOLCHAIN}/bin/avr-strip.exe)
SET(OBJCOPY  ${TOOLCHAIN}/bin/avr-objcopy.exe)
SET(OBJDUMP  ${TOOLCHAIN}/bin/avr-objdump.exe)
SET(SIZE  ${TOOLCHAIN}/bin/avr-size.exe)
SET(PROGRAMMER  ${TOOLCHAIN}/../avrdude/avrdude.exe)

PROJECT(main C ASM)

SET(MCU atmega8)
SET(F_CPU 1000000UL)

SET(CSTANDARD "-std=gnu99 -pedantic")
SET(COPT "-Os")
SET(CDEBUG "-gdwarf-2")
SET(CWARN "-Wall -Wstrict-prototypes -Wundef")
SET(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")

SET(CFLAGS "${CSTANDARD} -mmcu=${MCU} -DF_CPU=${F_CPU} ${COPT} ${CDEBUG} ${CWARN} ${CTUNING}")
SET(LDFLAGS "-Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref")

SET(CMAKE_C_FLAGS ${CFLAGS} CACHE STRING "" FORCE)
SET(CMAKE_CXX_FLAGS ${CXXFLAGS} CACHE STRING "" FORCE)
SET(CMAKE_EXE_LINKER_FLAGS ${LDFLAGS} CACHE STRING "" FORCE)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf src/${CMAKE_PROJECT_NAME}.c src/app.c src/lk.c src/rtc.c src/timer.c src/hal.c)

ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD COMMAND ${SIZE} ARGS --mcu=${MCU} --format=avr ${CMAKE_PROJECT_NAME}.elf)
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD COMMAND ${OBJCOPY} -O ihex -R .eeprom -R .fuse -R .lock ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.hex)
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD COMMAND ${OBJCOPY} -O binary -R .eeprom -R .fuse -R .lock ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin)
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD COMMAND ${SIZE} ARGS --target=ihex ${CMAKE_PROJECT_NAME}.hex)

ADD_CUSTOM_TARGET(flash COMMAND ${PROGRAMMER} -s -p ${MCU} -P com3 -c stk500v2 -U flash:w:${CMAKE_PROJECT_NAME}.hex)
