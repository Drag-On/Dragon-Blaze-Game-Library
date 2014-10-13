g++ -c test_module.cpp
g++ -shared -o test_module.dll test_module.o -Wl,--out-implib,libtest_module.a