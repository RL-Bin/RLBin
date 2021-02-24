echo off
set PATH=%PATH%;C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin
cls
MSBuild.exe "%~dp0\RLBin.sln" /p:Configuration=Release /p:Platform="x86" /t:Clean

rmdir .\core\bin /s /q
rmdir .\core\Release /s /q

rmdir .\inject\bin /s /q
rmdir .\inject\Release /s /q

rmdir .\RL-Bin\bin /s /q
rmdir .\RL-Bin\Release /s /q

rmdir .\bin
rmdir .\analysis /s /q
rem cd Tests
rem python cleanLogFiles.py
rem cd ..
