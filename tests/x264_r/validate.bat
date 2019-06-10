.\imagevalidate_525.exe -avg -threshold 0.5 -maxthreshold 20 frame_50.yuv .\compare\frame_50.org.tga > imagevalidate_frame_50.out 2> imagevalidate_frame_50.err

.\imagevalidate_525.exe -avg -threshold 0.5 -maxthreshold 20 frame_100.yuv .\compare\frame_100.org.tga > imagevalidate_frame_100.out 2> imagevalidate_frame_100.err

.\imagevalidate_525.exe -avg -threshold 0.5 -maxthreshold 20 frame_155.yuv .\compare\frame_155.org.tga > imagevalidate_frame_155.out 2> imagevalidate_frame_155.err

C:\cpu2017\bin\specperl.exe C:\cpu2017\bin\harness\specdiff -m -l 10 --reltol 0.085 .\output\imagevalidate_frame_100.out imagevalidate_frame_100.out > imagevalidate_frame_100.out.cmp

C:\cpu2017\bin\specperl.exe C:\cpu2017\bin\harness\specdiff -m -l 10 --reltol 0.085 .\output\imagevalidate_frame_155.out imagevalidate_frame_155.out > imagevalidate_frame_155.out.cmp

C:\cpu2017\bin\specperl.exe C:\cpu2017\bin\harness\specdiff -m -l 10 --reltol 0.085 .\output\imagevalidate_frame_50.out imagevalidate_frame_50.out > imagevalidate_frame_50.out.cmp

