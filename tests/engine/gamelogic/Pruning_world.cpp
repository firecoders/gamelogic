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

#include "engine/gamelogic/Pruning_world.hpp"
#include "engine/geometry/Rectangle.h"

using namespace engine;
using namespace engine::gamelogic;

class Entity {
    public:
        Entity ( geometry::Rectangle collision_box ) :
            collision_box ( collision_box )
        {}

        geometry::Rectangle get_collision_box () const
        {
            return collision_box;
        }

    private:
        geometry::Rectangle collision_box;
};

TEST ( engineGamelogicPruningWorld, basicTest )
{
    Pruning_world < Entity > w ( 10 );
    geometry::Vector < double > some_position { 5.8, -24.0 };
    EXPECT_EQ ( 0, w.get_collisions ( some_position ).size () );
    geometry::Rectangle some_rect { geometry::Interval < double > { -10, 15 }, { 0, 0.2 } };
    auto some_entity = std::make_shared < Entity > ( some_rect );
    EXPECT_TRUE ( some_entity->get_collision_box ().collides ( some_rect ) );
    w.add_entity ( some_entity );
    EXPECT_EQ ( 0, w.get_collisions ( some_position ).size () );
    geometry::Vector < double > colliding_position { 0, 0 };
    EXPECT_EQ ( 1, w.get_collisions ( colliding_position ).size () );
    w.update_pruning ( some_entity );
    EXPECT_EQ ( 1, w.get_collisions ( colliding_position ).size () );
    EXPECT_EQ ( 1, w.get_collisions ( some_rect ).size () );
    w.remove_entity ( some_entity );
    EXPECT_EQ ( 0, w.get_collisions ( some_rect ).size () );
}
