all:
	make p1 p2 p3

p1: p1.cpp

	g++ p1.cpp \
		-o p1 \
		-I ~/boost/

p2: p2.cpp \
	xor.hpp \
	upper.hpp \
	promote.hpp

	g++ p2.cpp \
		-o p2 \
		-I ~/boost/

p3: p3.cpp \
	xor.hpp \
	upper.hpp \
	add.hpp

	g++ p3.cpp \
		-o p3 \
		-I ~/boost/

clean:
	rm p1 p2 p3
