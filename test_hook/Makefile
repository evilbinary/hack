all:test.so 
2:test1
3:test2
test.so:test.c
	gcc -shared -o test.so test.c -fPIC -ldl -rdynamic
test1:log-malloc.c
	gcc -shared -o test.so log-malloc.c -fPIC -ldl -rdynamic
test2:new.cpp
	g++ new.cpp -o test
clean:
	rm -rf *.so *.o
