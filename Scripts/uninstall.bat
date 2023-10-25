@echo off
Rem kill existing process
tasklist /FI "IMAGENAME eq AltF4Enforcer.exe" 2>NUL | find /I /N "AltF4Enforcer.exe">NUL
if "%ERRORLEVEL%"=="0" taskkill /f /im AltF4Enforcer.exe

Rem delete directory recursive
rmdir /s /q %UserProfile%\AppData\LocalLow\AltF4Enforcer

Rem delete shortcut
del /q "%UserProfile%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\AltF4Enforcer.lnk"

echo Done!
pause
