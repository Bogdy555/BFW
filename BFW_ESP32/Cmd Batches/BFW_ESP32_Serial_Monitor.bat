@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

arduino-cli monitor -p COM3 -c baudrate=115200

@echo off

popd

echo on
