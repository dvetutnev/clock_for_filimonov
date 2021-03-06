CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(CMAKE_SYSTEM_NAME  Windows)

SET(CMAKE_VERBOSE_MAKEFILE ON)

PROJECT(main C CXX ASM)

SET(CSTANDARD "-std=gnu99 -pedantic")
SET(COPT "-Os")
#SET(CDEBUG "-gdwarf-2")
SET(CDEBUG "")
SET(CWARN "-Wall -Wstrict-prototypes -Wundef")
SET(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")
SET(CTUNING "")

SET(CFLAGS "${CSTANDARD} ${COPT} ${CDEBUG} ${CWARN} ${CTUNING}")
SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${CFLAGS} CACHE STRING "" FORCE)

ADD_DEFINITIONS(-DPC_BUILD)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ../src/${CMAKE_PROJECT_NAME}.c ../src/app.c ../src/lk.c ../src/rtc.c ../src/timer.c ../src/random.c ../src/hal_pc.c)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES})