//
//  LinkedList.cpp
//  Thesaurus
//
//  Created by Ahmer Mughal on 10/03/2020.
//  Copyright © 2020 Ahmer Mughal. All rights reserved.
//

#include "LinkedList.h"

LinkedList::LinkedList(){
    alphaHead = NULL;
    alphaTail = NULL;
    head = NULL;
    tail = NULL;
    readFromFile();
}


void LinkedList::createAlphabetNodes(){
    alphabetNode* alphaNode = new alphabetNode;
    alphabetNode* temp = new alphabetNode;
    
    alphaNode->alphabet = 'a';
    alphaNode->next = NULL;
    alphaHead = alphaNode;
    temp = alphaNode;
    
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

wordNode* LinkedList::traverseByWord(alphabetNode* node,string word){
    for(wordNode* temp = node->words; temp != NULL; temp= temp->next){
        if(temp->word == word){
            return temp;
        }
    }
    return NULL;
}

alphabetNode* LinkedList::traverseAlphabetByChar(char c){
    if(alphaHead != NULL){
        for(alphabetNode* temp = alphaHead; temp != NULL; temp = temp->next){
            if(temp->alphabet == c){
                return temp;
            }
        }
    }
    return NULL;
}

void LinkedList::insertSynonymAtWord(alphabetNode* node,string word, string synonym){
    
    synNode* newNode = new synNode;
    newNode->word = synonym;
    newNode->next = NULL;
    wordNode* wordNode = traverseByWord(node, word);
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

void LinkedList::displayAllWordsByChar(alphabetNode *node){
    wordNode* wordTemp = node->words;
    for(int i= 0; i < node->wordListSize; i++){
        if(wordTemp != NULL)
            cout<<"\t"<<wordTemp->word<<endl;
        displayAllSynoymsByWord(wordTemp);
        wordTemp = wordTemp->next;
    }
}

void LinkedList::displayLinkedListChar(){
    alphabetNode* temp = alphaHead;
    while (temp != NULL){
        cout<<temp->alphabet<<endl;
        cout<<temp->wordListSize<<endl;
        displayAllWordsByChar(temp);
        temp = temp->next;
    }
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
}

void LinkedList::displayAllSynoymsByWord(wordNode* node){
    synNode* synTemp = node->synonyms;
    for(int i= 0; i < node->synListSize; i++){
        if(synTemp != NULL)
            cout<<"\t\t"<<synTemp->word<<endl;
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

void LinkedList::insertWordAtAlphaNode(alphabetNode *alphaNode, string newWord){    
    wordNode* wordHead = alphaNode->words;
    wordNode* newNode = new wordNode;
    newNode->word = newWord;
    newNode->next = NULL;
    newNode->synonyms = NULL;
    
    if(alphaNode->words ==  NULL){
        alphaNode->words = newNode;
        alphaNode->wordListSize++;
    }else{
        wordNode* temp = wordHead;
        while(temp->next != NULL){
            temp= temp->next;
        }
        temp->next = newNode;
        alphaNode->wordListSize++;
    }
    
}

alphabetNode* LinkedList::getAlphaNodeByChar(char c){
    alphabetNode* node = traverseAlphabetByChar(c);
    if(node != NULL) return node;
    else return insertAlphabetNode(c);
}

alphabetNode* LinkedList::insertAlphabetNode(char c){
    
    alphabetNode* newNode = new alphabetNode;
    newNode->alphabet = c;
    newNode->next = NULL;
    newNode->words = NULL;
    
    if(alphaHead == NULL){
        alphaHead = newNode;
        alphaTail = newNode;
    }else{
        alphabetNode* temp = alphaHead;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
        alphaTail = newNode;
    }
    return newNode;
}

void LinkedList::findAndDisplaySynoymsByWord(alphabetNode* node,string word){
    wordNode* currentWordNode = traverseByWord(node, word);
    displayAllSynoymsByWord(currentWordNode);
    
}

void LinkedList::writeListToFile(){
    ofstream outFile("Thesaurus.txt");
    
    alphabetNode* alphaTemp = alphaHead;
    
    while(alphaTemp != NULL){
        
        wordNode* temp = alphaTemp->words;
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
        alphaTemp = alphaTemp->next;
    }
    
    
    outFile.close();
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
            alphabetNode* alphaNode = getAlphaNodeByChar(pch[0]);
            insertWord(pch);
            insertWordAtAlphaNode(alphaTail, pch);
            pch = strtok(NULL, ":");
            while(pch!= NULL){
                insertSynonymAtWord(alphaNode, alphaNode->words->word, string(pch));
                pch = strtok(NULL, ":");
            }
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

                alphabetNode* alphaNode = getAlphaNodeByChar(pch[0]);
                insertWord(pch);
                insertWordAtAlphaNode(alphaTail, pch);
                pch = strtok(NULL, ":");
                while(pch!= NULL){
                    insertSynonymAtWord(, string(pch));

                    pch = strtok(NULL, ":");
                }
            }
            
        }
    }
    inFile.close();
}
