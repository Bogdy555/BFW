#if !defined BFW_DLL_LINK && !defined BFW_STATIC_LINK

#error No target specified

#endif



#if defined BFW_DLL_LINK && defined BFW_STATIC_LINK

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

LicenseFile = {#ProjectDir}License\BFW_APP_License.txt
InfoBeforeFile = {#ProjectDir}ReadMe\BFW_APP_ReadMe.txt
InfoAfterFile = {#ProjectDir}Resources\Setup Info\BFW_APP_SetupInfoAfter.txt

OutputDir = {#OutDir}
OutputBaseFilename = Setup {#ProjectName}

SignTool = SignTool sign /f "{#SolutionDir}Solution Items\Digital Certificates\BFW\BFW_SPC_PFX.pfx" /p "BFWSoftware" /a /t "http://timestamp.digicert.com" /fd sha256 /d "BFW_APP" $f
SignedUninstaller = yes

SetupIconFile = {#SolutionDir}Solution Items\Resources\Icons\BFW_Icon.ico
UninstallDisplayIcon = {app}\{#ProjectName}.exe
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

#if defined BFW_APP_x86 && !defined BFW_APP_DEBUG

ArchitecturesAllowed = x86

#endif

#if defined BFW_APP_x64 && !defined BFW_APP_DEBUG

ArchitecturesAllowed = x64

#endif

#if defined BFW_APP_x64

ArchitecturesInstallIn64BitMode = x64

#endif



[Languages]

Name: "english"; MessagesFile: "compiler:Default.isl"



[Files]

#ifdef BFW_DLL_LINK

Source: "{#OutDir}BFW_DLL.dll"; DestDir: "{app}\"; Flags: ignoreversion

#endif

Source: "{#OutDir}{#ProjectName}.exe"; DestDir: "{app}\"; Flags: ignoreversion

Source: "{#ProjectDir}License\BFW_APP_License.txt"; DestDir: "{app}\"; Flags: ignoreversion
Source: "{#ProjectDir}ReadMe\BFW_APP_ReadMe.txt"; DestDir: "{app}\"; Flags: ignoreversion



[Tasks]

Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked



[Icons]

Name: "{autoprograms}\{#ProjectName}"; Filename: "{app}\{#ProjectName}.exe"
Name: "{autodesktop}\{#ProjectName}"; Filename: "{app}\{#ProjectName}.exe"; Tasks: desktopicon



[Run]

Filename: "{app}\{#ProjectName}.exe"; Description: "{cm:LaunchProgram,{#StringChange(ProjectName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
