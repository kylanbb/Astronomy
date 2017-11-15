#ifndef AUTOCOLLIMATOR_H //Start include guard.
#define AUTOCOLLIMATOR_H
#include <string>
#include <sstream>


namespace autocollimator
{
    //Data
    const std::string INPUTDATA = "planetary.dat";
    const std::string OUTPUTDATA = "planetary.log";

    //Functions
    int lineCounter(std::ifstream& planetary_log);
    void readData( std::string data[][3], int length1 ); 
    std::string arcsecCalc(int d, int m, int s);
    long double arcsec2Rad(int arc_sec);
    long double widthCalc(long double microrad, float distace);
    void dmsParser(std::stringstream& dms, 
                   int& d, int& m, int& s 
                   );
    void sortData( std::string data[][3], int length1 );
    void writeData( std::string data[][3], int length1 );
}

#endif //End include guard started on line 1.
