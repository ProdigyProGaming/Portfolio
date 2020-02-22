Created by Arron Rawstron

C++ Command Line Paper Games

This is still a work in progress (WIP) and does not represent how the final game
will be coded or even played.

To run:
	Navigate to cmake-build-debug
	Run Tic_Tac_Toe_V2_1.exe
	Command Promt will open and play

To view code:
	Open .cpp files to view source code

Features
	Local Score Tracking
		Local store tracking means that when the application is launched, you enter a username
		for player 1 and if you are playing with 2 people, player 2.
		If the username does not exist, it will be created and stored in the file.
		If the username does exist, it will display the current win loss and draw scores.
		Then when the user/users play any games, their scores will be updated in the file and
		stored for when they exit and reopen the application.
	BattleShips
		This is a standard version of battleships against an 'AI'.
		Open launching this game, you must place all your ships on the board using coordinates
		and orientations.
		The 'AI' will do the same, randomly placing their own ships.
		You will then take it in turns to attack coordinates to sink the ships.
		If an attack hits, the board will show an 'X', if it misses, it will show an 'O'.
		When a ship is sink, the whole ship will change to '-'.
		You can also see what ships you have left at the side.
		The AI will attempt to figure out where your ships are.
		It will begin by picking random positions, but once a ship has been hit, the 'AI'
		will determine if the ship is horizontal or vertical then attack accordingly until
		the ship has been sunk.
	Tic Tac Toe (Standard and Extreme)
		The standard tic tac toe is where you play against another player on the same pc to
		try to get 3 in a row.
		The extreme version is a board of tic tac toe boards.
		This is where you place a piece in one of the smaller boards and when a small board
		has been won, your piece gets placed onto the overall board.
		The goal is to win 3 games of tic tac toe in a row, filling in 3 of your pieces in the
		overall board.
		There is also the mechanic that where you place your piece in the smaller board,
		is the smaller board the other player must place their next piece.
		For example, if the current small board was 5 (the middle) and you placed your piece
		in slot 1 of the small board, the other player will then have to place a piece in the
		first small board (top left).
	Connect 4
		This is standard connect 4 where you can play against another player on the same pc.
		You enter the column you wish to place your piece and it will be placed at the next
		available slot in the column.
		The first one to connect 4 of their pieces horizontally, vertically or diagonally wins.
	Hangman
		This is the standard game of hangman where currently, the computer picks a random word
		from the text file and displays the number of letters to the user.
		The user can then enter letters to try to guess the word.
		After each guess, if the guess is correct, the letter appears. If the guess is incorrect,
		a new part to the hangman is added.
	Rock Paper Scissors
		This is a very basic game where the user can pick either Rock, Paper or Scissors and the
		computer also picks one of these at random. The winner is based on the standard rules.
