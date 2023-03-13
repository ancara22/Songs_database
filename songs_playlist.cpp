#include "hash.h"
#include <iostream>

int main() {
  bool isPathIncorrect = true;
  std::string file_path;
  
  //Read data from file
  while(isPathIncorrect)  {
    std::cout << "Enter absolute/relative file path(or enter Y to read the default file): ";
    std::cin >> file_path;
    if(file_path == "Y") {
      file_path = "./sample_song_data.dat";
    }

    // createSongsFromFile(file_path, "!!!!&vehiclesBase");

    if("!!!!vehiclesBase.size() == 0") {
      std::cout << "\n----------------------- Incorrect file path! Try again! -------------------------\n\n";
    } else  {
      std::cout << "\n-----------------------------------  Succes! ------------------------------------";
      isPathIncorrect = false;
    }

  }
  

  return 0;
}
