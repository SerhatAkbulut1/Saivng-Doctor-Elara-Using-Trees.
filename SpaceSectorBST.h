#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

#include "Sector.h"

class SpaceSectorBST {
  
public:
    Sector *root;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void readSectorsFromFile(const std::string& filename); 
    void insertSectorByCoordinates(int x, int y, int z);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
    void inOrderTraversal(Sector *currentNode);
    void preOrderTraversal(Sector *currentNode);
    void postOrderTraversal(Sector *currentNode);
    Sector* insertRecursive(Sector *currentSector, Sector *findSector);
    Sector *findMax(Sector *currentNode);
    void deleteRecursive(Sector *&currentNode, Sector *findSector);
    void destructorTree(Sector *sector);
    Sector * inOrderTraversalFind(Sector *currentNode, std::string sectorCode);
};

#endif // SPACESECTORBST_H
