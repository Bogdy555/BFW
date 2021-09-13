call ".\BFW_Path.bat"

cd "..\"
mkdir ".\Digital Certificates\"
cd ".\Digital Certificates\"
mkdir ".\BFW\"
cd ".\BFW\"

"%MakeCert%" -r -pe -n "CN=BFW" -ss CA -a sha256 -cy authority -sky signature -sv ".\BFW_CA_PK.pvk" ".\BFW_CA_CER.cer"
"%MakeCert%" -pe -n "CN=BFW" -a sha256 -cy end -sky signature -ic ".\BFW_CA_CER.cer" -iv ".\BFW_CA_PK.pvk" -sv ".\BFW_SPC_PK.pvk" ".\BFW_SPC_CER.cer"
"%MakePfx%" -pvk ".\BFW_SPC_PK.pvk" -spc ".\BFW_SPC_CER.cer" -pfx ".\BFW_SPC_PFX.pfx" -po "BFWSoftware"

pause
