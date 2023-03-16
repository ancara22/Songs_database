CXX = g++
CFLAGS = -g -std=c++11  -Wall -Wextra -Wpedantic


.PHONY : all
all: tracks_library

tracks_library: tracks_library.o track.o functions.o
	$(CXX) $(CFLAGS) -o $@ $^ 

tracks_library.o: tracks_library.cpp hash.h functions.o
	$(CXX) $(CFLAGS) -c tracks_library.cpp 

functions.o: functions.cpp functions.h
	$(CXX) $(CFLAGS) -c functions.cpp


track.o: track.cpp track.h
	$(CXX) $(CFLAGS) -c track.cpp


.PHONY : test
test: app_test.cpp track.o functions.o
	$(CXX) $(CFLAGS) -o $@ $^
	


.PHONY : clean
clean:
	rm -f  tracks_library
	rm -f  *.o
	rm -f *.out
	rm -f test


