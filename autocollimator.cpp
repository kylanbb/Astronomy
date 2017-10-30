#include <iostream>
#include <fstream>
#include <assert.h>
//#define NDEBUG
#include "autocollimator.h"

void autocollimator::printData()
{
    using namespace std;

    ifstream angular_data( "./angular.dat" );
    if( !angular_data.is_open() )
    {
        cout << "File was unable to open." << endl;
    }
    else
    {
        do
        {
            string output;
            getline( angular_data, output );
            cout << output << endl;
        }
        while( !angular_data.eof() );
    }
    angular_data.close();
    cout << "OK\n";
}
