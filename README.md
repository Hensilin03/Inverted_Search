# Inverted Search using C

This project is a simple implementation of an **Inverted Search system in C**.
The program reads multiple text files, extracts the words, and builds a database that records **which word appears in which file and how many times it occurs**.

To manage the data efficiently, the project uses a **hash table combined with linked lists**, which makes words searching across many files faster and easier.

## Project Overview

Normally, searching for a word across several files means checking each file one by one.
An **inverted search system** solves this by creating an index of all the words first.

Each word in the index keeps track of the files where it appears and the number of times it occurs in each file.

Example:

```
word : apple

file1.txt → 3 times
file3.txt → 1 time
```

This approach allows the program to quickly find where a word exists without scanning every file repeatedly.

## Features

* Builds an **inverted index** from multiple text files
* Uses **hash tables and linked lists** to store word data efficiently
* Keeps track of:
  * the word
  * the file name
  * how many times the word appears in that file
* Allows users to **search for words** across all indexed files
* Supports **updating the database** when new files are added
* Displays the entire database in a readable format
* Provides an option to **save the database as a backup file**

## File Structure

* **main.c / main.h**    – Contains the main function and the structure definitions used throughout the program.
* **create_database.c**  – Responsible for reading input files, extracting words, and building the inverted index.
* **search_database.c**  – Handles searching for a word and displaying the files where it appears.
* **update_database.c**  – Adds new files to the existing database without rebuilding everything.
* **display_database.c** – Displays the contents of the database.
* **save_database.c**    – Saves the database into a backup file so it can be reused later.

---

## Data Structure Used

The program uses a **hash table along with a multi-level linked list structure**.

```
Hash Table (26 indexes)
      ↓
Main Node
      ↓
Sub Node (word)
      ↓
File Node (file name + word count)
```

* **Hash Table** – Contains 26 indexes based on the first character of the word.
* **Main Node**  – Points to the list of words belonging to that index.
* **Sub Node**   – Stores the word and the number of files containing it.
* **File Node**  – Stores the file name and how many times the word appears in that file.

## Compilation
```
gcc *.c -o inverted_search
```

## Execution
```
./inverted_search file1.txt file2.txt file3.txt
```

## Menu Options

```
1. Create Database
2. Display Database
3. Search Database
4. Update Database
5. Save Database
6. Exit
```

## Input Rules

* Input files must be provided through **command-line arguments**
* Files must **exist and should not be empty**
* Duplicate files are ignored
* Words are indexed using the **first character as the hash key**

## Concepts Used

This project applies several important concepts from **C programming and data structures**, including:

* Hash Tables
* Linked Lists
* Dynamic Memory Allocation
* File Handling
* String Processing
* Modular Programming

## Author

**Hensilin Rithista S**
B.Tech Electronics and Communication Engineering
