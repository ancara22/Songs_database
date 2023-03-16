#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <string>
#include "hash.h"
#include "track.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <cstdio>


void readSongsFromFile(std::string file_path, SeparateChaningHash<std::string, Track> &table);
void addSongToHashTable(std::string artist, std::string title, std::string duration, SeparateChaningHash<std::string, Track> &table);
void readFile(SeparateChaningHash<std::string, Track> &table);
void search(SeparateChaningHash<std::string, Track> &table);
void saveToFile(SeparateChaningHash<std::string, Track> &table);
void remove(SeparateChaningHash<std::string, Track> &table);
void printMenu(SeparateChaningHash<std::string, Track> &table);


#endif