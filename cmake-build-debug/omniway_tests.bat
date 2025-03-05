@echo off
set exec=GameHub.exe

for /F %%a in ('echo prompt $E ^| cmd') do @set "ESC=%%a"

CALL :printFancy OMNIWAY TESTS
CALL :printFancy (.bat script must be in same directory as "GameHub.exe")

REM Testing create database
CALL :printFancy Testing Create database
CALL :runCmd create_database me@test.com pass123
CALL :runCmd create_database
CALL :runCmd create_database me@test.com
CALL :runCmd create_database me3@test.com pass123
CALL :runCmd login me3@test.com pass12

REM Testing Login
CALL :printFancy Testing Login
CALL :runCmd create_database me2@test.com pass111
CALL :runCmd login me2@test.com pass123
CALL :runCmd login me2@test.com
CALL :runCmd login me2@test.com pass111

REM Add Admin
CALL :printFancy Testing Add Admin
CALL :runCmd create_database me4@test.com pass111 
CALL :runCmd login me4@test.com pass111 add_admin pass321
CALL :runCmd login me4@test.com pass111 add_admin me5@test.com pass321
CALL :runCmd login me5@test.com pass321
CALL :runCmd login me5@test.com pass321 add_admin me5@test.com pass321
CALL :runCmd add_admin me5@test.com pass321

REM Remove User
CALL :printFancy Testing Remove User
CALL :runCmd create_database me4@test.com pass111
CALL :runCmd login me4@test.com pass111 add_admin me5@test.com pass321 remove_user me4@test.com
CALL :runCmd login me4@test.com pass111
CALL :runCmd login me5@test.com pass321 remove_user
CALL :runCmd login me5@test.com pass321 remove_user me44@test.com

REM Get User
CALL :printFancy Testing Get User
CALL :runCmd create_database me4@test.com pass111
CALL :runCmd login me4@test.com pass111 add_admin me5@test.com pass321 add_admin me6@test.com pass321 add_admin me7@test.com pass321 add_admin me8@test.com pass321 add_admin me9@test.com pass321
CALL :runCmd get_users
CALL :runCmd login me4@test.com pass111 get_users

REM Add Game
CALL :printFancy Testing Add Game
CALL :runCmd create_database me4@test.com pass111
CALL :runCmd login me4@test.com pass111 add_game
CALL :runCmd login me4@test.com pass111 add_game "Snake Game"
CALL :runCmd login me4@test.com pass111
CALL :runCmd login me4@test.com pass111 add_game "Snake Game"
CALL :runCmd add_game "Snake Game 2"

REM Remove Game
CALL :printFancy Testing Remove Game
CALL :runCmd create_database me4@test.com pass111
CALL :runCmd login me4@test.com pass111 add_game Maze remove_game Maze
CALL :runCmd login me5@test.com pass111 remove_game
CALL :runCmd login me5@test.com pass111 remove_game Maze 3
CALL :runCmd login me4@test.com pass111 add_game Maze
CALL :runCmd remove_game Maze

REM Get Games
CALL :printFancy Testing Get Games
CALL :runCmd create_database me4@test.com pass111
CALL :runCmd login me4@test.com pass111 add_game Snake1 add_game Snake2 add_game Snake3 add_game Snake4
CALL :runCmd get_games
CALL :runCmd login me4@test.com pass111 get_games

CALL :printFancy TESTS FINISHED!
echo:
GOTO :EOF

REM function for printing notes
:printFancy
echo:
echo %ESC%[44;93m NOTE: %* %ESC%[0m
EXIT /B 0

REM function for running executable
:runCmd
echo:
echo %ESC%[101;93m Running cmd: %exec% %* %ESC%[0m
%exec% %*
timeout /t 2 /nobreak
EXIT /B 0

