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

#include "engine/geometry/Interval.hpp"

using namespace engine::geometry;

TEST ( engineGeometryInterval, constructor )
{
    Interval < int > { 1, 0 };
    Interval < int > { 0, 0 };
}

TEST ( engineGeometryInterval, getters )
{
    Interval < char > letters { 'e', 'a' };
    EXPECT_EQ ( 'a', letters.get_min () );
    EXPECT_EQ ( 'e', letters.get_max () );
}

TEST ( engineGeometryInterval, operatorEquals )
{
    Interval < int > a { 1, 0 };
    Interval < int > b { 0, 1 };
    Interval < int > c { 2, 3 };
    EXPECT_TRUE ( a == a );
    EXPECT_TRUE ( a == b );
    EXPECT_FALSE ( a == c );
    EXPECT_FALSE ( b == c );
}

TEST ( engineGeometryInterval, valueCollision )
{
    Interval < int > a { 1, 0 };
    Interval < int > b { 2, 8 };
    EXPECT_TRUE ( a.collides ( 0 ) );
    EXPECT_FALSE ( a.collides ( 4 ) );
    EXPECT_TRUE ( b.collides ( 3 ) );
}

TEST ( engineGeometryInterval, intervalCollision )
{
    Interval < int > a { 1, 0 };
    Interval < int > b { 2, 8 };
    Interval < int > c { -5, 15 };
    EXPECT_FALSE ( a.collides ( b ) );
    EXPECT_TRUE ( a.collides ( a ) );
    EXPECT_TRUE ( c.collides ( b ) );
    EXPECT_TRUE ( b.collides ( c ) );
}
