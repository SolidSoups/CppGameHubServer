cmake_minimum_required(VERSION 3.30)
project(GameHub)

set(CMAKE_CXX_STANDARD 20)
# Force console subsystem (important for Windows)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static -Wl,-subsystem,console")

add_executable(GameHub main.cpp
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
        CommandFactory.h)
