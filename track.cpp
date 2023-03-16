#include "track.h"
#include <string>

Track::Track(std::string title, std::string artist, std::string duration) {
  this->title = title;
  this->artist = artist;
  this->duration = duration;
}

Track::Track() {}

Track::~Track() {}

std::string Track::getTitle() {
  return this->title;
}

std::string Track::getArtist() {
  return this->artist;
}

std::string Track::getDuration() {
  return this->duration;
}