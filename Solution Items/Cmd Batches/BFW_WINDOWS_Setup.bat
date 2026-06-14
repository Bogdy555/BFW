@echo off

echo on

if "%SolutionDir%" == "" call ".\BFW_WINDOWS_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

call ".\Solution Items\Cmd Batches\BFW_WINDOWS_CreateFolders.bat"

call ".\Solution Items\Cmd Batches\BFW_WINDOWS_GenerateCertificates.bat"

@echo off

popd

echo on
