#ifndef ASTRONOMY_H //Start include guard.
#define ASTRONOMY_H
#include <string>
#include <sstream>

//Currently this is just a decimal conversion factor, will be updated to use ratios.
namespace astronomy
{
    namespace conversions
    {
        const long double arcsec2microrad = 4.8481368110954;
        const long double micro2norm = 1000000;
    }
}
#endif /* ASTRONOMY_H */
