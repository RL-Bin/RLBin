cd ..\..\Release\
.\RL-Bin_Injector.exe ..\Tests\_g_02\_g_02.exe < ..\Tests\_g_02\input.txt > ..\Tests\_g_02\output.txt 2> ..\Tests\_g_02\error.txt 
cd ..\Tests\_g_02\

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