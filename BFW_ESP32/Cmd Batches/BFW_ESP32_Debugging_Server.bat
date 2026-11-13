@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

openocd -f board/esp32s3-builtin.cfg

@echo off

popd

echo on
