#pragma once
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class Verse{
    private:
        string bookName;
        int chapter;
        int verse;
        string text;
    public:
    Verse(string& bookName, int& chapter, int& verse, string& text) : bookName(bookName), chapter(chapter), verse(verse), text(text){}

    string toString(){
        stringstream out;
        out <<"  "<<verse << "  " <<text<<endl;
        return out.str();
    }
    bool hasWord(string word){
        string lowerWord;
        string lowerText;
        for(auto c : word){
            lowerWord+=(tolower(c));
        }
        for(auto c : text){
            lowerText+=(tolower(c));
        }
        return lowerText.find(lowerWord)!= string::npos;
    }
    vector<string> splitText(){
        stringstream ss(text);
        string s;
        vector<string> splitText;
        while(getline(ss, s, ' ')) {
            // store token string in the vector
            splitText.push_back(s);
        }
        return splitText;
    }
    
};