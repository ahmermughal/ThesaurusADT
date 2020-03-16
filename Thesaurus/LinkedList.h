//
//  LinkedList.hpp
//  Thesaurus
//
//  Created by Ahmer Mughal on 10/03/2020.
//  Copyright © 2020 Ahmer Mughal. All rights reserved.
//

#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct synNode{
    string word;
    synNode* next;
};


struct wordNode{
    string word;
    int synListSize = 0;
    synNode* synonyms;
    wordNode* next;
};

struct alphabetNode{
    char alphabet;
    int wordListSize = 0;
    wordNode* words;
    alphabetNode* next;
};

class LinkedList{
private:
    wordNode* head;
    wordNode* tail;
    wordNode* traverseByWord(string word);
    synNode* traverseSynByIndex(int index, synNode* head);
    void displayAllSynoymsByWord(wordNode* node);
    
public:
    LinkedList();
    void insertWordAtStart(string newWord);
    void insertSynonymAtWord(string word, string synonym);
    void displayLinkedList();
    void insertWord(string newWord);
    void findAndDisplaySynoymsByWord(string word);
    void writeListToFile();
    void readFromFile();

};

#endif /* LinkedList_hpp */
