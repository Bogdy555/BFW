@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

set Configuration=Release

echo on

call ".\BFW_ESP32\Cmd Batches\BFW_ESP32_Upload.bat"

@echo off

set Configuration=

popd

echo on
