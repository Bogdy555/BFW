cd "..\..\"

avrdude -C ".\BFW_ARDUINO\Vendor\Arduino\avrdude.conf" -v -p atmega328p -c arduino -P COM7 -b 115200 -D -U flash:w:".\Binaries\BFW_ARDUINO\Release\BFW_ARDUINO.hex":i

pause
