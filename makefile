CXX = g++
CFLAGS = -g -Wall
LINKING = -lglut -lGL -lGLU

run: pong.out
	./pong.out

pong.out: driver.cpp pong.cpp
	$(CXX) $(CFLAGS) driver.cpp pong.cpp Racket.cpp -o pong.out $(LINKING)

.PHONY: clean

clean:
	rm pong.out
