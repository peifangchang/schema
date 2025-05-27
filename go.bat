@echo off 
xmake b 
echo. 
if errorlevel 0 goto go 
if errorlevel -1 goto end 
:go 
build\mingw\x86_64\release\schema.exe %* 
:end 
echo. 
