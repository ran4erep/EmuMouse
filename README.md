# Mouse Wheel Emulation via Keyboard  

This program emulates mouse wheel scrolling using keyboard keys. It's useful for users who don't have a physical scroll wheel or when the mouse wheel are broken.
You can scroll up with `Windows + Q` and scroll down with `Windows + A` hotkeys.

Also you can copy EmuMouse.exe to your startup folder to launch it automatically when your system starts. Startup folder located at `C:\Users\USER_NAME\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup` or you can simply type `shell:startup` in the `Run` (Windows + R) window to get there.

## Why it's better than AutoHotKey scripts?
- Written in C++, which means low CPU and RAM usage.
- Works with any games or software without any problems.
- Hotkeys can be combined with `Shift`, `Ctrl`, `Alt` modifier keys.
- It just works, no need to write scripts with bizarre programming language.

![](mouse.gif)
