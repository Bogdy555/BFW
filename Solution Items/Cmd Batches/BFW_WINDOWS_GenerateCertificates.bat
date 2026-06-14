@echo off

echo on

if "%SolutionDir%" == "" call ".\BFW_WINDOWS_Path.bat"

@echo off

pushd "%SolutionDir%"

if not exist ".\Solution Items\Digital Certificates\BSW\" mkdir ".\Solution Items\Digital Certificates\BSW\"

popd

pushd "%SolutionDir%Solution Items\Digital Certificates\BSW\"

echo on

if not exist ".\BSW_CA_CER.cer" makecert /r /pe /n "CN=BSW" /ss CA /a SHA256 /cy authority /sky signature /sv ".\BSW_CA_PK.pvk" ".\BSW_CA_CER.cer"
if not exist ".\BSW_SPC_CER.cer" makecert /pe /n "CN=BSW" /a SHA256 /cy end /sky signature /ic ".\BSW_CA_CER.cer" /iv ".\BSW_CA_PK.pvk" /sv ".\BSW_SPC_PK.pvk" ".\BSW_SPC_CER.cer"
if not exist ".\BSW_SPC_PFX.pfx" pvk2pfx /pvk ".\BSW_SPC_PK.pvk" /spc ".\BSW_SPC_CER.cer" /pfx ".\BSW_SPC_PFX.pfx" /pi "BSW" /po "BSW"

@echo off

popd

echo on
