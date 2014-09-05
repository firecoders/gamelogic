# Files needed in libgamelogic.a
file ( GLOB_RECURSE GAMELOGIC_LIBRARY_SRC ${CMAKE_SOURCE_DIR} *.cpp )

# Create libgamelogic and target alias
add_library ( gamelogic ${GAMELOGIC_LIBRARY_SRC} )
add_custom_target ( libgamelogic.a DEPENDS gamelogic )
install ( TARGETS gamelogic ARCHIVE DESTINATION lib )
