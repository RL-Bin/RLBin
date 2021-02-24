echo off
set PATH=%PATH%;C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin
cls
MSBuild.exe "%~dp0\RLBin.sln" /p:Configuration=Release /p:Platform="x86" /maxcpucount  /nowarn:LNK4099 /nowarn:C4018 /nowarn:LNK4075 /nowarn:LNK4098 /v:minimal /m


