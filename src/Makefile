.PHONY: all clean

LIBRARIES := ../lib

INCLUDE := ../include

FILES := \
	x16test_main.c

OBJ = $(FILES:%.c=%.o)

OPT := -Oi
# OPT := -g

.c.o:
	cc65 -t cx16 $(OPT) -I $(INCLUDE) $<
	ca65 -t cx16 $(<:%.c=%.s)

all: libX16Test.lib

quit.o: quit.s
	ca65 -t cx16

libX16Test.lib: $(OBJ)
	ar65 r libX16Test.lib $(OBJ)
	cp *.lib $(LIBRARIES)

clean:
	rm -f $(LIBRARIES)/*.lib *.o *.lib