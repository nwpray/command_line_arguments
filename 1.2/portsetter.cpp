/*
    Command Line Arguments and Gathering Requirements
    Nick Pray
    CS-3370
*/
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

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

const string FLAG_ENVIRONMENT= "-e";

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

enum Error {
    ErrFlagInvalid,
    ErrInvalidPort,
    ErrParamCount,
    ErrUnknown
};

map<Error,string> errorMessages;

//Function references
Flag ParseFlag(int, char**);
void CollectErrorMessages();
void PrintError(Error);
void PrintFile(string);

string lang = "en";

int main(int argc, char* argv[]){
        
    Flag flag;
    
    //Load the error messages map
     CollectErrorMessages();
     
    //Parse the flag
    try{
        flag = ParseFlag(argc, argv);
    } catch (Error e){
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
        cout << endl;
        return 0;
    }
    
    //Version
    if(flag == Version){
        PrintFile(FILE_VERSION);
        cout << endl;
        return 0;
    }
    
    int port;
    
    //Environment
    if(flag == Environment){
        
        string temp = argc > INDEX_FLAG + 1 ?  getenv(argv[INDEX_PORT]) : getenv(DEFAULT_ENVIRONMENT_VAR.c_str());
        
        try{
            port = stoi(temp);
        }
        catch(exception e){
            PrintError(ErrInvalidPort);
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
            PrintError(ErrInvalidPort);
            return 1;
        }
        
        //Handles case where port number starts with valid int but ends in chars
        if((rawPort.substr(0,conversionLength).size() != rawPort.size()) || (port < MIN_PORT || port > MAX_PORT))
        {
            PrintError(ErrInvalidPort);
            return 1;
        }
    }
    
    //I have no idea how you got this without a port but this will catch it
    else{
        PrintError(ErrUnknown);
        return 1;
    }
    
    cout << "Listening on port " << port << "." << endl;
    return 0;
}

//Parses the flag into its enumeration, will throw type Error if failed parse or invalid formatting
Flag ParseFlag(int argc, char* argv[]){
    
    if(argc < INDEX_FLAG + 1) return Usage;
    
    string flag = argv[INDEX_FLAG];
    
    //Port
    if(flag == FLAG_PORT || flag == FLAG_PORT_SHORT){
        if(argc < INDEX_PORT + 1 || argc > INDEX_PORT + 1) throw ErrParamCount;
        return Port;
    };
    
    //Environment
    if(flag == FLAG_ENVIRONMENT){
        return Environment;
    };
    
    //Usage
    if(flag == FLAG_HELP || flag == FLAG_HELP_SHORT || flag == FLAG_HELP_SHORT_2){
        if(argc >= INDEX_PORT + 1) throw ErrParamCount;
        return Usage;
    };
    
    //About
    if(flag == FLAG_ABOUT || flag == FLAG_ABOUT_SHORT){
        if(argc >= INDEX_PORT + 1) throw ErrParamCount;
        return About;
    };
    
    //Version
    if(flag == FLAG_VERSION || flag == FLAG_VERSION_SHORT){
        if(argc >= INDEX_PORT + 1) throw ErrParamCount;
        return Version;
    };
    
    //Else
    throw ErrFlagInvalid;
}

//Collect all the error messages
void CollectErrorMessages(){
    
    errorMessages.clear();
    
    ifstream reader("lang/portsetter.errors_eng.json"); 
    
    string temp;
    
    getline(reader, temp);
    errorMessages[ErrFlagInvalid] = temp;
    
    getline(reader, temp);
    errorMessages[ErrParamCount] = temp;
    
    getline(reader, temp);
    errorMessages[ErrInvalidPort] = temp;
    
    getline(reader, temp);
    errorMessages[ErrUnknown] = temp;
    
    reader.close();
}

//Prints an error prepended by error enum
void PrintError(Error e){
    if(errorMessages.find(e) != errorMessages.end()) cout << ERROR_PREFIX << errorMessages.find(e)->second << endl;
    PrintFile(FILE_USAGE);
}

//Prints any of the info files with just the type name
void PrintFile(string kind){
     ifstream reader("templates/portsetter." + kind + "_" + lang + ".txt");
    
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