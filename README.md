# Saivng-Doctor-Elara-Using-Trees.

## Introduction
This repository contains code for implementing algorithms and data structures to facilitate space exploration and rescue operations. The project builds upon previous programming assignments, leveraging concepts such as Binary Search Trees (BSTs) and Left-Leaning Red-Black Trees (LLRBTs) to map space sectors and optimize traversal paths.

## Task 1: Space Sector Mapping

### 1.1 Input File and Sector Map Initialization
- Parse a DAT file containing space sector coordinates to initialize a BST representing the sector map.
- Sort sectors based on (X, Y, Z) coordinates using recursive insertion.

### 1.2 Deleting Dangerous Sectors
- Implement recursive deletion of dangerous sectors from the BST map.
- Handle leaf nodes, nodes with one child, and nodes with two children.

### 1.3 Finding a Path to Dr. Elara
- Implement BST traversal algorithms (inorder, preorder, postorder) to navigate the sector map.
- Determine the path from Earth to Dr. Elara's sector based on decoded messages.

## Task 2: Optimizing Space Sector Mapping

### 2.1 Insertion into Left-Leaning Red-Black Tree (LLRBT)
- Implement recursive node insertion into an LLRBT ensuring left-leaning red links.
- Fix LLRBT violations after insertion by rotating and flipping colors.

### 2.2 Finding an Optimized Path to Dr. Elara
- Utilize BST traversal algorithms to navigate the LLRBT map.
- Determine the optimized path from Earth to Dr. Elara's sector considering LLRBT's balanced structure.

## Implementation Tasks and Requirements

### Sector Class
- Initialize sector based on coordinates, calculate distance from Earth, and generate a unique sector code.
- Overload assignment and comparison operators.
- Implement destructor to free memory if necessary.

### SpaceSectorBST Class
- Read sectors from a file and insert them into the BST map.
- Implement functions for inserting, deleting, and displaying sectors.
- Find and print the path from Earth to Dr. Elara's sector.

### SpaceSectorLLRBT Class
- Implement similar functionality as SpaceSectorBST but using LLRBT for optimized mapping.
