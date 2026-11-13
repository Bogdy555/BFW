@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

xtensa-esp32s3-elf-gdb -ex "target remote :3333" -ex "monitor reset halt" ".\Binaries\BFW_ESP32\Debug\BFW_ESP32.elf"

@echo off

popd

echo on
