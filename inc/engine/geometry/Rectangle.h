/* gamelogic, A C++ library for 2D games
   Copyright (c) 2014 firecoders

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE. */

#ifndef ENGINE_GEOMETRY_RECTANGLE_GUARD
#define ENGINE_GEOMETRY_RECTANGLE_GUARD

#include "engine/geometry/Vector.hpp"
#include "engine/geometry/Interval.hpp"

namespace engine
{
    namespace geometry
    {
        class Rectangle
        {
            public:
                Rectangle ( Interval < double > x_interval, Interval < double > y_interval );
                Rectangle ( Vector < double > a, Vector < double > b );

                bool operator== ( const Rectangle& other ) const;

                bool collides ( const Vector < double >& position ) const;
                bool collides ( const Rectangle& other ) const;

                Interval < double > get_x_interval () const;
                Interval < double > get_y_interval () const;

            private:
                Interval < double > x_interval;
                Interval < double > y_interval;
        };
    } /* namespace geometry */
} /* namespace engine */

#endif // ENGINE_GEOMETRY_RECTANGLE_GUARD
