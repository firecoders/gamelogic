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

#include "engine/geometry/Vector.hpp"

using namespace engine::geometry;

TEST ( engineGeometryVector, memberVariables )
{
    Vector < int > v { 1, 42 };
    EXPECT_EQ ( 1, v.get_x () );
    EXPECT_EQ ( 42, v.get_y () );
    v.set_x ( 4 );
    EXPECT_EQ ( 4, v.get_x () );
    EXPECT_EQ ( 42, v.get_y () );
    v.set_y ( 8 );
    EXPECT_EQ ( 4, v.get_x () );
    EXPECT_EQ ( 8, v.get_y () );
}

TEST ( engineGeometryVector, compareOperators )
{
    Vector < int > a { 1, 42 };
    EXPECT_TRUE  ( a == a );
    EXPECT_FALSE ( a < a );
    Vector < int > b { 5, 42 };
    EXPECT_FALSE ( a == b );
}

TEST ( engineGeometryVector, length )
{
    Vector < int > a { 0, 42 };
    EXPECT_EQ ( 42, a.get_length () );
    Vector < float > b { 1, 1 };
    EXPECT_FLOAT_EQ ( std::sqrt ( 2 ), b.get_length () );
}

TEST ( engineGeometryVector, lexicographicalCompare )
{
    Vector < int > v1_0 { 1, 0 };
    Vector < int > v2_0 { 2, 0 };
    EXPECT_TRUE ( v1_0 < v2_0 );
    EXPECT_FALSE ( v2_0 < v1_0 );
    Vector < int > v0_3 { 0, 3 };
    EXPECT_TRUE ( v0_3 < v1_0 );
    EXPECT_TRUE ( v0_3 < v2_0 );
    EXPECT_FALSE ( v1_0 < v0_3 );
    EXPECT_FALSE ( v2_0 < v0_3 );
}

TEST ( engineGeometryVector, mathOperators )
{
    Vector < int > v1_1 { 1, 1 };
    Vector < int > v0_0 { 0, 0 };
    Vector < int > a { 2, 2 };

    EXPECT_EQ ( a, a * v1_1 );
    EXPECT_EQ ( a, a * 1 );

    EXPECT_EQ ( v0_0, a * v0_0 );
    EXPECT_EQ ( v0_0, a * 0 );

    EXPECT_EQ ( a, a / v1_1 );
    EXPECT_EQ ( a, a / 1 );

    EXPECT_EQ ( a, a + v0_0 );
    EXPECT_EQ ( a, a - v0_0 );

    Vector < int > b { 4, 4 };
}
