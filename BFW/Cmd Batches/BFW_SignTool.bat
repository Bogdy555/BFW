cd "..\..\"

call ".\Solution Items\Cmd Batches\BFW_Path.bat"

if exist ".\Binaries\BFW_DLL\Debug\x86\BFW_DLL.dll" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW" ".\Binaries\BFW_DLL\Debug\x86\BFW_DLL.dll"
if exist ".\Binaries\BFW_DLL\Debug\x64\BFW_DLL.dll" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW" ".\Binaries\BFW_DLL\Debug\x64\BFW_DLL.dll"
if exist ".\Binaries\BFW_DLL\Release\x86\BFW_DLL.dll" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW" ".\Binaries\BFW_DLL\Release\x86\BFW_DLL.dll"
if exist ".\Binaries\BFW_DLL\Release\x64\BFW_DLL.dll" "%SignTool%" sign /f ".\Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW" ".\Binaries\BFW_DLL\Release\x64\BFW_DLL.dll"

pause
