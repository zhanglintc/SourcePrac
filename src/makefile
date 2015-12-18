
obj = others.obj main.obj functions.obj affix.obj
head = headers.h

ddAPP: $(obj)
	g++ -o ddAPP $(obj)

others.obj: $(head)
	g++ -c others.cpp
main.obj: $(head)
	g++ -c main.cpp
functions.obj: $(head)
	g++ -c functions.cpp
affix.obj: $(head)
	g++ -c affix.cpp


.PHONY: clean
clean:
	rm *.obj

