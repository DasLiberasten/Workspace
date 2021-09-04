COMPILER = g++
COMPILER_FLAGS = -O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wcast-qual -Wwrite-strings -lm
LINK = -fsanitize=undefined -o


main: main.o Matrix.o Proxy.o Y_part.o X_part.o IterableDenceMatrix.o IterableSparseMatrix.o FinalMatrix.o Iterators.o
	$(COMPILER) $^ $(LINK) $@

main.o: main.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c main.cpp

Matrix.o: Matrix.cpp Matrix.h
	$(COMPILER) $(COMPILER_FLAGS) -c Matrix.cpp

Proxy.o: Proxy.cpp Proxy.h
	$(COMPILER) $(COMPILER_FLAGS) -c Proxy.cpp

Y_part.o: Y_part.cpp Y_part.h
	$(COMPILER) $(COMPILER_FLAGS) -c Y_part.cpp

X_part.o: X_part.cpp X_part.h
	$(COMPILER) $(COMPILER_FLAGS) -c X_part.cpp

IterableDenceMatrix.o: IterableDenceMatrix.cpp IterableDenceMatrix.h
	$(COMPILER) $(COMPILER_FLAGS) -c IterableDenceMatrix.cpp

IterableSparseMatrix.o: IterableSparseMatrix.cpp IterableSparseMatrix.h
	$(COMPILER) $(COMPILER_FLAGS) -c IterableSparseMatrix.cpp

FinalMatrix.o: FinalMatrix.cpp FinalMatrix.h
	$(COMPILER) $(COMPILER_FLAGS) -c FinalMatrix.cpp

Iterators.o: Iterators.cpp Iterators.h
	$(COMPILER) $(COMPILER_FLAGS) -c Iterators.cpp

clear_gch:
	rm *.gch
	rm main

clear_o:
	rm *.o
	rm main