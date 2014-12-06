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

#ifndef ENGINE_GAMELOGIC_PRUNING_WORLD_GUARD
#define ENGINE_GAMELOGIC_PRUNING_WORLD_GUARD

#include <set>
#include <map>
#include <queue>
#include <memory>
#include <cmath>
#include <cfloat>
#include <algorithm>
#include <iterator>

#include "engine/geometry/Vector.hpp"
#include "engine/geometry/Rectangle.h"
#include "engine/geometry/Interval.hpp"

namespace engine
{
    namespace gamelogic
    {
        std::set < geometry::Vector < int > > get_neighbors ( geometry::Vector < int > chunk );

        template < typename Entity >
            class Pruning_world {
                public:
                    Pruning_world ( double chunk_size );

                    void add_entity ( std::shared_ptr < Entity > entity );

                    void remove_entity ( std::shared_ptr < Entity > entity );
                    void remove_entity ( Entity* entity );

                    void update_pruning ( std::shared_ptr < Entity > entity );
                    void update_pruning ( Entity* entity );

                    std::set < std::shared_ptr < Entity > > get_collisions ( geometry::Vector < int > position ) const;
                    std::set < std::shared_ptr < Entity > > get_collisions ( geometry::Vector < double > position ) const;
                    std::set < std::shared_ptr < Entity > > get_collisions ( geometry::Rectangle rectangle ) const;
                    std::set < geometry::Vector < int > > get_chunk_collisions ( geometry::Rectangle rectangle ) const;

                    geometry::Vector < int > get_chunk ( geometry::Vector < double > position ) const;
                    geometry::Rectangle get_chunk_rectangle ( geometry::Vector < int > chunk ) const;

                private:
                    double chunk_size;

                    std::map < Entity*, std::shared_ptr < Entity > > entities;
                    std::map < geometry::Vector < int >, std::set < std::shared_ptr < Entity > > > chunks;

                    void clear_pruning ( std::shared_ptr < Entity > entity );
                    void calculate_pruning ( std::shared_ptr < Entity > entity );
            };

        inline std::set < geometry::Vector < int > > get_neighbors ( geometry::Vector < int > chunk )
        {
            return
            {
                { chunk.get_x (), chunk.get_y () + 1 },
                { chunk.get_x (), chunk.get_y () - 1 },
                { chunk.get_x () + 1, chunk.get_y () },
                { chunk.get_x () - 1, chunk.get_y () },
                { chunk.get_x () + 1, chunk.get_y () + 1 },
                { chunk.get_x () + 1, chunk.get_y () - 1 },
                { chunk.get_x () - 1, chunk.get_y () + 1 },
                { chunk.get_x () - 1, chunk.get_y () - 1 },
            };
        }

        template < typename Entity >
            Pruning_world < Entity >::Pruning_world ( double chunk_size ) :
                chunk_size ( chunk_size )
            {}

        template < typename Entity >
            void Pruning_world < Entity >::add_entity ( std::shared_ptr < Entity > entity )
            {
                entities.insert ( { entity.get (), entity } );
                calculate_pruning ( entity );
            }

        template < typename Entity >
            void Pruning_world < Entity >::remove_entity ( std::shared_ptr < Entity > entity )
            {
                clear_pruning ( entity );
                entities.erase ( entity.get () );
            }

        template < typename Entity >
            void Pruning_world < Entity >::remove_entity ( Entity* entity )
            {
                remove_entity ( entities.at ( entity ) );
            }

        template < typename Entity >
            void Pruning_world < Entity >::update_pruning ( std::shared_ptr < Entity > entity )
            {
                clear_pruning ( entity );
                calculate_pruning ( entity );
            }

        template < typename Entity >
            void Pruning_world < Entity >::update_pruning ( Entity* entity )
            {
                update_pruning ( entities.at ( entity ) );
            }

        template < typename Entity >
            std::set < std::shared_ptr < Entity > > Pruning_world < Entity >::get_collisions ( geometry::Vector < int > chunk ) const
            {
                auto iter = chunks.find ( chunk );
                if ( iter == chunks.end () )
                    return {};
                return iter->second;
            }

        template < typename Entity >
            std::set < std::shared_ptr < Entity > > Pruning_world < Entity >::get_collisions ( geometry::Vector < double > position ) const
            {
                std::set < std::shared_ptr < Entity > > candidates = get_collisions ( get_chunk ( position ) );
                std::set < std::shared_ptr < Entity > > collisions;
                std::copy_if
                (
                    candidates.begin (),
                    candidates.end (),
                    std::inserter ( collisions, collisions.begin () ),
                    [ position ] ( const std::shared_ptr < Entity >& entity )
                    {
                        return entity->get_collision_box ().collides ( position );
                    }
                );
                return collisions;
            }

        template < typename Entity >
            std::set < std::shared_ptr < Entity > > Pruning_world < Entity >::get_collisions ( geometry::Rectangle rectangle ) const
            {
                std::set < geometry::Vector < int > > chunk_collisions = get_chunk_collisions ( rectangle );
                std::set < std::shared_ptr < Entity > > candidates;
                for ( geometry::Vector < int > chunk : chunk_collisions )
                {
                    for ( std::shared_ptr < Entity > entity : get_collisions ( chunk ) )
                    {
                        candidates.insert ( entity );
                    }
                }
                std::set < std::shared_ptr < Entity > > collisions;
                std::copy_if
                (
                    candidates.begin (),
                    candidates.end (),
                    std::inserter ( collisions, collisions.begin () ),
                    [ rectangle ] ( const std::shared_ptr < Entity >& entity )
                    {
                        return entity->get_collision_box ().collides ( rectangle );
                    }
                );
                return collisions;
            }

        template < typename Entity >
            std::set < geometry::Vector < int > > Pruning_world < Entity >::get_chunk_collisions ( geometry::Rectangle rectangle ) const
            {
                std::set < geometry::Vector < int > > colliding_chunks;
                std::set < geometry::Vector < int > > visited_chunks;
                geometry::Vector < double > corner
                {
                    rectangle.get_x_interval ().get_min (),
                    rectangle.get_y_interval ().get_min ()
                };
                std::queue < geometry::Vector < int > > chunk_queue;
                chunk_queue.push ( get_chunk ( corner ) );
                while ( ! chunk_queue.empty () )
                {
                    geometry::Vector < int > chunk = chunk_queue.front ();
                    chunk_queue.pop ();
                    if ( ! visited_chunks.insert ( chunk ).second )
                    {
                        continue;
                    }
                    geometry::Rectangle chunk_box = get_chunk_rectangle ( chunk );
                    if ( rectangle.collides ( chunk_box ) )
                    {
                        colliding_chunks.insert ( chunk );
                        for ( geometry::Vector < int > neighbor : get_neighbors ( chunk ) )
                        {
                            chunk_queue.push ( neighbor );
                        }
                    }
                }
                return colliding_chunks;
            }

        template < typename Entity >
            geometry::Vector < int > Pruning_world < Entity >::get_chunk ( geometry::Vector < double > position ) const
            {
                return
                {
                    ( int ) std::floor ( position.get_x () / chunk_size ),
                    ( int ) std::floor ( position.get_y () / chunk_size ),
                };
            }

        template < typename Entity >
            geometry::Rectangle Pruning_world < Entity >::get_chunk_rectangle ( geometry::Vector < int > chunk ) const
            {
                return
                {
                    geometry::Interval < double >
                    {
                        ( double ) chunk.get_x () * chunk_size,
                        ( double ) ( chunk.get_x () + 1 ) * chunk_size - DBL_EPSILON,
                    },
                    geometry::Interval < double >
                    {
                        ( double ) chunk.get_y () * chunk_size,
                        ( double ) ( chunk.get_y () + 1 ) * chunk_size - DBL_EPSILON,
                    }
                };
            }

        template < typename Entity >
            void Pruning_world < Entity >::clear_pruning ( std::shared_ptr < Entity > entity )
            {
                for ( std::pair < geometry::Vector < int >, std::set < std::shared_ptr < Entity > > > pair : chunks )
                {
                    pair.second.erase ( entity );
                    chunks [ pair.first ] = pair.second;
                }
            }

        template < typename Entity >
            void Pruning_world < Entity >::calculate_pruning ( std::shared_ptr < Entity > entity )
            {
                for ( geometry::Vector < int > chunk : get_chunk_collisions ( entity->get_collision_box () ) )
                {
                    chunks [ chunk ].insert ( entity );
                }
            }

    } /* namespace gamelogic */
} /* namespace engine */

#endif // ENGINE_GAMELOGIC_PRUNING_WORLD_GUARD
