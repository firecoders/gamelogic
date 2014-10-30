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

#ifndef ENGINE_GEOMETRY_VECTOR_GUARD
#define ENGINE_GEOMETRY_VECTOR_GUARD

#include <string>
#include <sstream>
#include <cmath>

namespace engine
{
    namespace geometry
    {
        template < typename T >
        class Vector
        {
            public:
                Vector ( T x, T y );

                T get_x () const;
                T get_y () const;
                void set_x ( T to );
                void set_y ( T to );

                T get_length () const;
                std::string construct_string () const;

                bool operator== ( const Vector < T >& other ) const;
                bool operator< ( const Vector < T >& other ) const;
                Vector < T > operator+ ( const Vector < T >& other ) const;
                Vector < T > operator- ( const Vector < T >& other ) const;
                Vector < T > operator* ( const Vector < T >& other ) const;
                Vector < T > operator/ ( const Vector < T >& other ) const;
                Vector < T > operator* ( T multiplier ) const;
                Vector < T > operator/ ( T divisor ) const;

            private:
                T x;
                T y;
        };

        template < typename T >
        Vector < T >::Vector ( T x, T y ) :
            x ( x ),
            y ( y )
        {}

        template < typename T >
        T Vector < T >::get_x () const { return x; }
        template < typename T >
        T Vector < T >::get_y () const { return y; }

        template < typename T >
        void Vector < T >::set_x ( T to ) { x = to; }
        template < typename T >
        void Vector < T >::set_y ( T to ) { y = to; }

        template < typename T >
        T Vector < T >::get_length () const
        {
            T under_square_root = x * x + y * y;
            if ( under_square_root < 0 )
                // std::sqrt returns either float or double,
                // so we need to cast back to T
                return T ( - std::sqrt ( - under_square_root ) );
            return T ( std::sqrt ( under_square_root ) );
        }

        template < typename T >
        std::string Vector < T >::construct_string () const
        {
            std::stringstream stream;
            stream << x << ':' << y;
            return stream.str ();
        }

        template < typename T >
        std::ostream& operator<< ( std::ostream& stream, const Vector < T >& vector )
        {
            stream << vector.construct_string ();
            return stream;
        }

        template < typename T >
        bool Vector < T >::operator== ( const Vector < T >& other ) const
        {
            return x == other.x && y == other.y;
        }

        template < typename T >
        bool Vector < T >::operator< ( const Vector < T >& other ) const
        {
            return construct_string () < other.construct_string ();
        }

        template < typename T >
        Vector < T > Vector < T >::operator+ ( const Vector < T >& other ) const
        {
            return { x + other.x, y + other.y };
        }

        template < typename T >
        Vector < T > Vector < T >::operator- ( const Vector < T >& other ) const
        {
            return { x - other.x, y - other.y };
        }

        template < typename T >
        Vector < T > Vector < T >::operator* ( const Vector < T >& other ) const
        {
            return { x * other.x, y * other.y };
        }

        template < typename T >
        Vector < T > Vector < T >::operator/ ( const Vector < T >& other ) const
        {
            return { x / other.x, y / other.y };
        }

        template < typename T >
        Vector < T > Vector < T >::operator* ( T multiplier ) const
        {
            return { x * multiplier, y * multiplier };
        }

        template < typename T >
        Vector < T > Vector < T >::operator/ ( T divisor ) const
        {
            return { x / divisor, y / divisor };
        }
    } /* namespace geometry */
} /* namespace engine */

#endif // ENGINE_GEOMETRY_VECTOR_GUARD
