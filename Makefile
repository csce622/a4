all:
	make p1

p1: p1.cpp

	g++ p1.cpp \
		-o p1 \
		-I ~/boost/

clean:
	rm p1
