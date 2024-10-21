:: Disable command showing
@echo off
:: Set UTF-8 encoding
chcp 65001 > nul

:: Delete "build" folder due to uncontrolable cmake-action including
rmdir /s /q build > nul 2> nul

:: Make link to the MinGW x64 v11.2.0 due to install-qt-action limitations
mkdir C:\Qt\Tools > nul
mklink C:\Qt\Tools\mingw_64 C:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64 > nul

xcopy /s /q C:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\include\c++\11.2.0\x86_64-w64-mingw32\ C:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\include\c++\11.2.0\
xcopy /s /q C:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\include\c++\11.2.0\ C:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\include\
: rmdir /s /q C:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\include\c++\11.2.0\
tree C:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\lib\
set PATH=%PATH%;C:\Qt\5.15.2\mingw81_64\bin;C:\Qt\Tools\mingw_64\bin

:: Print 
echo Generals Zero Hour Hotkeys editor
echo Authors: mah_boi, nikitvs
echo.

:: Set up cmake config folder for the project
echo Configuring MinGW Make...
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=C:\Qt\Tools\mingw_64\bin\gcc.exe -DCMAKE_CXX_COMPILER:FILEPATH=C:\Qt\Tools\mingw_64\bin\g++.exe -S.\ -B.\build -G "MinGW Makefiles"
echo Configuring MinGW Make done
echo.

:: Start compiling
echo Compilation and linking executables...
cmake --build .\build --config Release --target all -j 16
echo Compilation and linking executables done
echo.

:: Add any file to "Logs" folder for good zipping
mkdir build\exe\Logs >nul 2> nul
cd build\exe\Logs
echo Do not delete this folder, please. Or program will can not be start. > readme.txt
