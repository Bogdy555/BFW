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
		$AllFlags = $CompileFlags
		$AllFlags += ' -c ".\BFW\Sources\'
		$AllFlags += $File
		$AllFlags += '.cpp" -o ".\Objects\BFW_STATIC\ESP32\'
		$AllFlags += $Configuration
		$AllFlags += '\'
		$AllFlags += $File
		$AllFlags += '.o"'
		Start-Process -File $Compiler -Wait -NoNewWindow -ArgumentList $AllFlags
	} -ArgumentList $Compiler, $CompileFlags, $Configuration, $File, $CurrentDir
}

$Jobs | Receive-Job -Wait
