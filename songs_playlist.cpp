#include "hash.h"
#include "song.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void readSongsFromFile(std::string file_path, SeparateChaningHash<std::string, Song> &table);
void addSongToHashTable(std::string artist, std::string title, std::string duration, SeparateChaningHash<std::string, Song> &table);

int main()
{

  SeparateChaningHash<std::string, Song> songTable;

  bool isPathIncorrect = true;
  std::string file_path;

  // Read data from file
  while (isPathIncorrect)
  {
    std::cout << "Enter absolute/relative file path(or enter Y to read the default file): ";
    std::cin >> file_path;
    if (file_path == "Y")
    {
      file_path = "./sample_song_data.dat";
    }

    readSongsFromFile(file_path, songTable);

    if (songTable.empty())
    {
      std::cout << "\n----------------------- Incorrect file path! Try again! -------------------------\n\n";
    }
    else
    {
      std::cout << "\n-----------------------------------  Succes! ------------------------------------" << std::endl;
      isPathIncorrect = false;
    }
  }

  // Test
  // Song obj = songTable["Balmorhea"];
  // std::cout << "Artist: " << obj.getArtist() << ",   Title: " << obj.getTitle() << ",   Duration: " << obj.getDuration() << std::endl;

  return 0;
}

void readSongsFromFile(std::string file_path, SeparateChaningHash<std::string, Song> &table)
{
  std::ifstream dataFile;
  std::string lineFull, lineElement;
  std::string arrLines[100000];
  int qty = 0, r;
  std::string *oneLineArray;

  dataFile.open(file_path);

  // split by lines
  while (std::getline(dataFile, lineFull))
  {
    std::cout << lineFull << std::endl;
    arrLines[qty] = lineFull;
    qty++;
  }

  // Split the line using delimiter
  for (int i = 0; i < qty - 1; i++)
  {
    oneLineArray = new std::string[3];
    std::istringstream istream(arrLines[i]);
    r = 0;

    while (std::getline(istream, lineElement, '\t'))
    {
      oneLineArray[r] = lineElement;
      r++;
    }

    std::string songArtist = oneLineArray[1];
    std::string songTitle = oneLineArray[0];
    std::string songDuration = oneLineArray[2];

    addSongToHashTable(songArtist, songTitle, songDuration, table);

    delete[] oneLineArray;
  }
}

void addSongToHashTable(std::string artist, std::string title, std::string duration, SeparateChaningHash<std::string, Song> &table)
{
  // Test
  //  std::cout << "Artist: " << artist << ", Title: " << title << ", DUration: " << duration << std::endl;

  Song songObj = Song(title, artist, duration);
  table[artist] = songObj;
}