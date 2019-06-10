
.\imagevalidate_538.exe -avg -threshold 0.95 -maxthreshold 0.001 test_output.tga .\compare\test_expected.tga > test_validate.out 2> test_validate.err

C:\cpu2017\bin\specperl.exe C:\cpu2017\bin\harness\specdiff -m -l 10 --reltol 0.01 .\output\test_validate.out test_validate.out > test_validate.out.cmp
