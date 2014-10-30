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

#include "engine/geometry/Rectangle.h"

using namespace engine::geometry;

Rectangle::Rectangle ( Interval < double > x_interval, Interval < double > y_interval ) :
    x_interval ( x_interval ),
    y_interval ( y_interval )
{}

Rectangle::Rectangle ( Vector < double > a, Vector < double > b ) :
    x_interval ( a.get_x (), b.get_x () ),
    y_interval ( a.get_y (), b.get_y () )
{}

bool Rectangle::operator== ( const Rectangle& other ) const
{
    return x_interval == other.x_interval
        && y_interval == other.y_interval;
}

bool Rectangle::collides ( const Vector < double >& position ) const
{
    return x_interval.collides ( position.get_x () )
        && y_interval.collides ( position.get_y () );
}

bool Rectangle::collides ( const Rectangle& other ) const
{
    return x_interval.collides ( other.x_interval )
        && y_interval.collides ( other.y_interval );
}

Interval < double > Rectangle::get_x_interval () const
{
    return x_interval;
}

Interval < double > Rectangle::get_y_interval () const
{
    return y_interval;
}
