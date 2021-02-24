rmdir .\analysis /s /q

RLBin --dynamic --verbose -o1 tests\lbm_r\lbm_r.exe 20 reference.dat 0 1 tests\lbm_r\100_100_130_cf_a.of
