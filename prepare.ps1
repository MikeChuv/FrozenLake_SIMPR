# Каталог проекта Visual Studio
$vc22ProjDir = ".\build\vc22"

# Каталог с файлами для отладки
$buildDebugDir = ".\build\vc22\x64\Debug"

# Каталог с DLL
$dllDir = ".\dep\CSFML\bin"

# Каталог с ресурсами
$resourcesDir = ".\resources"

# Массив DLL-файлов
$dlls = @(
    "csfml-audio-2.dll",
    "csfml-graphics-2.dll",
    "csfml-network-2.dll",
    "csfml-system-2.dll",
    "csfml-window-2.dll"
)

# Создание символических ссылок на DLL в каталоге для отладки
foreach ($dll in $dlls) {
    New-Item -ItemType SymbolicLink -Path "$buildDebugDir\$dll" -Target "$dllDir\$dll"
}

# Создание символической ссылки на каталог ресурсов
New-Item -ItemType SymbolicLink -Path "$buildDebugDir\resources" -Target $resourcesDir
New-Item -ItemType SymbolicLink -Path "$vc22ProjDir\resources" -Target $resourcesDir
