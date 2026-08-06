@echo off

echo on

if "%SolutionDir%" == "" call ".\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

set CCompiler=xtensa-esp32s3-elf-gcc
set CPPCompiler=xtensa-esp32s3-elf-g++
set Linker=xtensa-esp32s3-elf-ar
set CFiles=ColorFormat esp32-hal-adc esp32-hal-bt esp32-hal-cpu esp32-hal-dac esp32-hal-gpio esp32-hal-hosted esp32-hal-i2c-ng esp32-hal-i2c-slave esp32-hal-i2c esp32-hal-ldo esp32-hal-ledc esp32-hal-log-wrapper esp32-hal-matrix esp32-hal-misc esp32-hal-periman esp32-hal-psram esp32-hal-rgb-led esp32-hal-rmt esp32-hal-sigmadelta esp32-hal-spi esp32-hal-time esp32-hal-timer esp32-hal-tinyusb esp32-hal-touch-ng esp32-hal-touch esp32-hal-uart firmware_msc_fat idf_openthread_mpool_wrapper libb64\cdecode libb64\cencode stdlib_noniso wiring_pulse wiring_shift
set CPPFiles=freertos_stats main Esp FirmwareMSC FunctionalInterrupt HEXBuilder HWCDC HardwareSerial HashBuilder IPAddress MD5Builder MacAddress Print Stream StreamString StringUtils Tone USB USBCDC USBMSC WMath WString base64 cbuf chip-debug-report
set CompileFlags=-w -Os -Werror=return-type -DARDUINO_CORE_BUILD -DF_CPU=240000000L -DARDUINO=10607 -DARDUINO_ESP32S3_DEV -DARDUINO_ARCH_ESP32 -DARDUINO_BOARD=\"ESP32S3_DEV\" -DARDUINO_VARIANT=\"esp32s3\" -DARDUINO_PARTITION_huge_app -DARDUINO_HOST_OS=\"windows\" -DARDUINO_FQBN=\"esp32:esp32:esp32s3:UploadSpeed=921600,USBMode=hwcdc,CDCOnBoot=cdc,MSCOnBoot=default,DFUOnBoot=dfu,UploadMode=default,CPUFreq=240,FlashMode=qio,FlashSize=16M,PartitionScheme=huge_app,DebugLevel=none,PSRAM=opi,LoopCore=1,EventsCore=1,EraseFlash=none,JTAGAdapter=builtin,ZigbeeMode=default\" -DESP32=ESP32 -DCORE_DEBUG_LEVEL=0 -DARDUINO_RUNNING_CORE=1 -DARDUINO_EVENT_RUNNING_CORE=1 -DBOARD_HAS_PSRAM -DARDUINO_USB_MODE=1 -DARDUINO_USB_CDC_ON_BOOT=1 -DARDUINO_USB_MSC_ON_BOOT=0 -DARDUINO_USB_DFU_ON_BOOT=1 "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\defines" -iprefix "%ESPPack%tools\esp32s3-libs\%ArduLibVer%\include\\" "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\includes" "-I%ESPPack%tools\esp32s3-libs\%ArduLibVer%\qio_opi\include\\" "-I%ESPPack%hardware\esp32\%ArduLibVer%\cores\esp32\\" "-I%ESPPack%hardware\esp32\%ArduLibVer%\variants\esp32s3\\"
set CFlags="@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\c_flags"
set CPPFlags="@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\cpp_flags"

if not exist ".\Solution Items\Dependencies\ArduinoCore\Lib\libb64\" mkdir ".\Solution Items\Dependencies\ArduinoCore\Lib\libb64\"

echo on

for %%i in (%CFiles%) do (
	%CCompiler% %CompileFlags% %CFlags% -c "%ESPPack%hardware\esp32\%ArduLibVer%\cores\esp32\%%i.c" -o ".\Solution Items\Dependencies\ArduinoCore\Lib\%%i.o"
)

for %%i in (%CPPFiles%) do (
	%CPPCompiler% %CompileFlags% %CPPFlags% -c "%ESPPack%hardware\esp32\%ArduLibVer%\cores\esp32\%%i.cpp" -o ".\Solution Items\Dependencies\ArduinoCore\Lib\%%i.o"
)

for %%i in (%CFiles%) do (
	%Linker% rcs ".\Solution Items\Dependencies\ArduinoCore\Lib\ArduinoCore.a" ".\Solution Items\Dependencies\ArduinoCore\Lib\%%i.o"
)

for %%i in (%CPPFiles%) do (
	%Linker% rcs ".\Solution Items\Dependencies\ArduinoCore\Lib\ArduinoCore.a" ".\Solution Items\Dependencies\ArduinoCore\Lib\%%i.o"
)

@echo off

set CCompiler=
set CPPCompiler=
set Linker=
set CFiles=
set CPPFiles=
set CompileFlags=
set CFlags=
set CPPFlags=

popd

echo on
