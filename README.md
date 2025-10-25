# ds2onlinefix
Experimental workaround for dark souls 2 login error

Needs testing

I got a chance to test it seems to be working
https://www.youtube.com/watch?v=xp_bbVdFU2I

# How to use

Download test release build from releases

Drag xinput1_3.dll into game folder

You need to successfully connect once first then needed data will be cached to ds2onlinefix.cache file forever

# How to compile

Needs cmake and visual studio 2022

Run GenerateVSProject.bat then open sln in out folder

Compile as release

# The problem

The problem with ds2 servers is it sometimes null the redirect server ip and port from one of the initial packets

This is meant to send you to the main game server

I dont know if this is a bug

This might not be the only problem its hard to catch servers error times

Maybe if main servers are strained it doesnt allow more in

# How it works

This caches the decrypted server ip and port into a file ds2onlinefix.cache and reuses it if it finds that nulled data

You need to connect once for cache to be made

Cache file stays in the game folder for anytime u launch u dont have to successfully connect first every launch

I havent tested for bans

Compiling debug build could have a higher chance of a ban as it opens a console for logging

# Libraries used
https://github.com/TsudaKageyu/minhook
