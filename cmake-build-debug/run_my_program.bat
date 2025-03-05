@echo off
set exec=GameHub.exe

CALL :printfancy SHOWCASE OF GAMEHUBSERVER 


REM showcase create_database
CALL :printFancy Showcase create_database
CALL :runCmd create_database elias@gmail.com pass

REM showcase login
CALL :printFancy Showcase login
CALL :runCmd login elias@gmail.com wrongpass
CALL :runCmd login elias@gmail.com pass

REM showcase add_user
CALL :printFancy Showcasing user management
CALL :runCmd login elias@gmail.com pass add_user 
CALL :runCmd login elias@gmail.com pass add_user simple@user.com somepass 

REM showcase add_admin
CALL :runCmd login elias@gmail.com pass add_admin root@linux.se newpass
CALL :runCmd login elias@gmail.com pass get_users

REM showcase remove_user
CALL :runCmd login simple@user.com somepass remove_user root@linux.se 
CALL :runCmd login elias@gmail.com pass remove_user root@linux.se 
CALL :runCmd login elias@gmail.com pass get_users

REM showcase add_games
CALL :printFancy Showcase managing games
CALL :runCmd login simple@user.com somepass get_games
CALL :runCmd login elias@gmail.com pass add_game "Elden Ring" wrongarg
CALL :runCmd login elias@gmail.com pass add_game "Elden Ring"
CALL :runCmd login elias@gmail.com pass add_game Minecraft
CALL :runCmd login simple@user.com somepass get_games
CALL :runCmd login elias@gmail.com pass remove_game "Elden Ring"
CALL :runCmd login elias@gmail.com pass remove_game "Elden Ring"
CALL :runCmd login simple@user.com somepass get_games

CALL :printFancy Showcase finished!
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
timeout /t 5 /nobreak
EXIT /B 0

