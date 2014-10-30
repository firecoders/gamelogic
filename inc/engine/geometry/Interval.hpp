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

#ifndef ENGINE_GEOMETRY_INTERVAL_GUARD
#define ENGINE_GEOMETRY_INTERVAL_GUARD

namespace engine
{
    namespace geometry
    {
        template < typename T >
        class Interval
        {
            public:
                Interval ( T a, T b );

                T get_min () const;
                T get_max () const;

                bool operator== ( const Interval& other ) const;

                bool collides ( T value ) const;
                bool collides ( const Interval& other ) const;

            private:
                T min;
                T max;
        };

        template < typename T >
        Interval < T >::Interval ( T a, T b ) :
            min ( std::min ( a, b ) ),
            max ( std::max ( a, b ) )
        {}

        template < typename T >
        T Interval < T >::get_min () const { return min; }
        template < typename T >
        T Interval < T >::get_max () const { return max; }

        template < typename T >
        bool Interval < T >::operator== ( const Interval& other ) const
        {
            return get_min () == other.get_min ()
                && get_max () == other.get_max ();
        }

        template < typename T >
        bool Interval < T >::collides ( T value ) const
        {
            return value <= get_max ()
                && get_min () <= value;
        }

        template < typename T >
        bool Interval < T >::collides ( const Interval& other ) const
        {
            return collides ( other.get_min () )
                || collides ( other.get_max () )
                || other.collides ( get_min () );
        }

    } /* namespace geometry */
} /* namespace engine */

#endif // ENGINE_GEOMETRY_INTERVAL_GUARD
