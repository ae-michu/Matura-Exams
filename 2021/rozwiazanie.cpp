#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#define dataSize 2000
#define fileName "instrukcje.txt"

//create structure for counting occurences of letters
struct letterOccur {
    char letter;
    int occur;
};

//declare functions
void add(string &, char parameter);
void del(string &);
void change(string &, char parameter);
void move(string &, char parameter);
void checkLongest(string &, int &, string &, int &, string command);
void countLetters(char &, int &, vector <letterOccur> &, char parameter);

int main(void) {
    //declare variables
    string word = "";

    string longestCommand = "";
    int longestCommandCount = 0;
    string currCommand = "";
    int currCommandCout = 0;

    char mostFreqLetter;
    int mostFreqLetterCount;
    vector <letterOccur> letters;

    //load file
    ifstream dataFile;
    dataFile.open(fileName);

    //get data from file and process it to functions
    for(int i = 0; i < dataSize; i++){
        string command;
        char parameter;

        dataFile>>command>>parameter;
        
        if (command == "DOPISZ"){
            add(word, parameter);
            countLetters(mostFreqLetter, mostFreqLetterCount, letters, parameter);
        }else if (command == "ZMIEN"){
            change(word, parameter);
        }else if (command == "USUN"){
            del(word);
        }else if (command == "PRZESUN"){
            move(word, parameter);
        }

        checkLongest(longestCommand, longestCommandCount, currCommand, currCommandCout, command);
    }

    //display results
    cout<<"Completed word: "<<word<<endl;
    cout<<"Word length: "<<word.length()<<endl;
    cout<<endl;
    cout<<"Command with the longest streak: "<<longestCommand<<endl;
    cout<<"It's streak: "<<longestCommandCount<<endl;
    cout<<endl;
    cout<<"Parameter with the most occurences: "<<mostFreqLetter<<endl;
    cout<<"It's occurences: "<<mostFreqLetterCount<<endl;

    return 0;
}

//add letter passed as parameter to word
void add(string & word, char parameter) {
    word += parameter;
}

//delete last letter from word
void del(string & word) {
    word = word.substr(0, word.length() - 1);
}

//change last letter of word to letter passed as parameter
void change(string & word, char parameter) {
    del(word);
    word += parameter;
}

//find first letter same as one passed as parameter and changed it to next letter from alphabet (based on ascii dec values)
void move(string & word, char parameter) {
    //letter A has ascii dec value of 65
    //letter Z is dec 90
    int decNextParameter;
    if (int(parameter) == 90){
        decNextParameter = 65;
    }else{
        decNextParameter = int(parameter) + 1;
    }

    for(int i = 0; i < word.length(); i++){
        if (char(word[i]) == parameter){
            word[i] = char(decNextParameter);
            break;
        }
    }
}

//count longest streak of the same command
void checkLongest(string & longest, int & longestStreak, string & current, int & currentStreak, string next) {
    if (next == current){
        currentStreak++;
    }else{
        if (currentStreak > longestStreak){
            longestStreak = currentStreak;
            longest = current;
        }
        currentStreak = 1;
        current = next;
    }
}

//count letter occurences
void countLetters(char & freqLetter, int & freqCount, vector <letterOccur> & allLetters, char parameter) {
    bool exists = false;
    for (int i = 0; i < allLetters.size(); i++) {
        if (allLetters[i].letter == parameter){
            exists = true;
            allLetters[i].occur++;
            if (allLetters[i].occur > freqCount){
                freqLetter = allLetters[i].letter;
                freqCount = allLetters[i].occur;
            }
        }
    }
    if (exists == false) {
        allLetters.push_back(letterOccur());
        allLetters[allLetters.size() - 1].letter = parameter;
        allLetters[allLetters.size() - 1].occur = 1;
    }
}