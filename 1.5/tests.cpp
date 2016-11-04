/*
    Test Script For PortSetter
    Nick Pray
    CS-3370
*/
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

int FormatCode(int);
void RunTest(string, string, int);
string GetLang();

const int CODE_FORMATTER = 256;
int CODE_SUCCESS = 0;
const int CODE_FAIL = 1;

const string TEMP_FILE_NAME = "__temp";
const string BOOL_FILE_NAME = "__boolCheck";                        //co5 epj added (if no lang, add the no lang string, shown below.)

string lang, path;
string badLangString = "No valid language defined, using English."; //co5 epj this text needs to be the same as in setport.cpp
bool badLangBool = false;                                           //co5 epj added to check for no lang.

int main(int argc,  char* argv[]){
    
    lang = GetLang();
    
    if(lang == ""){
        cout << badLangString << endl;
        lang = "en";
        badLangBool = true;
    }
    
    //Get this files path
    path = argv[0];
    path = path.substr(0, path.find_last_of("\\/"));
    
    RunTest("./setport", "usage.txt", CODE_SUCCESS);
    RunTest("./setport -h", "usage.txt", CODE_SUCCESS);
    RunTest("./setport --help", "usage.txt", CODE_SUCCESS);
    RunTest("./setport -?", "usage.txt", CODE_SUCCESS);
    RunTest("./setport -!", "about.txt", CODE_SUCCESS);
    RunTest("./setport --about", "about.txt", CODE_SUCCESS);
    RunTest("./setport -v", "version.txt", CODE_SUCCESS);
    RunTest("./setport --version", "version.txt", CODE_SUCCESS);
    RunTest("./setport -e", "tests/success_env.txt", CODE_SUCCESS);
    RunTest("./setport --environment", "tests/success_env.txt", CODE_SUCCESS); //co5 epj added
    RunTest("./setport -p 4040", "tests/success.txt", CODE_SUCCESS);
    RunTest("./setport --port 4040", "tests/success.txt", CODE_SUCCESS);
    RunTest("./setport help", "tests/err_invalid_flag.txt", CODE_FAIL);
    RunTest("./setport -help", "tests/err_invalid_flag.txt", CODE_FAIL);
    RunTest("./setport --h", "tests/err_invalid_flag.txt", CODE_FAIL);
    RunTest("./setport -h --help", "tests/err_param_count.txt", CODE_FAIL);
    RunTest("./setport -hs", "tests/err_invalid_flag.txt", CODE_FAIL);
    RunTest("./setport -p --port 9", "tests/err_param_count.txt", CODE_FAIL);
    RunTest("./setport -p 77 33", "tests/err_param_count.txt", CODE_FAIL);
    RunTest("./setport -p -21", "tests/err_invalid_port.txt", CODE_FAIL);
    RunTest("./setport -p 0", "tests/err_invalid_port.txt", CODE_FAIL);
    RunTest("./setport --port", "tests/err_param_count.txt", CODE_FAIL);
    RunTest("./setport -p 90642", "tests/err_invalid_port.txt", CODE_FAIL);
    RunTest("./setport -x 45321", "tests/err_invalid_flag.txt", CODE_FAIL);
    RunTest("./setport -P 714", "tests/err_invalid_flag.txt", CODE_FAIL);
    RunTest("./setport -? 444", "tests/err_param_count.txt", CODE_FAIL);
    RunTest("./setport -! 444", "tests/err_param_count.txt", CODE_FAIL);
    RunTest("./setport --about 444", "tests/err_param_count.txt", CODE_FAIL);
    RunTest("./setport -v 444", "tests/err_param_count.txt", CODE_FAIL);
    RunTest("./setport --version 444", "tests/err_param_count.txt", CODE_FAIL);
    RunTest("./setport -e 444", "tests/err_invalid_port.txt", CODE_FAIL);
    RunTest("./setport --environment 445", "tests/err_invalid_port.txt", CODE_FAIL); //co5 epj added
    
    
    //Remove the temporary file
    //system(("rm " + path + "/" + TEMP_FILE_NAME).c_str());
      
    system("rm __temp __boolCheck");                            //co5 epj added to remove temp files.
    
}

void RunTest(string command, string check, int checkCode){
    
    string temp;
    string fileNameToCheck = path + "/lang/" + lang + "/" + check;
    
    //Setport
    int statusCode = system((command + " > " + path + "/" + TEMP_FILE_NAME).c_str()) / 256;
    cout << command + " code  : " << ((statusCode == checkCode) ? "Success" : "Fail") << endl; //co5 epj changed spaces for readability
    
    ifstream reader(fileNameToCheck);
    ofstream checkFileWithBool(BOOL_FILE_NAME);
    
    if(!reader.good()){
        cout << "Missing " + lang + " translation test for '" + lang + "/" + check + "'." << endl;
    }
    else{
        
        //co5 epj added so no lang error is fixed
        if (badLangBool){
            checkFileWithBool << badLangString << endl;
        }
        string catString = "cat " + fileNameToCheck + " >> " + BOOL_FILE_NAME;
        system(catString.c_str());
        
        statusCode = system(("diff " + path + "/" + TEMP_FILE_NAME + " " + BOOL_FILE_NAME + " > /dev/null").c_str()) / 256; //co5 epj changed for readability
        cout << command + " output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    }
    
    reader.close();
    checkFileWithBool.close();
}

string GetLang(){
  
  string input = "en_US";
  regex pattern("^(.{2})(?:_[A-Z]{2}(?:\\.UTF-8)?|\\.UTF-8)?$");
  smatch matches;
  
  //Define all environment variables to search in order
  string envs[]{"LANGUAGE", "LC_ALL", "LC_MESSAGES", "LANG"};
  
  int size = sizeof(envs) / sizeof(string);
  char* temp;
  string lang;
  
  for(int i = 0; i < size; i++){
    
    //Get environment variable
    temp = getenv(envs[i].c_str());
    
    //Couldn't find the environment variable
    if(temp == nullptr) continue;
    
    //Convert to string for comparison and regex
    lang = temp;
    
    //Environment variable set to default
    if(lang == " " || lang == "C" || lang == "C.UTF-8") continue;
    
    //Find matches
    regex_match(lang, matches, pattern);
    
    //If there is a match return it else continue to next environment variable
    if(matches.size() > 0) return matches[1];
    else continue;
    
  }

  return "";
}

//graveyard / notes by epj: 

//these tests RELY on the fact that there is a lang set.
//if not, it adds in the "defaulting to english" line. and tests fail.
//FIXED! you're welcome.

//the env tests also RELY on 8080 as the PORT value in env.