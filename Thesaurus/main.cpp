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


void addWordFunction(){
    cout<<"Enter word: ";
    string word;
    cin>>word;
    list.insertWord(word);
    cout<<"\nHow many synoyms do you wish to add?\n";
    int size;
    cin>>size;
    for(int i = 0; i < size; i++){
        cout<<"\n Enter synonym: ";
        string syn;
        cin>> syn;
        list.insertSynonymAtWord(word, syn);
    }
}

void addSynonymOfWord(){
    cout<<"Enter word: ";
    string word;
    cin>>word;
    cout<<"\nHow many synoyms do you wish to add?\n";
    int size;
    cin>>size;
    for(int i = 0; i < size; i++){
        cout<<"\n Enter synonym: ";
        string syn;
        cin>> syn;
        list.insertSynonymAtWord(word, syn);
    }
}

void searchSynonymByWord(){
    cout<<"Enter word: ";
    string word;
    cin>>word;
    list.findAndDisplaySynoymsByWord(word);
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
                break;
            case 3:
                addWordFunction();
                //list.readFromFile();
                break;
            case 4:
                addSynonymOfWord();

                break;
            case 5:
                list.displayLinkedList();
                break;
            case 6:
                list.writeListToFile();
            default:
                break;
        }

    }
       
//    list.insertWord("Strong");
//    list.insertSynonymAtWord("Strong","Powerful");
//    list.insertSynonymAtWord("Strong", "Basit");
//    list.displayLinkedList();
//
    return 0;
}
