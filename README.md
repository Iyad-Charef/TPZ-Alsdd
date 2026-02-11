# Optimized Word Search in Binary Search Trees (BST)

TP 2 – Khawarizm Project  
By: **Charef Iyad**  
Section D – Group 13  
Language: **Z (custom language)**

---

## Overview
This project implements an **optimized word search system** using multiple Binary Search Trees (BSTs).  
It explores tree construction, balancing techniques, and efficient search operations for single words and ranges.  
The program is written in the **Z language**, a custom academic language, although you can find the compiled-to-c file.

---

## Features
- **File Generation**: Create a file with randomly generated words (`File_gen_word`).
- **Tree Construction**: Build three BSTs (`Createbst1`, `Createbst2`, `Createbst3`) with different balancing strategies.
- **Operations on Trees**:
  - Insert words into BSTs
  - Count words starting with specific letters (X, Y, Z, a)
  - Compute tree depth
  - Inorder traversal
  - Level-by-level word counts
- **Search Operations**:
  - Single word search across BST1, BST2, BST3
  - Range queries: find all words between two given bounds
- **Optimizations**:
  - Rotations (`Rol`, `Ror`) for balancing
  - Range queries using in-order successor (`Next_inordre`)
  - Efficient smallest-value search (`Searchsmallest`)

---

## Usage
1. Run the program to access the **menu-driven interface**:
   - **Part I**: Generate files, construct BSTs, and verify operations.
   - **Part II**: Perform word search operations (single word or range).
   - **Quit**: Exit the program.

2. Example menu options:
   - Generate a file with random words
   - Build BSTs from the file
   - Count words starting with X, Y, Z, a
   - Compute depth and traverse trees
   - Search for a word or perform range queries

---

## Notes
- Words are stored in BSTs based on their first character.
- Rotations are applied to maintain balance depending on word prefixes.
- The project demonstrates **tree balancing, search efficiency, and range queries** in a pedagogical setting.

---

Made for **ESI Practical Work – TP Khawarizm (Optimized Word Search)**.
