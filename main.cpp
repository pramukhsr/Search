// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.

// Remove starter comments and add your own
// comments on each function and on complex code sections.

#include <iostream>
#include "search.h"
using namespace std;

int main() {
    
    // Use this function to call and test the functions you write inside of
    // search.h.  If you do not call the functions here, nothing will run.

    //string s = "be!";
    
    //cout << s << endl;
    //string y = cleanToken(s);

    //cout << y << endl;
    
    //set<string> tokens = gatherTokens("123 123a123 (((123)) (((123a123)))");
    //set<string> tokensANS;


    //cout << "1. " << tokens.size() << endl;

    /*for(auto x: tokens){
        cout << x << endl;
    }*/
    //map<string, set<string>> index;
    
    //buildIndex("tiny.txt", index);
    
    /*for(auto x: index){
        cout << x.first << endl;
        for(auto y: x.second){
            cout << y << endl;
        }
    }*/
    //cout << r << endl;
    
    //string sentence = "fish -red";
    
    //set<string> result = findQueryMatches(index, sentence);
    
    /*for(auto x: result){
        cout << x << endl;
    }*/
    searchEngine("tiny.txt");

    
    return 0;
}

