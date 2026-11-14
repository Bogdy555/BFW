@echo off

echo on

if "%SolutionDir%" == "" set ESPPack=%USERPROFILE%\AppData\Local\Arduino15\packages\esp32\
if "%SolutionDir%" == "" set CompilerVer=2601
if "%SolutionDir%" == "" set UploadVer=5.3.1
if "%SolutionDir%" == "" set ArduLibVer=3.3.12
if "%SolutionDir%" == "" set Path=%ESPPack%tools\esp-x32\%CompilerVer%\bin\;%Path%
if "%SolutionDir%" == "" set Path=%ESPPack%tools\esptool_py\%UploadVer%\;%Path%
if "%SolutionDir%" == "" set Path=%ESPPack%hardware\esp32\%ArduLibVer%\tools\;%Path%
if "%SolutionDir%" == "" set Path=%ESPPack%tools\openocd-esp32\v0.12.0-esp32-20260424\bin\;%Path%
if "%SolutionDir%" == "" set Path=%ESPPack%tools\xtensa-esp-elf-gdb\17.1_20260402\bin\;%Path%
if "%SolutionDir%" == "" set Path=D:\Aplicatii\arduino-cli\;%Path%

if "%SolutionDir%" == "" set SolutionDir=%USERPROFILE%\source\repos\BFW\

@echo off

echo on
