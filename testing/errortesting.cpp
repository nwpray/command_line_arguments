#include <iostream>
#include <fstream>
#include <regex>
#include <map>

using namespace std;

string GetLang();

int main(int argc, char* argv[]){
  
  string lang = GetLang();
  
  if(lang == "") cout << "NOT FOUND" << endl;
  else cout << lang << endl;
  
};


string GetLang(){
  
  string input = "en_US";
  regex pattern("^(.{2})(?:_[A-Z]{2}(?:\\.UTF-8)?|\\.UTF-8)?$");
  smatch matches;
  
  string envs[]{"LANGUAGE", "LC_ALL", "LC_MESSAGES", "LANG"};
  
  int size = sizeof(envs) / sizeof(string);
  char* temp;
  string lang;
  
  for(int i = 0; i < size; i++){
    
    temp = getenv(envs[i].c_str());
    
    if(temp != nullptr){
      
      lang = temp;
      regex_match(lang, matches, pattern);
      
      if(matches.size() > 0) return matches[1];
      else return "";
      
    }
    else{
      return "";
    }
    
  }
  
  return "";
}