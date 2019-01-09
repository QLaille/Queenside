
# QUEENSIDE API

#### First and foremost

The API relies on the [Universal Chess Interface](https://ipfs.io/ipfs/QmXoypizjW3WknFiJnKLwHCnL72vedxjQkDDP1mXWo6uco/wiki/Universal_Chess_Interface.html) (UCI for short) for communicating between the server and its clients, and on the [Forsyth-Edwards Notation](http://portablegamenotation.com/Fen.html) (FEN) for declaring the state of a game.

## A message is consisted of 3 keywords: TYPE, NAME, COMMENT , separated by a colon **":"** and ends with a Line Feed **"\n"**

### TYPE defines the "scope" of the message

### NAME defines the actual request

### COMMENT defines additional values if needed, otherwise, NULL

---

#### Possible TYPEs of a request

-  **TEXT**: the request is aimed to the server as a client.

-  **UCI**: the request is aimed to the server as a player (i.e. when in a game).

---

#### Possible TEXT requests

-  **ALLROOM**:NULL - Returns the list of all available rooms.

-  **ROOMINFO**:`$RoomId` - Returns infos about the players inside the room identified by its `$RoomId`.

-  **JOINROOM**:`$RoomId` - Returns a `$RoomId` if successfully joined the room. If `$RoomId` is NEWROOM, will create a new room and return its new `$RoomId`.

-  **QUITROOM**:NULL - Quits the current room you are part of.

-  **STATE**:`$State` - Tells the server your `$State`, be it READY or anything else if you aren't.

---

#### Possible UCI requests

- id:`$Name` - provide the `$Name` of the player.

- uciok:NULL - Tells the server the player is ready.

- readyok:NULL - Sent when the player received a "isready" request from the server.

- bestmove:`$Move` - Tells the server the player stopped thinking and is giving the starting and the ending point of a movement (i.e. e2e4 for White King's Pawn opening).

- info:`$Infos` - Gives the server infos, this request can be interpreted as logs.
