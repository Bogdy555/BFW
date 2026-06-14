@echo off

echo on

if "%SolutionDir%" == "" set Path=%USERPROFILE%\AppData\Local\Arduino15\packages\esp32\tools\esp-x32\2411\bin\;%Path%
if "%SolutionDir%" == "" set Path=%USERPROFILE%\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\4.9.dev3\;%Path%
if "%SolutionDir%" == "" set Path=%USERPROFILE%\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.2.0\tools\;%Path%

@echo off

echo on

if "%SolutionDir%" == "" set ESPPack=%USERPROFILE%\AppData\Local\Arduino15\packages\esp32\
if "%SolutionDir%" == "" set SolutionDir=%USERPROFILE%\source\repos\BFW\

@echo off

echo on
