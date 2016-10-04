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
const int CODE_SUCCESS = 0;
const int CODE_FAIL = 1;

const string TEMP_FILE_NAME = "__temp";

string lang, path;

int main(int argc,  char* argv[]){
    
    lang = GetLang();
    
    if(lang == ""){
        cout << "No language defined, using English." << endl;
        lang = "en";
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
    
    
    //Remove the temporary file
    //system(("rm " + path + "/" + TEMP_FILE_NAME).c_str());
    
}

void RunTest(string command, string check, int checkCode){
    
    string temp;
    
    //Setport
    int statusCode = system((command + " > " + path + "/" + TEMP_FILE_NAME).c_str()) / 256;
    cout << command + " code: " << ((statusCode == checkCode) ? "Success" : "Fail") << endl;
    
    ifstream reader(path + "/lang/" + lang + "/" + check);
    
    if(!reader.good()){
        cout << "Missing " + lang + " translation test for '" + lang + "/" + check + "'." << endl;
    }
    else{
        statusCode = system(("diff " + path + "/" + TEMP_FILE_NAME + " " + path + "/lang/" + lang + "/" + check  + " > /dev/null").c_str()) / 256;
        cout << command + " output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    }
    
    reader.close();
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