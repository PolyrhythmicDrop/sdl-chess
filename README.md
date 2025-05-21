# SDL Chess

SDL Chess is a chess game created using C++, the [Easylogging++ logging library](https://github.com/abumq/easyloggingpp), the [SDL2 library](https://www.libsdl.org/), and the [Stockfish open-source chess engine](https://stockfishchess.org/). The game currently uses Stockfish 16.1 to enable single-player mode and check for checkmate. All other rule implementations, move mechanics, and game functionality has been built from the ground up.

> [!NOTE]
> SDL Chess is a work in progress! While both single-player and two-player mode are fully functional, I plan on adding more features in the future, including:
> * A GUI for the main menu (instead of the current console-based menu).
> * The ability to select a color to play. Currently, the first player defaults to white and the second player (or Stockfish) defaults to black.
> * The ability to change board and piece color themes.
> * The ability to adjust the level of the Stockfish player.

## Getting Started

SDL Chess does not currently have a public build available. To build and run the game:

1. Clone the repository to your local machine.
2. Open the *SDL Chess.sln* solution in Visual Studio.
3. Build and run the solution from Visual Studio.

### Start a Match

Once you have the game running, a terminal window and a game window with a grey background display. The terminal window displays menu entries and logs debug information throughout gameplay. Pardon the excessive logging: SDL Chess is still a work in progress!

1. Press **Enter** in the game window to initialize the game.
2. The terminal window prompts you to select a game mode. Switch focus to the terminal window. Select a game mode by pressing the corresponding key, then pressing **Enter**.

  * `Single Player` - Play against Stockfish 16.1.
  * `Head to Head` - Play against a human opponent or yourself.

> [!WARNING]
> You cannot adjust the difficulty when playing against Stockfish! Stockfish will treat you like the chess master you (probably) are.

3. In the terminal window, enter a name for Player One, then press **Enter** to accept.
4. Enter a name for Player Two, then press **Enter** to accept.

After choosing a name for Player Two, the game takes a few seconds to build the board, initialize Stockfish, and place the pieces. When complete, the game window displays the populated board and you're ready to play!

### Play SDL Chess

1. Click on one of your pieces to select it. 
   * The possible moves for the selected piece display as blue semi-transparent squares on the board.
   * If you can capture an opponent's piece using the selected piece, the capturable piece is highlighted with a red semi-transparent square.
2. Click on a square to move the selected piece to the square, or click on a capturable piece to capture the piece.

### Interface and Move Tips

* To deselect a piece, either select another piece or click anywhere in the game window that is not a moveable square.
* The game will not allow you to perform a move that puts your king in check. If you can't move a piece, check the terminal window to see why.
* When promoting a pawn, use the terminal window to select the piece you want the pawn to turn into.
* To capture *en passant*, select the pawn you want to capture with. If you can capture *en passant*, the square behind the opposing pawn will be highlighted in red. Click the red highlighted square to move you pawn to the square and capture the opposing pawn.
* To castle, make sure the conditions are right, then select your king and select the moveable square next to the rook. Your king and rook will automatically move to the castling position.
* To exit the game, press **Esc** at any time and select **Exit Game**, or select **Back** to close the menu and resume play.
* You can change the resolution **before** loading the board by pressing **Esc**, selecting **Options**, and clicking the desired resolution.

> [!CAUTION]
> **DO NOT attempt to change the resolution while a game is in session!** Your board will turn into a black square and you will be unable to play.
> This is a bug that is on my list of things to fix.
