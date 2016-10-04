/*
    Test Script For PortSetter
    Nick Pray
    CS-3370
*/
#include <iostream>
#include <fstream>

using namespace std;

int FormatCode(int);

const int CODE_FORMATTER = 256;
const int CODE_SUCCESS = 0;
const int CODE_INVALID_SYNTAX = 1;
const int CODE_INVALID_INPUT = 2;
const int CODE_INVALID_PORT = 3;

int main(int argc,  char* argv[]){
    
    //Get this files path
    string path = argv[0];
    path = path.substr(0, path.find_last_of("\\/"));
    
    //Set the path variable to the current path
    setenv("SET_PORT", &path[0], 1);
    
    cout << "Running Tests:" << endl;
    
    //Setport
    int statusCode = system("./setport > $SET_PORT/templates/__out") / 256;
    cout << "setport code: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/usage > /dev/null") / 256;
    cout << "setport output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //Setport -h
    statusCode = system("./setport -h > $SET_PORT/templates/__out") / 256;
    cout << "setport -h code: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/usage > /dev/null") / 256;
    cout << "setport -h output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport --help
    statusCode = system("./setport --help > $SET_PORT/templates/__out") / 256;
    cout << "setport --help code: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/usage > /dev/null") / 256;
    cout << "setport --help output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport -p 4040
    statusCode = system("./setport -p 4040 > $SET_PORT/templates/__out") / 256;
    cout << "setport -p 4040 code: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/success > /dev/null") / 256;
    cout << "setport -p 4040 output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport --port 4040
    statusCode = system("./setport --port 4040 > $SET_PORT/templates/__out") / 256;
    cout << "setport --port 4040 code: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/success > /dev/null") / 256;
    cout << "setport --port 4040 output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport help
    statusCode = system("./setport help > $SET_PORT/templates/__out") / 256;
    cout << "setport help code: " << ((statusCode == CODE_INVALID_SYNTAX) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_flag > /dev/null") / 256;
    cout << "setport help output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport -help
    statusCode = system("./setport -help > $SET_PORT/templates/__out") / 256;
    cout << "setport -help code: " << ((statusCode == CODE_INVALID_SYNTAX) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_flag > /dev/null") / 256;
    cout << "setport -help output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport --h
    statusCode = system("./setport --h > $SET_PORT/templates/__out") / 256;
    cout << "setport --h code: " << ((statusCode == CODE_INVALID_SYNTAX) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_flag > /dev/null") / 256;
    cout << "setport --h output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport -h --help
    statusCode = system("./setport -h --help > $SET_PORT/templates/__out") / 256;
    cout << "setport -h --help code: " << ((statusCode == CODE_INVALID_PORT) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_param_count > /dev/null") / 256;
    cout << "setport -h --help output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport -hs
    statusCode = system("./setport -hs > $SET_PORT/templates/__out") / 256;
    cout << "setport -hs code: " << ((statusCode == CODE_INVALID_SYNTAX) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_flag > /dev/null") / 256;
    cout << "setport -hs output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport -p --port 9
    statusCode = system("./setport -p --port 9 > $SET_PORT/templates/__out") / 256;
    cout << "setport -p --port 9 code: " << ((statusCode == CODE_INVALID_SYNTAX) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_param_count > /dev/null") / 256;
    cout << "setport -p --port 9 output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport -p 77 33
    statusCode = system("./setport -p 77 33 > $SET_PORT/templates/__out") / 256;
    cout << "setport -p 77 33 code: " << ((statusCode == CODE_INVALID_SYNTAX) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_param_count > /dev/null") / 256;
    cout << "setport -p 77 33 output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport -p -21
    statusCode = system("./setport -p -21 > $SET_PORT/templates/__out") / 256;
    cout << "setport -p -21 code: " << ((statusCode == CODE_INVALID_PORT) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_invalid_port > /dev/null") / 256;
    cout << "setport -p -21 output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport -p 0
    statusCode = system("./setport -p 0 > $SET_PORT/templates/__out") / 256;
    cout << "setport -p 0 code: " << ((statusCode == CODE_INVALID_PORT) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_invalid_port > /dev/null") / 256;
    cout << "setport -p 0 output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport --port
    statusCode = system("./setport --port > $SET_PORT/templates/__out") / 256;
    cout << "setport --port code: " << ((statusCode == CODE_INVALID_PORT) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_missing_port > /dev/null") / 256;
    cout << "setport --port output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport -p 90642
    statusCode = system("./setport -p 90642 > $SET_PORT/templates/__out") / 256;
    cout << "setport -p 90642 code: " << ((statusCode == CODE_INVALID_PORT) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_invalid_port > /dev/null") / 256;
    cout << "setport -p 90642 output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport -x 45321
    statusCode = system("./setport -x 45321 > $SET_PORT/templates/__out") / 256;
    cout << "setport -x 45321 code: " << ((statusCode == CODE_INVALID_SYNTAX) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_flag > /dev/null") / 256;
    cout << "setport -x 45321 output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
    
    //setport -P 714
    statusCode = system("./setport -P 714 > $SET_PORT/templates/__out") / 256;
    cout << "setport -P 714 code: " << ((statusCode == CODE_INVALID_SYNTAX) ? "Success" : "Fail") << endl;
    
    statusCode = system("diff $SET_PORT/templates/__out $SET_PORT/templates/err_flag > /dev/null") / 256;
    cout << "setport -P 714 output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;

    //Remove the temporary file
    system("rm $SET_PORT/templates/__out");
    
}