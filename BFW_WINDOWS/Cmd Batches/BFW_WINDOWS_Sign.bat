@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\BFW_WINDOWS_Path.bat"

@echo off

pushd "%SolutionDir%"

set SignToolTemp=signtool sign /q /f ".\Solution Items\Digital Certificates\BSW\BSW_SPC_PFX.pfx" /fd SHA256 /p "BSW" /tr "http://timestamp.digicert.com" /td SHA256 /ph /d "BFW_WINDOWS"

echo on

if exist ".\Binaries\BFW_WINDOWS_DYNAMIC\Release\x64\BFW_WINDOWS_DYNAMIC.exe" %SignToolTemp% ".\Binaries\BFW_WINDOWS_DYNAMIC\Release\x64\BFW_WINDOWS_DYNAMIC.exe"
if exist ".\Binaries\BFW_WINDOWS_DYNAMIC\Release\x86\BFW_WINDOWS_DYNAMIC.exe" %SignToolTemp% ".\Binaries\BFW_WINDOWS_DYNAMIC\Release\x86\BFW_WINDOWS_DYNAMIC.exe"
if exist ".\Binaries\BFW_WINDOWS_DYNAMIC\Debug\x64\BFW_WINDOWS_DYNAMIC.exe" %SignToolTemp% ".\Binaries\BFW_WINDOWS_DYNAMIC\Debug\x64\BFW_WINDOWS_DYNAMIC.exe"
if exist ".\Binaries\BFW_WINDOWS_DYNAMIC\Debug\x86\BFW_WINDOWS_DYNAMIC.exe" %SignToolTemp% ".\Binaries\BFW_WINDOWS_DYNAMIC\Debug\x86\BFW_WINDOWS_DYNAMIC.exe"
if exist ".\Binaries\BFW_WINDOWS_STATIC\Release\x64\BFW_WINDOWS_STATIC.exe" %SignToolTemp% ".\Binaries\BFW_WINDOWS_STATIC\Release\x64\BFW_WINDOWS_STATIC.exe"
if exist ".\Binaries\BFW_WINDOWS_STATIC\Release\x86\BFW_WINDOWS_STATIC.exe" %SignToolTemp% ".\Binaries\BFW_WINDOWS_STATIC\Release\x86\BFW_WINDOWS_STATIC.exe"
if exist ".\Binaries\BFW_WINDOWS_STATIC\Debug\x64\BFW_WINDOWS_STATIC.exe" %SignToolTemp% ".\Binaries\BFW_WINDOWS_STATIC\Debug\x64\BFW_WINDOWS_STATIC.exe"
if exist ".\Binaries\BFW_WINDOWS_STATIC\Debug\x86\BFW_WINDOWS_STATIC.exe" %SignToolTemp% ".\Binaries\BFW_WINDOWS_STATIC\Debug\x86\BFW_WINDOWS_STATIC.exe"

@echo off

set SignToolTemp=

popd

echo on
