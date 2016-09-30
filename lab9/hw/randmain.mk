randmain: randmain.o randcpuid.o
	$(CC) $(CFLAGS) -ldl -Wl,-rpath=$(PWD) -o randmain randmain.o randcpuid.o

randmain.o: randmain.c
	$(CC) $(CFLAGS) -I . -c -o randmain.o randmain.c 

randcpuid.o: randcpuid.c
	$(CC) $(CFLAGS) -c -o randcpuid.o randcpuid.c

randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) -fPIC -c -o randlibhw.o randlibhw.c
	$(CC) -shared randlibhw.o -o randlibhw.so

randlibsw.so: randlibsw.c
	$(CC) $(CFLAGS) -fPIC -c -o randlibsw.o randlibsw.c
	$(CC) -shared randlibsw.o -o randlibsw.so

