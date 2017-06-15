#include <iostream>
#include "iniParser.h"
#include <map>

using namespace std;

int main(int argc, char* argv[]) {
    Parser parser("sample.ini");
    parser.parse();
    parser.print();

    map<string, map<string, string> > iniMap = parser.getINIMap();
    cout<<iniMap["Server"]["IP"]<<endl;

    map<string, string> variableMap = parser.getVariableMap("Server");
    cout<<variableMap["IP"]<<endl;

    string ip = parser.getValue("Server", "IP");
    cout<<ip<<endl;
    return 0;
}
