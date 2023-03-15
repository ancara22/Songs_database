#include "song.h"
#include <string>

Song::Song(std::string title, std::string artist, std::string duration) {
  this->title = title;
  this->artist = artist;
  this->duration = duration;
}

Song::Song() {}

Song::~Song() {}

std::string Song::getTitle() {
  return this->title;
}

std::string Song::getArtist() {
  return this->artist;
}

std::string Song::getDuration() {
  return this->duration;
}

bool Song::operator==(Song &song) {
  if(this->getArtist() == song.getArtist()) {
    if(this->getTitle() == song.getTitle()) {
      if(this->getDuration() == song.getDuration()) {
        return true;
      }
    }
  }

  return false; 
}