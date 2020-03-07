.PHONY: all clean

LIBRARIES := ../lib

INCLUDE := ../include

all: factorial_test.prg

clean:
	rm -f *.prg *.o *.s

factorial_test.prg:	factorial.c test_factorial.c main.c ../include/x16test.h
	cl65 -t cx16 -I $(INCLUDE) -L $(LIBRARIES) -o factorial_test.prg factorial.c test_factorial.c main.c libX16Test.lib cx16.lib