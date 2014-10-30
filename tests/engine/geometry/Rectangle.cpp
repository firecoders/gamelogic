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

#include <gtest/gtest.h>

#include "engine/geometry/Rectangle.h"

using namespace engine::geometry;

TEST ( engineGeometryRectangle, constructor )
{
    Rectangle a { Interval < double > { -1, 3 }, Interval < double > { 2, 5 } };
    Rectangle b { Vector < double > { -1, 2 }, Vector < double > { 3, 5 } };
}

TEST ( engineGeometryRectangle, operatorEquals )
{
    Rectangle a { Interval < double > { -1, 3 }, Interval < double > { 2, 5 } };
    Rectangle b { Vector < double > { -1, 2 }, Vector < double > { 3, 5 } };
    Rectangle c { Vector < double > { -1, 12 }, Vector < double > { 3, 5 } };
    EXPECT_TRUE ( a == b );
    EXPECT_TRUE ( a == a );
    EXPECT_FALSE ( c == a );
}

TEST ( engineGeometryRectangle, vectorCollision )
{
    Rectangle r { Interval < double > { -1, 3 }, Interval < double > { 2, 5 } };
    Vector < double > v0_0 { 0, 0 };
    Vector < double > v0_3 { 0, 3 };
    EXPECT_TRUE ( r.collides ( v0_3 ) );
    EXPECT_FALSE ( r.collides ( v0_0 ) );
}

TEST ( engineGeometryRectangle, rectangleCollision )
{
    Rectangle a { Interval < double > { -1, 3 }, Interval < double > { 2, 5 } };
    Rectangle b { Interval < double > { 0, 3 }, Interval < double > { 3, 4 } };
    Rectangle c { Interval < double > { 0, 3 }, Interval < double > { -12, -17 } };
    EXPECT_TRUE ( a.collides ( a ) );
    EXPECT_TRUE ( b.collides ( a ) );
    EXPECT_FALSE ( c.collides ( a ) );
}

TEST ( engineGeometryRectangle, getters )
{
    Interval < double > x_interval { -1, 3 };
    Interval < double > y_interval { 2, 5 };
    Rectangle r { x_interval, y_interval };
    EXPECT_EQ ( x_interval, r.get_x_interval () );
    EXPECT_EQ ( y_interval, r.get_y_interval () );
}
