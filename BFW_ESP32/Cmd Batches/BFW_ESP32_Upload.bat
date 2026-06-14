@echo off

echo on

if "%SolutionDir%" == "" call "..\..\Solution Items\Cmd Batches\BFW_ESP32_Path.bat"

@echo off

pushd "%SolutionDir%"

echo on

esptool --chip esp32s3 elf2image --flash_mode dio --flash_freq 80m --flash_size 16MB -o ".\Binaries\BFW_ESP32\%Configuration%\BootLoader.bin" "%ESPPack%tools\esp32-arduino-libs\idf-release_v5.4-2f7dcd86-v1\esp32s3\bin\bootloader_qio_80m.elf"
gen_esp32part -q "%ESPPack%hardware\esp32\3.2.0\tools\partitions\huge_app.csv" ".\Binaries\BFW_ESP32\%Configuration%\Partitions.bin"
esptool --chip esp32s3 elf2image --flash_mode dio --flash_freq 80m --flash_size 16MB --elf-sha256-offset 0xb0 -o ".\Binaries\BFW_ESP32\%Configuration%\BFW_ESP32.bin" ".\Binaries\BFW_ESP32\%Configuration%\BFW_ESP32.elf"
esptool --chip esp32s3 --port COM3 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode keep --flash_freq keep --flash_size keep 0x0 ".\Binaries\BFW_ESP32\%Configuration%\BootLoader.bin" 0x8000 ".\Binaries\BFW_ESP32\%Configuration%\Partitions.bin" 0xe000 "%ESPPack%hardware\esp32\3.2.0\tools\partitions\boot_app0.bin" 0x10000 ".\Binaries\BFW_ESP32\%Configuration%\BFW_ESP32.bin"

@echo off

popd

echo on
