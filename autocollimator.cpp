#include <iostream>
#include <iomanip>
#include <fstream>
#include <assert.h>
#include <sstream>
#include <cmath>
//#define NDEBUG
#include "astronomy.h"
#include "autocollimator.h"

std::string* guid;
int* arcseconds;
float* width;

//reads the data and runs conversions, storing in the multidimensional array.
void autocollimator::readData()
{
    //Declare arrays to hold my information. Will be moved out of main.
    guid = autocollimator::createStringArray();
    arcseconds = autocollimator::createIntArray();
    width = autocollimator::createFloatArray();

    //open filestream and check for failure. Will be moved.
    std::ifstream planetary_data;
    planetary_data.open( autocollimator::INPUTDATA );
    if( !planetary_data.is_open() )
    {
        std::cout << "Unable to open one of the files. input" << std::endl;
        std::exit( EXIT_FAILURE );
    }

    //Define a counter for the rows of the arrays.
    int r = 0;

    // Start a do while loop to parse through the file loading info into the arrays.
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

            //Take first line after second comma and until the end of the line 
            //and store in distance field. Use ' ' as a delimitor to drop the au
            //at the end of the lines.
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


            long double width_temp = widthCalc( arc_seconds , distance );

            guid[r] = guid_temp;
            arcseconds[r] = arc_seconds;
            width[r] = width_temp;
        }
        r++;
    }while( !planetary_data.eof() );
    planetary_data.close();
}

//Working
void autocollimator::writeData() 
{
    using namespace autocollimator;
    std::ofstream planetary_log( autocollimator::OUTPUTDATA );

    if( !planetary_log.is_open() )
    {
        std::cout << "The file was unable to open. output" << std::endl;
    }

    for( int r = 0; r < autocollimator::lineCounter(); r++ )
    {
        planetary_log << "guid:" << guid[r] << " " 
                     // << "microradians:" << std::setw(16) << std::setprecision(15) 
                     // << arcsec2Rad(stoi(data[r][1])) << " " 
                      << "arcseconds:" << std::setw(5) << arcseconds[r] << " "
                      << "width:" << std::setw(10) << std::setprecision(10) << width[r]
                      << std::endl;
    }

    planetary_log.close();
}

//Unwritten
void autocollimator::sortData()
{
    for( int r = 0; r < autocollimator::lineCounter(); r++ )
    {
        std::cout << r << std::endl;
        for( int i = 0; i < ( autocollimator::lineCounter() - r - 1 ); i++ )
        {
            std::cout << i << std::endl;
            if( width[i] > width[i+1] )
            {
                std::swap( guid[i], guid[i+1] );
                std::swap( arcseconds[i], arcseconds[i+1] );
            }
        }
    }
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
        std::cout << i << std::endl;
        degrees += dms.get();
    }

    //This loops over and puts the next two characters (two bytes which 
    //totals the  degree symbol) on each line into the trash.
    for( int i = 0; i < 2; i++)
    {
        std::cout << i << std::endl;
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
float autocollimator::arcsec2Rad( int arc_sec )
{
    using namespace astronomy::conversions;
    float microradians = arc_sec * arcsec2microrad;
    return microradians;
}

int autocollimator::lineCounter()
{
    std::ifstream data_input( autocollimator::INPUTDATA );
    int line_count = 0;

    if( data_input.is_open() )
    {
        std::string line;

        do
        {
            if( getline( data_input, line ) && line.length() > 0 )
            {
                line_count++;
            }
        } while( !data_input.eof() );
        data_input.close();
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    return line_count;
}

float autocollimator::widthCalc( int arcsec, float distance )
{
    //Convert from arcseconds to radians.
    float microradians = autocollimator::arcsec2Rad( arcsec );
    float radians = microradians / astronomy::conversions::micro2norm;

    float au_width;
    float km_width;

    au_width = ((2.0 * distance) * (std::tan(radians/2.0)));

    km_width = (au_width * 149597871.0);
    return km_width;
}

std::string* autocollimator::createStringArray()
{
    int length = autocollimator::lineCounter();
    std::string* newArray = new std::string[length];
    return newArray;
}

int* autocollimator::createIntArray()
{
    int length = autocollimator::lineCounter();
    int* newArray = new int[length];
    return newArray;
}

float* autocollimator::createFloatArray()
{
    int length = autocollimator::lineCounter();
    float* newArray = new float(length);
    return newArray;
}



void autocollimator::clearData()
{
    delete guid;
    guid = nullptr;

    delete arcseconds;
    arcseconds = nullptr;

    delete width;
    width = nullptr;
}



/*
string* creatFinalArray( some number of streams)
{
    string[argc-1] shortArrays[argc-1] = {0}
    
    for(int i=0; i<argc-1; i++)
    {
        shortArrays[i] = 
    string* file3Array = autocollimator::createArray(autocollimator::lineCounter(stream3));

    string* finalArray = autocollimator::createArray( autocollimator::lineCounter(stream1) + autocollimator::lineCounter(stream2) + autocollimator::lineCounter(stream3) );
    
    r = 0;
    copyArray(r,file1Array, finalArray);
    copyArray(r,file2Array, finalArray);
    copyArray(r,file3Array, finalArray);
}

for(i=0;i<argc-1;i++)
{
    std::ifstream file */
