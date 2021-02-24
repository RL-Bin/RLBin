SET data=%1
FOR /f "tokens=1,2 delims=." %%a IN ("%data%") do (
nasm.exe -f win32 -g %1
GoLink.exe  /console /entry _start .%%a.obj kernel32.dll
)