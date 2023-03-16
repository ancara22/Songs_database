#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "hash.h"
#include "functions.h"
#include "track.h"
#include <string>


std::string artist = "ACDC";
std::string title = "Thunderstruck";
std::string duration = "243";
Track track = Track(title, artist, duration);
SeparateChaningHash<std::string, Track> hashTable;
std::vector<Node<std::string, Track>*> searchResult;



TEST_CASE("track", "[componet]") {
    REQUIRE(track.getArtist() == artist);
    REQUIRE(track.getTitle() == title);
    REQUIRE(track.getDuration() == duration);
}


TEST_CASE("hash", "[table]") {
    REQUIRE(hashTable.getSize() == 0);
    REQUIRE(hashTable.empty() == true);
    REQUIRE(hashTable.contains(artist) != true);
    REQUIRE(hashTable.getAllNodes().size() == 0);
}


TEST_CASE("put", "[table]") {
    hashTable.put(artist, track);

    REQUIRE(hashTable.contains(artist) == true);
    REQUIRE(hashTable.getAllNodes().size() == 1);

    Node<std::string, Track> *node = hashTable.getAllNodes()[0];

    REQUIRE(node->key == artist);
    REQUIRE(node->value.getArtist() == artist);
    REQUIRE(node->value.getTitle() == title);
    REQUIRE(node->value.getDuration() == duration);
    REQUIRE(node->next == nullptr);
}


TEST_CASE("resize", "[table]") {
    size_t oldCapacity = hashTable.getCapacity();
    hashTable.resize(2 * oldCapacity);
    size_t newCapacity = hashTable.getCapacity();

    REQUIRE(newCapacity == oldCapacity*2);
}


TEST_CASE("search", "[table]") {
    std::vector<Node<std::string, Track>*> searchResult =  hashTable.search(artist);

    REQUIRE(searchResult.size() == 1);

    //add a different track and artist
    Track track2 = Track("track 1", "50 Cent", "333");
    hashTable.put("50 Cent", track2);
    searchResult =  hashTable.search(artist);   
    REQUIRE(searchResult.size() == 1);

    //add a track with the same artist name
    Track track3 = Track("track 2", artist, "332");
    Track track4 = Track("track 3", artist, "34");
    hashTable.put(artist, track3);
    hashTable.put(artist, track4);

    searchResult =  hashTable.search(artist); 
    REQUIRE(searchResult.size() == 3);

    //search an element that doesnt exist
    searchResult =  hashTable.search("dd"); 
    REQUIRE(searchResult.size() == 0);
}


TEST_CASE("remove", "[table]") {
    searchResult = hashTable.search(artist);

    //delete 1
    hashTable.remove(artist, "track 2");
    searchResult = hashTable.search(artist);

    REQUIRE(searchResult.size() == 2);

    //delete all
    hashTable.remove(artist);
    searchResult = hashTable.search(artist);
    
    REQUIRE(searchResult.size() == 0);
    
}


TEST_CASE("getAllNodes", "[table]") {
    std::vector<Node<std::string, Track>*>  allNodes = hashTable.getAllNodes();
    
    REQUIRE(allNodes.size() == 1);

    Track track2 = Track("track 1", "50 Cent", "333");
    hashTable.put("50 Cent", track2);

    allNodes = hashTable.getAllNodes();
    REQUIRE(allNodes.size() == 2);

    hashTable.remove("50 Cent");
    allNodes = hashTable.getAllNodes();
    REQUIRE(allNodes.size() == 0);

    //delete all
    searchResult = hashTable.search(artist);
    
    REQUIRE(searchResult.size() == 0);
    
}


TEST_CASE("addSongToHashTable", "[functions]") {
    REQUIRE(hashTable.getAllNodes().size() == 0);

    addSongToHashTable(artist, title, duration, hashTable);

    REQUIRE(hashTable.getAllNodes().size() == 1);

    addSongToHashTable(artist, "title1", "333", hashTable);
    addSongToHashTable(artist, "title2", "555", hashTable);

    REQUIRE(hashTable.getAllNodes().size() == 3);

    std::vector<Node<std::string, Track>*> searchResult =  hashTable.search(artist);

    REQUIRE(searchResult.size() == 3);
}


TEST_CASE("readSongsFromFile", "[functions]") {
    int sizeBefore = hashTable.getAllNodes().size();
    readSongsFromFile("./sample_song_data.dat", hashTable);
    int sizeAfter = hashTable.getAllNodes().size();
    REQUIRE(sizeBefore <= sizeAfter);
}