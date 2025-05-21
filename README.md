# SDL Chess

SDL Chess is a chess game created using C++, the SDL2 library, and the [Stockfish open-source chess engine](https://stockfishchess.org/). The game currently uses Stockfish 16.1 to enable single-player mode and check for checkmate. All other rule implementations, move mechanics, and game functionality has been built from the ground up.

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

> [!WARNING]
> You cannot currently adjust the difficulty! Stockfish will treat you like the chess master you (probably) are.

  * `Head to Head` - Play against a human opponent or yourself.

3. In the terminal window, enter a name for Player One, then press **Enter** to accept.
4. Enter a name for Player Two, then press **Enter** to accept.

After choosing a name for Player Two, the game takes a few seconds to build the board, initialize Stockfish, and place the pieces. When complete, the game window displays the populated board and you're ready to play!

### Play SDL Chess

1. Click on one of your pieces to select it. 
   * The possible moves for the selected piece display as blue semi-transparent squares on the board.
   * If you can capture an opponent's piece using the selected piece, the capturable piece is highlighted with a red semi-transparent square.
2. Click on a square to move the selected piece to the square, or click on a capturable piece to capture the piece.

> [!NOTE]
> To deselect a piece, either select another piece or click anywhere in the game window that is not a moveable square.
