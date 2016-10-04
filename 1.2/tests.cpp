/*
    Test Script For PortSetter
    Nick Pray
    CS-3370
*/
#include <iostream>
#include <fstream>

using namespace std;

int FormatCode(int);
void RunTest(string, string, int);

const int CODE_FORMATTER = 256;
const int CODE_SUCCESS = 0;
const int CODE_FAIL = 1;

string lang = "en";

int main(int argc,  char* argv[]){
    
    //Get this files path
    string path = argv[0];
    path = path.substr(0, path.find_last_of("\\/"));
    
    //Set the path variable to the current path
    setenv("SET_PORT", &path[0], 1);
    
    RunTest("./setport", "/templates/portsetter.usage_" + lang + ".txt", CODE_SUCCESS);
    RunTest("./setport -h", "/templates/portsetter.usage_" + lang + ".txt", CODE_SUCCESS);
    RunTest("./setport --help", "/templates/portsetter.usage_" + lang + ".txt", CODE_SUCCESS);
    RunTest("./setport -p 4040", "/templates/portsetter.success_" + lang + ".txt", CODE_SUCCESS);
    RunTest("./setport --port 4040", "/templates/portsetter.success_" + lang + ".txt", CODE_SUCCESS);
    RunTest("./setport help", "/templates/portsetter.err_invalid_flag_" + lang + ".txt", CODE_FAIL);
    RunTest("./setport -help", "/templates/portsetter.err_invalid_flag_" + lang + ".txt", CODE_FAIL);
    RunTest("./setport --h", "/templates/portsetter.err_invalid_flag_" + lang + ".txt", CODE_FAIL);
    RunTest("./setport -h --help", "/templates/portsetter.err_param_count_" + lang + ".txt", CODE_FAIL);
    RunTest("./setport -hs", "/templates/portsetter.err_invalid_flag_" + lang + ".txt", CODE_FAIL);
    RunTest("./setport -p --port 9", "/templates/portsetter.err_param_count_" + lang + ".txt", CODE_FAIL);
    RunTest("./setport -p 77 33", "/templates/portsetter.err_param_count_" + lang + ".txt", CODE_FAIL);
    RunTest("./setport -p -21", "/templates/portsetter.err_invalid_port_" + lang + ".txt", CODE_FAIL);
    RunTest("./setport -p 0", "/templates/portsetter.err_invalid_port_" + lang + ".txt", CODE_FAIL);
    RunTest("./setport --port", "/templates/portsetter.err_param_count_" + lang + ".txt", CODE_FAIL);
    RunTest("./setport -p 90642", "/templates/portsetter.err_invalid_port_" + lang + ".txt", CODE_FAIL);
    RunTest("./setport -x 45321", "/templates/portsetter.err_invalid_flag_" + lang + ".txt", CODE_FAIL);
    RunTest("./setport -P 714", "/templates/portsetter.err_invalid_flag_" + lang + ".txt", CODE_FAIL);
    
    //Remove the temporary file
    //system("rm $SET_PORT/templates/__out");
    
}

void RunTest(string command, string check, int checkCode){
    
    string temp;
    
    //Setport
    int statusCode = system((command + " > $SET_PORT/templates/__out").c_str()) / 256;
    cout << command + " code: " << ((statusCode == checkCode) ? "Success" : "Fail") << endl;
    
    statusCode = system(("diff $SET_PORT/templates/__out $SET_PORT" + check  + " > /dev/null").c_str()) / 256;
    cout << command + " output: " << ((statusCode == CODE_SUCCESS) ? "Success" : "Fail") << endl;
}