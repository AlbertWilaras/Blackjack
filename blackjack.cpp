#include <iostream>
#include "table.h"

int main()
{

    auto curTable = Table();
    std::cout << "init done\n";
    curTable.resolve();
    std::cout << curTable << "\n";
    return 0;
}