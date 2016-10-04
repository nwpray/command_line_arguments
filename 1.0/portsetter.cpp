/*
    Command Line Arguments and Gathering Requirements
    Nick Pray
    CS-3370
*/
#include <iostream>
#include <string>

using namespace std;

const int INDEX_FLAG = 1;
const int INDEX_PORT = 2;
const int PORT_MAX = 65535;
const int PORT_MIN = 1;

const string FLAG_PORT = "--port";
const string FLAG_PORT_SHORT = "-p";
const string FLAG_HELP = "--help";
const string FLAG_HELP_SHORT = "-h";
    
const string ERROR_PREFIX = "[!Error!] : ";

void PrintError(const string &error);
void UsagePage();

int main(int argc, char* argv[]){

    int port;
    string flag, rawPort;
    size_t conversionLength;
    
    //User enters too few parameters Program responds with User Page and returns 1
    //User enters too many parameters Program responds with Usage Page and returns 1
    if ( argc < INDEX_FLAG + 1 || argc > INDEX_PORT + 1 ){
        
        PrintError("Invalid parameter count");
        UsagePage();
        return 1;
        
    }
    
    flag = argv[INDEX_FLAG];

    //User enters invalid input Program responds with Usage Page and returns 1
    if ( (flag != FLAG_HELP) && (flag != FLAG_HELP_SHORT) && 
        (flag != FLAG_PORT)  && (flag != FLAG_PORT_SHORT) ){
            
        PrintError("Invalid Flag");
        UsagePage();
        return 1;
        
    }
    
    //User enters -h/--help Program responds with Usage Page and returns 0
    if ((flag == FLAG_HELP) || (flag == FLAG_HELP_SHORT)){
        
        UsagePage();
        return 0;
    }
    
    //User enters -p/--port but no port number Program responds with Usage Page and returns 3
    if( ((flag == FLAG_PORT) || (flag == FLAG_PORT_SHORT)) && argc < INDEX_PORT + 1 )
    {
        PrintError("Missing port number");
        UsagePage();
        return 3;
    }
    
    rawPort = argv[INDEX_PORT];
    
    //User enters bad port number Program responds with Usage Page and returns 3
    try
    {
        port = stoi(rawPort, &conversionLength);
    }
    catch(exception e)
    {
        PrintError("Invalid port number");
        UsagePage();
        return 3;
    }
    
    //User enters bad port number Program responds with Usage Page and returns 3
    if((rawPort.substr(0,conversionLength).size() != rawPort.size()) || port < PORT_MIN || port > PORT_MAX)
    {
        PrintError("Invalid port number");
        UsagePage();
        return 3;
    }
    
    cout << "Listening on port " << port << "." << endl;
    return 0;
}

//Prints an error prepended by error tag
void PrintError(const string &error){
    
    cout << endl << ERROR_PREFIX << error << endl;
    
}

//Prints out the proper usage of this application
void UsagePage(){
    
    cout << endl << "CS-3370 Port Setter." << endl;
    cout << "Usage: portsetter [FLAG]… [PORT]…" << endl;
    
    cout << "Examples:" << endl;
    cout << "\tportsetter -p 1234\t\t#Sets port to listen to" << endl;
    cout << "\tportsetter --port 123\t\t#Sets port to listen to" << endl;
    cout << "\tportsetter -h\t\t\t#Displays this screen" << endl;
    cout << "\tportsetter --help\t\t#Displays this screen" << endl;
    
    cout << "Flags:" << endl;
    cout << "\t-p, --port\t\t\tSpecify which port you want to listen to." << endl;
	cout << "\t-h, --help\t\t\tDisplays this window." << endl;
	
	cout << "Error Codes:" << endl;
	cout << "\t1\t\t\t\tInvalid Input Syntax" << endl;
	cout << "\t2\t\t\t\tInvalid Input" << endl;
	cout << "\t3\t\t\t\tPort out of range" << endl << endl;

}