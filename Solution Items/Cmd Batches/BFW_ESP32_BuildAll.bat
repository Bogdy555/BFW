@echo off

echo on

if "%SolutionDir%" == "" call ".\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

call ".\BFW_ESP32\Cmd Batches\BFW_ESP32_Build_Release.bat"
call ".\BFW_ESP32\Cmd Batches\BFW_ESP32_Build_Debug.bat"

@echo off

popd

echo on
