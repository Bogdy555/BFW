@echo off

echo on

if "%SolutionDir%" == "" call ".\BFW_WINDOWS_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

if not exist ".\BFW\Resources\Icons\" mkdir ".\BFW\Resources\Icons\"
if not exist ".\BFW_ESP32\Files\" mkdir ".\BFW_ESP32\Files\"
if not exist ".\BFW_LINUX\Files\" mkdir ".\BFW_LINUX\Files\"
if not exist ".\BFW_WINDOWS\Files\" mkdir ".\BFW_WINDOWS\Files\"
if not exist ".\BFW_WINDOWS\Resources\Icons\" mkdir ".\BFW_WINDOWS\Resources\Icons\"
if not exist ".\Solution Items\Dependencies\ArduinoCore\Lib\libb64\" mkdir ".\Solution Items\Dependencies\ArduinoCore\Lib\libb64\"
if not exist ".\Solution Items\Digital Certificates\BSW\" mkdir ".\Solution Items\Digital Certificates\BSW\"
if not exist ".\Solution Items\Docs\" mkdir ".\Solution Items\Docs\"
if not exist ".\Solution Items\Examples\" mkdir ".\Solution Items\Examples\"
if not exist ".\Solution Items\ReadMe Resources\" mkdir ".\Solution Items\ReadMe Resources\"

@echo off

popd

echo on
