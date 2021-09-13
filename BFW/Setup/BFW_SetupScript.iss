#if !defined BFW_DLL_BUILD && !defined BFW_STATIC_BUILD

#error No target specified

#endif



#if defined BFW_DLL_BUILD && defined BFW_STATIC_BUILD

#error You have to specifie just one target

#endif



#define Version "1.0.0.0"
#define Publisher "BFW"
#define GithubLink "https://github.com/Bogdy555/BFW"



[Setup]

AppId = {#ProjectName}
AppName = {#ProjectName}
AppVersion = {#Version}
AppPublisher = {#Publisher}

AppPublisherURL={#GithubLink}
AppSupportURL={#GithubLink}
AppUpdatesURL={#GithubLink}

LicenseFile = {#ProjectDir}License\BFW_License.txt
InfoBeforeFile = {#ProjectDir}ReadMe\BFW_ReadMe.txt
InfoAfterFile = {#ProjectDir}Resources\Setup Info\BFW_SetupInfoAfter.txt

OutputDir = {#OutDir}
OutputBaseFilename = Setup {#ProjectName}

SignTool = SignTool sign /f "{#SolutionDir}Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW" $f
SignedUninstaller = yes

SetupIconFile = {#SolutionDir}Solution Items\Resources\Icons\BFW_Icon.ico
UninstallDisplayIcon = {app}\Solution\Solution Items\Resources\Icons\BFW_Icon.ico
UninstallDisplayName = {#ProjectName}
UninstallFilesDir = {app}\Uninstall\
AppCopyright = Copyright (C) {#Publisher}

VersionInfoCompany = {#Publisher}
VersionInfoCopyRight = Copyright (C) {#Publisher}
VersionInfoDescription = Setup {#ProjectName}
VersionInfoOriginalFileName = Setup {#ProjectName}.exe
VersionInfoProductName = Setup {#ProjectName}
VersionInfoProductTextVersion = {#Version}
VersionInfoProductVersion = {#Version}
VersionInfoTextVersion = {#Version}
VersionInfoVersion = {#Version}

WizardStyle = modern
DefaultDirName = {autopf}\{#ProjectName}\
DefaultGroupName = {#ProjectName}
AllowNoIcons = yes
Compression = lzma
SolidCompression = yes

#if defined BFW_x86 && !defined BFW_DEBUG

ArchitecturesAllowed = x86

#endif

#if defined BFW_x64 && !defined BFW_DEBUG

ArchitecturesAllowed = x64

#endif

#if defined BFW_x64

ArchitecturesInstallIn64BitMode = x64

#endif



[Languages]

Name: "english"; MessagesFile: "compiler:Default.isl"



[Files]

#ifdef BFW_DLL_BUILD

Source: "{#OutDir}BFW_DLL.dll"; DestDir: "{app}\Binaries\"; Flags: ignoreversion

#endif

Source: "{#OutDir}{#ProjectName}.lib"; DestDir: "{app}\Binaries\"; Flags: ignoreversion
Source: "{#OutDir}{#ProjectName}.pdb"; DestDir: "{app}\Binaries\"; Flags: ignoreversion

Source: "{#ProjectDir}License\BFW_License.txt"; DestDir: "{app}\Binaries\"; Flags: ignoreversion
Source: "{#ProjectDir}ReadMe\BFW_ReadMe.txt"; DestDir: "{app}\Binaries\"; Flags: ignoreversion

Source: "{#ProjectDir}Headers\*"; DestDir: "{app}\Headers\"; Flags: ignoreversion recursesubdirs createallsubdirs

Source: "{#SolutionDir}BFW\*"; DestDir: "{app}\Solution\BFW\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#SolutionDir}BFW_APP\*"; DestDir: "{app}\Solution\BFW_APP\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#SolutionDir}BFW_ARDUINO\*"; DestDir: "{app}\Solution\BFW_ARDUINO\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#SolutionDir}Solution Items\*"; DestDir: "{app}\Solution\Solution Items\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#SolutionDir}BFW.sln"; DestDir: "{app}\Solution\"; Flags: ignoreversion
