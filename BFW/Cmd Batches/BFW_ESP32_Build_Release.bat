@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

set Configuration=Release

echo on

call ".\BFW\Cmd Batches\BFW_ESP32_Build.bat"

@echo off

set Configuration=

popd

echo on
