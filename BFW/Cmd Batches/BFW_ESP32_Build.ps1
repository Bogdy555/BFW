param
(
	[string] $Compiler,
	[string] $CompileFlags,
	[string[]] $Files,
	[string] $Configuration
)

$Files = $Files[0] -split ' '

$CurrentDir = Get-Location

$Jobs= @()

foreach ($File in $Files)
{
	$Jobs += Start-Job -ScriptBlock {
		param
		(
			$Compiler, $CompileFlags, $Configuration, $File, $CurrentDir
		)
		Set-Location $CurrentDir
		$Command = $Compiler
		$Command += ' '
		$Command += $CompileFlags
		$Command += ' -c ".\BFW\Sources\'
		$Command += $File
		$Command += '.cpp" -o ".\Objects\BFW_STATIC\ESP32\'
		$Command += $Configuration
		$Command += '\'
		$Command += $File
		$Command += '.o"'
		& cmd /c $Command
	} -ArgumentList $Compiler, $CompileFlags, $Configuration, $File, $CurrentDir
}

$Jobs | Receive-Job -Wait
