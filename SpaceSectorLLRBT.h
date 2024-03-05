#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

class SpaceSectorLLRBT {
public:
    Sector* root;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
    void inOrderTraversal(Sector *currentNode);
    void preOrderTraversal(Sector *currentNode);
    void postOrderTraversal(Sector *currentNode);
    Sector * insertRecursive(Sector *currentNode, Sector *newSector);
    //Sector *findSector(Sector *currentNode, int x, int y, int z);
    Sector* rotateRight(Sector* node);
    Sector* rotateLeft(Sector* node);
    bool isRed(Sector *node);
    std::vector<Sector *> findPath(const std::string &sector_code, Sector *findSector);
    void destructorLLRBTTree(Sector *sector);
    Sector *inOrderTraversalFind(Sector *currentNode, std::string sectorCode);
};

#endif // SPACESECTORLLRBT_H
