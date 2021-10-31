call ".\BFW_Path.bat"

call ".\BFW_Setup.bat"

"%MSBuild%" ".\BFW.sln" -property:Configuration=Debug -property:Platform=x64
"%MSBuild%" ".\BFW.sln" -property:Configuration=Debug -property:Platform=x86
"%MSBuild%" ".\BFW.sln" -property:Configuration=Release -property:Platform=x64
"%MSBuild%" ".\BFW.sln" -property:Configuration=Release -property:Platform=x86

cd ".\BFW_ARDUINO\Cmd Batches\"
call ".\BFW_ARDUINO_Rebuild.bat"

cd ".\BFW\Cmd Batches\"
call ".\BFW_SignTool.bat"

cd ".\BFW_APP\Cmd Batches\"
call ".\BFW_APP_SignTool.bat"

cd ".\BFW\Cmd Batches\"
call ".\BFW_ISCC.bat"

cd ".\BFW_APP\Cmd Batches\"
call ".\BFW_APP_ISCC.bat"

pause
