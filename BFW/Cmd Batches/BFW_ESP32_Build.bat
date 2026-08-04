@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

if not exist ".\Solution Items\Dependencies\ArduinoCore\Lib\ArduinoCore.a" call ".\Solution Items\Cmd Batches\BFW_ESP32_BuildCore.bat"

set CompileFlags=-DBFW_ESP32_PLATFORM -DBFW_LITTLE_ENDIAN -DBFW_BUILD_STATIC -DBFW_X86 -std=c++20 -w -Os -Werror=return-type "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\cpp_flags" -DF_CPU=240000000L -DARDUINO=10607 -DARDUINO_ESP32S3_DEV -DARDUINO_ARCH_ESP32 -DARDUINO_BOARD=\"ESP32S3_DEV\" -DARDUINO_VARIANT=\"esp32s3\" -DARDUINO_PARTITION_huge_app -DARDUINO_HOST_OS=\"windows\" -DARDUINO_FQBN=\"esp32:esp32:esp32s3:UploadSpeed=921600,USBMode=hwcdc,CDCOnBoot=cdc,MSCOnBoot=default,DFUOnBoot=dfu,UploadMode=default,CPUFreq=240,FlashMode=qio,FlashSize=16M,PartitionScheme=huge_app,DebugLevel=none,PSRAM=opi,LoopCore=1,EventsCore=1,EraseFlash=none,JTAGAdapter=builtin,ZigbeeMode=default\" -DESP32=ESP32 -DCORE_DEBUG_LEVEL=0 -DARDUINO_RUNNING_CORE=1 -DARDUINO_EVENT_RUNNING_CORE=1 -DBOARD_HAS_PSRAM -DARDUINO_USB_MODE=1 -DARDUINO_USB_CDC_ON_BOOT=1 -DARDUINO_USB_MSC_ON_BOOT=0 -DARDUINO_USB_DFU_ON_BOOT=1 "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\defines" -iprefix "%ESPPack%tools\esp32s3-libs\%ArduLibVer%\include\\" "@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\includes" "-I%ESPPack%tools\esp32s3-libs\%ArduLibVer%\qio_opi\include\\" "-I%ESPPack%hardware\esp32\%ArduLibVer%\cores\esp32\\" "-I%ESPPack%hardware\esp32\%ArduLibVer%\variants\esp32s3\\"

if "%Configuration%" == "Debug" set CompileFlags=%CompileFlags% -DBFW_DEBUG
if "%Configuration%" == "Release" set CompileFlags=%CompileFlags%

if not exist ".\Binaries\BFW_STATIC\ESP32\%Configuration%\" mkdir ".\Binaries\BFW_STATIC\ESP32\%Configuration%\"
if not exist ".\Objects\BFW_STATIC\ESP32\%Configuration%\" mkdir ".\Objects\BFW_STATIC\ESP32\%Configuration%\"

echo on

xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_Assets.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Assets.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_Cryptography.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Cryptography.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_Debug.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Debug.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_GUI.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_GUI.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_GUID.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_GUID.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_EntryPoint.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_EntryPoint.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_FileSystem.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_FileSystem.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_Input.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Input.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_Log.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Log.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_Math_Matrix.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Math_Matrix.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_Math_Quaternion.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Math_Quaternion.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_Math_Vector.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Math_Vector.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_Math.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Math.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_MultiProcessing.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_MultiProcessing.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_RunTime.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_RunTime.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_String.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_String.o"
xtensa-esp32s3-elf-g++ %CompileFlags% -c ".\BFW\Sources\BFW_Time.cpp" -o ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Time.o"

xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Assets.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Cryptography.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Debug.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_GUI.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_GUID.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_EntryPoint.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_FileSystem.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Input.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Log.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Math_Matrix.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Math_Quaternion.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Math_Vector.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Math.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_MultiProcessing.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_RunTime.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_String.o"
xtensa-esp32s3-elf-ar rcs ".\Binaries\BFW_STATIC\ESP32\%Configuration%\BFW_STATIC.a" ".\Objects\BFW_STATIC\ESP32\%Configuration%\BFW_Time.o"

@echo off

set CompileFlags=

popd

echo on
