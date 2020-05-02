#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>


using namespace std;

void bleep(string word, string &text){
    string temp;
    for(int i = 0; i < text.size(); i++){
        if(text[i] != ' ' && text[i] != '.' && text[i] != '?' && text[i]!='#'){
            temp += text[i];
            if(temp == word){
                for(int j = i; j>i -word.size();j--){
                    text[j] = '*';
                }
            }
        }
        else{
            temp.clear();
        }
    }


}

int main(){
    
    std::string word = "broccoli";
    std::string text = "I sometimes eat broccoli. There are three interesting things about broccoli. Number One. Nobody knows how to spell it. Number Two. No matter how long you boil it, it's always cold by the time it reaches your plate. Number Three. It's green. #broccoli";
    string temp;
    bleep(word,text);
    cout << text;
    return 0;
}
