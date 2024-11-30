# Создание каталога dist и его подкаталога resources
New-Item -ItemType Directory -Path ".\dist" -Force
New-Item -ItemType Directory -Path ".\dist\resources" -Force

# Копирование PNG-файлов из resources в dist\resources
Copy-Item -Path ".\resources\*.png" -Destination ".\dist\resources" -Force

# Копирование исполняемого файла в dist
Copy-Item -Path ".\build\vc22\x64\Debug\SIMPRApp.exe" -Destination ".\dist" -Force

# Копирование DLL-файлов CSFML в dist
Copy-Item -Path ".\dep\CSFML\bin\csfml*.dll" -Destination ".\dist" -Force
