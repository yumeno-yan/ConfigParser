#include <iostream>
#include "IniParser.h"

int main()
{
    auto iniconfig = IniParser();
    iniconfig.parser("../configs/config.ini");
    std::cout << iniconfig.get("color", "white");
    return 0;
}