COMPILER = gcc --coverage -O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -std=gnu11 -lm


main: main.o
	$(COMPILER) main.o -o main
	./main

main.o: main.c
	$(COMPILER) -O0 -g -c main.c

clear_reg:
	rm *.o
	rm main

clear_code:
	rm *.gcno
	rm *.gcda


