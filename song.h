#ifndef _SONG_H_
#define _SONG_H_

#include <string>

class Song {
private:
  std::string title;
  std::string artist;
  std::string duration;

public:
  Song(std::string title, std::string artist, std::string duration);
  Song();
  virtual ~Song();
  std::string getTitle();
  std::string getArtist();
  std::string getDuration();
};

#endif
