
obj = others.o main.o functions.o affix.o lexicon_part_1.o lexicon_part_2.o lexicon_part_3.o
head = headers.h

SourcePractice: $(obj)
	g++ -o SourcePractice $(obj)
	rm *.o

others.o: $(head)
	g++ -c others.cpp
main.o: $(head)
	g++ -c main.cpp
functions.o: $(head)
	g++ -c functions.cpp
affix.o: $(head)
	g++ -c affix.cpp
lexicon_part_1.o: $(head)
	g++ -c ../res/lexicon_part_1.cpp
lexicon_part_2.o: $(head)
	g++ -c ../res/lexicon_part_2.cpp
lexicon_part_3.o: $(head)
	g++ -c ../res/lexicon_part_3.cpp


.PHONY: clean start
clean:
	rm *.o
start:
	./SourcePractice

