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
    int lineCounter();
    void readData(); 
    int arcsecCalc( int d, int m, int s );
    float arcsec2Rad( int arc_sec);
    float widthCalc( int arcsec, float distace );
    void dmsParser( 
                      std::stringstream& dms, 
                      int& d, int& m, int& s 
                  );
    void sortData();
    void writeData();

    std::string* createStringArray();
    int* createIntArray();
    float* createFloatArray();

    void clearData();
}

#endif //End include guard started on line 1.
