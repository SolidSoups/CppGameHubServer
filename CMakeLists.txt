cmake_minimum_required(VERSION 3.30)
project(GameHub)

set(CMAKE_CXX_STANDARD 20)
# Force console subsystem (important for Windows)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static -Wl,-subsystem,console")

# Create a library target without main.cpp
add_library(GameHubLib 
        Tokenizer.cpp
        Tokenizer.h
        User.cpp
        User.h
        GameHubServer.cpp
        GameHubServer.h
        Game.cpp
        Game.h
        datatypes.h
        TokenParser.cpp
        TokenParser.h
        Command.cpp
        Command.h
        CommandFactory.cpp
        CommandFactory.h
        Player.cpp
        Player.h)

# Create an executable target with main.cpp
add_executable(GameHub main.cpp)

# Link the executable to the library
target_link_libraries(GameHub GameHubLib)

add_subdirectory(Google_tests)