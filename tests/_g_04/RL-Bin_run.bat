cd ..\..\Release\
.\RL-Bin_Injector.exe ..\Tests\_g_04\_g_04.exe < ..\Tests\_g_04\input.txt > ..\Tests\_g_04\output.txt 2> ..\Tests\_g_04\error.txt 
cd ..\Tests\_g_04\

@echo off

echo __________________________________________________________________________________
echo input.txt
echo __________________________________________________________________________________

type input.txt

echo __________________________________________________________________________________
echo output.txt
echo __________________________________________________________________________________

type output.txt

echo __________________________________________________________________________________
echo error.txt
echo __________________________________________________________________________________

type error.txt
