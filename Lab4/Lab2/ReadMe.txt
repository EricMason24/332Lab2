Eric Mason, ID: 441557, wustl key: m.mason 
Tommy Blackwell, ID: 443832, wustl key: tommy.blackwell

Lab4 (we built this off of lab2, so the .exe and main .cpp files are lab2)


List of possible errors that could be thrown and what they return:

wrongNumberOfArguments = -1, cannotOpenTextFile = -2, vectorPushedBadInput = -3, oneArgumentNoTextFile = -4, twoArgumentsNoShuffle = -5, noArguments = -6, emptyDeck = -7, badInput = -9, InstanceNotAvailable = -10,
gameAlreadyStarted = -11, unknownGame = -12, allocException = -13, noGameInProgress = -14, alreadyPlaying = -15, bothDecksEmpty = -16, tooManyPlayers = -17, roundOver = -18,outOfBoundsException = -8, Success = 0, UsageMessageRequested = 3

vectorPushedBadInput should not be seen by the user, as it is intended for internal purposes only, signaling that the parseCard function pushed a bad input into the vector given


Cases ran:

Case 1: command line executed: Lab2.exe 
expected results: wrongNumberofArguments error, and printing out the usageMessage for Lab2.exe
output: Lab2.exe must include name of game and 2+ players, and make sure not to include the .txt of the player files, only include the file name in the argument.
This is the expected output as this is the usage message.
%errorlevel%: -1 (wrongNumberofArguments) as expected

Case 2: command line executed: Lab2.exe game eric tommy
expected results: an unkown game exception, as game does not contain 'FiveCardDraw'or 'SevenCardStud'
output: As expected
%errorlevel%: -12 (unkownGame) as expected

Case 3: command line executed: Lab2.exe FiveCardDraw eric tommy
eric.txt and tommy.txt both exist on file system
then playing 1 hand, by eric betting 1 chip and tommy calling before the hand has been dealt, with both players having enough chips to bet
and then have eric leave the game, and answering 'n' to play another game
expected results: a game should be started with the two players being eric and tommy (eric.txt and tommy.txt for the files), 1 round (2 turns) should be played
and once eric leaves, the game should end, with the updated wins and losses and chips being updated in eric.txt and tommy.txt, and then return success.
output: As expected
%errorlevel%: 0 (Success) as expected

Case 4: command line executed: Lab2.exe FiveCardDraw bill ted
bill.txt and ted.txt do not exist on file system
play 2 rounds of fiveCardDraw
The first round exists of 1 hand and then bill leaves, stopping the game but prompting for another one
then 'FiveCardDraw bill ted' is then inputted, starting another game, in this game, bill bets until he is out of chips, and ted calls him on his bet
this ends all current betting and advances to the end of the round
then bill leaves the game, ending their adventure.
expected results: Should print out that bill.txt and ted.txt could not be opened, but still start a game with bill and ted (both with zero wins and losses and 20 chips)
first round should be played with no issue, then a second round will also be played.
then after bill leaves the first round, save bill and teds wins and losses into bill.txt and ted.txt, which will be created on the file system and return success after te second game is complete.
%errorlevel%: 0 (Success) as expected

Case 5: command line executed: Lab2.exe FiveCardDraw eric tommy
eric.txt and tommy.txt both exist on file system
play 1 hand, have tommy bet until he runs out of chips and lose the game, then try to play another round, forcing tommy to refill his chip count to 20
then eric leaves, ending the game
expected output: The program should read in the wins and losses of eric + tommy, play the 1 hand, and then proceed to the next hand with tommy dealing, as if he had 
never left, with 20 chips (19 after ante) and then exiting the game once eric leaves, returning success.
%errorlevel%: 0 (Success) as expected

Case 6: command line executed: Lab2.exe SevenCardStud eric tommy
eric.txt and tommy.txt both exist on file system
play 1 hand, with eric and tommy both checking every turn, then leaving the game after the round ends and answering 'n' to another game
expected output: 
The seven card stud should deal two ** cards, then 4 face up cards, and finally another ** card, then deciding the best possible poker hands for the 2 players
and finally awarding the pot to to the winning player and then exiting with Success after 'n' is recieved.
%errorlevel%: 0 (Success) as expected
 
Case 7: command line executed: Lab2.exe SevenCardStud eric tommy
eric.txt and tommy.txt both exist on file system
play 2 hands, with eric and tommy both betting every turn, until tommy is out of chips, 
which should play the rest of the turns for the players, and then end the round awarding the pot to the winning player
then leaving the game after the round ends and answering 'y' to another game, creating another SevenCardStud Game
In this second game, eric and tommy both check on the initial bet, then eric folds once 4 cards have been dealt, ending the round and awarding the chips to Tommy
after this round, eric leaves the game, then answers 'n' to the another game prompt
expected output: Both rounds should be played as described, with the pot awarding to the correct player and two games should be able to be played without an issue
And returning success after both games have been completed.
%errorlevel%: 0 (Success) as expected

Case 8: command line executed: Lab2.exe SevenCardStud eric tommy
eric.txt and tommy.txt both exist on file system
play 2 hands, with eric and tommy both betting every turn, until tommy is out of chips, 
which should play the rest of the turns for the players, and then end the round awarding the pot to the winning player
then leaving the game after the round ends and answering 'y' to another game, creating a FiveCardDraw Game
In this second game, eric and tommy both check on the initial bet, then eric raises the pot unitl he is all in, which should advance the betting to end the round.
expected output: Both rounds should be played as described, with the pot awarding to the correct player and two games should be able to be played without an issue
And returning success after both games have been completed.
%errorlevel%: 0 (Success) as expected


Errors encountered:

using Player p instead of Player & p: There were many cases where we were working with copies instead of references, so certain values were changed by the constructor

decrementing instead of incrementing losses at one point, resulting in a huge number: because of how unsigned int works, we did not account for this in checking for all ins

correcting one pair and two pair: as they did not work: We did not account for the cards being the same pairs, so having to compare the other cards in the hand, which 
is important for finding the best possible poker hand in 7 cards didn't work.

not setting best hand: we did not set best hand in our pokerRank method, so we were comparing empty vectors, which return an error.

visual studio issue where variables were not being added to the project: No idea what caused this, but restarting both the rdp connection and visual studio fixed it.

visual studio issue where progress was erased: There was an issue with external files being overwritten by visual studio, where some progress was erased.

variable not defined error because declaring variable as a function: In our new variable declarations in sevenCardStud and Hand.cpp, we declared a new hand using the default
constructor as (), instead of not including, the (), which caused an illegal variable exception.