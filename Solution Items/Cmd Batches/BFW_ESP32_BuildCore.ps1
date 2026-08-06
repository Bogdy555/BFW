param
(
	[string] $ESPPack,
	[string] $ArduLibVer,
	[string] $CCompiler,
	[string] $CPPCompiler,
	[string] $CompileFlags,
	[string] $CFlags,
	[string] $CPPFlags,
	[string[]] $CFiles,
	[string[]] $CPPFiles
)

$CFiles = $CFiles[0] -split ' '
$CPPFiles = $CPPFiles[0] -split ' '

$CurrentDir = Get-Location

$CJobs= @()

foreach ($CFile in $CFiles)
{
	$CJobs += Start-Job -ScriptBlock {
		param
		(
			$ESPPack, $ArduLibVer, $CCompiler, $CompileFlags, $CFlags, $CFile, $CurrentDir
		)
		Set-Location $CurrentDir
		$AllFlags = $CompileFlags
		$AllFlags += ' '
		$AllFlags += $CFlags
		$AllFlags += ' -c "'
		$AllFlags += $ESPPack
		$AllFlags += 'hardware\esp32\'
		$AllFlags += $ArduLibVer
		$AllFlags += '\cores\esp32\'
		$AllFlags += $CFile
		$AllFlags += '.c" -o ".\Solution Items\Dependencies\ArduinoCore\Lib\'
		$AllFlags += $CFile
		$AllFlags += '.o"'
		Start-Process -File $CCompiler -Wait -NoNewWindow -ArgumentList $AllFlags
	} -ArgumentList $ESPPack, $ArduLibVer, $CCompiler, $CompileFlags, $CFlags, $CFile, $CurrentDir
}

$CJobs | Receive-Job -Wait

$CPPJobs= @()

foreach ($CPPFile in $CPPFiles)
{
	$CPPJobs += Start-Job -ScriptBlock {
		param
		(
			$ESPPack, $ArduLibVer, $CPPCompiler, $CompileFlags, $CPPFlags, $CPPFile, $CurrentDir
		)
		Set-Location $CurrentDir
		$AllFlags = $CompileFlags
		$AllFlags += ' '
		$AllFlags += $CPPFlags
		$AllFlags += ' -c "'
		$AllFlags += $ESPPack
		$AllFlags += 'hardware\esp32\'
		$AllFlags += $ArduLibVer
		$AllFlags += '\cores\esp32\'
		$AllFlags += $CPPFile
		$AllFlags += '.cpp" -o ".\Solution Items\Dependencies\ArduinoCore\Lib\'
		$AllFlags += $CPPFile
		$AllFlags += '.o"'
		Start-Process -File $CPPCompiler -Wait -NoNewWindow -ArgumentList $AllFlags
	} -ArgumentList $ESPPack, $ArduLibVer, $CPPCompiler, $CompileFlags, $CPPFlags, $CPPFile, $CurrentDir
}

$CPPJobs | Receive-Job -Wait
