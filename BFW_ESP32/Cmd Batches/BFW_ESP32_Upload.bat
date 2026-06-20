@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

esptool --chip esp32s3 elf2image --flash-mode dio --flash-freq 80m --flash-size 16MB -o ".\Binaries\BFW_ESP32\%Configuration%\BootLoader.bin" "%ESPPack%tools\esp32s3-libs\%ArduLibVer%\bin\bootloader_qio_80m.elf"
gen_esp32part -q "%ESPPack%hardware\esp32\%ArduLibVer%\tools\partitions\huge_app.csv" ".\Binaries\BFW_ESP32\%Configuration%\Partitions.bin"
esptool --chip esp32s3 elf2image --flash-mode dio --flash-freq 80m --flash-size 16MB --elf-sha256-offset 0xb0 -o ".\Binaries\BFW_ESP32\%Configuration%\BFW_ESP32.bin" ".\Binaries\BFW_ESP32\%Configuration%\BFW_ESP32.elf"
flasher --esptool esptool.exe --build-dir ".\Binaries\BFW_ESP32\%Configuration%\\" --chip esp32s3 --port "COM3" --baud 921600 --before default-reset --after hard-reset write-flash -z --flash-mode keep --flash-freq keep --flash-size keep 0x0 ".\Binaries\BFW_ESP32\%Configuration%\BootLoader.bin" 0x8000 ".\Binaries\BFW_ESP32\%Configuration%\Partitions.bin" 0xe000 "%ESPPack%hardware\esp32\%ArduLibVer%\tools\partitions\boot_app0.bin" 0x10000 ".\Binaries\BFW_ESP32\%Configuration%\BFW_ESP32.bin"

@echo off

popd

echo on
