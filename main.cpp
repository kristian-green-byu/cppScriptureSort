#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include "Verse.h"
#include "Chapter.h"
#include "Book.h"
#include <map>
#include <algorithm>
#include <cctype>
#include <set>


using namespace std;

vector<string> split(string s, char del){
    vector<string> words;
    stringstream ss(s);
    string word;
    while (!ss.eof()) {
        getline(ss, word, del);
        words.push_back(word + "\n");
    }
    return words;
}

vector<string> getBibleVector(ifstream& bible, string url) {
    bible.open(url);
    string line;
    vector<string> bibleStrings;
    if (bible.is_open())
    {
        while (getline(bible,line) )
        {
            line = line+"\n";
            bibleStrings.push_back(line);
        }
        bible.close();
    }
    return bibleStrings;
}

string StringRegex(string line, regex regexstring){
    smatch m;
    regex_search(line, m, regexstring);
    for(string s : m){
        return s;
    }
    string null;
    return null;
}
string eraseSpace(string& text){
    if(text.at(0) == '\t'){
        text.erase(0,1);
    }
    text = regex_replace(text, std::regex("^ +"), "");
    return text;
}

vector<Chapter> makeChapters(map<int, vector<Verse> >& chapterNumToVerses, string& bookName){
    vector<Chapter> chapters;
    for(int i = 1; i<=chapterNumToVerses.size(); i++){
        vector<Verse> verses = chapterNumToVerses[i];
        Chapter chapterObj(bookName, i, verses);
        chapters.push_back(chapterObj);
    }
    return chapters;
}

map<int, vector<Verse> > makeChapterNumToVerses(vector<string> &bibleText){
    map<int, vector<Verse> > chapterNumToVerses;
    string line = bibleText[0];
    string bookName = StringRegex(line, regex("([[:alnum:]] [[:alnum:]]*)|([[:alnum:]]*)"));
    string chapter = StringRegex(line, regex("([0-9][0-9]?[0-9]?):"));
    chapter.erase(chapter.size()-1);
    int chapterIntOld = stoi(chapter);
    vector<Verse> verses;
    int i = 1;
    for(string& line : bibleText){
        /*Logic we need:
        First, make the chapter object in a map while the chapter number stays the same
        When chapter number changes, make new chapter objecta nd add it to next position in map.
        */
        string bookName = StringRegex(line, regex("([[:alnum:]] [[:alnum:]]*)|([[:alnum:]]*)"));
        string chapter = StringRegex(line, regex("([0-9][0-9]?[0-9]?):"));
        chapter.erase(chapter.size()-1);
        int chapterInt = stoi(chapter);
        if(chapterIntOld != chapterInt){
            chapterNumToVerses[i] = verses;
            verses.clear();
            i++;
        }
        string verse = StringRegex(line, regex(":([0-9][0-9]?[0-9]?)"));
        string text = StringRegex(line, regex(":[0-9][0-9]?[0-9]?(.*)"));
        text.erase(0,verse.size());
        text = eraseSpace(text);
        verse.erase(0, 1);
        int verseInt = stoi(verse);
        Verse verseObj(bookName, chapterInt, verseInt, text);
        verses.push_back(verseObj);
        chapterIntOld = chapterInt;
    }
    chapterNumToVerses[i] = verses;
    verses.clear();
    return chapterNumToVerses;
}
set<string> getFilenamesSet(){
    set<string> filenames;
    filenames.insert("Genesis.txt");
    filenames.insert("Exodus.txt");
    filenames.insert("Leviticus.txt");
    filenames.insert("Numbers.txt");
    filenames.insert("Deuteronomy.txt");
    filenames.insert("Joshua.txt");
    filenames.insert("Judges.txt");
    filenames.insert("Ruth.txt");
    filenames.insert("1Samuel.txt");
    filenames.insert("2Samuel.txt");
    filenames.insert("1Kings.txt");
    filenames.insert("2Kings.txt");
    filenames.insert("1Chronicles.txt");
    filenames.insert("2Chronicles.txt");
    filenames.insert("Ezra.txt");
    filenames.insert("Nehemiah.txt");
    filenames.insert("Esther.txt");
    filenames.insert("Job.txt");
    filenames.insert("Psalm.txt");
    filenames.insert("Proverbs.txt");
    filenames.insert("Ecclesiastes.txt");
    filenames.insert("SongofSolomon.txt");
    filenames.insert("Isaiah.txt");
    filenames.insert("Jeremiah.txt");
    filenames.insert("Lamentations.txt");
    filenames.insert("Ezekiel.txt");
    filenames.insert("Daniel.txt");
    filenames.insert("Hosea.txt");
    filenames.insert("Joel.txt");
    filenames.insert("Amos.txt");
    filenames.insert("Obadiah.txt");
    filenames.insert("Jonah.txt");
    filenames.insert("Micah.txt");
    filenames.insert("Nahum.txt");
    filenames.insert("Habakkuk.txt");
    filenames.insert("Zephaniah.txt");
    filenames.insert("Haggai.txt");
    filenames.insert("Zechariah.txt");
    filenames.insert("Malachi.txt");
    filenames.insert("Matthew.txt");
    filenames.insert("Mark.txt");
    filenames.insert("Luke.txt");
    filenames.insert("John.txt");
    filenames.insert("Acts.txt");
    filenames.insert("Romans.txt");
    filenames.insert("1Corinthians.txt");
    filenames.insert("2Corinthians.txt");
    filenames.insert("Galatians.txt");
    filenames.insert("Ephesians.txt");
    filenames.insert("Philippians.txt");
    filenames.insert("Colossians.txt");
    filenames.insert("1Thessalonians.txt");
    filenames.insert("2Thessalonians.txt");
    filenames.insert("1Timothy.txt");
    filenames.insert("2Timothy.txt");
    filenames.insert("Titus.txt");
    filenames.insert("Philemon.txt");
    filenames.insert("Hebrews.txt");
    filenames.insert("James.txt");
    filenames.insert("1Peter.txt");
    filenames.insert("2Peter.txt");
    filenames.insert("1John.txt");
    filenames.insert("2John.txt");
    filenames.insert("3John.txt");
    filenames.insert("Jude.txt");
    filenames.insert("Revelation");
    return filenames;
}

int main() {
    ifstream bible;
    cout<<"\nWelcome to the Bible Processor!\nVersion V0.1\n\n";
    bool repeat = true;
    while(repeat == true){
        repeat = false;
        cout<<"Input the book you wish to examine with no spaces.\nFor example, if you want to input 1 Corinthians, write 1Corinthians instead.\n Input: ";
        string response1;
        cin >> response1;
        string textFile = response1 + ".txt";
        cout<<"You requested to access "<<textFile<<endl;
        set<string> filenames = getFilenamesSet();
        if(filenames.find(textFile) != filenames.end()){
            cout<<"File "<<textFile<<" found. Loading file...\n";
            string fullUrl = "bibleFiles/"+textFile;
            vector<string> bibleText = getBibleVector(bible, fullUrl);
            map<int, vector<Verse> > chapterNumToVerses = makeChapterNumToVerses(bibleText);
            string line = bibleText[0];
            string bookName = StringRegex(line, regex("([[:alnum:]] [[:alnum:]]*)|([[:alnum:]]*)"));
            vector<Chapter> chapters = makeChapters(chapterNumToVerses, bookName);
            Book book(bookName, chapters);
            cout<<"\nLoading Complete!\nWhich operation do you want to perform?";
            bool repeat4 = true;
            while(repeat4 == true){
                repeat4 = false;
                cout<<"\n1: Print all Text 2: Find all matches for specific word or phrase 3: Find the most common words of a book\n";
                string response2;
                cin >> response2;
                if(response2 == "1"){
                cout<<book.toString();
                cout<<"Would you like to save your response in a text file? (y/n)\n";
                string response3;
                cin>>response3;
                bool repeat3 = true;
                while(repeat3 == true){
                    if(response3 == "y"){
                        cout<<"Input the name of your desired output (without .txt on the end): ";
                        string response4;
                        cin>>response4;
                        string output = response4+".txt";
                        ofstream outfile(output);
                        outfile<<book.toString();
                        outfile.close();
                        repeat3 = false;
                    }
                    else if (response3 != "n"){
                        cout<<"\n Please only type y for yes and n for no.\n";
                    }
                    else{
                        repeat3 = false;
                    }
                }
                
            }
            else if (response2 == "2"){
                cout<<"Enter the word or phrase you want to search: ";
                string word;
                cin.ignore();
                getline(cin, word);
                cout<<"\n\nSearching for word/phrase "<<word<<"...\n\n";
                Book newBook = book.findWord(word);
                int timesFound = newBook.wordCount(word);
                cout<<word<<" found "<<timesFound<<" times.\n\n";
                if(timesFound>0){
                    cout<<"Chapters and verses containing the word or phrase "<<word<<": \n\n";
                    cout<<newBook.toString()<<endl;
                    cout<<"Would you like the chapters and verses you found in a text file? (y/n)\n";
                    string response3;
                    cin>>response3;
                    bool repeat3 = true;
                    while(repeat3 == true){
                        if(response3 == "y"){
                            cout<<"Input the name of your desired output (without .txt on the end): ";
                            string response4;
                            cin>>response4;
                            string output = response4+".txt";
                            ofstream outfile(output);
                            outfile<<word<<" found "<<timesFound<<" times.\n\n";
                            outfile<<"Chapters and verses containing the word or phrase "<<word<<": \n\n";
                            outfile<<newBook.toString();
                            outfile.close();
                            repeat3 = false;
                        }
                        else if (response3 != "n"){
                            cout<<"\n Please only type y for yes and n for no.\n";
                        }
                        else{
                            repeat3 = false;
                        }
                    }
                }
            }
            else if (response2 == "3"){
                map<string, int> mostCommonWords = book.findMostCommonWords();
                cout<<"Input the name of your desired output file (without .txt on the end): ";
                string response4;
                cin>>response4;
                string output = response4+".txt";
                ofstream outfile(output);
                for(auto pair : mostCommonWords){
                    outfile<<pair.first<<" found "<<pair.second<<" times.\n";
                }
                outfile.close();
            }
            else {
                cout<<"Unknown operation: "<<response2<<".\n Please try again. \n"; 
                repeat4 = true;
            }
            }
        }
        else{
            cout<<"File "<<textFile<<" not found. Please verify your input and try again.\n";
        }
        bool repeat2 = true;
        while(repeat2 == true){
            cout<<"\nDo you want analyze something else? (y/n)\n";
            string response3;
            cin>>response3;
            if(response3 == "y"){
                repeat = true;
                repeat2 = false;
            }
            else if(response3 == "n"){
                cout<<"\nExiting program...\n";
                repeat2 = false;
            }
            else{
                cout<<"\nPlease only enter the letter y for yes or n for no.\n";
            }
        }
    }
    return 0;
}