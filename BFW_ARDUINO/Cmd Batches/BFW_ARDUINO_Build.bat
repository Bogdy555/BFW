cd "..\..\"

mkdir ".\Binaries\"
mkdir ".\Binaries\BFW_ARDUINO\"
mkdir ".\Binaries\BFW_ARDUINO\%Configuration%\"

mkdir ".\Objects\"
mkdir ".\Objects\BFW_ARDUINO\"
mkdir ".\Objects\BFW_ARDUINO\%Configuration%\"



set OutDir=.\Binaries\BFW_ARDUINO\%Configuration%\
set IntDir=.\Objects\BFW_ARDUINO\%Configuration%\

set SrcDir=.\BFW_ARDUINO\Sources\
set ArduinoSrcDir=.\BFW_ARDUINO\Vendor\Arduino\Sources\
set BFWSrcDir=.\BFW\Sources\

set ASSEMBLY_FLAGS=-c -g -x assembler-with-cpp -flto -MMD -mmcu=atmega328p
set ASSEMBLY_DEFINES=-DF_CPU=16000000L -DARDUINO=10815 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR %BFW_DEFINES%

set C_FLAGS=-c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p
set C_DEFINES=-DF_CPU=16000000L -DARDUINO=10815 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR %BFW_DEFINES%

set CPP_FLAGS=-c -g -Os -w -std=gnu++17 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p
set CPP_DEFINES=-DF_CPU=16000000L -DARDUINO=10815 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR %BFW_DEFINES%

set LINK_FLAGS=-w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p
set LINK_LIB="%OutDir%BFW.a" "%OutDir%Arduino.a" -lm
set LINK_OBJ="%IntDir%BFW_ARDUINO_EntryPoint.o" "%IntDir%BFW_ARDUINO_Application.o" "%IntDir%BFW_ARDUINO_MainMenu.o"



avr-gcc %ASSEMBLY_FLAGS% %ASSEMBLY_DEFINES% -o "%IntDir%wiring_pulse_asm.o" "%ArduinoSrcDir%wiring_pulse_asm.S"

avr-gcc %C_FLAGS% %C_DEFINES% -o "%IntDir%WInterrupts.o"	"%ArduinoSrcDir%WInterrupts.c"
avr-gcc %C_FLAGS% %C_DEFINES% -o "%IntDir%wiring_digital.o"	"%ArduinoSrcDir%wiring_digital.c"
avr-gcc %C_FLAGS% %C_DEFINES% -o "%IntDir%wiring_pulse.o"	"%ArduinoSrcDir%wiring_pulse.c"
avr-gcc %C_FLAGS% %C_DEFINES% -o "%IntDir%wiring_analog.o"	"%ArduinoSrcDir%wiring_analog.c"
avr-gcc %C_FLAGS% %C_DEFINES% -o "%IntDir%hooks.o"			"%ArduinoSrcDir%hooks.c"
avr-gcc %C_FLAGS% %C_DEFINES% -o "%IntDir%wiring_shift.o"	"%ArduinoSrcDir%wiring_shift.c"
avr-gcc %C_FLAGS% %C_DEFINES% -o "%IntDir%wiring.o"			"%ArduinoSrcDir%wiring.c"

avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%HardwareSerial.o"		"%ArduinoSrcDir%HardwareSerial.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%HardwareSerial0.o"	"%ArduinoSrcDir%HardwareSerial0.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%CDC.o"				"%ArduinoSrcDir%CDC.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%PluggableUSB.o"		"%ArduinoSrcDir%PluggableUSB.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%HardwareSerial1.o"	"%ArduinoSrcDir%HardwareSerial1.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%HardwareSerial2.o"	"%ArduinoSrcDir%HardwareSerial2.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%IPAddress.o"			"%ArduinoSrcDir%IPAddress.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%HardwareSerial3.o"	"%ArduinoSrcDir%HardwareSerial3.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%Print.o"				"%ArduinoSrcDir%Print.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%Stream.o"				"%ArduinoSrcDir%Stream.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%Tone.o"				"%ArduinoSrcDir%Tone.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%USBCore.o"			"%ArduinoSrcDir%USBCore.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%WMath.o"				"%ArduinoSrcDir%WMath.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%WString.o"			"%ArduinoSrcDir%WString.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%abi.o"				"%ArduinoSrcDir%abi.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%main.o"				"%ArduinoSrcDir%main.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%new.o"				"%ArduinoSrcDir%new.cpp"

avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%abi.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%CDC.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%HardwareSerial.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%HardwareSerial0.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%HardwareSerial1.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%HardwareSerial2.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%HardwareSerial3.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%hooks.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%IPAddress.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%main.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%new.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%PluggableUSB.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%Print.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%Stream.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%Tone.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%USBCore.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%WInterrupts.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%wiring.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%wiring_analog.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%wiring_digital.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%wiring_pulse.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%wiring_pulse_asm.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%wiring_shift.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%WMath.o"
avr-gcc-ar rcs "%OutDir%Arduino.a" "%IntDir%WString.o"



avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_EntryPoint.o"			"%BFWSrcDir%BFW_EntryPoint.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_Debug.o"				"%BFWSrcDir%BFW_Debug.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_Log.o"				"%BFWSrcDir%BFW_Log.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_Multiprocessing.o"	"%BFWSrcDir%BFW_Multiprocessing.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_Time.o"				"%BFWSrcDir%BFW_Time.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_Application.o"		"%BFWSrcDir%BFW_Application.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_Menu.o"				"%BFWSrcDir%BFW_Menu.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_Input.o"				"%BFWSrcDir%BFW_Input.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_Hardware.o"			"%BFWSrcDir%BFW_Hardware.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_Math.o"				"%BFWSrcDir%BFW_Math.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_Math_Matrix.o"		"%BFWSrcDir%BFW_Math_Matrix.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_Math_Vector.o"		"%BFWSrcDir%BFW_Math_Vector.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_Sound.o"				"%BFWSrcDir%BFW_Sound.cpp"

avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_EntryPoint.o"
avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_Debug.o"
avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_Log.o"
avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_Multiprocessing.o"
avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_Time.o"
avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_Application.o"
avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_Menu.o"
avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_Input.o"
avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_Hardware.o"
avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_Math.o"
avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_Math_Matrix.o"
avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_Math_Vector.o"
avr-gcc-ar rcs "%OutDir%BFW.a" "%IntDir%BFW_Sound.o"



avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_ARDUINO_EntryPoint.o"		"%SrcDir%BFW_ARDUINO_EntryPoint.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_ARDUINO_Application.o"	"%SrcDir%BFW_ARDUINO_Application.cpp"
avr-g++ %CPP_FLAGS% %CPP_DEFINES% -o "%IntDir%BFW_ARDUINO_MainMenu.o"		"%SrcDir%BFW_ARDUINO_MainMenu.cpp"



avr-gcc %LINK_FLAGS% -o "%IntDir%BFW_ARDUINO.elf" %LINK_OBJ% %LINK_LIB%

avr-objcopy -O ihex -R .eeprom "%IntDir%BFW_ARDUINO.elf" "%OutDir%BFW_ARDUINO.hex"



pause
