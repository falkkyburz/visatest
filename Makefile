all: run

visatest: visatest.c
	gcc -I. -L. -lvisa64 -mconsole -o visatest visatest.c

visafind: visafind.c
	gcc -I. -L. -lvisa64 -mconsole -o visafind visafind.c

run: visatest
	./visatest

find: visafind
	./visafind

clean:
	rm -f visatest.exe
	rm -f visafind.exe

    