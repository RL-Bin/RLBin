cd ..\..\Release\
.\RL-Bin_Injector.exe ..\Tests\_v_00\_v_00.exe 
rem .\RL-Bin_Injector.exe ..\Tests\_v_00\_v_00.exe < ..\Tests\_v_00\input.txt > ..\Tests\_v_00\output.txt 2> ..\Tests\_v_00\error.txt 
cd ..\Tests\_v_00\

@echo off

echo __________________________________________________________________________________
echo input.txt
echo __________________________________________________________________________________

type input.txt

echo __________________________________________________________________________________
echo output.txt
echo __________________________________________________________________________________

type output.txt

echo.
echo __________________________________________________________________________________
echo error.txt
echo __________________________________________________________________________________

type error.txt
