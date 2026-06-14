@echo off

echo on

if "%SolutionDir%" == "" call ".\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

call ".\Solution Items\Cmd Batches\BFW_ESP32_CreateFolders.bat"

call ".\Solution Items\Cmd Batches\BFW_ESP32_BuildCore.bat"

@echo off

popd

echo on
