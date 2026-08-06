@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

if not exist ".\Solution Items\Dependencies\ArduinoCore\Lib\ArduinoCore.a" call ".\Solution Items\Cmd Batches\BFW_ESP32_BuildCore.bat"

set Compiler=xtensa-esp32s3-elf-g++
set Linker=xtensa-esp32s3-elf-ar
set Files=BFW_Assets BFW_Cryptography BFW_Debug BFW_GUI BFW_GUID BFW_EntryPoint BFW_FileSystem BFW_Input BFW_Log BFW_Math_Matrix BFW_Math_Quaternion BFW_Math_Vector BFW_Math BFW_MultiProcessing BFW_RunTime BFW_String BFW_Time
set CompileFlags=-DBFW_ESP32_PLATFORM -DBFW_LITTLE_ENDIAN -DBFW_BUILD_STATIC -DBFW_X86 -std=c++20 -w -Os -Werror=return-type "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\cpp_flags" -DF_CPU=240000000L -DARDUINO=10607 -DARDUINO_ESP32S3_DEV -DARDUINO_ARCH_ESP32 -DARDUINO_BOARD=\"ESP32S3_DEV\" -DARDUINO_VARIANT=\"esp32s3\" -DARDUINO_PARTITION_huge_app -DARDUINO_HOST_OS=\"windows\" -DARDUINO_FQBN=\"esp32:esp32:esp32s3:UploadSpeed=921600,USBMode=hwcdc,CDCOnBoot=cdc,MSCOnBoot=default,DFUOnBoot=dfu,UploadMode=default,CPUFreq=240,FlashMode=qio,FlashSize=16M,PartitionScheme=huge_app,DebugLevel=none,PSRAM=opi,LoopCore=1,EventsCore=1,EraseFlash=none,JTAGAdapter=builtin,ZigbeeMode=default\" -DESP32=ESP32 -DCORE_DEBUG_LEVEL=0 -DARDUINO_RUNNING_CORE=1 -DARDUINO_EVENT_RUNNING_CORE=1 -DBOARD_HAS_PSRAM -DARDUINO_USB_MODE=1 -DARDUINO_USB_CDC_ON_BOOT=1 -DARDUINO_USB_MSC_ON_BOOT=0 -DARDUINO_USB_DFU_ON_BOOT=1 "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\defines" -iprefix "%ESPPack%tools\esp32s3-libs\%ArduLibVer%\include\\" "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\includes" "-I%ESPPack%tools\esp32s3-libs\%ArduLibVer%\qio_opi\include\\" "-I%ESPPack%hardware\esp32\%ArduLibVer%\cores\esp32\\" "-I%ESPPack%hardware\esp32\%ArduLibVer%\variants\esp32s3\\"

if "%Configuration%" == "Debug" set CompileFlags=%CompileFlags% -DBFW_DEBUG
if "%Configuration%" == "Release" set CompileFlags=%CompileFlags%

if not exist ".\Binaries\BFW_STATIC\ESP32\%Configuration%\" mkdir ".\Binaries\BFW_STATIC\ESP32\%Configuration%\"
if not exist ".\Objects\BFW_STATIC\ESP32\%Configuration%\" mkdir ".\Objects\BFW_STATIC\ESP32\%Configuration%\"

echo on

for %%i in (%Files%) do (
	%Compiler% %CompileFlags% -c ".\BFW\Sources\%%i.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\%%i.o"
)

for %%i in (%Files%) do (
	%Linker% rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\%%i.o"
)

@echo off

set Compiler=
set Linker=
set Files=
set CompileFlags=

popd

echo on
