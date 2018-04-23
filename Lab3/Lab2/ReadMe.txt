
Eric Mason, ID: 441557, wustl key: m.mason 
Tommy Blackwell, ID: 443832, wustl key: tommy.blackwell

Lab3 (we built this off of lab2, so the .exe and main .cpp files are lab2)


List of possible errors that could be thrown and what they return:

enum errors {
	wrongNumberOfArguments = -1, cannotOpenTextFile = -2, vectorPushedBadInput = -3, oneArgumentNoTextFile = -4, twoArgumentsNoShuffle = -5, noArguments = -6, emptyDeck = -7, badInput = -9, InstanceNotAvailable = -10,
	gameAlreadyStarted = -11, unknownGame = -12, allocException = -13, noGameInProgress = -14, alreadyPlaying = -15, bothDecksEmpty = -16, outOfBoundsException = -8, Success = 0, UsageMessageRequested = 3
};

vectorPushedBadInput should not be seen by the user, as it is inteded for internal purposes only, signaling that the parseCard function pushed a bad input into the vector given


Cases ran:

Case 1: command line executed: Lab2.exe 
	expected results: wrongNumberofArguments error, and printing out the usageMessage for Lab2.exe
	output: Lab2.exe must include name of game and 2+ players, and make sure not to include the .txt of the player files, only include the file name in the argument.
	 This is the expected output as this is the usage message.
	%errorlevel%: -1 (wrongNumberofArguments) as expected

Case 2: command line executed: Lab2.exe game eric tommy
	expected results: an unkown game exception, as game does not contain 'FiveCardDraw'
	output: As expected
	%errorlevel%: -12 (unkownGame) as expected

	
Case 3: command line executed: Lab2.exe FiveCardDraw eric tommy
	eric.txt and tommy.txt both exist on file system
	then playing 1 hand, and then have eric leave the game
	expected results: a game should be started with the two players being eric and tommy (eric.txt and tommy.txt for the files), 1 round (2 turns) should be played
	and once eric leaves, the game should end, with the updated wins and losses being updated in eric.txt and tommy.txt, and then return success.
	output: As expected
	%errorlevel%: 0 (Success) as expected

Case 4: command line executed: Lab2.exe FiveCardDraw bill ted
	bill.txt and ted.txt do not exist on file system
	play 2 hands, discarding 3 cards first hand, all 5 cards second hand (attempt at position 5 for ted)
	then bill leaves the game, ending their adventure.
	expected results: Should print out that bill.txt and ted.txt could not be opened, but still start a game with bill and ted (both with zero wins and losses)
	first hand should be played no issue, same with the second hand, except ted will have to enter his discards again because 5 is out of bounds.
	then after bill leaves, save bill and teds wins and losses into bill.txt and ted.txt, which will be created on the file system and return success.
	%errorlevel%: 0 (Success) as expected

Case 5: command line executed: Lab2.exe FiveCardDraw eric tommy
	eric.txt and tommy.txt both exist on file system
	play 1 hand, have tommy leave, and then have tommy rejoin right after leaving when prompted and playing one more hand
	then eric leaves, ending the game
	expected output: The program should read in the wins and losses of eric + tommy, play the 1 hand, and then proceed to the next hand with tommy dealing, as if he had 
	never left, and then exiting the game once eric leaves, returning success.
	%errorlevel%: 0 (Success)as expected


Errors encountered:

A string null exception: I was assigning argv[1] to a variable before checking if there are enough arguments, which caused a string null exception when 0 arguments
beside the program name were entered.

A dealer error where the dealer printed was always the first player: this was due to us using the wrong symbol, instead of using %, we were using &

An infinite loop: When comparing for ties after the round, we did not increment our while loop, so there was an infinite loop

Discarding incorrectly: We used the wrong iterator (i, instead of pos[i]) when discarding cards, leading to only the first x (x being the size of the vector of positions to 
	be discarded) cards in the hand to be discarded, no matter what the position was. 

