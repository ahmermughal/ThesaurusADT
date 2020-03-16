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
    readFromFile();
}

// traverse words Linked List
// returns the found word node
wordNode* LinkedList::traverseByWord(alphabetNode* node,string word){   
    for(wordNode* temp = node->words; temp != NULL; temp= temp->next){
        if(temp->word == word){
            return temp;
        }
    }
    return NULL;
}

// traverse alphabet linked list
// returns the found alphabet node
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

// inserts synoynm of the passed word
void LinkedList::insertSynonymAtWord(alphabetNode* node, string word, string synonym){
    synNode* newNode = new synNode;
    newNode->word = synonym;
    newNode->next = NULL;
    wordNode* wordNode = traverseByWord(node, word);
    if(wordNode->synListSize == 0){
        wordNode->synonyms = newNode;
        wordNode->synListSize++;
    }else{
        synNode* prevNode = traverseSynByIndex(wordNode->synListSize, wordNode->synonyms);
        prevNode->next = newNode;
        wordNode->synListSize++;
    }
}

// traverse Synonym Linked List
// returns the found Synonym Node
synNode* LinkedList::traverseSynByIndex(int index, synNode* head){
    synNode* temp;
    temp = head;
    for(int i = 1; i < index; i++){
        temp = temp->next;
    }
    return temp;
}

// display all the words in the linked list
void LinkedList::displayAllWordsByChar(alphabetNode *node){
    wordNode* wordTemp = node->words;
    for(int i= 0; i < node->wordListSize; i++){
        if(wordTemp != NULL)
            cout<<"\t"<<wordTemp->word<<endl;
        displayAllSynoymsByWord(wordTemp);
        wordTemp = wordTemp->next;
    }
}

// display all the alphabets with the words and synoyms
void LinkedList::displayLinkedListChar(){
    alphabetNode* temp = alphaHead;
    while (temp != NULL){
        cout<<temp->alphabet<<endl;
        displayAllWordsByChar(temp);
        temp = temp->next;
    }
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
}
// display all the synoynms of a word
void LinkedList::displayAllSynoymsByWord(wordNode* node){
    if(node != NULL){
    synNode* synTemp = node->synonyms;
    for(int i= 0; i < node->synListSize; i++){
        if(synTemp != NULL)
            cout<<"\t\t"<<synTemp->word<<endl;
        synTemp = synTemp->next;
    }
    }

}

// inserts word at the alphabet node
void LinkedList::insertWordAtAlphaNode(alphabetNode *alphaNode, string newWord){
    wordNode* newNode = traverseByWord(alphaNode, newWord);
    if(newNode == NULL){
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
    }else{
        cout<<"Word Already Exsists!"<<endl;
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
    }
    
}

// gets alphabet or creates a new alphabet node
alphabetNode* LinkedList::getAlphaNodeByChar(char c){
    alphabetNode* node = traverseAlphabetByChar(c);
    if(node != NULL) return node;
    else return insertAlphabetNode(c);
}

// creates alphabet node
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

// find and prints synonym by word
void LinkedList::findAndDisplaySynoymsByWord(alphabetNode* node,string word){
    wordNode* currentWordNode = traverseByWord(node, word);
    if(currentWordNode == NULL){
        cout<<word<<" does not exsist!"<<endl;
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
        return;
    }
    displayAllSynoymsByWord(currentWordNode);
    
}

// writes the current multilinkedlist to file
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
// reads all the data from file
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
                insertWordAtAlphaNode(alphaTail, pch);
                pch = strtok(NULL, ":");
                while(pch!= NULL){
                    insertSynonymAtWord(alphaNode, currentWord, string(pch));

                    pch = strtok(NULL, ":");
                }
            }
            
        }
    }
    inFile.close();
}

// delete synoyms of a word
void LinkedList::deleteWordSynonyms(string word){
    
    alphabetNode* alphaNode = getAlphaNodeByChar(word.at(0));
    wordNode* currentWordNode = traverseByWord(alphaNode, word);
    if(currentWordNode != NULL){
    synNode* synNodeTemp = currentWordNode->synonyms;
    synNode* nextNode = synNodeTemp;
    while (synNodeTemp != NULL) {
        nextNode = synNodeTemp->next;
        delete synNodeTemp;
        synNodeTemp = nextNode;
    }
    currentWordNode->synListSize = 0;
    synNodeTemp = NULL;
    nextNode = NULL;
    }else{
        cout<<"Word Does Not Exsist!"<<endl;
    }
}

// delete the passed word
void LinkedList::deleteWord(string word){
    alphabetNode* alphaNode = getAlphaNodeByChar(word.at(0));
    wordNode* currentWordNode = traverseByWord(alphaNode, word);
    
    if(currentWordNode != NULL){
    alphaNode->wordListSize -=1;
    
    if(alphaNode->words == currentWordNode){
        // word is head
        cout<<"Current Word is Header"<<endl;
        alphaNode->words = alphaNode->words->next;
        delete currentWordNode;
    }else{
        wordNode* prevNode = alphaNode->words;
        
        while (prevNode->next != currentWordNode) {
            prevNode = prevNode->next;
        }
        
        if(currentWordNode->next == NULL){ // word is tail
            prevNode->next = NULL;
            delete currentWordNode;
        }else{
            // word is somewhere in middle
            prevNode->next = currentWordNode->next;
            currentWordNode->next = NULL;
            delete currentWordNode;
        }
    }
    
    alphaNode = NULL;
    currentWordNode = NULL;
    }else{
        cout<<"Word Does Not Exsist!"<<endl;
    }
}
