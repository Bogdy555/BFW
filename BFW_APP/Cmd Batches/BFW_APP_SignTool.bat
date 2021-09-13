cd "..\..\"

call ".\Solution Items\Cmd Batches\BFW_Path.bat"

if exist ".\Binaries\BFW_DLL\Debug\x86\BFW_DLL.exe" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW" ".\Binaries\BFW_DLL\Debug\x86\BFW_DLL.dll"
if exist ".\Binaries\BFW_DLL\Debug\x64\BFW_DLL.exe" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW" ".\Binaries\BFW_DLL\Debug\x64\BFW_DLL.dll"
if exist ".\Binaries\BFW_DLL\Release\x86\BFW_DLL.exe" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW" ".\Binaries\BFW_DLL\Release\x86\BFW_DLL.dll"
if exist ".\Binaries\BFW_DLL\Release\x64\BFW_DLL.exe" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW" ".\Binaries\BFW_DLL\Release\x64\BFW_DLL.dll"

if exist ".\Binaries\BFW_APP_DLL\Debug\x86\BFW_APP_DLL.exe" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW_APP" ".\Binaries\BFW_APP_DLL\Debug\x86\BFW_APP_DLL.exe"
if exist ".\Binaries\BFW_APP_DLL\Debug\x64\BFW_APP_DLL.exe" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW_APP" ".\Binaries\BFW_APP_DLL\Debug\x64\BFW_APP_DLL.exe"
if exist ".\Binaries\BFW_APP_DLL\Release\x86\BFW_APP_DLL.exe" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW_APP" ".\Binaries\BFW_APP_DLL\Release\x86\BFW_APP_DLL.exe"
if exist ".\Binaries\BFW_APP_DLL\Release\x64\BFW_APP_DLL.exe" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW_APP" ".\Binaries\BFW_APP_DLL\Release\x64\BFW_APP_DLL.exe"

if exist ".\Binaries\BFW_APP_STATIC\Debug\x86\BFW_APP_STATIC.exe" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW_APP" ".\Binaries\BFW_APP_STATIC\Debug\x86\BFW_APP_STATIC.exe"
if exist ".\Binaries\BFW_APP_STATIC\Debug\x64\BFW_APP_STATIC.exe" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW_APP" ".\Binaries\BFW_APP_STATIC\Debug\x64\BFW_APP_STATIC.exe"
if exist ".\Binaries\BFW_APP_STATIC\Release\x86\BFW_APP_STATIC.exe" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW_APP" ".\Binaries\BFW_APP_STATIC\Release\x86\BFW_APP_STATIC.exe"
if exist ".\Binaries\BFW_APP_STATIC\Release\x64\BFW_APP_STATIC.exe" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW_APP" ".\Binaries\BFW_APP_STATIC\Release\x64\BFW_APP_STATIC.exe"

pause
