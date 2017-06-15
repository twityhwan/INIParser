#ifndef _INI_PARSER_H_
#define _INI_PARSER_H_
#include <fstream>
#include <string>
#include <map>
#include <cstring>

static void trim(std::string& s);

class Parser {
    std::ifstream m_file;
    std::map<std::string, std::map<std::string, std::string> > m_iniMap;
public:
    Parser(const char* filename);
    const std::map<std::string, std::map<std::string, std::string> >
        parse();
    const std::map<std::string, std::map<std::string, std::string> >
        getINIMap();
    const std::map<std::string, std::string> getVariableMap(std::string sname);
    const std::string getValue(std::string sname, std::string key);
    void print();
};

Parser::Parser(const char* filename) : m_file(filename)
{
    if (!m_file.is_open()) {
        std::cout<<"File open failed.. "<<filename<<std::endl;
    }
}

const std::map<std::string, std::map<std::string, std::string> >
Parser::parse()
{
    bool isInSection = false;
    std::string sname;
    std::string line;
    while(std::getline(m_file, line)) {
        trim(line);

        if (line[0] == ';') continue;
        if (line.empty()) {
            isInSection = false;
            continue;
        }
        // section name
        if (!isInSection && line[0] == '[') {
            size_t idx = line.find(']');
            sname = line.substr(1, idx-1);
            isInSection = true;
            continue;
        }

        // key - value
        if (isInSection) {
            size_t idx = line.find('=');
            size_t commentIdx = line.find(';');
            std::string key = line.substr(0, idx);
            std::string value;
            if (commentIdx == std::string::npos)
                value = line.substr(idx+1);
            else
                value = line.substr(idx+1, commentIdx);
            m_iniMap[sname][key] = value;
        }
    }

    return m_iniMap;
}

const std::map<std::string, std::map<std::string, std::string> >
Parser::getINIMap()
{
    return m_iniMap;
}

const std::map<std::string, std::string>
Parser::getVariableMap(std::string sname)
{
    return m_iniMap[sname];
}

const std::string
Parser::getValue(std::string sname, std::string key)
{
    return m_iniMap[sname][key];
}

void
Parser::print()
{
    std::map<std::string, std::map<std::string, std::string> >::iterator it
        = m_iniMap.begin();
    for (it; it!=m_iniMap.end(); ++it) {
        std::map<std::string, std::string>::iterator it2 = it->second.begin();
        std::cout << "["<< it->first <<"]"<< std::endl;
        for (it2; it2!=it->second.end(); ++it2) {
            std::cout << it2->first << " = " << it2->second << std::endl;
        }
    }
}

void trim(std::string& s)
{
    char p[] = " \t\r\n";
    size_t begin = s.find_first_of(p);
    while(begin != std::string::npos) {
        size_t noSpaceIdx = s.find_first_not_of(p);
        s.erase(begin, noSpaceIdx-begin);
        begin = s.find_first_of(p);
    }
}
#endif
