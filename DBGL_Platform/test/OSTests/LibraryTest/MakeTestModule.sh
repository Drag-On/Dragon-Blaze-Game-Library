g++ -c test_module.cpp -fPIC
g++ -shared -o test_module.so test_module.o -Wl,--export-dynamic
