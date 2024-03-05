#include "Sector.h"
Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED) {
        // TODO: Calculate the distance to the Earth, and generate the sector code
}

Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary

    // Assuming parent should not be responsible for deleting this node, only the children are deleted.
}
Sector& Sector::operator=(const Sector& other) {
    if (this == &other) {
        return *this;
    }

    x = other.x;
    y = other.y;
    z = other.z;
    distance_from_earth = other.distance_from_earth;
    sector_code = other.sector_code;
    left = other.left;
    right = other.right;
    parent = other.parent;
    color = other.color;

    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return (x == other.x && y == other.y && z == other.z &&
            distance_from_earth == other.distance_from_earth &&
            sector_code == other.sector_code &&
            left == other.left && right == other.right &&
            parent == other.parent && color == other.color);
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}
