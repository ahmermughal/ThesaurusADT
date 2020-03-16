//
//  main.cpp
//  Thesaurus
//
//  Created by Ahmer Mughal on 10/03/2020.
//  Copyright © 2020 Ahmer Mughal. All rights reserved.
//

#include <iostream>
#include "LinkedList.h"

LinkedList list;



string makeLowerCase(string word){
    
    char str[word.length()+1];
    strcpy(str, word.c_str());
    for(int i = 0; i <= word.length(); i++){
        if(isupper(str[i])){
            str[i] = str[i]+32;
        }
    }
    string s(str);
    return s;
}
void addWordByCharFunction(){
    cout<<"Enter word: ";
    string word;
    cin>>word;
    alphabetNode* alphaNode = list.getAlphaNodeByChar(tolower(word.at(0)));
    string newWord = makeLowerCase(word);
    list.insertWordAtAlphaNode(alphaNode, newWord);
    cout<<"\nHow many synoyms do you wish to add?\n";
    int size;
    cin>>size;
    for(int i = 0; i < size; i++){
        cout<<"\n Enter synonym: ";
        string syn;
        cin>> syn;
        list.insertSynonymAtWord(alphaNode, newWord, syn);
    }
}

void addSynonymOfWord(){
    cout<<"Enter word: ";
    string word;
    cin>>word;
    alphabetNode* alphaNode = list.getAlphaNodeByChar(tolower(word.at(0)));
    string newWord = makeLowerCase(word);
    cout<<"\nHow many synoyms do you wish to add?\n";
    int size;
    cin>>size;
    for(int i = 0; i < size; i++){
        cout<<"\n Enter synonym: ";
        string syn;
        cin>> syn;
        list.insertSynonymAtWord(alphaNode, newWord, syn);
    }
}



void searchSynonymByWord(){
    cout<<"Enter word: ";
    string word;
    cin>>word;
    alphabetNode* alphaNode = list.getAlphaNodeByChar(tolower(word.at(0)));
    string newWord = makeLowerCase(word);
    list.findAndDisplaySynoymsByWord(alphaNode, newWord);
}
void deleteWordAndSynonym(){
    cout<<"Enter word: ";
    string word;
    cin>>word;
    string newWord = makeLowerCase(word);
    list.deleteWordSynonyms(newWord);
    
    cout<<"Do you wish to delete the word\""<<word<<"\" itself? (y\n)";
    char ans;
    cin>>ans;
    
    if(tolower(ans) == 'y'){
        list.deleteWord(newWord);
    }else{
        return;
    }
    
}

int main(int argc, const char * argv[]) {
    int option = 0;
    while(option != 6){
        cout << "\n\n\t\tLINKED LIST" << endl;
        cout << "\n1)Search Synonym By Word."<<endl;
        cout << "\n2)Delete Word."<<endl;
        cout << "\n3)Add Word."<<endl;
        cout << "\n4)Add Synonym of Word."<<endl;
        cout << "\n5)Display all meanings."<<endl;
        cout << "\n6)Exit"<<endl;
        cout << "\nEnter your choice: ";
        cin >> option;                

        switch (option) {
            case 1:
                searchSynonymByWord();
                system( "read -n 1 -s -p \"Press any key to continue...\"" );
                break;
            case 2 :
                deleteWordAndSynonym();
                break;
            case 3:
                addWordByCharFunction();
                break;
            case 4:
                addSynonymOfWord();
                break;
            case 5:
                list.displayLinkedListChar();
                break;
            case 6:
                list.writeListToFile();
                break;
            default:
                cout<<"Wrong Input!"<<endl;
                system( "read -n 1 -s -p \"Press any key to continue...\"" );
                break;
        }
    }
    return 0;
}
