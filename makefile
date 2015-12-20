
obj = others.o main.o functions.o affix.o lexicon_part_1.o lexicon_part_2.o lexicon_part_3.o
head = ./src/headers.h

SourcePractice: $(obj)
	g++ -o SourcePractice $(obj)
	rm *.o

others.o: $(head)
	g++ -c ./src/others.cpp
main.o: $(head)
	g++ -c ./src/main.cpp
functions.o: $(head)
	g++ -c ./src/functions.cpp
affix.o: $(head)
	g++ -c ./src/affix.cpp
lexicon_part_1.o: $(head)
	g++ -c ./res/lexicon_part_1.cpp
lexicon_part_2.o: $(head)
	g++ -c ./res/lexicon_part_2.cpp
lexicon_part_3.o: $(head)
	g++ -c ./res/lexicon_part_3.cpp


.PHONY: clean start
clean:
	rm *.o
start:
	./SourcePractice

