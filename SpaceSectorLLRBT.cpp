#include <algorithm>
#include <cmath>
#include "SpaceSectorLLRBT.h"

using namespace std;
vector<Sector*> sectors_not_local2;
SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
    // according to the given comparison critera based on the sector coordinates.
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

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    // TODO: Free any dynamically allocated memory in this class.
    destructorLLRBTTree(root);
}
void SpaceSectorLLRBT::destructorLLRBTTree(Sector* sector){
    if (sector != nullptr) {
        destructorLLRBTTree(sector->left);
        destructorLLRBTTree(sector->right);
        delete sector;
    }
}
void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    // TODO: Instantiate and insert a new sector into the space sector LLRBT map 
    // according to the coordinates-based comparison criteria.
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
    newSector->color = true;
    root = insertRecursive(root,newSector);
    root->color = false;
    sectors_not_local2.push_back(newSector);

}
Sector* SpaceSectorLLRBT::insertRecursive(Sector* currentNode, Sector* newSector) {
    if(currentNode == nullptr){
        return newSector;
    }
    if((newSector->x < currentNode->x) ||
       (newSector->x == currentNode->x && newSector->y < currentNode->y) ||
       (newSector->x == currentNode->x && newSector->y == currentNode->y && newSector->z < currentNode->z)){
        currentNode->left = insertRecursive(currentNode->left,newSector);
    }else if((newSector->x > currentNode->x) ||
             (newSector->x == currentNode->x && newSector->y > currentNode->y) ||
             (newSector->x == currentNode->x && newSector->y == currentNode->y && newSector->z > currentNode->z)){
        currentNode->right = insertRecursive(currentNode->right,newSector);
    }else{
        currentNode;
    }

    if(isRed(currentNode->right)&&!isRed(currentNode->left)){
        currentNode = rotateLeft(currentNode);
        bool temp = currentNode->color;
        currentNode->color = currentNode->left->color;
        currentNode->left->color = temp;
    }
    if (isRed(currentNode -> left) &&
        isRed(currentNode -> left -> left)){
        currentNode = rotateRight(currentNode);
        bool temp = currentNode->color;
        currentNode->color = currentNode->right->color;
        currentNode->right->color = temp;
    }
    if (isRed(currentNode -> left) && isRed(currentNode -> right)){
        currentNode -> color = !currentNode -> color;
        currentNode -> left -> color = false;
        currentNode -> right -> color = false;
    }
    return currentNode;

}

Sector* SpaceSectorLLRBT::rotateLeft(Sector* sector) {
    Sector* rightChild = sector->right;
    Sector* rightChild_Left = rightChild->left;

    rightChild->left = sector;
    sector->right = rightChild_Left;

    return rightChild;
}

Sector* SpaceSectorLLRBT::rotateRight(Sector* sector) {
    Sector *leftChild = sector->left;
    Sector *leftChildRight = leftChild->right;

    leftChild->right = sector;
    sector->left = leftChildRight;

    return leftChild;
}
bool SpaceSectorLLRBT::isRed(Sector* node) {
    if (node == NULL){
        return 0;
    }
    return (node -> color == true);
}

void SpaceSectorLLRBT::displaySectorsInOrder() {
    // TODO: Traverse the space sector LLRBT map in-order and print the sectors 
    // to STDOUT in the given format.
    cout<<"Space sectors inorder traversal:"<<endl;
    inOrderTraversal(root);
    cout<<endl;
}

void SpaceSectorLLRBT::displaySectorsPreOrder() {
    // TODO: Traverse the space sector LLRBT map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout<<"Space sectors preorder traversal:"<<endl;
    preOrderTraversal(root);
    cout<<endl;
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    // TODO: Traverse the space sector LLRBT map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout<<"Space sectors postorder traversal:"<<endl;
    postOrderTraversal(root);
    cout<<endl;
}

void SpaceSectorLLRBT::inOrderTraversal(Sector* currentNode) {
    if (currentNode != nullptr) {
        inOrderTraversal(currentNode->left);
        if(currentNode->color){
            std::cout<<"RED sector: "<<currentNode->sector_code<<endl;
        }else{
            std::cout<<"BLACK sector: "<<currentNode->sector_code<<endl;
        }

        inOrderTraversal(currentNode->right);
    }
}

void SpaceSectorLLRBT::preOrderTraversal(Sector* currentNode) {
    if (currentNode != nullptr) {
        if(currentNode->color){
            std::cout<<"RED sector: "<<currentNode->sector_code<<endl;
        }else{
            std::cout<<"BLACK sector: "<<currentNode->sector_code<<endl;
        }
        preOrderTraversal(currentNode->left);
        preOrderTraversal(currentNode->right);
    }
}

void SpaceSectorLLRBT::postOrderTraversal(Sector* currentNode) {
    if (currentNode != nullptr) {
        postOrderTraversal(currentNode->left);
        postOrderTraversal(currentNode->right);
        if(currentNode->color){
            std::cout<<"RED sector: "<<currentNode->sector_code<<endl;
        }else{
            std::cout<<"BLACK sector: "<<currentNode->sector_code<<endl;
        }
    }
}
std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    int number1 = 0,number2 = 0,number3 = 0;
    std::vector<Sector*> path;
    std::vector<Sector*> pathEarth;
    std::vector<Sector*> pathFindSector;
    Sector* earthSector = inOrderTraversalFind(root,"0SSS");
    Sector* findSector = inOrderTraversalFind(root,sector_code);
    std::string sectorCode ;

    if(findSector == nullptr){
        return path;
    }

    pathEarth = findPath(earthSector->sector_code, earthSector);
    std::reverse(pathEarth.begin(), pathEarth.end());
    pathFindSector = findPath(findSector->sector_code,findSector);

    for (int i = 0; i < pathEarth.size(); ++i) {
        for (int j = 0; j < pathFindSector.size(); ++j) {
            if(pathEarth[i]->sector_code == pathFindSector[j]->sector_code){
                sectorCode = pathEarth[i]->sector_code;
                number1 = i;
                number2 = j;
                number3++;
                break;
            }
        }
        if(number3 == 1){
            break;
        }
    }
    for (int a = 0; a < pathEarth.size(); ++a) {
        if(a < number1){
            path.push_back(pathEarth[a]);
        }
    }

    for (int b = 0; b < pathFindSector.size(); ++b) {
        if(b>=number2){
            path.push_back(pathFindSector[b]);
        }
    }
    return path;
}
std::vector<Sector*> SpaceSectorLLRBT::findPath(const std::string& sector_code,Sector* findSector) {
   std::vector<Sector*> path;
    Sector* currentNode = root;

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

void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
    // TODO: Print the stellar path obtained from the getStellarPath() function
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
Sector* SpaceSectorLLRBT::inOrderTraversalFind(Sector* currentNode,std::string sectorCode) {
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