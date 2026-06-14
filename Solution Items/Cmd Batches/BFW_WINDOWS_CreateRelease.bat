@echo off

echo on

if "%SolutionDir%" == "" call ".\BFW_WINDOWS_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

call ".\Solution Items\Cmd Batches\BFW_WINDOWS_BuildAll.bat"

call ".\BFW\Cmd Batches\BFW_WINDOWS_Sign.bat"

call ".\BFW_WINDOWS\Cmd Batches\BFW_WINDOWS_Sign.bat"

@echo off

popd

echo on
