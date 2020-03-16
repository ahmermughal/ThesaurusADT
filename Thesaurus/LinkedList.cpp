//
//  LinkedList.cpp
//  Thesaurus
//
//  Created by Ahmer Mughal on 10/03/2020.
//  Copyright © 2020 Ahmer Mughal. All rights reserved.
//

#include "LinkedList.h"

LinkedList::LinkedList(){
    head = NULL;
    tail = NULL;
    readFromFile();
}



void LinkedList::insertWordAtStart(string newWord){
    wordNode* newNode = new wordNode;
    newNode->word = newWord;
    
    if(head == NULL){
        head = newNode;
        tail = newNode;
    }else{
        newNode->next = head->next;
        head = newNode;
    }
    newNode = NULL;
}

wordNode* LinkedList::traverseByWord(string word){
    for(wordNode* temp = head; temp != NULL; temp= temp->next){
        if(temp->word == word){
            return temp;
        }
    }
    return NULL;
}

void LinkedList::insertSynonymAtWord(string word, string synonym){
    
    synNode* newNode = new synNode;
    newNode->word = synonym;
    newNode->next = NULL;
    wordNode* wordNode = traverseByWord(word);
    //MARK - wordNode returns null if 2 words are added.
    if(wordNode->synListSize == 0){
        wordNode->synonyms = newNode;
        wordNode->synListSize++;
    }else{
        synNode* prevNode = traverseSynByIndex(wordNode->synListSize, wordNode->synonyms);
        prevNode->next = newNode;
        wordNode->synListSize++;
    }
}

synNode* LinkedList::traverseSynByIndex(int index, synNode* head){
    synNode* temp;
    temp = head;
    for(int i = 1; i < index; i++){
        temp = temp->next;
    }
    return temp;
}

void LinkedList::displayLinkedList(){
    wordNode* temp = head;
    while (temp != NULL){
        cout<<temp->word<<endl;
        displayAllSynoymsByWord(temp);
        temp = temp->next;
    }
    system( "read -n 1 -s -p \"Press any key to continue...\"" );


}

void LinkedList::writeListToFile(){
    ofstream outFile("Thesaurus.txt");
    wordNode* temp = head;
    while (temp != NULL){
        //cout<<temp->word;
        outFile<< temp->word;
        synNode* synTemp = temp->synonyms;
        for(int i= 0; i < temp->synListSize; i++){
            if(synTemp != NULL)
                outFile<<":"<<synTemp->word;
            synTemp = synTemp->next;
        }
        outFile<<endl;
        temp = temp->next;
    }
    outFile.close();
}

void LinkedList::displayAllSynoymsByWord(wordNode* node){
    synNode* synTemp = node->synonyms;
    for(int i= 0; i < node->synListSize; i++){
        if(synTemp != NULL)
        cout<<"\t"<<synTemp->word<<endl;
        synTemp = synTemp->next;
    }
}

void LinkedList::insertWord(string newWord){
    
    wordNode* newNode = new wordNode;
    newNode->word = newWord;
    newNode->next = NULL;
    newNode->synonyms = NULL;
    
    if(head ==  NULL){
        head = newNode;
        tail = newNode;
    }else{
        wordNode* temp = head;
        while(temp->next != NULL){
            temp= temp->next;
        }
        temp->next = newNode;
    }
}

void LinkedList::findAndDisplaySynoymsByWord(string word){
    wordNode* currentWordNode = traverseByWord(word);
    displayAllSynoymsByWord(currentWordNode);

}

void LinkedList::readFromFile(){
    string fileName = "Thesaurus.txt";
    ifstream inFile(fileName);
    string nextItem;
    
    if(inFile >> nextItem){
        int strSize = nextItem.length();
        char str[strSize+1];
        strcpy(str, nextItem.c_str());
        char* pch;
        pch = strtok(str, ":");
        if(pch!= NULL){
            
            insertWord(pch);
            pch = strtok(NULL, ":");
        }
        while(pch!= NULL){
            insertSynonymAtWord(head->word, string(pch));
            pch = strtok(NULL, ":");
        }
        
        while (inFile >> nextItem) {
            int strSize = nextItem.length();
            char str[strSize+1];
            strcpy(str, nextItem.c_str());
            char* pch;
            string currentWord;
            pch = strtok(str, ":");
            currentWord = pch;
            if(pch!= NULL){
                
                insertWord(pch);
                pch = strtok(NULL, ":");
            }
            while(pch!= NULL){
                insertSynonymAtWord(currentWord, string(pch));

                pch = strtok(NULL, ":");
            }
        }
    }
    inFile.close();
}
