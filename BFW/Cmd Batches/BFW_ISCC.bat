cd "..\..\"

call ".\Solution Items\Cmd Batches\BFW_Path.bat"

if exist ".\Binaries\BFW_DLL\Debug\x86\BFW_DLL.dll" "%ISCC%" /DConfiguration="Debug" /DBFW_DEBUG /DPlatformShortName="x86" /DBFW_x86 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW\" /DOutDir="%cd%\Binaries\BFW_DLL\Debug\x86\" /DProjectName="BFW_DLL" /DBFW_DLL_BUILD /Q "%cd%\BFW\Setup\BFW_SetupScript.iss"
if exist ".\Binaries\BFW_DLL\Debug\x64\BFW_DLL.dll" "%ISCC%" /DConfiguration="Debug" /DBFW_DEBUG /DPlatformShortName="x64" /DBFW_x64 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW\" /DOutDir="%cd%\Binaries\BFW_DLL\Debug\x64\" /DProjectName="BFW_DLL" /DBFW_DLL_BUILD /Q "%cd%\BFW\Setup\BFW_SetupScript.iss"
if exist ".\Binaries\BFW_DLL\Release\x86\BFW_DLL.dll" "%ISCC%" /DConfiguration="Release" /DPlatformShortName="x86" /DBFW_x86 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW\" /DOutDir="%cd%\Binaries\BFW_DLL\Release\x86\" /DProjectName="BFW_DLL" /DBFW_DLL_BUILD /Q "%cd%\BFW\Setup\BFW_SetupScript.iss"
if exist ".\Binaries\BFW_DLL\Release\x64\BFW_DLL.dll" "%ISCC%" /DConfiguration="Release" /DPlatformShortName="x64" /DBFW_x64 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW\" /DOutDir="%cd%\Binaries\BFW_DLL\Release\x64\" /DProjectName="BFW_DLL" /DBFW_DLL_BUILD /Q "%cd%\BFW\Setup\BFW_SetupScript.iss"

if exist ".\Binaries\BFW_STATIC\Debug\x86\BFW_STATIC.lib" "%ISCC%" /DConfiguration="Debug" /DBFW_DEBUG /DPlatformShortName="x86" /DBFW_x86 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW\" /DOutDir="%cd%\Binaries\BFW_STATIC\Debug\x86\" /DProjectName="BFW_STATIC" /DBFW_STATIC_BUILD /Q "%cd%\BFW\Setup\BFW_SetupScript.iss"
if exist ".\Binaries\BFW_STATIC\Debug\x64\BFW_STATIC.lib" "%ISCC%" /DConfiguration="Debug" /DBFW_DEBUG /DPlatformShortName="x64" /DBFW_x64 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW\" /DOutDir="%cd%\Binaries\BFW_STATIC\Debug\x64\" /DProjectName="BFW_STATIC" /DBFW_STATIC_BUILD /Q "%cd%\BFW\Setup\BFW_SetupScript.iss"
if exist ".\Binaries\BFW_STATIC\Release\x86\BFW_STATIC.lib" "%ISCC%" /DConfiguration="Release" /DPlatformShortName="x86" /DBFW_x86 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW\" /DOutDir="%cd%\Binaries\BFW_STATIC\Release\x86\" /DProjectName="BFW_STATIC" /DBFW_STATIC_BUILD /Q "%cd%\BFW\Setup\BFW_SetupScript.iss"
if exist ".\Binaries\BFW_STATIC\Release\x64\BFW_STATIC.lib" "%ISCC%" /DConfiguration="Release" /DPlatformShortName="x64" /DBFW_x64 /DSolutionDir="%cd%\" /DProjectDir="%cd%\BFW\" /DOutDir="%cd%\Binaries\BFW_STATIC\Release\x64\" /DProjectName="BFW_STATIC" /DBFW_STATIC_BUILD /Q "%cd%\BFW\Setup\BFW_SetupScript.iss"

pause
