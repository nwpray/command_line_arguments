/*
    Command Line Arguments and Gathering Requirements
    Nick Pray
    CS-3370
*/
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <regex>

using namespace std;

const int INDEX_FLAG = 1;
const int INDEX_PORT = 2;

const int MAX_PORT = 65535;
const int MIN_PORT = 1;

const string FLAG_PORT = "--port";
const string FLAG_PORT_SHORT = "-p";

const string FLAG_HELP = "--help";
const string FLAG_HELP_SHORT = "-h";
const string FLAG_HELP_SHORT_2 = "-?";

const string FLAG_ABOUT = "--about";
const string FLAG_ABOUT_SHORT = "-!";

const string FLAG_VERSION = "--version";
const string FLAG_VERSION_SHORT = "-v";

const string FLAG_ENVIRONMENT= "--environment";
const string FLAG_ENVIRONMENT_SHORT= "-e";

const string ERROR_PREFIX = "![ERROR]! - ";

const string FILE_USAGE = "usage";
const string FILE_ABOUT = "about";
const string FILE_VERSION = "version";

const string DEFAULT_ENVIRONMENT_VAR = "PORT";

enum Flag {
    Port,
    Usage, 
    About, 
    Version, 
    Environment
};

enum Message {
    MsgFlagInvalid,
    MsgInvalidPort,
    MsgParamCount,
    MsgUnknown,
    MsgListening
};

map<Message,string> consoleMessages;

//Function references
Flag ParseFlag(int, char**);
void CollectMessages();
void PrintError(Message);
void PrintFile(string);
string GetLang();

string lang;

int main(int argc, char* argv[]){
        
    Flag flag;
    
    lang = GetLang();
    
    if(lang == ""){
        cout << "No valid language defined, using English." << endl;
        lang = "en";
    }
    
    //Load the error messages map
    CollectMessages();
     
    //Parse the flag
    try{
        flag = ParseFlag(argc, argv);
    } catch (Message e){
        PrintError(e);
        return 1;
    }
    
    //Usage
    if(flag == Usage)
    {
        PrintFile(FILE_USAGE);
        return 0;
    }
    
    //About
    if(flag == About){
        PrintFile(FILE_ABOUT);
        return 0;
    }
    
    //Version
    if(flag == Version){
        PrintFile(FILE_VERSION);
        return 0;
    }
    
    int port;
    char* temp;
    string envVar;
    
    //Environment
    if(flag == Environment){
        
        temp = argc > INDEX_FLAG + 1 ?  getenv(argv[INDEX_PORT]) : getenv(DEFAULT_ENVIRONMENT_VAR.c_str());
        
        if(temp!= nullptr) envVar = temp;
        else {
            PrintError(MsgInvalidPort);
            return 1;
        }
            
        try{
            port = stoi(envVar);
        }
        catch(exception e){
            PrintError(MsgInvalidPort);
            return 1;
        }
    }
    
    //Port
    else if(flag == Port){
        
        string rawPort = argv[INDEX_PORT];
        size_t conversionLength;
    
        //Handles case where port number starts with chars
        try{
            port = stoi(rawPort, &conversionLength);
        } catch (exception e){
            PrintError(MsgInvalidPort);
            return 1;
        }
        
        //Handles case where port number starts with valid int but ends in chars
        if((rawPort.substr(0,conversionLength).size() != rawPort.size()) || (port < MIN_PORT || port > MAX_PORT))
        {
            PrintError(MsgInvalidPort);
            return 1;
        }
    }
    
    //I have no idea how you got this without a port but this will catch it
    else{
        PrintError(MsgUnknown);
        return 1;
    }
    
    cout << consoleMessages[MsgListening] + " " << port << "." << endl;
    return 0;
}

//Parses the flag into its enumeration, will throw type Error if failed parse or invalid formatting
Flag ParseFlag(int argc, char* argv[]){
    
    if(argc < INDEX_FLAG + 1) return Usage;
    
    string flag = argv[INDEX_FLAG];
    
    //Port
    if(flag == FLAG_PORT || flag == FLAG_PORT_SHORT){
        if(argc < INDEX_PORT + 1 || argc > INDEX_PORT + 1) throw MsgParamCount;
        return Port;
    };
    
    //Environment
    if(flag == FLAG_ENVIRONMENT || flag == FLAG_ENVIRONMENT_SHORT){
        return Environment;
    };
    
    //Usage
    if(flag == FLAG_HELP || flag == FLAG_HELP_SHORT || flag == FLAG_HELP_SHORT_2){
        if(argc >= INDEX_PORT + 1) throw MsgParamCount;
        return Usage;
    };
    
    //About
    if(flag == FLAG_ABOUT || flag == FLAG_ABOUT_SHORT){
        if(argc >= INDEX_PORT + 1) throw MsgParamCount;
        return About;
    };
    
    //Version
    if(flag == FLAG_VERSION || flag == FLAG_VERSION_SHORT){
        if(argc >= INDEX_PORT + 1) throw MsgParamCount;
        return Version;
    };
    
    //Else
    throw MsgFlagInvalid;
}

//Collect all the error messages
void CollectMessages(){
    
    consoleMessages.clear();
    
    ifstream reader("lang/" + lang + "/messages.txt"); 
    
    if(!reader.good()){
        cout << "Missing " + lang + " translation file for error messages. Using English." << endl;
        reader.close();
        reader.open("lang/en/messages.txt");
    }
    
    string temp;
    
    getline(reader, temp);
    consoleMessages[MsgFlagInvalid] = temp;
    
    getline(reader, temp);
    consoleMessages[MsgParamCount] = temp;
    
    getline(reader, temp);
    consoleMessages[MsgInvalidPort] = temp;
    
    getline(reader, temp);
    consoleMessages[MsgUnknown] = temp;
    
    getline(reader, temp);
    consoleMessages[MsgListening] = temp;
    
    reader.close();
}

//Prints an error prepended by error enum
void PrintError(Message m){
    if(consoleMessages.find(m) != consoleMessages.end()) cout << ERROR_PREFIX << consoleMessages.find(m)->second << endl;
    PrintFile(FILE_USAGE);
}

//Prints any of the info files with just the type name
void PrintFile(string kind){
    
    ifstream reader("lang/" + lang + "/" + kind + ".txt");
    
    if(!reader.good()){
        cout << "Missing " + lang + " translation file for '" + kind + ".txt'. Using English." << endl;
        reader.close();
        reader.open("lang/en/" + kind + ".txt");
    }
    
    string temp;
    getline(reader, temp);
    while(!reader.eof())
    {
        cout << temp << endl;
        getline(reader, temp);
    }
    
    cout << temp;
    
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

//graveyard / notes:

//i *think* you were supposed to say -p to tell it to set the port and then
    // -e to tell it to look at the evironment.
    //like: setport -p -e THE_ENV_PORT
    //which makes the logic a bit more difficult.
    //if you look at the co5 requirements you will see what is meant.
    //but, I just added --environment for now, not changing the logic.