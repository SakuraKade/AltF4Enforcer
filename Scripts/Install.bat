@echo off
Rem kill existing process
tasklist /FI "IMAGENAME eq AltF4Enforcer.exe" 2>NUL | find /I /N "AltF4Enforcer.exe">NUL
if "%ERRORLEVEL%"=="0" taskkill /f /im AltF4Enforcer.exe

Rem create directory and copy file
mkdir %UserProfile%\AppData\LocalLow\AltF4Enforcer
copy /v /y /b %~dp0AltF4Enforcer.exe %UserProfile%\AppData\LocalLow\AltF4Enforcer\AltF4Enforcer.exe

Rem create shortcut
cscript //nologo "%~dp0CreateShortcut.DontRunMe.vbs"

Rem Start program
start "" /D "%UserProfile%\AppData\LocalLow\AltF4Enforcer" "%UserProfile%\AppData\LocalLow\AltF4Enforcer\AltF4Enforcer.exe"

echo Done!
pause
