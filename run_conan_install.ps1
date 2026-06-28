param(
    [switch]$Force   # pass -Force to rebuild all packages from source
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

# Require Conan 2.x
$conanVersion = (conan --version 2>&1) -replace 'Conan version ', ''
if (-not ($conanVersion -match '^2\.')) {
    Write-Error "Conan 2.x required, found: $conanVersion"
    exit 1
}

$buildFlag  = if ($Force) { '--build=*' } else { '--build=missing' }
$outputFolder = 'out/conan'

foreach ($buildType in 'Debug', 'Release') {
    Write-Host "==> conan install ($buildType)" -ForegroundColor Cyan
    conan install . $buildFlag -s build_type=$buildType -s compiler.cppstd=17 --output-folder $outputFolder -c tools.cmake.cmaketoolchain:generator=Ninja
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}

# Remove conan-generated preset files — we manage presets in CMakePresets.json.
# Only conan_toolchain.cmake is needed; the preset files cause duplicate/conflicting
# entries in VS Code and Visual Studio.
Remove-Item -Force "$outputFolder/CMakePresets.json" -ErrorAction SilentlyContinue
Remove-Item -Force "CMakeUserPresets.json" -ErrorAction SilentlyContinue

Write-Host "`nDone. Reconfigure CMake to pick up the toolchain." -ForegroundColor Green
