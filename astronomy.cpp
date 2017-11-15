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

int main(int argc, char* argv[])
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

    //Create filestream- will end up being based off of the user arguments, but
    //currently is just setup to allow my function to hardcode 25 lines.
    std::ifstream temp;
    int line_count = autocollimator::lineCounter(temp);

    //Declare a multidimensional array to hold my information. Will be moved out of main.
    std::string data[line_count][3];

    //Read the data from the file, run conversions, and store in the above declared array.
    autocollimator::readData( data,line_count );

    //Sort the above arrays smallest to largest based on width.
    autocollimator::sortData( data,line_count );

    //Write the now sorted arrays out to the file in the specified format.
    autocollimator::writeData( data,line_count );

    //Print out that we're done.
    std::cout << "ok\n";
}
