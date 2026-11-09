param
(
	[string] $ESPPack,
	[string] $ArduLibVer,
	[string] $Compiler,
	[string] $CompileFlags,
	[string[]] $Files
)

$Files = $Files[0] -split ' '

$CurrentDir = Get-Location

$Jobs= @()

foreach ($File in $Files)
{
	$Jobs += Start-Job -ScriptBlock {
		param
		(
			$ESPPack, $ArduLibVer, $Compiler, $CompileFlags, $File, $CurrentDir
		)
		Set-Location $CurrentDir
		$Command = $Compiler
		$Command += ' '
		$Command += $CompileFlags
		$Command += ' -c "'
		$Command += $ESPPack
		$Command += 'hardware\esp32\'
		$Command += $ArduLibVer
		$Command += '\libraries\SD_MMC\src\'
		$Command += $File
		$Command += '.cpp" -o ".\Solution Items\Dependencies\SD_MMC\Lib\'
		$Command += $File
		$Command += '.o"'
		& cmd /c $Command
	} -ArgumentList $ESPPack, $ArduLibVer, $Compiler, $CompileFlags, $File, $CurrentDir
}

$Jobs | Receive-Job -Wait
