#include <iostream>
#include <iomanip>
#include <fstream>
#include <assert.h>
#include <sstream>
#include <cmath>
//#define NDEBUG
#include "astronomy.h"
#include "autocollimator.h"

//reads the data and runs conversions, storing in the multidimensional array.
void autocollimator::readData( std::string data[][3], int line_count )
{
    //open filestream and check for failure. Will be moved.
    std::ifstream planetary_data;
    planetary_data.open( autocollimator::INPUTDATA );
    if( !planetary_data.is_open() )
    {
        std::cout << "Unable to open one of the files. input" << std::endl;
    }

    //Define a counter for the rows of the array.
    int r = 0;

    // Start a do while loop to parse through the file loading info into the array.
    do
    {
        std::string temp;
        if( getline(planetary_data, temp) )
        {
            std::stringstream tempstream;
            tempstream.str(temp);
            //Declare strings to hold GUID dms and distance for each line.
            std::string guid_temp, dms_temp, distance_temp, trash;

            //Declare ints to hold final dms.
            int d, m, s;

            //Take first line from beginning to the first comma and store in GUID.
            getline( tempstream, guid_temp, ',' );

            //Take first line between first and second commas and store in dms 
            //field.
            getline( tempstream, dms_temp, ',' );

            //Take first line after second comma and until the end of the line and 
            //store in distance field.
            getline( tempstream, distance_temp, ' ' );

            //Trash the rest of the line (from file specs "au".
            getline( tempstream, trash );

            //Convert distance_temp into a floating point value.
            float distance = stof( distance_temp );

            //Declare stream for dms parsing.
            std::stringstream dms;

            //Open dms field string into dms stream for parsing.
            dms.str( dms_temp );

            //Run dms parser on dms stream.
            autocollimator::dmsParser( dms,d,m,s );

            //Run calculator to convert from dms to arc seconds.
            int arc_seconds = autocollimator::arcsecCalc( d, m, s );


            long double width = widthCalc( arc_seconds , distance );
            data[r][0] = guid_temp;
            data[r][1] = arc_seconds;
            data[r][2] = width;
        }
        r++;
    }while( !planetary_data.eof() );
    planetary_data.close();
}

//Working
void autocollimator::writeData( std::string data[][3], int line_count ) 
{
    using namespace autocollimator;
    std::ofstream planetary_log( autocollimator::OUTPUTDATA );

    if( !planetary_log.is_open() )
    {
        std::cout << "The file was unable to open. output" << std::endl;
    }

    for( int r = 0; r < line_count; r++ )
    {
        planetary_log << "guid:" << data[r][0] << " " 
                     // << "microradians:" << std::setw(16) << std::setprecision(15) 
                     // << arcsec2Rad(stoi(data[r][1])) << " " 
                      << "arcseconds:" << std::setw(5) << data[r][1] << " "
                      << "width:" << std::setw(10) << std::setprecision(10) << data[r][2]
                      << std::endl;
    }

    planetary_log.close();
}

//Unwritten
void autocollimator::sortData( std::string data[][3], int line_count )
{
    return;
}

//Working
void autocollimator::dmsParser( std::stringstream& dms, 
                                int& d, int& m, int& s )
{
    

    //Initialize strings to hold the seperated values for degrees, minutes,
    //seconds and a trash string to hold garbage characters. 
    
    //Strings must be initialized as empty as the only assignments append 
    //the new information and don't overwrite anything.
    std::string degrees = "", minutes = "", seconds = "", trash;

    //Due to file specs, the significant characters (numbers) will always
    //be in specific spots:
    //deg: spaces 1 2 and 3
    //min: spaces 5 and 6
    //sec: spaces 8 and 9

    //This loops over and puts the first three characters on each line into
    //the degrees string.
    for( int i = 0; i < 3; i++ )
    {
        degrees += dms.get();
    }

    //This loops over and puts the next two characters (two bytes which 
    //totals the  degree symbol) on each line into the trash.
    for( int i = 0; i < 2; i++)
    {
        trash = dms.get();
    }

    //This loops over and puts the next two characters on each line into
    //the minutes string.
    for( int i = 0; i < 2; i++ )
    {
        minutes += dms.get();
    }

    //This loops over the double quotes on each line and puts it in the
    //trash.
    trash = dms.get();


    for( int i = 0; i < 2; i++ )
    {
        seconds += dms.get();
    }
    for( int i = 0; i < 2; i++ )
    {
        trash = dms.get();
    }
        int deg = stoi(degrees);
        int min = stoi(minutes);
        int sec = stoi(seconds);
        d = deg; 
        m = min;
        s = sec;
}


//Working
int autocollimator::arcsecCalc( int d, int m, int s )
{
    //Convert degrees to minutes.
    int deg2min = d * 60; 

    //Add degrees in minutes to minutes.
    m += deg2min; 

    //Convert degrees and minutes in minutes to seconds.
    int min2sec = m * 60; 

    //Add running total in seconds to seconds.
    s += min2sec; 

    //Return total value in seconds.
    return s;
}

//WIP: need to change to ratio
long double autocollimator::arcsec2Rad( int arc_sec )
{
    using namespace astronomy::conversions;
    long double microradians = arc_sec * arcsec2microrad;
    return microradians;
}

//Broken
int autocollimator::lineCounter( std::ifstream& planetary_log )
{
    /*ifstream data_count(  )
    {
    }*/
    return 25;
}

//Unwritten
long double autocollimator::widthCalc( int arcsec, float distance )
{
    //Convert from arcseconds to radians.
    long double microradians = autocollimator::arcsec2Rad( arcsec );
    return 0;
}
