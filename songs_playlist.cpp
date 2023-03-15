#include "hash.h"
#include "song.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void readSongsFromFile(std::string file_path, SeparateChaningHash<std::string, Song> &table);
void addSongToHashTable(std::string artist, std::string title, std::string duration, SeparateChaningHash<std::string, Song> &table);
void printMenu(SeparateChaningHash<std::string, Song> &table);
void readFile(SeparateChaningHash<std::string, Song> &table);
//void saveToFile(SeparateChaningHash<std::string, Song> &table);

int main() {

  SeparateChaningHash<std::string, Song> songsTable;

  readFile(songsTable);
  printMenu(songsTable);

  // Test
  // Song obj = songTable["Balmorhea"];
  // std::cout << "Artist: " << obj.getArtist() << ",   Title: " << obj.getTitle() << ",   Duration: " << obj.getDuration() << std::endl;


  std::vector<Node<std::string, Song>*>  result = songsTable.search("Кай Метов");

  std::cout << "Size: " <<result.size() << "      " << std::endl;

  for(Node<std::string, Song>* node: result) {
    std::cout << node->value.getArtist() << ",  " << node->value.getTitle() << std::endl;
  }
  



  return 0;
}

void readFile(SeparateChaningHash<std::string, Song> &table) {
  bool isPathIncorrect = true;
  std::string file_path;

  // Read data from file
  while (isPathIncorrect) {
    std::cout << "Enter absolute/relative file path(or enter Y to read the default file): ";
    std::cin >> file_path;

    if (file_path == "Y") {
      file_path = "./sample_song_data.dat";
    }

    size_t qtyBefore = table.getSize();
    readSongsFromFile(file_path, table);
    size_t qtyAfter = table.getSize();

    std::cout << qtyAfter << std::endl;

    if (table.empty() || qtyBefore == qtyAfter) {
      std::cout << "\n-- Incorrect file path! Try again! --" << std::endl;
    } else {
      std::cout << "\n-------------   Succes!   -----------" << std::endl;
      isPathIncorrect = false;
    }
  }
}

void readSongsFromFile(std::string file_path, SeparateChaningHash<std::string, Song> &table) {
  std::ifstream dataFile;
  std::string lineFull, lineElement;
  std::string arrLines[100000];
  int qty = 0, r;
  std::string *oneLineArray;

  dataFile.open(file_path);

  // split by lines
  while (std::getline(dataFile, lineFull)) {
    arrLines[qty] = lineFull;
    qty++;
  }

  // Split the line using delimiter
  for (int i = 0; i < qty - 1; i++) {
    oneLineArray = new std::string[3];
    std::istringstream istream(arrLines[i]);
    r = 0;

    while (std::getline(istream, lineElement, '\t')) {
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

void addSongToHashTable( std::string artist, std::string title, std::string duration, SeparateChaningHash<std::string, Song> &table) {
  // Test
  //std::cout << "Artist: " << artist << ", Title: " << title << ", DUration: " << duration << std::endl;


  Song songObj = Song(title, artist, duration);
  //table.insert(artist, songObj);
  table.put(artist, songObj);
  //table[artist] = songObj;
 
}

void printMenu(SeparateChaningHash<std::string, Song> &table) {
  bool passCheck = false;
  std::string option;

  while (!passCheck) {
    std::cout << std::endl
              << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "-------------    Menu     -----------" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Add tracks from a file..............1" << std::endl;
    std::cout << "Save to a file......................2" << std::endl;
    std::cout << "Search by artist/band name..........3" << std::endl;
    std::cout << "Remove specific track(s)............4" << std::endl;
    std::cout << "Exit................................5" << std::endl;
    std::cout << "-------------------------------------" << std::endl
              << std::endl;

    std::cout << "Select option please: ";
    std::cin >> option;

    if (option == "1")  {
      readFile(table);
      passCheck = true;
    }  else if (option == "2")  {
      //saveToFile(table);
      passCheck = true;
    }  else if (option == "3") {
      std::cout << "-3" << std::endl;
      passCheck = true;
    } else if (option == "4") {
      std::cout << "-4" << std::endl;
      passCheck = true;
    } else if (option == "5") {
      std::cout << "\n-------------  Goodbye!  ------------" << std::endl
                << std::endl;
      passCheck = true;
      exit(1);
    } else {
      std::cout << "\n--------  Incorrect option!  --------" << std::endl;
    }
  }
}


/*
// Save file
void saveToFile(SeparateChaningHash<std::string, Song> &table) {
  std::ofstream file;

  std::string file_name;
  std::cout << "Enter file name: "; 
  std::cin >> file_name;

  file.open(file_name);
  std::string line = "";

  std::vector<std::string> artists_name = table.getKeys();


  for(std::string name: artists_name) {
    Song song = "table[name]";

    line = "";
    line += song.getArtist() + "\t" + song.getTitle() + "\t" + song.getDuration();

    file << line << std::endl;
  }

  file.close();

}

*/