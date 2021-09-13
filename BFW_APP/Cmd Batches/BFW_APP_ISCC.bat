cd "..\..\"

call ".\Solution Items\Cmd Batches\BFW_Path.bat"

if exist ".\Binaries\BFW_APP_DLL\Debug\x86\BFW_APP_DLL.exe" "%ISCC%" /DConfiguration="Debug" /DBFW_APP_DEBUG /DPlatformShortName="x86" /DBFW_APP_x86 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW_APP\" /DOutDir="%cd%\Binaries\BFW_APP_DLL\Debug\x86\" /DProjectName="BFW_APP_DLL" /DBFW_DLL_LINK /Q "%cd%\BFW_APP\Setup\BFW_APP_SetupScript.iss"
if exist ".\Binaries\BFW_APP_DLL\Debug\x64\BFW_APP_DLL.exe" "%ISCC%" /DConfiguration="Debug" /DBFW_APP_DEBUG /DPlatformShortName="x64" /DBFW_APP_x64 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW_APP\" /DOutDir="%cd%\Binaries\BFW_APP_DLL\Debug\x64\" /DProjectName="BFW_APP_DLL" /DBFW_DLL_LINK /Q "%cd%\BFW_APP\Setup\BFW_APP_SetupScript.iss"
if exist ".\Binaries\BFW_APP_DLL\Release\x86\BFW_APP_DLL.exe" "%ISCC%" /DConfiguration="Release" /DPlatformShortName="x86" /DBFW_APP_x86 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW_APP\" /DOutDir="%cd%\Binaries\BFW_APP_DLL\Release\x86\" /DProjectName="BFW_APP_DLL" /DBFW_DLL_LINK /Q "%cd%\BFW_APP\Setup\BFW_APP_SetupScript.iss"
if exist ".\Binaries\BFW_APP_DLL\Release\x64\BFW_APP_DLL.exe" "%ISCC%" /DConfiguration="Release" /DPlatformShortName="x64" /DBFW_APP_x64 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW_APP\" /DOutDir="%cd%\Binaries\BFW_APP_DLL\Release\x64\" /DProjectName="BFW_APP_DLL" /DBFW_DLL_LINK /Q "%cd%\BFW_APP\Setup\BFW_APP_SetupScript.iss"

if exist ".\Binaries\BFW_APP_STATIC\Debug\x86\BFW_APP_STATIC.exe" "%ISCC%" /DConfiguration="Debug" /DBFW_APP_DEBUG /DPlatformShortName="x86" /DBFW_APP_x86 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW_APP\" /DOutDir="%cd%\Binaries\BFW_APP_STATIC\Debug\x86\" /DProjectName="BFW_APP_STATIC" /DBFW_STATIC_LINK /Q "%cd%\BFW_APP\Setup\BFW_APP_SetupScript.iss"
if exist ".\Binaries\BFW_APP_STATIC\Debug\x64\BFW_APP_STATIC.exe" "%ISCC%" /DConfiguration="Debug" /DBFW_APP_DEBUG /DPlatformShortName="x64" /DBFW_APP_x64 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW_APP\" /DOutDir="%cd%\Binaries\BFW_APP_STATIC\Debug\x64\" /DProjectName="BFW_APP_STATIC" /DBFW_STATIC_LINK /Q "%cd%\BFW_APP\Setup\BFW_APP_SetupScript.iss"
if exist ".\Binaries\BFW_APP_STATIC\Release\x86\BFW_APP_STATIC.exe" "%ISCC%" /DConfiguration="Release" /DPlatformShortName="x86" /DBFW_APP_x86 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW_APP\" /DOutDir="%cd%\Binaries\BFW_APP_STATIC\Release\x86\" /DProjectName="BFW_APP_STATIC" /DBFW_STATIC_LINK /Q "%cd%\BFW_APP\Setup\BFW_APP_SetupScript.iss"
if exist ".\Binaries\BFW_APP_STATIC\Release\x64\BFW_APP_STATIC.exe" "%ISCC%" /DConfiguration="Release" /DPlatformShortName="x64" /DBFW_APP_x64 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW_APP\" /DOutDir="%cd%\Binaries\BFW_APP_STATIC\Release\x64\" /DProjectName="BFW_APP_STATIC" /DBFW_STATIC_LINK /Q "%cd%\BFW_APP\Setup\BFW_APP_SetupScript.iss"

pause
