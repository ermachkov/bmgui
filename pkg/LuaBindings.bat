set LUA_BINDINGS=..\src\LuaBindings.inc

del /Q %LUA_BINDINGS%

C:\Projects\Dependencies\bin\Win32\tolua++.exe -o %LUA_BINDINGS% LuaBindings.pkg
