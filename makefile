CXX = g++
CFLAGS = -g -Wall
LINKING = -lglut -lGL -lGLU

run: pong.out
	./pong.out

pong.out: driver.cpp
	$(CXX) $(CFLAGS) driver.cpp Window.cpp Racket.cpp Ball.cpp -o pong.out $(LINKING)

.PHONY: clean

clean:
	rm pong.out
