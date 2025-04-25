#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
                  const std::string& in,
                  std::string temp,
                  const std::string& floating,
                  const std::set<std::string>& dict,
                  std::set<std::string>& res,
                  int pos);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> res;
    string temp = in;
    wordleHelper(in, temp, floating, dict, res, 0);
    return res;
}

// Define any helper functions here
void wordleHelper(
    const std::string& in,
    std::string temp,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& res,
    int pos)
{
    if (pos == in.length()) { // aka, gone off the ledge
        if (floating.empty() && dict.find(temp) != dict.end()) {
            res.insert(temp);
        }
    }
    else if (in[pos] == '-') {
        for (size_t i = 0; i < floating.length(); i++) {
            char letter = floating[i];
            temp[pos] = letter;
            string float_store = floating;
            float_store.erase(i, 1);
            wordleHelper(in, temp, float_store, dict, res, pos + 1);
        }
        int pos_left = in.length() - pos;
        if (pos_left > floating.length()) {
            for (int i = 0; i < 26; i++) {
                char c = 'a' + i;
                if (floating.find(c) == string::npos) {
                    temp[pos] = c;
                    wordleHelper(in, temp, floating, dict, res, pos + 1);
                }
            }
        }
    }
    else {
        wordleHelper(in, temp, floating, dict, res, pos + 1);
    }
}

