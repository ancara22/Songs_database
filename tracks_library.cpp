#include "hash.h"
#include "functions.h"
#include "track.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <cstdio>



int main() {
  SeparateChaningHash<std::string, Track> songsTable;

  readFile(songsTable);
  printMenu(songsTable);

  return 0;
}

