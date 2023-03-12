CXX = g++
CFLAGS = -g -std=c++11  -Wall -Wextra -Wpedantic


.PHONY : all
all: songs_database

songs_list: songs_database.cpp song.o
	$(CXX) $(CFLAGS) -o $@ $^

song.o: song.cpp song.h
	$(CXX) $(CFLAGS) -c song.cpp



.PHONY : test
test: songs_test.cpp song.o
	$(CXX) $(CFLAGS) -o $@ $^


.PHONY : clean
clean:
	rm -f  songs_database
	rm -f  *.o
	rm -f *.out
	rm -f test


