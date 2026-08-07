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
		$Command = $CCompiler
		$Command += ' '
		$Command += $CompileFlags
		$Command += ' '
		$Command += $CFlags
		$Command += ' -c "'
		$Command += $ESPPack
		$Command += 'hardware\esp32\'
		$Command += $ArduLibVer
		$Command += '\cores\esp32\'
		$Command += $CFile
		$Command += '.c" -o ".\Solution Items\Dependencies\ArduinoCore\Lib\'
		$Command += $CFile
		$Command += '.o"'
		& cmd /c $Command
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
		$Command = $CPPCompiler
		$Command += ' '
		$Command += $CompileFlags
		$Command += ' '
		$Command += $CPPFlags
		$Command += ' -c "'
		$Command += $ESPPack
		$Command += 'hardware\esp32\'
		$Command += $ArduLibVer
		$Command += '\cores\esp32\'
		$Command += $CPPFile
		$Command += '.cpp" -o ".\Solution Items\Dependencies\ArduinoCore\Lib\'
		$Command += $CPPFile
		$Command += '.o"'
		& cmd /c $Command
	} -ArgumentList $ESPPack, $ArduLibVer, $CPPCompiler, $CompileFlags, $CPPFlags, $CPPFile, $CurrentDir
}

$CPPJobs | Receive-Job -Wait
