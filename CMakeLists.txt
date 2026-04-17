cmake_minimum_required(VERSION 3.23)
project(GeometrySurvivor)


#-------------DECLARE FILES---------------------
#MAIN
set(APP_SRC
        src/main.cpp
)

#LIBRARY HEADERS

set(LIB_HEADERS
        include/Game.h
        include/SDL_wrapper.h
        include/Vector2D.h
        include/State.h
        include/PlayingState.h
        include/Components/Component.h
        include/Components/TransformComponent.h
        include/Components/ComponentsList.h
        include/Entity.h
        include/EntityManager.h

)

#LIBRARY SOURCES

set(LIB_SRC
        src/Game.cpp
        src/PlayingState.cpp
        src/Components/TransformComponent.cpp
        src/EntityManager.cpp

)


#-----------Library dependency---------#


include(FetchContent)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.0 
)

FetchContent_MakeAvailable(SDL2)



add_library(Library)

target_sources(Library
    PRIVATE
        ${LIB_SRC}
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include
        FILES
            ${LIB_HEADERS}

)
target_link_libraries(Library 
    PUBLIC 
        SDL2::SDL2
)

add_executable(GeometrySurvivorApp)
target_sources(GeometrySurvivorApp
    PRIVATE
        ${APP_SRC}
)

target_link_libraries(GeometrySurvivorApp 
    PRIVATE 
        Library
)

