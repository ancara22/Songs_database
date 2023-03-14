CXX = g++
CFLAGS = -g -std=c++11  -Wall -Wextra -Wpedantic


.PHONY : all
all: songs_playlist

songs_playlist: songs_playlist.o song.o 
	$(CXX) $(CFLAGS) -o $@ $^ 

songs_playlist.o: songs_playlist.cpp hash.h
	$(CXX) $(CFLAGS) -c songs_playlist.cpp 

song.o: song.cpp song.h
	$(CXX) $(CFLAGS) -c song.cpp


.PHONY : test
test: songs_test.cpp song.o
	$(CXX) $(CFLAGS) -o $@ $^


.PHONY : clean
clean:
	rm -f  songs_playlist
	rm -f  *.o
	rm -f *.out
	rm -f test


