//Start of code.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;
/*********************************************************************/
/* Dwijesh Gontla                                                    */
/* Lab 5 Solution                                                    */
/*                                                                   */
/* This program diplays a main menu of options to manage a small CD  */
/* collection with the following options:                            */
/*       1. Read Collection                                          */
/*       2. Display Collection                                       */
/*       3. Sort Collection                                          */
/*       4. Find a CD                                                */
/*		 5. Find a CD * Recursive Version *							 */
/*       6. Edit a CD                                                */
/*		 7. Add Tracks for a CD										 */
/*		 8. Delete All Tracks for a CD								 */
/*       9. Math Break                                               */
/*       10. Quit                                                     */
/*                                                                   */
/* The implemented steps are:                                        */
/*		 1. Read Collection(Reads the elements of a file and saves   */
/*          it in an array.)                                         */
/*       2. Display Collection(Displays the array made from option   */
/*          1.)                                                      */
/*       3. Sort Collection(Sorts the collection using a selection   */
/*			sort in acending order.)                                 */
/*       4. Find a CD(Finds a CD.)                                   */
/*		 5. Find a CD * Recursive Version *							 */
/*       5. Edit a CD(Edits the components of a CD.)                 */
/*		 6. Add Tracks for a CD(Lets the user add tracks to a CD.)	 */
/*		 7. Delete All Tracks for a CD(Deletes all the tracks for a  */
/*          CD)								 						 */
/*       8. Math Break(Gives the user a small break.)                */
/*       9. Quit(Quits the program.)                                 */
/*                                                                   */
/* editCD has its own menu:										 	 */
/* 		 1. Edit a CD												 */
/* 		 2. Quit(When done with this option.)						 */
/*																	 */
/* addTracks has its own menu:										 */
/*		 1. Add Tracks												 */
/*		 2. Quit													 */
/*																	 */
/* Math Break has its own menu:                                      */
/*       1. Even or Odd(Checks if a number is even or not.)          */
/*       2. Prime Number(Checks if a number is prime or not.)        */
/*		 3. String Reverse(Reverses a string the user sends in.)	 */
/*       4. Quit                                                     */
/*********************************************************************/

//Start of the class declaration.
class CD
{
	private:
		string artist;
		string title;
		int year;
		string* tracks;
		int maxTracks;
		int numTracks;
		
	public:
//Constructor prototypes.
		CD();
		CD(string, string, int);
		CD(const CD&);

//Destructor prototype.
		~CD();

//Set method prototypes.		
		void setArtist(string);
		void setTitle(string);
		void setYear(int);
		void setMaxTracks(int);
		bool setTrackName(string);

//Get method prototypes.		
		string getArtist();
		string getTitle();
		int getYear();
		int getMaxTracks();
		int getNumTracks();
		vector<string> getAllTracks();
		
//Other methods
		void deleteTracks();
};
//End of the class declarations.

//Default Constructor
CD::CD()
{
	artist = "";
	title = "";
	year = 0;
	tracks = nullptr;
	maxTracks = 0;
	numTracks = 0;
}

//Parameterized Constructor
CD::CD(string a, string t, int y)
{
	artist = a;
	title = t;
	year = y;
	tracks = nullptr;
	maxTracks = 0;
	numTracks = 0;
}

//Copy Constructor
CD::CD(const CD& original)
{
	artist = original.artist;
	title = original.title;
	year = original.year;
	maxTracks = original.maxTracks;
	numTracks = original.numTracks;
	tracks = nullptr;

	if (original.tracks)
	{
		tracks = new string[maxTracks];
		for (int i = 0; i < numTracks; i++)
		{
			tracks[i] = original.tracks[i];
		}
	}
}

//Destructor
CD::~CD()
{
	delete[] tracks;
	tracks = nullptr;
}

//Start of member function declarations.
//Set methods declaration.
void CD::setArtist(string a) {artist = a;}
void CD::setTitle(string t) {title = t; }
void CD::setYear(int y) {year = y; }

void CD::setMaxTracks(int numberOfTracks)
{
	if (numberOfTracks > 0)
	{
		maxTracks = numberOfTracks;
		tracks = new string[maxTracks];
		numTracks = 0;
	}
	else
	{
		maxTracks = 0;
		delete[] tracks;
		tracks = nullptr;
		numTracks = 0;
	}
}

bool CD::setTrackName(string trackName)
{
	if (numTracks < maxTracks && tracks != nullptr)
	{
		tracks[numTracks] = trackName;
		numTracks++;
		return true;
	}
	else
	{
		return false;
	}
}

//Get methods declaration.
string CD::getArtist() {return artist; }
string CD::getTitle() {return title; }
int CD::getYear() {return year; }
int CD::getMaxTracks() { return maxTracks; }
int CD::getNumTracks() { return numTracks; }

vector<string> CD::getAllTracks()
{
	vector<string> allTracks;
	if (tracks != nullptr)
	{
		for (int i = 0; i < numTracks; i++)
		{
			allTracks.push_back(tracks[i]);
		}
	}
	
	return allTracks;
}

//Other methods
void CD::deleteTracks()
{
	delete[] tracks;
	tracks = nullptr;
	maxTracks = 0;
	numTracks = 0;
}
//End of member function declarations.


//A constant placed which represents the maximum number of songs the array can have.
const int TOTAL_SONGS = 35;

//Prototypes of functions.
int menuOption();
int invalid();
int finder(CD collection[], int);

//Option 1: Read Collection Function Prototypes
void readCollection(CD collection[], int &, bool &);

//Option 2: Display Collection Function Prototypes
void displayCollection(CD collection[], const int);

//Option 3: Sort Collection Function Prototypes
void sortCollection(CD collection[], const int);

//Option 4: Find a CD Function Prototypes
void findCD(CD collection[], const int);

//Option 5: Find a CD * Recursive Version *
void recursiveFindCD(CD collection[], const int);
bool recursiveFinder(CD collection[], int, string, string);

//Option 6: Edit a CD Functions
void editCD(CD collection[], const int);
int editMenuOption();
void editTheCD(CD*);
int editTheCDMenuOption();

//Option 7: Add Tracks for CD
void addTracks(CD collection[], const int);
int addTracksOption();

//Option 8: Delete all tracks for a CD
void deleteTracksCD(CD collection[], const int);

//Option 9: Math Break Function Prototypes
void mathBreak();
int mathMenuOption();
void evenOdd();
bool isEven(const int);
void primeNumber();
bool isPrime(const long int);
void stringReverse();
string reversify(string, string, int);


int main()
/********************************************************************/
/* Function:   main                                       
/* Inputs:     none
/* Outputs:    This function returns the value of 0 to let the computer know that the program ran succesfully.                     
/* Purpose:    This function is the main function of the program, this will lead the user to other functions within the program.   
/********************************************************************/
{
//Variable declarations.
	int option = 0;
	int count = 0;
	bool read = false;
	CD collection[TOTAL_SONGS];

//Gets the option choice from the user.
	option = menuOption();

//Uses a while loop to run the program until the user choses to quit.
	while (option != 10)
	{
//This if-else statement is used to redirect the user to what ever menu option they have chosen.
		if (option == 1)
		{
			readCollection(collection, count, read);
		}
		else if (((option == 2) || (option == 3) || (option == 4) || (option == 5) || (option == 6) || (option == 7) || (option == 8)) && !read) 
		{
			cout << "You must first read the collection, choose option 1." << endl;
		}
		else if (option == 2)
		{
			displayCollection(collection, count);
		}
		else if (option == 3)
		{
			sortCollection(collection, count);
		}
		else if (option == 4)
		{
			findCD(collection, count);
		}
		else if (option == 5)
		{
			recursiveFindCD(collection, count);
		}
		else if (option == 6)
		{
			editCD(collection, count);
		}
		else if (option == 7)
		{
			addTracks(collection, count);
		}
		else if (option == 8)
		{
			deleteTracksCD(collection, count);
		}
		else
		{
			mathBreak();
		}
		
//Gets the option choice from the user.
		option = menuOption();
	}

//Prints a "Thank You" statement at the end of the program.
	if (option == 10)
	{
		cout << endl;
		cout << "*********************************************************" << endl;
		cout << "Thank You for using the program." << endl;
		cout << "*********************************************************" << endl;
	}
	
	return 0;
}

int menuOption()
/********************************************************************/
/* Function:   menuOption                                       
/* Inputs:     none
/* Outputs:    This function returns the option choice chosen by the user.
/* Purpose:    This function is supposed to get the option choice from the user, 
/* validate if it is in the range, and return it to the the main() function.
/********************************************************************/
{
//Variable declarations.
	int option;

//Displays the possible options the user can choose.
	cout << endl;
	cout << "***************************************************************************************";
	cout << endl;
	cout << "Hello user, select one of the following options:" << endl;
	cout << "1. Read Collection" << endl;
	cout << "2. Display Collection" << endl;
	cout << "3. Sort Collection" << endl;
	cout << "4. Find a CD" << endl;
	cout << "5. Find a CD * Recursive Version *" << endl;
	cout << "6. Edit a CD" << endl;
	cout << "7. Add Tracks for a CD" << endl;
	cout << "8. Delete All Tracks for a CD" << endl;
	cout << "9. Math Break" << endl;
	cout << "10. Quit" << endl;
	cout << "Choose your option:  ";
	cin >> option;
//This while loop takes in a value which represents the menu option and validates it to check if it is in the range.
	while (option > 10 || option < 1)
	{
		option = invalid();
	}

//Returns the option chosen by the user.
	return option;
}

//Option 1: Read Collection Functions
void readCollection(CD collection[], int &count, bool &read)
/********************************************* */
/* Function:   readCollection                       
/* Inputs:     "collection" which is an array with nothing. Count which is variable set to 0, 
/* this variable is supposed to get the number of elements in the list.
/* Outputs:    none
/* Purpose:    The purpose of this function is to add the contents of cd.txt to the array "collection",
/* and to set count to the number of objects in the file.
/********************************************* */
{
//Variable declarations.
	string artist = " ";
	string title = " ";
	int year = 0;

//Opening the file, so it can be read.
	ifstream inFile;
	inFile.open("cd.txt");
	
	if (inFile)
	{
		count = 0;
		while (getline(inFile, artist) && count < TOTAL_SONGS)
		{
			getline(inFile, title);
			inFile >> year;
			inFile.ignore();
			
			collection[count].setArtist(artist);
			collection[count].setTitle(title);
			collection[count].setYear(year);

			count++;
		}
		
		cout << "Your file has been read and the count is: " << count << endl;
//Sets read to true if the file is read.
		read = true;
		
//Closing the file to save memory space and to not have bad data.
		inFile.close();
	}
	else
	{
		cout << "No file was found." << endl;
	}
}

//Option 2: Display Collection Functions
void displayCollection(CD collection[], const int count)
/********************************************* */
/* Function:   displayCollection                       
/* Inputs:     A array called "collection" which has all the songs from the file "cd.txt". Count which is the size of the list collection.
/* Outputs:    none
/* Purpose:    To display each element in display collection and any tracks if applicable.
/********************************************* */
{
	//Variable declarations.
	vector<string> tracks;
	
//The header for the display contents.
	cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << left << setw(30) << "Artist:" << setw(35) << "Title:" << "Year Released:" << endl;
	cout << endl;

//A loop to output all the songs.
	for (int d = 0; d < count; d++)
	{
		cout << left << setw(30) << collection[d].getArtist() << setw(35) << collection[d].getTitle() << collection[d].getYear() << endl;
		
		tracks = collection[d].getAllTracks();
		for (int g = 0; collection[d].getNumTracks() > g; g++)
		{
			cout << "	" << g + 1 << ". " << tracks[g] << endl;
		}
	}
	cout << endl;
}

//Option 3: Sort Collection Functions
void sortCollection(CD collection[], const int count)
/********************************************* */
/* Function:   sortCollection
/* Inputs:     A array called "collection" which has all the songs from the file "cd.txt". Count which is the size of the list collection.
/* Outputs:    none
/* Purpose:    The function is used to sort the collection in ascending order for by artist name. It uses a selection sort to maximize efficency.
/********************************************* */
{
//Variable declarations.
	CD temp;
	int minIndex = 0;
	
//Running a selection sort for better efficiency.
	for (int d = 0; d < count - 1; d++)
	{
		minIndex = d;
		
		for (int g = d + 1; g < count; g++)
		{
			if (collection[g].getArtist() < collection[minIndex].getArtist())
			{
				minIndex = g;
			}
		}
		
//Swapping the objects.
		temp = collection[d];
		collection[d] = collection[minIndex];
		collection[minIndex] = temp;
	}
	
	cout << "Done sorting." << endl;
}

//Option 4: Find a CD Functions
void findCD(CD collection[], const int count)
/********************************************* */
/* Function:   findCD
/* Inputs:     A array called "collection" which has all the songs from the file "cd.txt". Count which is the size of the list collection.
/* Outputs:    none
/* Purpose:    This function is used to find and display the elements of a CD.
/********************************************* */
{	
//Variable declarations.
	int place = -1;
	
//Running the finder function to find the specific CD the user it trying to find.
	place = finder(collection, count);

//Using this if-else loop to display the correct message to the user if it was found or not.
	if (place != -1)
	{
		cout << endl;
		cout << "The CD was found." << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << left << setw(30) << "Artist:" << setw(35) << "Title:" << "Year Released:" << endl;
		cout << left << setw(30) << collection[place].getArtist() << setw(35) << collection[place].getTitle() << collection[place].getYear() << endl;
	}
	else
	{
		cout << "The CD was not found, try again and check your spelling and capitalization this time." << endl;
	}
}

//Option 5: Find a CD * Recursive Version *
void recursiveFindCD(CD collection[], const int count)
/********************************************* */
/* Function:   recursiveFindCD
/* Inputs:     A array called "collection" which has all the songs from the file "cd.txt". Count which is the size of the list collection.
/* Outputs:    none
/* Purpose:    This function is used to display if the CD entered by the user exists or not in the collection.
/********************************************* */
{	
//Variable declarations.
	int place = -1;
	string artistToFind = "";
	string titleToFind = "";
	bool found = false;

//Acquiring the information to find the CD.
	cout << "Enter the artist name you want to find: ";
	cin.ignore();
	getline(cin, artistToFind);
	cout << "Enter the title you want to find: ";
	getline(cin, titleToFind);

//Running the recursiveFinder function to find the specific CD the user it trying to find.
	found = recursiveFinder(collection, count, artistToFind, titleToFind);

//Using this if-else loop to display the correct message to the user if it was found or not.
	if (found)
	{
		cout << "The CD was found." << endl;
	}
	else
	{
		cout << "The CD was not found, try again and check your spelling and capitalization this time." << endl;
	}
}

bool recursiveFinder(CD collection[], int count, string artistToFind, string titleToFind)
/********************************************* */
/* Function:   recursiveFinder
/* Inputs:     A array called "collection" which has all the songs from the file "CD.txt". Count which starts as the total amount of elements 
			   in the list and then reduces by one each time to act as the index to check. "artistToFind" which is the artist the program 
			   has to find. "titleToFind" which is to check if it is the correct CD.
/* Outputs:    Returns true if the CD is found. And it returns false if the CD is not found.
/* Purpose:    The function is used to find the CD the user is looking for.
/********************************************* */
{
//This if condition is used to see if the index is going out of the bound.
	if (count == -1)
	{
		return false;
	}
	
//This if condition is used to check if the CD is found.
	if (collection[count].getArtist() == artistToFind)
	{
		if (collection[count].getTitle() == titleToFind)
		{
			return true;
		}
	}
	
	return recursiveFinder(collection, count - 1, artistToFind, titleToFind);
}

//Option 6: Edit a CD Functions
void editCD(CD collection[], const int count)
/**********************************************/
/* Function:   editCD
/* Inputs:     A array called "collection" which has all the songs from the file "cd.txt". Count which is the size of the list collection.
/* Outputs:    none
/* Purpose:    This function is used to send the user to editTheCD where they can edit the CD.
/**********************************************/
{
//Variable declarations.
	int editOption = 0;
	int place = -1;
	CD* theCD = nullptr;

//Getting the option from the user.
	editOption = editMenuOption();

//Uses a while loop to run the option until the user choses to quit.
	while (editOption != 2)
	{
		cout << endl;
		cout << "Input the artist and title to find your CD." << endl;
		place = finder(collection, count);
		theCD = &collection[place];
		
		if (place != -1)
		{
			editTheCD(theCD);
		}
		else
		{
			cout << "The CD was not found, try again and check your spelling and capitalization this time." << endl;
		}

//Getting the option from the user.
		editOption = editMenuOption();
	}		
}

int editMenuOption()
/********************************************************************/
/* Function:   editMenuOption
/* Inputs:     none
/* Outputs:    This function returns "option" which is the option choice chosen by the user.
/* Purpose:    This function is supposed to get the option choice from the user, 
/* validate if it is in the range, and return it to the the editCD() function.
/********************************************************************/
{
//Variable declarations.
	int option;
	
//Displays the possible options the user can choose.
	cout << endl;
	cout << "Hello user select one of the following options:" << endl;
	cout << "1. Edit a CD" << endl;
	cout << "2. Quit(When done with editing.)" << endl;
	cout << "Choose your option:  ";
	cin >> option;
//This while loop takes in a value which represents the menu option and validates it to check if it is in the range.	
	while (option > 2 || option < 1)
	{
		option = invalid();
	}

//Returns the option chosen by the user.
	return option;
}

void editTheCD(CD* cdToEdit)
/********************************************************************/
/* Function:   editTheCD
/* Inputs:     "cdToEdit" which is the pointer of the CD the user wants to edit.
/* Outputs:    none
/* Purpose:    This function is used to edit the CD elements to whatever the user wants to change it to.
/********************************************************************/
{
	int editOption = 0;
	string artist = "";
	string title = "";
	int year = 0;

//Getting the option from the user.
	editOption = editTheCDMenuOption();

//Uses a while loop to run the option until the user choses to quit.
	while (editOption != 4)
	{
		if (editOption == 1)
		{	
			cout << "What do you want to change the artist name to: ";
			cin.ignore();
			getline(cin, artist);
			cdToEdit->setArtist(artist);	
		}
		else if (editOption == 2)
		{
			cout << "What do you want to change the title to: ";
			cin.ignore();
			getline(cin, title);
			cdToEdit->setTitle(title);
		}
		else if (editOption == 3)
		{
			cout << "What do you want to change the year to: ";
			cin >> year;
			cdToEdit->setYear(year);
		}

//Getting the option from the user.
		editOption = editTheCDMenuOption();
	}
}

int editTheCDMenuOption()
/********************************************************************/
/* Function:   editTheCDMenuOption
/* Inputs:     none
/* Outputs:    This function returns "option" which is the option choice chosen by the user.
/* Purpose:    This function is supposed to get the option choice from the user, 
/* validate if it is in the range, and return it to the the editCD() function.
/********************************************************************/
{
//Variable declarations.
	int option;
	
//Displays the possible options the user can choose.
	cout << endl;
	cout << "Hello user select the category you want to edit:" << endl;
	cout << "1. Artist" << endl;
	cout << "2. Title" << endl;
	cout << "3. Year" << endl;
	cout << "4. When done editing this CD." << endl;
	cout << "Choose your option:  ";
	cin >> option;
//This while loop takes in a value which represents the menu option and validates it to check if it is in the range.	
	while (option > 4 || option < 1)
	{
		option = invalid();
	}

//Returns the option chosen by the user.
	return option;
}

//Option 7: Add Tracks for CD
void addTracks(CD collection[], const int count)
/********************************************* */
/* Function:   addTracks                       
/* Inputs:     An array called "collection" which has all the songs from the file "cd.txt". "Count", which is the size of the list "collection".
/* Outputs:    none
/* Purpose:    To add tracks to the CD's the user wishes to add.
/********************************************* */
{
//Variable declarations.
	int place = -1;
	int numberOfTracks = 0;
	int trackOption = 0;
	int available = 0;
	string trackName = "";

//Gets the option choice from the user.
	trackOption = addTracksOption();

//Uses a while loop to run the option until the user choses to quit.
	while (trackOption != 2)
	{
		trackName = "";
		available = 0;
		
		cout << endl;
		cout << "Input the artist and title to find your CD." << endl;
		place = finder(collection, count);
			
		if (place != -1)
		{
			if (collection[place].getMaxTracks() == 0)
			{
				cout << "How many tracks do you want to add: ";
				cin >> numberOfTracks;
				collection[place].setMaxTracks(numberOfTracks);
			
				for (int i = 0; collection[place].getMaxTracks() > i && trackName != ">"; i++)
				{
					cout << "Enter track number " << i + 1 << " (or click '>' to quit): ";
					cin >> trackName;
					if (trackName != ">")
					{
						collection[place].setTrackName(trackName);
					}
				}
			}
			else if (collection[place].getMaxTracks() == collection[place].getNumTracks())
			{
				cout << "You have reached your maximum number of chosen tracks." << endl;
			}
			else
			{
				available = collection[place].getMaxTracks() - collection[place].getNumTracks();
				
				for (int i = collection[place].getMaxTracks() - available; collection[place].getMaxTracks() > i && trackName != ">"; i++)
				{
					cout << "Enter track number " << i + 1 << " (or click '>' to quit): ";
					cin >> trackName;
					if (trackName != ">")
					{
						collection[place].setTrackName(trackName);
					}
				}
			}
			
		}   	
		else
		{
			cout << "The CD was not found, try again and check your spelling and capitalization this time." << endl;
		}
		
//Gets the option choice from the user.
		trackOption = addTracksOption();
	}
}

int addTracksOption()
/********************************************************************/
/* Function:   addTracksOption
/* Inputs:     none
/* Outputs:    This function returns "option" which is the option choice chosen by the user.
/* Purpose:    This function is supposed to get the option choice from the user, 
/* validate if it is in the range, and return it to the the addTracksD() function.
/********************************************************************/
{
//Variable declarations.
	int option;
	
//Displays the possible options the user can choose.
	cout << endl;
	cout << "Hello user select one of the following options to edit:" << endl;
	cout << "1. Add Tracks" << endl;
	cout << "2. Quit" << endl;
	cout << "Choose your option:  ";
	cin >> option;
//This while loop takes in a value which represents the menu option and validates it to check if it is in the range.	
	while (option > 2 || option < 1)
	{
		option = invalid();
	}

//Returns the option chosen by the user.
	return option;
}

//Option 8: Delete all tracks for a CD
void deleteTracksCD(CD collection[], const int count)
/********************************************* */
/* Function:   displayCollection                       
/* Inputs:     A array called "collection" which has all the songs from the file "cd.txt". Count which is the size of the list collection.
/* Outputs:    none
/* Purpose:    To delete tracks for a specific CD.	2
/********************************************* */
{
//Variable declarations.
	int place = -1;
	
	cout << endl;
	cout << "Input the artist and title to find your CD." << endl;
	place = finder(collection, count);
	
//This if-else loop is used to validate the index(place) and delete the CD 
	if (place != -1)
	{
		if (collection[place].getNumTracks() > 0)
		{
			collection[place].deleteTracks();
		}
		
		cout << "Tracks for this CD have been deleted." << endl;
	}
	else
	{
		cout << "The CD was not found, try again and check your spelling and capitalization this time." << endl;
	}
}

//Option 9: Math Break Functions
void mathBreak()
/********************************************************************/
/* Function:   mathBreak                                       
/* Inputs:     There are no parameter inputs for this function.                                           
/* Outputs:    none                   
/* Purpose:    The purpose of this function is to show all the sub-menu options of the math break option. This program will redirect the user to 
whatever sub-menu option the user commands. 
/********************************************************************/
{
//Variable declarations.
	int mathOption;

//Gets the option choice from the user.
	mathOption = mathMenuOption();

//Uses a while loop to run the option until the user choses to quit.
	while (mathOption != 4)
	{		
//This if statement is used to redirect the user to what ever menu option they have chosen.		
		if (mathOption == 1)
		{
			evenOdd();
		}
		else if (mathOption == 2)
		{
			primeNumber();
		}
		else
		{
			stringReverse();
		}
		
//Gets the option choice from the user.
		mathOption = mathMenuOption();
	}
}

int mathMenuOption()
/********************************************************************/
/* Function:   mathMenuOption
/* Inputs:     none
/* Outputs:    This function returns "option" which is the option choice chosen by the user.
/* Purpose:    This function is supposed to get the option choice from the user, 
/* validate if it is in the range, and return it to the the mathBreak() function.
/********************************************************************/
{
//Variable declarations.
	int option;
	
//Displays the possible options the user can choose.
	cout << endl;
	cout << "Hello user select one of the following options:" << endl;
	cout << "1. Even or Odd" << endl;
	cout << "2. Prime Number" << endl;
	cout << "3. String Reverse" << endl;
	cout << "4. End my Math Break" << endl;
	cout << "Choose your option:  ";
	cin >> option;
//This while loop takes in a value which represents the menu option and validates it to check if it is in the range.	
	while (option > 4 || option < 1)
	{
		option = invalid();
	}

//Returns the option chosen by the user.
	return option;
}

//Even number functions.
void evenOdd()
/********************************************************************/
/* Function:   evenOdd                                       
/* Inputs:     There are no parameter inputs for this function.                                           
/* Outputs:    none                                        
/* Purpose:    This function is used to let the user know if the number entered by the user is even or not.
/********************************************************************/
{
//Variable declarations.
	int number;
	bool result;
	
	cout << endl;
	
	cout << "Enter a integer greater than 0 or 0 to quit this game:  ";
	cin >> number;
//This while loop takes in a integer value and validates it to check if it is in the range.
	while (number < 0)
	{
		number = invalid();
	}
	
	while (number != 0)
	{
//This if-else statement is used to check which statement to print.
		result = isEven(number);
	
		if (result == true)
		{
			cout << number << " is even." << endl;
		}
		else
		{
			cout << number << " is not even." << endl;
		}
		
//This while loop takes in a integer value and validates it to check if it is in the range.
		cout << "Enter a integer greater than 0 or 0 to quit this game:  ";
		cin >> number;
		while (number < 0)
		{
			number = invalid();
		}	
	}
}

bool isEven(const int number)
/********************************************************************/
/* Function:   isEven                                       
/* Inputs:     The parameter of this function is the integer the user enters in the evenOdd() function.                                   
/* Outputs:    The return value of this program is a boolean value of true or false. True meaning the number is even and false meaning 
the number is false.                     
/* Purpose:    This function is used to check weather the number is even or odd, and then the value is returned to the evenOdd() function.
/********************************************************************/
{
//This if-else statement is used to check weather the number is even or not and sends the correct return statement abck to the evenOdd() 
//function.
	bool result;

	if (number % 2 == 0)
	{
		result = true;
	}
	else
	{
		result = false;
	}
	
	return result;
}

//Prime number functions.
void primeNumber()
/********************************************************************/
/* Function:   primeNumber
/* Inputs:     There are no parameter inputs for this function.                                           
/* Outputs:    none                                       
/* Purpose:    This function is used to let the user know if the number entered by the user is prime or not.
/********************************************************************/
{
//Variable declarations.
	long int number;
//The number is assigned as long int so that the range of the variable is larger.
	bool result;

//This while loop takes in a integer value and validates it to check if it is in the range.
	cout << "Enter a integer greater than 0 or 0 to quit this game:  ";
	cin >> number;
	while (number < 0)
	{
		number = invalid();
	}
		
	while (number != 0)
	{
		result = isPrime(number);

//This if-else statement is used to check which statement to print.
		if (result == true)
		{
			cout << number << " is prime." << endl;
		}
		else
		{
			cout << number << " is not prime." << endl;
		}
			
//This while loop takes in a integer value and validates it to check if it is in the range.
		cout << "Enter a integer greater than 0 or 0 to quit this game:  ";
		cin >> number;
		while (number < 0)
		{
			number = invalid();
		}				
	}
}

bool isPrime(const long int number)
/********************************************************************/
/* Function:   isEven                                       
/* Inputs:     The parameter of this function is the integer the user enters in the isPrime() function.                                   
/* Outputs:    The return value of this program is a boolean value of true or false. True meaning the number is even and false meaning 
the number is false.                     
/* Purpose:    This function is used to check weather the number is prime or not, and then the value is returned to the primeNumber() function.
/********************************************************************/
{
//Variable declarations.
	bool result;
	int checker = 0;
	int accumulator = 1;

//This while loop checks to see the number of times the number divides by a number and has a result of 0.
//The 2nd condition is there in the loop so that the loop doesn't run until accumulator is as large as number.
//This is done so that the program doesn't take alot of time when handling large numbers.
	for (accumulator = 2; accumulator < number && checker != 1; accumulator++)
	{
		if (accumulator < number)
		{
			if (number % accumulator == 0)
			{
				checker++; 
			}
		}
	}

//This if-else statement is used to check weather the number is prime or not and sends the correct return statement abck to the primeNumber() 
//function.
	if (checker == 0)
	{
		result = true;
	}
	else
	{
		result = false;
	}
	
	return result;
}

//String reverse funtions.
void stringReverse()
/********************************************************************/
/* Function:   stringReverse                                       
/* Inputs:     none
/* Outputs:    none
/* Purpose:    This function gets the word(s) to reverse and sends it to the function reversify.
/********************************************************************/
{
//Variable declarations.
	string userInput = "";
	string newWord = "";
	int index = 0;

//Getting the word(s) to reverse.
	cout << "Enter a word to reverse:  ";
	cin.ignore();
	getline(cin, userInput);

	index = userInput.size();
	newWord = reversify(userInput, newWord, index);

//Displaying the user the reversed version of the word.
	cout << "The reversed version of the word is:  " << newWord << endl;
}

string reversify(string word, string newWord, int index)
/********************************************************************/
/* Function:   reversify                                       
/* Inputs:     "word" which is the word entered by the user. "newWord" which is the reversed version of "word". Index which is the index to check.
/* Outputs:    Returns newWord which is the reversed version of word. And it returns the function each time to make the recursive loop work.
/* Purpose:    This function is used to add each letter from word in reverse order to newWord and then return it.
/********************************************************************/
{
//This if condition is used to see if the index is going out of the bound.
	if (index == -1)
	{
		return newWord;
	}

//Adds the letter to newWord.
	newWord.push_back(word[index]);
	return reversify(word, newWord, index - 1);
}

//Used in many function.
int finder(CD collection[], int count)
/********************************************* */
/* Function:   finder
/* Inputs:     A array called "collection" which has all the songs from the file "CD.txt". Count which is the amount elements in the list.
/* Outputs:    Returns place which is the index of the CD.
/* Purpose:    The function is used to find the CD the user is looking for.
/********************************************* */
{
//Variable declarations.
	string artistToFind = "";
	string titleToFind = "";
	int place = -1;
	bool found = false;
	
	cout << "Enter the artist name you want to find: ";
	cin.ignore();
	getline(cin, artistToFind);
	cout << "Enter the title you want to find: ";
	getline(cin, titleToFind);
	
	for (int i = 0; count > i && !found; i++)
	{
		if (collection[i].getArtist() == artistToFind)
		{
			if (collection[i].getTitle() == titleToFind)
			{
				place = i;
				found = true;
			}
		}
	}
	
	return place;
}

int invalid()
/********************************************************************/
/* Function:   invalid                                       
/* Inputs:     none
/* Outputs:    The return value of this program is a integer value which returns the new option choice entered by the user.
/* Purpose:    This function is used to get a new value if the user enters a wrong option choice.
/********************************************************************/
{
//Variable declarations.
	int option = 0;
	
	cout << "Invaild option, reenter your option choice:  ";
	cin >> option;
	
	return option;
}

//End of code.
