
.\imagevalidate_526.exe -avg -threshold 0.75 -maxthreshold 0.01 cube_0001.tga .\compare\cube_0001.org.tga > imagevalidate_cube_0001.out 2> imagevalidate_cube_0001.err

C:\cpu2017\bin\specperl.exe C:\cpu2017\bin\harness\specdiff -m -l 10 --reltol 0.05 .\output\imagevalidate_cube_0001.out imagevalidate_cube_0001.out > imagevalidate_cube_0001.out.cmp

