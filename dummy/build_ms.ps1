# Get MS Build Path
$Script_Path = Get-Location
$Babel_Path = (get-item $Script_Path).parent.FullName

Write-Host "Checking MS Visual Studio installation folder on C:\"
$C_Path = �C:\�
if(!(Test-Path -Path $C_Path))
{
    Write-Host -ForegroundColor RED "C:\ Is Not Found"
    exit
}
$MSVS_Installer_path = "C:\Program Files (x86)\Microsoft Visual Studio\Installer"
if(!(Test-Path -Path $MSVS_Installer_path))
{
    Write-Host -ForegroundColor RED "Visual Studio Installaer is not found"
    exit
}
else
{
    Write-Host -ForegroundColor GREEN "Found MS Visual Studio installation: " $MSVS_Installer_path
    cd $MSVS_Installer_path
}
$MSVS_Installation_Path = .\vswhere.exe -property InstallationPath
Write-Host -ForegroundColor GREEN "Using MSVS Installation On: " $MSVS_Installation_Path

Write-Host "Checking MSBuild Installation"
$MSBuild_Installation_Path = $MSVS_Installation_Path + "\MSBuild\Current\Bin"
if(!(Test-Path -Path $MSBuild_Installation_Path))
{
    Write-Host -ForegroundColor RED "MSBuild is not found, please install it"
    exit
}
else
{
    Write-Host -ForegroundColor GREEN "Found MSBuild Installation: " $MSBuild_Installation_Path
    cd $MSBuild_Installation_Path
}

# _____________
# Build x64 DLL
#
Write-Host ""
Write-Host -BackgroundColor GREEN "Building x64 DLL          " 

[String]$x64_Path = [String]$Script_Path + "\msvscpp\msvscpp\x64"
if(!(Test-Path -Path $x64_Path))
{
    mkdir $x64_Path | out-null
    [String]$x64_Release_Path = [String]$Script_Path + "\msvscpp\msvscpp\x64\Release"
    mkdir $x64_Release_Path | out-null
}

[String]$Log_File_Path =
    [String]$Script_Path + "\msvscpp\msvscpp\x64\Release\Build_Output_" + [DateTime]::Now.ToString("yyyyMMdd-HHmmss") + ".log"

[String]$MSBuild_Cmd = 
    (".\MSBuild ") + 
    ([String]$Script_Path + "\msvscpp\msvscpp\msvscpp.vcxproj" + " /property:Configuration=Release /property:Platform=x64") + 
    ("  >  " + [String]$Log_File_Path)

Invoke-expression $MSBuild_Cmd
Write-Host "Build Log Is Found In: "$Log_File_Path

Write-Host "Checking Build Results"

[String]$x64_DLL_Path = [String]$x64_Release_Path + "\xhptdc8_driver_64.dll"
[String]$x64_Lib_Path = [String]$x64_Release_Path + "\xhptdc8_driver_64.lib"
if(!(Test-Path -Path $x64_DLL_Path))
{
    Write-Host -ForegroundColor RED "Error generating DLL"
}
else
{
    [String]$Babel_Libx64_Path = $Babel_Path + "\lib\dummy"
    Copy-Item $x64_DLL_Path -Destination $Babel_Libx64_Path
    Copy-Item $x64_Lib_Path -Destination $Babel_Libx64_Path
    Write-Host -ForegroundColor GREEN "DLL and Lib are copied successfully to the corresponding lib folder: " $Babel_Libx64_Path
}
