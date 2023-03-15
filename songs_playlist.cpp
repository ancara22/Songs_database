#include "hash.h"
#include "song.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <cstdio>

void readSongsFromFile(std::string file_path, SeparateChaningHash<std::string, Song> &table);
void addSongToHashTable(std::string artist, std::string title, std::string duration, SeparateChaningHash<std::string, Song> &table);
void printMenu(SeparateChaningHash<std::string, Song> &table);
void readFile(SeparateChaningHash<std::string, Song> &table);
void search(SeparateChaningHash<std::string, Song> &table);
void saveToFile(SeparateChaningHash<std::string, Song> &table);
void remove(SeparateChaningHash<std::string, Song> &table);
std::set<std::string> toSet(std::vector<std::string> vect);


int main() {
  SeparateChaningHash<std::string, Song> songsTable;

  readFile(songsTable);
  printMenu(songsTable);

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
  Song songObj = Song(title, artist, duration);
  table.put(artist, songObj);
}

void printMenu(SeparateChaningHash<std::string, Song> &table) {
  bool passCheck = false;
  
  while (!passCheck) {
    std::string option;

    std::cout << std::endl;
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
    std::cout << " \n" << std::endl;

  if (option == "1")  {
      readFile(table);

    }  else if (option == "2")  {
      saveToFile(table);

    }  else if (option == "3") {
      search(table);
      std::cout << " \n" << std::endl;

    } else if (option == "4") {
      remove(table);
      
    } else if (option == "5") {
      std::cout << "\n-------------  Goodbye!  ------------" << std::endl
                << std::endl;
      passCheck = true;
      exit(1);
    } else {
      std::cout << "\n--------  Incorrect option!  --------\n" << std::endl;
    }

    
  }
}

void search(SeparateChaningHash<std::string, Song> &table) {
  
  char searchInput[100]={0};
  std::cout << "Enter artist/band name: ";
  std::cin.ignore();
	std::cin.getline(searchInput, 40);

  std::vector<Node<std::string, Song>*>  result = table.search(searchInput);
  
  if(result.size() > 0) {
    std::cout << "\n-------------------------------------" << std::endl;
    std::cout << "----------- Search Result -----------" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    for(Node<std::string, Song>* node: result) {
      std::cout << "Artist   | " << node->value.getArtist() << std::endl;
      std::cout << "Title    | " << node->value.getTitle() << std::endl;
      std::cout << "Duration | " << node->value.getDuration() << std::endl;
      std::cout << "-------------------------------------" << std::endl;
    }
  } else {
    std::cout << "\n------------  No Results  -----------";
  }
}

void remove(SeparateChaningHash<std::string, Song> &table) {
  std::string option;
  std::cout << "Remove one.............1\nRemove all.............2\n\n";
  std::cout << "Enter option: ";
  std::cin >> option;
  

  if(option == "1") {
    char artistInput[100]={0}, titleInput[100]={0};
  
    std::cout << "Enter artist/band name: ";
    std::cin.ignore();
    std::cin.getline(artistInput, 40);

    std::cout << "\nEnter song title: ";
    std::cin.getline(titleInput, 40);

    bool status = table.remove(artistInput, titleInput);

    if(status) {
      std::cout << "\n------- The Song is deleted!! -------" << std::endl;
    } else {
      std::cout << "\n----- This song does not exist! -----" << std::endl;
    }
  } else if(option == "2") {
    char artistInput[100]={0};

    std::cout << "Enter artist/band name: ";
    std::cin.ignore();
    std::cin.getline(artistInput, 40);
    std::cout << "\n------ The Songs are deleted!! ------" << std::endl;

    table.remove(artistInput);
  } else {
    std::cout << "\n--------  Incorrect option!  --------\n" << std::endl;
  }

  
}

// Save file
void saveToFile(SeparateChaningHash<std::string, Song> &table) {
  std::ofstream file;

  std::string file_name;
  std::cout << "Enter file name: "; 
  std::cin >> file_name;

  file.open(file_name);
  std::string line = "";

  std::vector<Node<std::string, Song>*> allNodes = table.getAllNodes();

  for(Node<std::string, Song>* node: allNodes) {
    Song song = node->value;

    line = "";
    line += song.getTitle() + "\t" + song.getArtist() + "\t" + song.getDuration();

    file << line << std::endl;
  }
    
  file.close();
}


