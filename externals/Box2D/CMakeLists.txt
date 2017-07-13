project(Box2D)


include_directories(Box2D/)

file(GLOB_RECURSE Box2D_SRC 
    Box2D/Box2D/*.h Box2D/Box2D/*.cpp)

add_library(Box2D STATIC ${Box2D_SRC})
set_property(TARGET Box2D PROPERTY CXX_STANDARD 11)
