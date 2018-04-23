TO DO: FIX ERRORS, WRITE README, DESCRIPTIONS AT TOP OF EACH FILE, CHECK CODING STANDARDS PAGE

Eric Mason, ID: 441557, wustl key: m.mason Lab2


List of possible errors that could be thrown and what they return:

enum errors { wrongNumberOfArguments = -1, cannotOpenTextFile = -2,  vectorPushedBadInput = -3, oneArgumentNoTextFile = -4, twoArgumentsNoShuffle = -5, noArguments = -6, emtpyDeck = -7, Success = 0, UsageMessageRequested = 3}

vectorPushedBadInput should not be seen by the user, as it is inteded for internal purposes only, signaling that the parseCard function pushed a bad input into the vector given


Cases ran:

Case 1: command line executed: Lab2.exe 
	expected results: noArguments error, and printing out the usageMessage for Lab2.exe
	output: Lab2.exe In order to run this program, input 2 possible commands, one being a 
	-shuffle, which will randomize the cards inputted and a valid text file that contains 
	card definitions. These commands can come in any order, and the -shuffle command 
	does not have to be inputted, so the acceptible number of arguments are either
	 1 or 2 This is the expected output as this is the usage message.
	%errorlevel%: -6 (noArguments) as expected

Case 2: command line executed: Lab2.exe cards.txt
	cards.txt contains 52 valid cards (an entire deck) in standard order
	expected results: the original 9 hands + the remainder of the deck should be printed out, then the cards sorted by the hand< should be printed out, and finally
	the hands sorted by thier poker rank should be printed out.
	output: As expected
	%errorlevel%: 0 (Success) as expected

	
Case 3: command line executed: Lab2.exe cards.txt -shuffle
	cards.txt contains 52 valid cards (an entire deck) in standard order
	expected results: the original 9 hands + the remainder of the deck should be printed out, then the cards sorted by the hand< should be printed out, and finally
	the hands sorted by thier poker rank should be printed out. But this time the cards will be in a random order. 
	output: As expected
	%errorlevel%: 0 (Success) as expected

Case 4: command line executed: Lab2.exe cards.txt -shuffle
	cards.txt contains 52 valid cards (an entire deck) in standard order, with extra input of gibberish along with comments
	expected results: the original 9 hands + the remainder of the deck should be printed out, then the cards sorted by the hand< should be printed out, and finally
	the hands sorted by thier poker rank should be printed out. But this time the cards will be in a random order. The invalid cards should be ignored along with the comments
	output: As expected
	%errorlevel%: 0 (Success) as expected

Case 5: command line executed: Lab2.exe test.txt
	test.text does not exist in the local directory
	
	expected output: The program should return a cannotOpenTextFile Error and print out the appropriate error message
	actual output: as expected
	%errorlevel%: -2 (cannotOpenTextFile) as expected

Case 6: command line executed: Lab2.exe cards.txt test.txt
	cards.txt contains 52 valid cards (an entire deck) in standard order and test.txt does not exist on in the local directory
	
	expected output: The program should return a twoArgumentsNoShuffle error and print out the usage message
	actual output: as expected
	%errorlevel%: -5 (twoArgumentsNoShuffle) as expected

Case 7: command line executed: Lab2.exe -shuffle
	expected output: The program should return a oneArgumentNoTextFile error and print out the usage message
	actual ouptut: as expected
	%errorlevel%: -4 (oneArgumentNoTextFile) as expected

Case 8: command line exectuted: Lab2.exe cards.txt
	cards.txt is an empty text file
	expected output: The program should return an emptyDeck error and print out "Deck is emtpy so no cards can be dealt"
	actual output: as expected
	%errorlevel%: -7 (emptyDeck) as expected

Errors encountered:

vector iteratable not dereferencable error: I was attempting dereference the at the .end() of an iterator, which is out of bounds. To fix this I adjusted this value to just
be the value at the size of the vector -1.

invalid comparator: my hands < operator was not working correctly (it did not have strict weak ordering), so I had to fix this.

A Debug error: I was catching an int in my try catch block, but was throwing 'cannotOpenTextFile', which is part of an enum of errors, so I had to fix what I was
	catching to be an error instead.
