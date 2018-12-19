THE SERVER USES THE FEN NOTATION IN ENGLISH TO DESCRIBE CURRENT STATE OF THE BOARD :http://www.chessgames.com/fenhelp.html

THE SERVER USES THE UNIVERSAL CHESS INTERFACE FOR SERVER AND PLAYERS TO COMMUNICATE :http://wbec-ridderkerk.nl/html/UCIProtocol.html

Beforehand, we mainly use a text protocol, because we aim to get lower promotions of our school to start learning about networking.
A binary protocol will be implemented in the future.

A message consists of three words/sentences all separated by a colon (:).
The first define the type of the message itself, it can either be TEXT, or UCI.
The second is a keyword, representing your request (i.e., ROOMINFO to get infos of your current room).
The third is a comment, used when necessary to provide more infos,
depending on the context (i.e., when joining a room, NEWROOM makes you create a new room).

TEXT is when you want to speak to the server as a client.

Name:ALLROOM
Comment:None
Description: Dumps the list of all room IDs.
Answer: a list of strings, defining the IDs of all rooms.

Name:ROOMINFO
Comment:None
Description: Dumps the room players you are currently part of.
Answer: two strings, your ID and the other player in the room.

Name:JOINROOM
Comment:NEWROOM, RoomID
Description: Makes you join a room, type NEWROOM if you want to create a new one or a Room ID for an existing one.
Answer: the ID of the room you joined.

Name:QUITROOM
Comment:None
Description: Quits the current room you are part of.
Answer: the comment REMOVED if you were removed from a room, else an error occured.

Name:STATE
Comment:READY, NOT_READY
Description: State your availability to the server.
Answer: your State if you were in a room, else an error occured.

UCI is when you want to speak to it as a player, names and comments follows the uci.

Name:id
Comment:name,author
Description: Name of the engine and its author

Name:uciok
Comment:None
Description: Tells the server the player is ready and in uci mode, must be sent after sending infos.

Name:readyok
Comment:None
Description: Sent when the player received an "isready" from the server

Name:bestmove
Comment:move (i.e. "e2e4")
Description: Tells the server the player stopped thinking and gives its best move for the current state of the board

Name:info
Comment:depth, seldepth,time,nodes,... (see the uci for the whole list of info commands)
Description: The player is sending infos to the server, this can be interpreted as logs.

Name:option
Comment:None
Description: This command is ignored, since it is relative to Engine parameters available for GUIs, thus client side.

Name:registration
Comment:None
Description: This command is ignored, since it is relative to Engine parameters available for GUIs, thus client side.

Name:copyprotection
Comment:None
Description: This command is ignored, since it is relative to Engine parameters available for GUIs, thus client side.
