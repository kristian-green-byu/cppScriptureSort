#pragma once
#include <string>
#include <sstream>
#include "Verse.h"
using namespace std;

class Chapter{
    private:
        string bookName;
        int chapter;

    public:
    vector<Verse> verses;
    Chapter(string& bookName, int& chapter, vector<Verse>& verses) : bookName(bookName), chapter(chapter), verses(verses){}

    string toString(){
        stringstream out;
        for(auto verse : verses){
            out<< verse.toString();
        }
        return out.str();
    }
    int getChapter() {
        return chapter;
    }
    int verseCount() {
        return verses.size();
    }
};