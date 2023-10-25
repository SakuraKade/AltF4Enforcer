Set objShell = CreateObject("WScript.Shell")
userProfile = objShell.ExpandEnvironmentStrings("%UserProfile%")

Set objShortcut = objShell.CreateShortcut(userProfile & "\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\AltF4Enforcer.lnk")

objShortcut.TargetPath = userProfile & "\AppData\LocalLow\AltF4Enforcer\AltF4Enforcer.exe"
objShortcut.Save
