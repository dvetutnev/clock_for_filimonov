# CMAKE generated file: DO NOT EDIT!
# Generated by "MSYS Makefiles" Generator, CMake Version 3.1

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /C/msys64/mingw64/bin/cmake.exe

# The command to remove a file.
RM = /C/msys64/mingw64/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /D/GoogleDrive/ElP/clock_for_filimonov/Firmware

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/b

# Include any dependencies generated for this target.
include CMakeFiles/main.elf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.elf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.elf.dir/flags.make

CMakeFiles/main.elf.dir/src/main.c.obj: CMakeFiles/main.elf.dir/flags.make
CMakeFiles/main.elf.dir/src/main.c.obj: ../src/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/b/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.elf.dir/src/main.c.obj"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.elf.dir/src/main.c.obj   -c /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/main.c

CMakeFiles/main.elf.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.elf.dir/src/main.c.i"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -E /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/main.c > CMakeFiles/main.elf.dir/src/main.c.i

CMakeFiles/main.elf.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.elf.dir/src/main.c.s"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -S /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/main.c -o CMakeFiles/main.elf.dir/src/main.c.s

CMakeFiles/main.elf.dir/src/main.c.obj.requires:
.PHONY : CMakeFiles/main.elf.dir/src/main.c.obj.requires

CMakeFiles/main.elf.dir/src/main.c.obj.provides: CMakeFiles/main.elf.dir/src/main.c.obj.requires
	$(MAKE) -f CMakeFiles/main.elf.dir/build.make CMakeFiles/main.elf.dir/src/main.c.obj.provides.build
.PHONY : CMakeFiles/main.elf.dir/src/main.c.obj.provides

CMakeFiles/main.elf.dir/src/main.c.obj.provides.build: CMakeFiles/main.elf.dir/src/main.c.obj

CMakeFiles/main.elf.dir/src/app.c.obj: CMakeFiles/main.elf.dir/flags.make
CMakeFiles/main.elf.dir/src/app.c.obj: ../src/app.c
	$(CMAKE_COMMAND) -E cmake_progress_report /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/b/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.elf.dir/src/app.c.obj"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.elf.dir/src/app.c.obj   -c /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/app.c

CMakeFiles/main.elf.dir/src/app.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.elf.dir/src/app.c.i"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -E /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/app.c > CMakeFiles/main.elf.dir/src/app.c.i

CMakeFiles/main.elf.dir/src/app.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.elf.dir/src/app.c.s"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -S /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/app.c -o CMakeFiles/main.elf.dir/src/app.c.s

CMakeFiles/main.elf.dir/src/app.c.obj.requires:
.PHONY : CMakeFiles/main.elf.dir/src/app.c.obj.requires

CMakeFiles/main.elf.dir/src/app.c.obj.provides: CMakeFiles/main.elf.dir/src/app.c.obj.requires
	$(MAKE) -f CMakeFiles/main.elf.dir/build.make CMakeFiles/main.elf.dir/src/app.c.obj.provides.build
.PHONY : CMakeFiles/main.elf.dir/src/app.c.obj.provides

CMakeFiles/main.elf.dir/src/app.c.obj.provides.build: CMakeFiles/main.elf.dir/src/app.c.obj

CMakeFiles/main.elf.dir/src/lk.c.obj: CMakeFiles/main.elf.dir/flags.make
CMakeFiles/main.elf.dir/src/lk.c.obj: ../src/lk.c
	$(CMAKE_COMMAND) -E cmake_progress_report /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/b/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.elf.dir/src/lk.c.obj"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.elf.dir/src/lk.c.obj   -c /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/lk.c

CMakeFiles/main.elf.dir/src/lk.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.elf.dir/src/lk.c.i"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -E /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/lk.c > CMakeFiles/main.elf.dir/src/lk.c.i

CMakeFiles/main.elf.dir/src/lk.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.elf.dir/src/lk.c.s"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -S /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/lk.c -o CMakeFiles/main.elf.dir/src/lk.c.s

CMakeFiles/main.elf.dir/src/lk.c.obj.requires:
.PHONY : CMakeFiles/main.elf.dir/src/lk.c.obj.requires

CMakeFiles/main.elf.dir/src/lk.c.obj.provides: CMakeFiles/main.elf.dir/src/lk.c.obj.requires
	$(MAKE) -f CMakeFiles/main.elf.dir/build.make CMakeFiles/main.elf.dir/src/lk.c.obj.provides.build
.PHONY : CMakeFiles/main.elf.dir/src/lk.c.obj.provides

CMakeFiles/main.elf.dir/src/lk.c.obj.provides.build: CMakeFiles/main.elf.dir/src/lk.c.obj

CMakeFiles/main.elf.dir/src/rtc.c.obj: CMakeFiles/main.elf.dir/flags.make
CMakeFiles/main.elf.dir/src/rtc.c.obj: ../src/rtc.c
	$(CMAKE_COMMAND) -E cmake_progress_report /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/b/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.elf.dir/src/rtc.c.obj"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.elf.dir/src/rtc.c.obj   -c /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/rtc.c

CMakeFiles/main.elf.dir/src/rtc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.elf.dir/src/rtc.c.i"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -E /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/rtc.c > CMakeFiles/main.elf.dir/src/rtc.c.i

CMakeFiles/main.elf.dir/src/rtc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.elf.dir/src/rtc.c.s"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -S /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/rtc.c -o CMakeFiles/main.elf.dir/src/rtc.c.s

CMakeFiles/main.elf.dir/src/rtc.c.obj.requires:
.PHONY : CMakeFiles/main.elf.dir/src/rtc.c.obj.requires

CMakeFiles/main.elf.dir/src/rtc.c.obj.provides: CMakeFiles/main.elf.dir/src/rtc.c.obj.requires
	$(MAKE) -f CMakeFiles/main.elf.dir/build.make CMakeFiles/main.elf.dir/src/rtc.c.obj.provides.build
.PHONY : CMakeFiles/main.elf.dir/src/rtc.c.obj.provides

CMakeFiles/main.elf.dir/src/rtc.c.obj.provides.build: CMakeFiles/main.elf.dir/src/rtc.c.obj

CMakeFiles/main.elf.dir/src/timer.c.obj: CMakeFiles/main.elf.dir/flags.make
CMakeFiles/main.elf.dir/src/timer.c.obj: ../src/timer.c
	$(CMAKE_COMMAND) -E cmake_progress_report /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/b/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.elf.dir/src/timer.c.obj"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.elf.dir/src/timer.c.obj   -c /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/timer.c

CMakeFiles/main.elf.dir/src/timer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.elf.dir/src/timer.c.i"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -E /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/timer.c > CMakeFiles/main.elf.dir/src/timer.c.i

CMakeFiles/main.elf.dir/src/timer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.elf.dir/src/timer.c.s"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -S /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/timer.c -o CMakeFiles/main.elf.dir/src/timer.c.s

CMakeFiles/main.elf.dir/src/timer.c.obj.requires:
.PHONY : CMakeFiles/main.elf.dir/src/timer.c.obj.requires

CMakeFiles/main.elf.dir/src/timer.c.obj.provides: CMakeFiles/main.elf.dir/src/timer.c.obj.requires
	$(MAKE) -f CMakeFiles/main.elf.dir/build.make CMakeFiles/main.elf.dir/src/timer.c.obj.provides.build
.PHONY : CMakeFiles/main.elf.dir/src/timer.c.obj.provides

CMakeFiles/main.elf.dir/src/timer.c.obj.provides.build: CMakeFiles/main.elf.dir/src/timer.c.obj

CMakeFiles/main.elf.dir/src/random.c.obj: CMakeFiles/main.elf.dir/flags.make
CMakeFiles/main.elf.dir/src/random.c.obj: ../src/random.c
	$(CMAKE_COMMAND) -E cmake_progress_report /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/b/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.elf.dir/src/random.c.obj"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.elf.dir/src/random.c.obj   -c /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/random.c

CMakeFiles/main.elf.dir/src/random.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.elf.dir/src/random.c.i"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -E /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/random.c > CMakeFiles/main.elf.dir/src/random.c.i

CMakeFiles/main.elf.dir/src/random.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.elf.dir/src/random.c.s"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -S /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/random.c -o CMakeFiles/main.elf.dir/src/random.c.s

CMakeFiles/main.elf.dir/src/random.c.obj.requires:
.PHONY : CMakeFiles/main.elf.dir/src/random.c.obj.requires

CMakeFiles/main.elf.dir/src/random.c.obj.provides: CMakeFiles/main.elf.dir/src/random.c.obj.requires
	$(MAKE) -f CMakeFiles/main.elf.dir/build.make CMakeFiles/main.elf.dir/src/random.c.obj.provides.build
.PHONY : CMakeFiles/main.elf.dir/src/random.c.obj.provides

CMakeFiles/main.elf.dir/src/random.c.obj.provides.build: CMakeFiles/main.elf.dir/src/random.c.obj

CMakeFiles/main.elf.dir/src/hal.c.obj: CMakeFiles/main.elf.dir/flags.make
CMakeFiles/main.elf.dir/src/hal.c.obj: ../src/hal.c
	$(CMAKE_COMMAND) -E cmake_progress_report /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/b/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.elf.dir/src/hal.c.obj"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.elf.dir/src/hal.c.obj   -c /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/hal.c

CMakeFiles/main.elf.dir/src/hal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.elf.dir/src/hal.c.i"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -E /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/hal.c > CMakeFiles/main.elf.dir/src/hal.c.i

CMakeFiles/main.elf.dir/src/hal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.elf.dir/src/hal.c.s"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -S /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/hal.c -o CMakeFiles/main.elf.dir/src/hal.c.s

CMakeFiles/main.elf.dir/src/hal.c.obj.requires:
.PHONY : CMakeFiles/main.elf.dir/src/hal.c.obj.requires

CMakeFiles/main.elf.dir/src/hal.c.obj.provides: CMakeFiles/main.elf.dir/src/hal.c.obj.requires
	$(MAKE) -f CMakeFiles/main.elf.dir/build.make CMakeFiles/main.elf.dir/src/hal.c.obj.provides.build
.PHONY : CMakeFiles/main.elf.dir/src/hal.c.obj.provides

CMakeFiles/main.elf.dir/src/hal.c.obj.provides.build: CMakeFiles/main.elf.dir/src/hal.c.obj

CMakeFiles/main.elf.dir/src/twimaster.c.obj: CMakeFiles/main.elf.dir/flags.make
CMakeFiles/main.elf.dir/src/twimaster.c.obj: ../src/twimaster.c
	$(CMAKE_COMMAND) -E cmake_progress_report /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/b/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.elf.dir/src/twimaster.c.obj"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.elf.dir/src/twimaster.c.obj   -c /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/twimaster.c

CMakeFiles/main.elf.dir/src/twimaster.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.elf.dir/src/twimaster.c.i"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -E /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/twimaster.c > CMakeFiles/main.elf.dir/src/twimaster.c.i

CMakeFiles/main.elf.dir/src/twimaster.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.elf.dir/src/twimaster.c.s"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  $(C_DEFINES) $(C_FLAGS) -S /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/src/twimaster.c -o CMakeFiles/main.elf.dir/src/twimaster.c.s

CMakeFiles/main.elf.dir/src/twimaster.c.obj.requires:
.PHONY : CMakeFiles/main.elf.dir/src/twimaster.c.obj.requires

CMakeFiles/main.elf.dir/src/twimaster.c.obj.provides: CMakeFiles/main.elf.dir/src/twimaster.c.obj.requires
	$(MAKE) -f CMakeFiles/main.elf.dir/build.make CMakeFiles/main.elf.dir/src/twimaster.c.obj.provides.build
.PHONY : CMakeFiles/main.elf.dir/src/twimaster.c.obj.provides

CMakeFiles/main.elf.dir/src/twimaster.c.obj.provides.build: CMakeFiles/main.elf.dir/src/twimaster.c.obj

# Object files for target main.elf
main_elf_OBJECTS = \
"CMakeFiles/main.elf.dir/src/main.c.obj" \
"CMakeFiles/main.elf.dir/src/app.c.obj" \
"CMakeFiles/main.elf.dir/src/lk.c.obj" \
"CMakeFiles/main.elf.dir/src/rtc.c.obj" \
"CMakeFiles/main.elf.dir/src/timer.c.obj" \
"CMakeFiles/main.elf.dir/src/random.c.obj" \
"CMakeFiles/main.elf.dir/src/hal.c.obj" \
"CMakeFiles/main.elf.dir/src/twimaster.c.obj"

# External object files for target main.elf
main_elf_EXTERNAL_OBJECTS =

main.elf: CMakeFiles/main.elf.dir/src/main.c.obj
main.elf: CMakeFiles/main.elf.dir/src/app.c.obj
main.elf: CMakeFiles/main.elf.dir/src/lk.c.obj
main.elf: CMakeFiles/main.elf.dir/src/rtc.c.obj
main.elf: CMakeFiles/main.elf.dir/src/timer.c.obj
main.elf: CMakeFiles/main.elf.dir/src/random.c.obj
main.elf: CMakeFiles/main.elf.dir/src/hal.c.obj
main.elf: CMakeFiles/main.elf.dir/src/twimaster.c.obj
main.elf: CMakeFiles/main.elf.dir/build.make
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable main.elf"
	/c/toolchain/avr8-gnu-toolchain/bin/avr-gcc.exe  -std=gnu99 -pedantic -mmcu=atmega8 -DF_CPU=1000000UL -Os -gdwarf-2 -Wall -Wstrict-prototypes -Wundef -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums  -Wl,-Map=main.map,--cref $(main_elf_OBJECTS) $(main_elf_EXTERNAL_OBJECTS)  -o main.elf  
	/c/toolchain/avr8-gnu-toolchain/bin/avr-size.exe --mcu=atmega8 --format=avr main.elf
	/c/toolchain/avr8-gnu-toolchain/bin/avr-objcopy.exe -O ihex -R .eeprom -R .fuse -R .lock main.elf main.hex
	/c/toolchain/avr8-gnu-toolchain/bin/avr-objcopy.exe -O binary -R .eeprom -R .fuse -R .lock main.elf main.bin
	/c/toolchain/avr8-gnu-toolchain/bin/avr-size.exe --target=ihex main.hex

# Rule to build all files generated by this target.
CMakeFiles/main.elf.dir/build: main.elf
.PHONY : CMakeFiles/main.elf.dir/build

CMakeFiles/main.elf.dir/requires: CMakeFiles/main.elf.dir/src/main.c.obj.requires
CMakeFiles/main.elf.dir/requires: CMakeFiles/main.elf.dir/src/app.c.obj.requires
CMakeFiles/main.elf.dir/requires: CMakeFiles/main.elf.dir/src/lk.c.obj.requires
CMakeFiles/main.elf.dir/requires: CMakeFiles/main.elf.dir/src/rtc.c.obj.requires
CMakeFiles/main.elf.dir/requires: CMakeFiles/main.elf.dir/src/timer.c.obj.requires
CMakeFiles/main.elf.dir/requires: CMakeFiles/main.elf.dir/src/random.c.obj.requires
CMakeFiles/main.elf.dir/requires: CMakeFiles/main.elf.dir/src/hal.c.obj.requires
CMakeFiles/main.elf.dir/requires: CMakeFiles/main.elf.dir/src/twimaster.c.obj.requires
.PHONY : CMakeFiles/main.elf.dir/requires

CMakeFiles/main.elf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.elf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.elf.dir/clean

CMakeFiles/main.elf.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MSYS Makefiles" /D/GoogleDrive/ElP/clock_for_filimonov/Firmware /D/GoogleDrive/ElP/clock_for_filimonov/Firmware /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/b /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/b /D/GoogleDrive/ElP/clock_for_filimonov/Firmware/b/CMakeFiles/main.elf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.elf.dir/depend

