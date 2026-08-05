@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

call ".\BFW\Cmd Batches\BFW_ESP32_Build.bat"

set CompileFlags=-DBFW_ESP32_PLATFORM -DBFW_LITTLE_ENDIAN -DBFW_BUILD_STATIC -DBFW_X86 -std=c++20 -w -Os -Werror=return-type "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\cpp_flags" "-I.\BFW\Headers\\" -DF_CPU=240000000L -DARDUINO=10607 -DARDUINO_ESP32S3_DEV -DARDUINO_ARCH_ESP32 -DARDUINO_BOARD=\"ESP32S3_DEV\" -DARDUINO_VARIANT=\"esp32s3\" -DARDUINO_PARTITION_huge_app -DARDUINO_HOST_OS=\"windows\" -DARDUINO_FQBN=\"esp32:esp32:esp32s3:UploadSpeed=921600,USBMode=hwcdc,CDCOnBoot=cdc,MSCOnBoot=default,DFUOnBoot=dfu,UploadMode=default,CPUFreq=240,FlashMode=qio,FlashSize=16M,PartitionScheme=huge_app,DebugLevel=none,PSRAM=opi,LoopCore=1,EventsCore=1,EraseFlash=none,JTAGAdapter=builtin,ZigbeeMode=default\" -DESP32=ESP32 -DCORE_DEBUG_LEVEL=0 -DARDUINO_RUNNING_CORE=1 -DARDUINO_EVENT_RUNNING_CORE=1 -DBOARD_HAS_PSRAM -DARDUINO_USB_MODE=1 -DARDUINO_USB_CDC_ON_BOOT=1 -DARDUINO_USB_MSC_ON_BOOT=0 -DARDUINO_USB_DFU_ON_BOOT=1 "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\defines" -iprefix "%ESPPack%tools\esp32s3-libs\%ArduLibVer%\include\\" "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\includes" "-I%ESPPack%tools\esp32s3-libs\%ArduLibVer%\qio_opi\include\\" "-I%ESPPack%hardware\esp32\%ArduLibVer%\cores\esp32\\" "-I%ESPPack%hardware\esp32\%ArduLibVer%\variants\esp32s3\\"

if "%Configuration%" == "Debug" set CompileFlags=%CompileFlags% -DBFW_DEBUG
if "%Configuration%" == "Release" set CompileFlags=%CompileFlags%

if not exist ".\Binaries\BFW_ESP32\%Configuration%\" mkdir ".\Binaries\BFW_ESP32\%Configuration%\"
if not exist ".\Objects\BFW_ESP32\%Configuration%\" mkdir ".\Objects\BFW_ESP32\%Configuration%\"

echo on

xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW_ESP32\Sources\BFW_ESP32_Application.cpp" -o ".\Objects\BFW_ESP32\%Configuration%\BFW_ESP32_Application.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW_ESP32\Sources\BFW_ESP32_EntryPoint.cpp" -o ".\Objects\BFW_ESP32\%Configuration%\BFW_ESP32_EntryPoint.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW_ESP32\Sources\BFW_ESP32_MainMenu.cpp" -o ".\Objects\BFW_ESP32\%Configuration%\BFW_ESP32_MainMenu.o"

xtensa-esp32s3-elf-g++ "-Wl,--Map=.\Binaries\BFW_ESP32\%Configuration%\BFW_ESP32.map" "-L%ESPPack%tools\esp32s3-libs\%ArduLibVer%\lib\\" "-L%ESPPack%tools\esp32s3-libs\%ArduLibVer%\ld" "-L%ESPPack%tools\esp32s3-libs\%ArduLibVer%\qio_opi" -Wl,--wrap=esp_panic_handler -Wl,--wrap=esp_bt_mem_release -Wl,--wrap=esp_bt_controller_mem_release "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\ld_flags" "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\ld_scripts" -Wl,--start-group ".\Objects\BFW_ESP32\%Configuration%\BFW_ESP32_Application.o" ".\Objects\BFW_ESP32\%Configuration%\BFW_ESP32_EntryPoint.o" ".\Objects\BFW_ESP32\%Configuration%\BFW_ESP32_MainMenu.o" ".\Solution Items\Dependencies\ArduinoCore\Lib\ArduinoCore.a" ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\ld_libs" -Wl,--end-group -Wl,-EL -o ".\Binaries\BFW_ESP32\%Configuration%\BFW_ESP32.elf"

@echo off

set CompileFlags=

popd

echo on
