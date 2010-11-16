all:
	make p1 p2

p1: p1.cpp

	g++ p1.cpp \
		-o p1 \
		-I ~/boost/

p2: p2.cpp

	g++ p2.cpp \
		-o p2 \
		-I ~/boost/

clean:
	rm p1 p2
