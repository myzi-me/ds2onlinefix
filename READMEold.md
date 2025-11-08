# ds2onlinefix
Experimental workaround for dark souls 2 login error

Needs testing

I got a chance to test it seems to be working
https://www.youtube.com/watch?v=xp_bbVdFU2I

26/10/2025 - Login server has been fully offline for a day, fix wont work when this happens, maybe its for maintenence for a fix, or it died, no maintenence tweet

# How to use

Download release build from releases

Drag xinput1_3.dll into game folder

You dont have to connect once first

Theres a cheat engine version if you want 

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

Login server and game server share the same ip

Writes the nulled data with the login server ip the game is using and port 50000

You dont have to connect once first

Compiling debug build could have a higher chance of a ban as it opens a console for logging

# Libraries used
https://github.com/TsudaKageyu/minhook
