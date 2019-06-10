cd ..\..\Release\

.\RL-Bin_Injector.exe "..\Tests\namd_r\namd_r.exe --input ..\Tests\namd_r\apoa1.input --iterations 1 --output ..\Tests\namd_r\apoa1.test.output" > ..\Tests\namd_r\namd.out 2> ..\Tests\namd_r\namd.err

cd ..\Tests\namd_r\
