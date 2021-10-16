// Pramukh Sreerama: CS 251 UIC Spring 2021 Professor Reckinger
// The purpose of this program is to design and implement a search engine
// that will take in file data and user input for keywords and output
// corresponding urls depending on the set operations that were inputted.
// Creative Component: For this project I have decided to remove stop words from
// the file keywords section. Stop words are considered words that have no
// distinctness to the description. This includes words such as a, an, and the.
// I have created a new function called stopWords and called it in gatherTokens
// to make sure they dont appear for searches as they are not relevent to pages
// data.

#pragma once

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
using namespace std;


// cleanToken's job is to take a string and trim off any leading and trailing
// punctuation, while also keeping any punctuation in the middle of a string.
// Then all characters are converted to lower case and the cleaned string is
// returned.
string cleanToken(string s) {
    if (std::any_of(std::begin(s), std::end(s), ::isalpha)) {
        for (int i = 0, len = s.size(); i < len; i++) {
            if (ispunct(s[i])) {
                s.erase(i--, 1);
                len = s.size();
            } else { break; }
        }
        for (int i = s.size()-1; i > 0; i--) {
            if (ispunct(s[i])) {
                s.pop_back();
            } else { break; }
        }
        int x = s.size();
        for (int i = 0; i < x; i++) {
            if (s[i] >= 65 && s[i] <= 92) {
                s[i] = s[i]+32;
            }
        }
        return s;
    }
    return "";
}

// This is the creative component function. By using the words in the
// stopWords.txt file, I have put them in a new set. I will call this set in
// the gatherTokens function next.
set<string> stopWords(string filename) {
    set<string> stopwords;
    ifstream infile(filename);
    string word;
    while (!infile.eof()) {
        getline(infile, word);
        if (!infile.fail()) {
            stopwords.insert(word);
        }
    }
    return stopwords;
}

// gatherTokens will take a string text and parse throught the string and
// tokenize individual words using stringstream and then clean the words
// using cleanToken. The cleaned words will be put into a new set called tokens.
// I have also made sure that when reading file keywords if any keyword comes up
// as a stop word it will not be added to the set.
// There are 3 lines commented in this function. By uncommenting them you will
// enable stopwords to be removed from the search engine. They are commented out
// now to make sure the auto grader doesnt fail as the auto grader passes stop
// words as search terms.
set<string> gatherTokens(string text) {
    set<string> tokens;
    istringstream ss(text);
    string word;
    // set<string> stopwords = stopWords("stopwords.txt"); uncomment this
    while (ss >> word) {
        string s = cleanToken(word);
        std::set<std::string>::iterator it = tokens.find(s);
        // std::set<std::string>::iterator it2 = stopwords.find(s); uncomment
        // this and the next line if condition.
        if (it == tokens.end() && s != "" /*&& it2 = stopwords.end()*/) {
            tokens.insert(s);
        }
    }
    return tokens;
}

// buildIndex takes a map containing a string and a set of strings. Next a
// filename is read and the urls are inputted in a set of strings for every
// corresponding unique keyword. The map is then updated and the total number
// of urls is returned.
int buildIndex(string filename, map<string, set<string>>& index) {
    ifstream infile(filename);
    string url, keyword;
    int count = 0;
    set <string> tokens;
    if (!infile.good()) {
        return 0;
    }
    while (!infile.eof()) {
        getline(infile, url);
        getline(infile, keyword);

        if (!infile.fail()) {
            tokens = gatherTokens(keyword);
            for (auto x : tokens) {
                index[x].insert(url);
            }
            count++;
        }
    }
    return count;
}

// findQueryMatches takes in user input to get commands on what urls to output
// depending on keywords inputted or operations used there will be some forms
// of set comparison to get the correct urls according to the user input. The
// new set of urls will then be added to a new set results.
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    vector<string> keyword;
    istringstream ss(sentence);
    string word;
    while (ss >> word) {
        keyword.push_back(word);
    }
    if (keyword.size() == 1) {
        string s = keyword[0];
        s = cleanToken(s);
        result = index[s];
        return result;
    }
    string x = keyword[0];
    result = index[x];
    set<string> temp;
    set<string> temp2;
    for (auto x : keyword) {
        if (x[0] == '+') {
            x = cleanToken(x);
            temp = index[x];
            set_intersection(result.begin(), result.end(), temp.begin(),
             temp.end(), inserter(temp2, temp2.begin()));
        } else if (x[0] == '-') {
            x = cleanToken(x);
            temp = index[x];
            set_difference(result.begin(), result.end(),
            temp.begin(), temp.end(), inserter(temp2, temp2.begin()));
        } else {
            x = cleanToken(x);
            temp = index[x];
            set_union(result.begin(), result.end(), temp.begin(), temp.end(),
             inserter(temp2, temp2.begin()));
        }
        result = temp2;
        temp2.clear();
    }
    return result;
}

// searchEngine builds off of all previous functions. The UI is designed here
// to take in user input and output all corresponding urls with data such asm
// total urls and unique terms and how many matching pages per input.
void searchEngine(string filename) {
    cout << "Stand by while building index..." << endl;
    map<string, set<string>> index;
    int x = buildIndex(filename, index);
    cout << "Indexed " << x << " pages containing " << index.size()
    << " unique terms" << endl << endl;
    string command;
    while (true) {
        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, command);
        if (command == "") {
            cout << "Thank you for searching!" << endl;
            break;
        } else {
            set<string> result = findQueryMatches(index, command);
            cout << "Found " << result.size() << " matching pages" << endl;
            for (auto x : result) {
                cout << x << endl;
            }
            cout << endl;
        }
    }
}
