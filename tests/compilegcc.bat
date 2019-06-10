@echo off
SET data=%1
FOR /f "tokens=1,2 delims=." %%a IN ("%data%") do (
nasm.exe -fwin32 %1
Gcc  .%%a.obj -o .%%a.exe
)