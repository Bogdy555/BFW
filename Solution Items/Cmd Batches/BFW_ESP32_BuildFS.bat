@echo off

echo on

if "%SolutionDir%" == "" call ".\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

set Compiler=xtensa-esp32s3-elf-g++
set Linker=xtensa-esp32s3-elf-ar
set Files=FS vfs_api
set CompileFlags=-w -Os -Werror=return-type -DF_CPU=240000000L -DARDUINO=10607 -DARDUINO_ESP32S3_DEV -DARDUINO_ARCH_ESP32 -DARDUINO_BOARD=\\\"ESP32S3_DEV\\\" -DARDUINO_VARIANT=\\\"esp32s3\\\" -DARDUINO_PARTITION_huge_app -DARDUINO_HOST_OS=\\\"windows\\\" -DARDUINO_FQBN=\\\"esp32:esp32:esp32s3:UploadSpeed=921600,USBMode=hwcdc,CDCOnBoot=cdc,MSCOnBoot=default,DFUOnBoot=dfu,UploadMode=default,CPUFreq=240,FlashMode=qio,FlashSize=16M,PartitionScheme=huge_app,DebugLevel=none,PSRAM=opi,LoopCore=1,EventsCore=1,EraseFlash=none,JTAGAdapter=builtin,ZigbeeMode=default\\\" -DESP32=ESP32 -DCORE_DEBUG_LEVEL=0 -DARDUINO_RUNNING_CORE=1 -DARDUINO_EVENT_RUNNING_CORE=1 -DBOARD_HAS_PSRAM -DARDUINO_USB_MODE=1 -DARDUINO_USB_CDC_ON_BOOT=1 -DARDUINO_USB_MSC_ON_BOOT=0 -DARDUINO_USB_DFU_ON_BOOT=1 \"@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\defines\" -iprefix \"%ESPPack%tools\esp32s3-libs\%ArduLibVer%\include\\\\\" \"@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\includes\" \"-I%ESPPack%tools\esp32s3-libs\%ArduLibVer%\qio_opi\include\\\\\" \"-I%ESPPack%hardware\esp32\%ArduLibVer%\cores\esp32\\\\\" \"-I%ESPPack%hardware\esp32\%ArduLibVer%\variants\esp32s3\\\\\" \"-I%ESPPack%hardware\esp32\%ArduLibVer%\libraries\FS\src\\\\\" \"-I%ESPPack%hardware\esp32\%ArduLibVer%\libraries\SD_MMC\src\\\\\" \"@%ESPPack%tools\esp32s3-libs\%ArduLibVer%\flags\cpp_flags\"

if not exist ".\Solution Items\Dependencies\FS\Lib\" mkdir ".\Solution Items\Dependencies\FS\Lib\"

echo on

"C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe" -NoLogo -NoProfile -ExecutionPolicy Bypass -File ".\Solution Items\Cmd Batches\BFW_ESP32_BuildFS.ps1" -ESPPack "%ESPPack%\" -ArduLibVer "%ArduLibVer%" -Compiler "%Compiler%" -CompileFlags "%CompileFlags%" -Files "%Files%"

for %%i in (%Files%) do (
	%Linker% rcs ".\Solution Items\Dependencies\FS\Lib\FS.a" ".\Solution Items\Dependencies\FS\Lib\%%i.o"
)

@echo off

set Compiler=
set Linker=
set Files=
set CompileFlags=

popd

echo on
