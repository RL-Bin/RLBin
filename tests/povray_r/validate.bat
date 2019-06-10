
.\imagevalidate_511.exe SPEC-benchmark.tga .\compare\SPEC-benchmark.org.tga > imagevalidate_SPEC-benchmark.tga.out 2> imagevalidate_SPEC-benchmark.tga.err

C:\cpu2017\bin\specperl.exe C:\cpu2017\bin\harness\specdiff -m -l 10 --reltol 0.06 .\output\imagevalidate_SPEC-benchmark.tga.out imagevalidate_SPEC-benchmark.tga.out > imagevalidate_SPEC-benchmark.tga.out.cmp

