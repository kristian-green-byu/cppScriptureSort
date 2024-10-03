#pragma once
#include <string>
#include <sstream>
#include "Chapter.h"
#include <map>
#include <regex>
using namespace std;

class Book{
    private:
        string bookName;
    public:
    vector<Chapter> chapters;
    Book(string& bookName, vector<Chapter>& chapters) : bookName(bookName), chapters(chapters) {}

    string toString(){
        stringstream out;
        for(Chapter chapter : chapters){
            out <<bookName<<" "<<chapter.getChapter()<<endl;
            out<<chapter.toString()<<endl;
        }
        return out.str();
    }
    int wordCount(string word){
        int cnt = 0;
        vector<Chapter> newChapters;
        for(auto i = 0; i<chapters.size(); i++){
            vector<Verse> newVerses;
            for(Verse verse : chapters[i].verses){
                if(verse.hasWord(word)){
                    cnt++;
                }
            }
        }
        return cnt;
    }
    map<string, int> findMostCommonWords(){
        map<string, int> mostCommonWords;
        for(Chapter chapter: chapters){
            for(Verse verse: chapter.verses){
                vector<string> splitText = verse.splitText();
                for(string word : splitText){
                    string finalword;
                    for(auto c : word){
                        if(isalnum(c)){
                            finalword+=(tolower(c));
                        }
                    }
                    if(mostCommonWords.find(finalword)==mostCommonWords.end()){
                        mostCommonWords[finalword] = 1;
                    }
                    else{
                        mostCommonWords[finalword] += 1;
                    }
                 }
            }
        }
        return mostCommonWords;
    }
    Book findWord(string word){
        vector<Chapter> newChapters;
        for(auto i = 0; i<chapters.size(); i++){
            vector<Verse> newVerses;
            for(Verse verse : chapters[i].verses){
                if(verse.hasWord(word)){
                    newVerses.push_back(verse);
                }
            }
            int chapterInt = chapters[i].getChapter();
            Chapter newChapter(bookName, chapterInt, newVerses);
            if(newChapter.verseCount()>0){
                newChapters.push_back(newChapter);
            }
        }
        Book newBook(bookName, newChapters);
        return newBook;
    }
};