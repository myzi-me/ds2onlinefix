# ds2onlinefix
Experimental workaround for dark souls 2 login error
Needs testing

Needs cmake and visual studio 2022
GenerateVSProject.bat then open sln in out folder

The problem with ds2 servers is it will sometimes null the redirect server ip and port from one of the initial packets
I dont know if this is a bug or the only problem
Maybe if main servers are strained it doesnt allow more in

This caches the decrypted server ip and port into a file ds2onlinefix.cache and reuses it if it finds that nulled data
You need to log in at least once for cache to be made

I havent tested for bans
Compiling debug build could have a higher chance of a ban as it opens a console for logging

Drag xinput1_3.dll into game folder