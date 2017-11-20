/* 
 * Author: Kylan Byrd
 * Date: 11/15/2017
 *
 * Version: 0.5
 *
 * Currently: takes data from an input file of length 25 lines, and copies out 
 * planet's GUID, the angular data in microradians and arcseconds, and finally 
 * the width. This is all sorted by width smallest to largest.
 */
#include <string>
#include <iostream>
#include <fstream>
#include "autocollimator.h"

int main( int argc, char* argv[] )
{
    /**
     * Register an exit handler for
     * autocollimator function library.
     * */
    //std::atexit( autocollimator::exit_autocollimator );

    /* Show all the command line arguments. */
    for (int i=0; i<argc; i++ )
    {
        std::cout << "argv[" << i << "]\t" << argv[i] << "\n";
    }
    
    //Read the data from the file, run conversions, and store in the above declared array.
    autocollimator::readData();

    //Sort the above arrays smallest to largest based on width.
    autocollimator::sortData();

    //Write the now sorted arrays out to the file in the specified format.
    autocollimator::writeData();

    //Print out that we're done.
    std::cout << "ok\n";
}
