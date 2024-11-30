# Каталог с файлами для отладки
$buildDebugDir = ".\build\vc22\x64\Debug"

# Каталог проекта Visual Studio
$vc22ProjDir = ".\build\vc22"

# Массив DLL-файлов
$dlls = @(
    "csfml-audio-2.dll",
    "csfml-graphics-2.dll",
    "csfml-network-2.dll",
    "csfml-system-2.dll",
    "csfml-window-2.dll"
)

# Удаление символических ссылок на DLL в каталоге для отладки
foreach ($dll in $dlls) {
    $dllPath = "$buildDebugDir\$dll"
    if (Test-Path $dllPath) {
        Remove-Item -Path $dllPath -Force
    }
}

# Удаление символических ссылок на каталог ресурсов
$resourceLinks = @("$buildDebugDir\resources", "$vc22ProjDir\resources")
foreach ($link in $resourceLinks) {
    if (Test-Path $link) {
        Remove-Item -Path $link -Force -Recurse
    }
}
