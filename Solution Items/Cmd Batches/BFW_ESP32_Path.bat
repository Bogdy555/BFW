@echo off

echo on

if "%SolutionDir%" == "" set ESPPack=%USERPROFILE%\AppData\Local\Arduino15\packages\esp32\
if "%SolutionDir%" == "" set CompilerVer=2601
if "%SolutionDir%" == "" set UploadVer=5.3.0
if "%SolutionDir%" == "" set ArduLibVer=3.3.10
if "%SolutionDir%" == "" set Path=%ESPPack%tools\esp-x32\%CompilerVer%\bin\;%Path%
if "%SolutionDir%" == "" set Path=%ESPPack%tools\esptool_py\%UploadVer%\;%Path%
if "%SolutionDir%" == "" set Path=%ESPPack%hardware\esp32\%ArduLibVer%\tools\;%Path%

if "%SolutionDir%" == "" set SolutionDir=%USERPROFILE%\source\repos\BFW\

@echo off

echo on
