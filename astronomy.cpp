#include <string>
#include <iostream>
#include <fstream>
#include "autocollimator.h"

int main()
{
    using namespace autocollimator;

    //std::ifstream temp;
    //int line_count = lineCounter(temp);
    int line_count = 25;

    std::string data[line_count][3];

    readData( data,line_count );

    sortData( data,line_count );

    writeData( data,line_count );

    std::cout << "ok\n";
}
