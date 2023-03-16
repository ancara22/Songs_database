#ifndef _TRACK_H_
#define _TRACK_H_

#include <string>

class Track {
private:
  std::string title;
  std::string artist;
  std::string duration;

public:
  Track(std::string title, std::string artist, std::string duration);
  Track();
  virtual ~Track();
  std::string getTitle();
  std::string getArtist();
  std::string getDuration();
  bool operator==(Track &song);

};


#endif
