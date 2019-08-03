#ifndef REAL_INCLUDED__
#define REAL_INCLUDED__

//
// this header file defines some basic types
// and constants
//
// the idea, as well as the names of variables and the file,
// of having such a configuration file is from GTL
// (and perhaps they borrowed it from OpenGL :p )
//
// the URL of GTL:
//   http://www.nigels.com/glt/
//
// however, the contents here is quite different from
// the math/real.h in GTL
//

#include <math.h>
#include <limits>

namespace TinyGraphics { 

  typedef double real;

  // Constants 
  const real TG_PI     = 2.0 * acos(0.0);
  const real TG_2PI    = 4.0 * acos(0.0);
  const real TG_PI_2   = acos(0.0);
  const real TG_PI_DEG = TG_PI / 180.0;
  const real TG_DEG_PI = 180.0 / TG_PI;

  const real TG_EPSILON = 1.0E-10;
}

#endif
