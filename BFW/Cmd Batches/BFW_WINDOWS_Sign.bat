@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\BFW_WINDOWS_Path.bat"

@echo off

pushd "%SolutionDir%"

set SignToolTemp=signtool sign /q /f ".\Solution Items\Digital Certificates\BSW\BSW_SPC_PFX.pfx" /fd SHA256 /p "BSW" /tr "http://timestamp.digicert.com" /td SHA256 /ph /d "BFW"

echo on

if exist ".\Binaries\BFW_DYNAMIC\Windows\Release\x64\BFW_DYNAMIC.dll" %SignToolTemp% ".\Binaries\BFW_DYNAMIC\Windows\Release\x64\BFW_DYNAMIC.dll"
if exist ".\Binaries\BFW_DYNAMIC\Windows\Release\x86\BFW_DYNAMIC.dll" %SignToolTemp% ".\Binaries\BFW_DYNAMIC\Windows\Release\x86\BFW_DYNAMIC.dll"
if exist ".\Binaries\BFW_DYNAMIC\Windows\Debug\x64\BFW_DYNAMIC.dll" %SignToolTemp% ".\Binaries\BFW_DYNAMIC\Windows\Debug\x64\BFW_DYNAMIC.dll"
if exist ".\Binaries\BFW_DYNAMIC\Windows\Debug\x86\BFW_DYNAMIC.dll" %SignToolTemp% ".\Binaries\BFW_DYNAMIC\Windows\Debug\x86\BFW_DYNAMIC.dll"

if exist ".\Binaries\BFW_WINDOWS_DYNAMIC\Release\x64\" copy ".\Binaries\BFW_DYNAMIC\Windows\Release\x64\BFW_DYNAMIC.dll" ".\Binaries\BFW_WINDOWS_DYNAMIC\Release\x64\"
if exist ".\Binaries\BFW_WINDOWS_DYNAMIC\Release\x86\" copy ".\Binaries\BFW_DYNAMIC\Windows\Release\x86\BFW_DYNAMIC.dll" ".\Binaries\BFW_WINDOWS_DYNAMIC\Release\x86\"
if exist ".\Binaries\BFW_WINDOWS_DYNAMIC\Debug\x64\" copy ".\Binaries\BFW_DYNAMIC\Windows\Debug\x64\BFW_DYNAMIC.dll" ".\Binaries\BFW_WINDOWS_DYNAMIC\Debug\x64\"
if exist ".\Binaries\BFW_WINDOWS_DYNAMIC\Debug\x86\" copy ".\Binaries\BFW_DYNAMIC\Windows\Debug\x86\BFW_DYNAMIC.dll" ".\Binaries\BFW_WINDOWS_DYNAMIC\Debug\x86\"

@echo off

set SignToolTemp=

popd

echo on
