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
    alphabetNode* alphaHead;
    alphabetNode* alphaTail;
    
    wordNode* traverseByWord(alphabetNode* node,string word);
    synNode* traverseSynByIndex(int index, synNode* head);
    void displayAllSynoymsByWord(wordNode* node);
    void displayAllWordsByChar(alphabetNode* node);
    alphabetNode* traverseAlphabetByChar(char c);
    alphabetNode* insertAlphabetNode(char c);
    
public:
    LinkedList();
    void insertSynonymAtWord(alphabetNode* nord, string word, string synonym);
    void displayLinkedList();
    void displayLinkedListChar();
    void insertWordAtAlphaNode(alphabetNode* alphaNode ,string newWord);
    void findAndDisplaySynoymsByWord(alphabetNode* node, string word);
    void writeListToFile();
    void readFromFile();
    alphabetNode* getAlphaNodeByChar(char c);
    void deleteWordSynonyms(string word);
    void deleteWord(string word);


};

#endif /* LinkedList_hpp */
