OBJS = driver.cpp Pong.cpp Racket.cpp Ball.cpp
OUT = pong.out
CXX = g++
CFLAGS = -g -Wall
LFLAGS = -lglut -lGL -lGLU

run: pong.out
	./pong.out

pong.out: driver.cpp
	$(CXX) $(CFLAGS) $(OBJS) -o $(OUT) $(LFLAGS)

.PHONY: clean

clean:
	rm $(OUT)
