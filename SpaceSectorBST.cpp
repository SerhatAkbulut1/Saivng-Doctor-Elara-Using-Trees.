#include "SpaceSectorBST.h"
#include <cmath>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;
vector<Sector*> sectors_not_local;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    destructorTree(root);
}
void SpaceSectorBST::destructorTree(Sector* sector){
    if (sector != nullptr) {
        destructorTree(sector->left);
        destructorTree(sector->right);
        delete sector;
    }
}

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        return;
    }
    std::vector<Sector> sectors;

    std::string line;
    std::getline(inputFile, line);

    while (std::getline(inputFile, line)) {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream iss(line);
        int x, y, z;

        if (iss >> x >> y >> z) {
            Sector sector(x, y, z);
            sectors.push_back(sector);
        }
    }

    for (int i = 0; i < sectors.size(); ++i) {
        insertSectorByCoordinates(sectors[i].x,sectors[i].y,sectors[i].z);
    }

    inputFile.close();
}

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    Sector* newSector = new Sector(x, y, z);

    double distance = sqrt(pow(0-newSector->x,2)+pow(0-newSector->y,2)+pow(0-newSector->z,2));
    newSector->distance_from_earth = distance;
    newSector->sector_code += std::to_string((int) distance);
    if (newSector->x == 0) {
        newSector->sector_code += 'S';
    } else if (newSector->x > 0) {
        newSector->sector_code  += 'R';
    } else {
        newSector->sector_code  += 'L';
    }

    if (newSector->y == 0) {
        newSector->sector_code  += 'S';
    } else if (newSector->y > 0) {
        newSector->sector_code  += 'U';
    } else {
        newSector->sector_code  += 'D';
    }

    if (newSector->z == 0) {
        newSector->sector_code  += 'S';
    } else if (newSector->z> 0) {
        newSector->sector_code  += 'F';
    } else {
        newSector->sector_code  += 'B';
    }
    root  = insertRecursive(root, newSector);
    sectors_not_local.push_back(newSector);

}
Sector* SpaceSectorBST::insertRecursive(Sector* currentSector, Sector* findSector) {
    if (currentSector == nullptr) {
        return findSector;
    } else if ((findSector->x < currentSector->x) ||
               (findSector->x == currentSector->x && findSector->y < currentSector->y) ||
               (findSector->x == currentSector->x && findSector->y == currentSector->y && findSector->z < currentSector->z)) {
        currentSector->left = insertRecursive(currentSector->left, findSector);
    } else if ((findSector->x > currentSector->x) ||
               (findSector->x == currentSector->x && findSector->y > currentSector->y) ||
               (findSector->x == currentSector->x && findSector->y == currentSector->y && findSector->z > currentSector->z)) {
        currentSector->right = insertRecursive(currentSector->right, findSector);
    }
    return currentSector;
}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    Sector* findSector = nullptr;
    findSector = inOrderTraversalFind(root,sector_code);
    if (findSector != nullptr) {
        deleteRecursive(root, findSector);
    }
}


void SpaceSectorBST::deleteRecursive(Sector* &currentNode,Sector* findSector) {
    if (currentNode == nullptr ) {
        return ;
    }
    if ((findSector->x < currentNode->x ) ||
        (findSector->x == currentNode->x && findSector->y < currentNode->y) ||
        (findSector->x == currentNode->x && findSector->y == currentNode->y && findSector->z < currentNode->z))
    {
        deleteRecursive(currentNode->left,findSector);
    }
    else if ((findSector->x > currentNode->x ) ||
        (findSector->x == currentNode->x && findSector->y > currentNode->y) ||
        (findSector->x == currentNode->x && findSector->y == currentNode->y && findSector->z > currentNode->z))
    {
        deleteRecursive(currentNode->right,findSector);
    }
    else {
        if (currentNode->left != nullptr && currentNode->right != nullptr) {
            Sector* maxRight = findMax(currentNode->right);
            currentNode->x = maxRight->x;
            currentNode->y = maxRight->y;
            currentNode->z = maxRight->z;
            currentNode->distance_from_earth = maxRight->distance_from_earth;
            currentNode->sector_code = maxRight->sector_code;
            deleteRecursive(currentNode->right, findSector);
        } else {
            Sector* deletingSector = currentNode;
            if (currentNode->left == nullptr) {
                currentNode = currentNode->right;
            } else if (currentNode->right == nullptr) {
                currentNode = currentNode->left;
            }
            delete deletingSector;
        }
    }
    return ;
}
Sector* SpaceSectorBST::findMax(Sector* currentNode) {
    if (currentNode->left != nullptr) {
        return findMax(currentNode->left);
    }
    return currentNode;
}
void SpaceSectorBST::displaySectorsInOrder() {
    cout<<"Space sectors inorder traversal:"<<endl;
    inOrderTraversal(root);
    cout<<endl;
}

void SpaceSectorBST::displaySectorsPreOrder() {
    cout<<"Space sectors preorder traversal:"<<endl;
    preOrderTraversal(root);
    cout<<endl;
}

void SpaceSectorBST::displaySectorsPostOrder() {
    cout<<"Space sectors postorder traversal:"<<endl;
    postOrderTraversal(root);
    cout<<endl;
}

void SpaceSectorBST::inOrderTraversal(Sector* currentNode) {
    if (currentNode != nullptr) {
        inOrderTraversal(currentNode->left);
        std::cout<<currentNode->sector_code<<endl;
        inOrderTraversal(currentNode->right);
    }
}

void SpaceSectorBST::preOrderTraversal(Sector* currentNode) {
    if (currentNode != nullptr) {
        std::cout<<currentNode->sector_code<<endl;
        preOrderTraversal(currentNode->left);
        preOrderTraversal(currentNode->right);
    }
}

void SpaceSectorBST::postOrderTraversal(Sector* currentNode) {
    if (currentNode != nullptr) {
        postOrderTraversal(currentNode->left);
        postOrderTraversal(currentNode->right);
        std::cout <<currentNode->sector_code<<endl;
    }
}
Sector* SpaceSectorBST::inOrderTraversalFind(Sector* currentNode,std::string sectorCode) {
    if (currentNode != nullptr) {
        Sector* leftResult = inOrderTraversalFind(currentNode->left, sectorCode);
        if (leftResult != nullptr) {
            return leftResult;
        }
        if (currentNode->sector_code == sectorCode) {
            return currentNode;
        }
        Sector* rightResult = inOrderTraversalFind(currentNode->right, sectorCode);
        if (rightResult != nullptr) {
            return rightResult;
        }
    }

    return nullptr;
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    Sector* currentNode = root;
    Sector* findSector = inOrderTraversalFind(root,sector_code);

    if(findSector == nullptr){
        return path;
    }

    while (currentNode != nullptr) {
        path.push_back(currentNode);
        if (sector_code == currentNode->sector_code) {
            return path;
        } else if (findSector->x < currentNode->x ||
                   (findSector->x == currentNode->x && findSector->y < currentNode->y) ||
                   (findSector->x == currentNode->x && findSector->y == currentNode->y && findSector->z < currentNode->z)) {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
    }
    return path;

}
void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
    if (path.empty()) {
        std::cout << "A path to Dr. Elara could not be found. "<< std::endl;
        return;
    }else{
        std::cout << "The stellar path to Dr. Elara: ";

        for (const Sector* sector : path) {
            std::cout << sector->sector_code;
            if (sector != path.back()) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
}
