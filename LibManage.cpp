////////////////////////////////////////////
//                                        //
//   LibManage                            //
//   Library Management Sytem             //
//                                        //
//   Copyright (c) 2007 Kartik Singhal.   //
//   kartiksinghal@gmail.com              //
//   All rights reserved.                 //
//                                        //
////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// Files required include: (program won't run without these)    //
// * LibManage.cpp * (this source file)                         //
// * LibManage.h *   (header file which includes all the        //
//                    required classes)                         //
// * date.h *        (header file concerning date class         //
//                    and date functions)                       //
// * conio2.h *      (replacement for 16-bit conio.h)           //
// * libconio.a *    (library file for conio2.h)                //
//////////////////////////////////////////////////////////////////
// This program uses the following files for data input/output: //
// * BOOK.DAT *    (to hold book information)                   //
// * MEMBER.DAT *  (to hold member information)                 //
// * TEMP.DAT  *   (to do certain temporary stuff)              //
//////////////////////////////////////////////////////////////////


#include "LibManage.h"

#define FINERATE   2             //the rate of fine in Rs. per day

// The names of data files can be changed here
#define BOOKFILE   "BOOK.DAT"
#define MEMBERFILE "MEMBER.DAT"
#define TEMPFILE   "TEMP.DAT"

char *tempText = NULL;           //pointer to hold temporary text data

// Program Execution starts
int main()
{
	Menu menu;
	menu.displayIntroduction();

	cout.setf(ios::showpoint | ios::fixed);
	cout<<setprecision(2);

	menu.displayMainMenu();

	delete tempText;

	return EXIT_SUCCESS;
} //End main()


///////////////////////////////////////////////////
// Function definitions pertaining to Menu Class //
///////////////////////////////////////////////////

// Displays the introductory screeen
void Menu::displayIntroduction(void)
{
	clrscr();

	gotoxy(33,6);                   cout<<"Welcome to";

	textcolor(BLACK); textbackground(WHITE);
	gotoxy(33,8);                 cprintf("LibManage");

	textcolor(LIGHTGRAY); textbackground(BLACK);
	gotoxy(15,10);cout<<"LibManage can maintain records of Books and Members.";


	gotoxy(15,13);cout<<"One member is allowed to issue one book at a time. If";
	gotoxy(15,14);cout<<"he/she does not return book upto 15 days, he/she has";
	gotoxy(15,15);cout<<"to pay a fine of Rs. "<<FINERATE<<"/- per day.";






	textcolor(LIGHTGRAY); textbackground(BLACK);
	gotoxy(27,22);          cprintf("Press any key to continue...");

	textcolor(LIGHTGRAY);

	_getch();
} //End displayIntroduction()

// Displays Main Menu
void Menu::displayMainMenu(void)
{
	char ch;
	while(1)
	{
		clrscr();
		gotoxy(29,6); cout<<"B O O K   L I B R A R Y";
		gotoxy(29,7); cout<<"-----------------------";
		gotoxy(30,10); cout<<"1. Introduction";
		gotoxy(30,11); cout<<"2. Add New Book(s)";
		gotoxy(30,12); cout<<"3. Add New Member(s)";
		gotoxy(30,13); cout<<"4. Issue Book";
		gotoxy(30,14); cout<<"5. Return Book";
		gotoxy(30,15); cout<<"6. List of Books";
		gotoxy(30,16); cout<<"7. List of Members";
		gotoxy(30,17); cout<<"8. Edit";
		gotoxy(30,18); cout<<"0. Quit";

		gotoxy(29,20);cout<<"Enter your choice: ";
		ch = _getche();

		if(ch == 27)
			break;
		else if(ch == '1')
			displayIntroduction();
		else if(ch == '2')
		{   
			Working W;
			W.addBook();
		}
		else if(ch == '3')
		{
			Working W;
			W.addMember();
		}
		else if(ch == '4')
		{
			Working W;
			W.issueBook();
		}
		else if(ch == '5')
		{
			Working W;
			W.returnBook();
		}
		else if(ch == '6')
		{
			Book B;
			B.displayList();
		}
		else if(ch == '7')
		{
			Member M;
			M.displayList();
		}
		else if(ch == '8')
			displayEditMenu();
		else if(ch == '0')
			break;
	}
} //End displayMainMenu()

// Displays Edit Menu
void Menu::displayEditMenu(void)
{
	char ch;
	while(1)
	{
		clrscr();
		gotoxy(32,9);  cout<<"E D I T   M E N U";
		gotoxy(32,10); cout<<"------------------";
		gotoxy(34,13);   cout<<"1. Books";
		gotoxy(34,14);   cout<<"2. Members";
		gotoxy(34,15);   cout<<"0. Exit";

		gotoxy(32,17); cout<<"Enter your choice: ";
		ch = _getche();

		if(ch == 27)
			break;
		else if(ch == '1')
			displayEditBookMenu();
		else if(ch == '2')
			displayEditMemberMenu();
		else if(ch == '0')
			break;
	}
} //End displayEditMenu()

// Displays Book-Edit Menu
void Menu::displayEditBookMenu(void)
{
	char ch;
	while(1)
	{
		clrscr();
		gotoxy(31,9);  cout<<"E D I T   B O O K S";
		gotoxy(31,10); cout<<"-------------------";
		gotoxy(34,13);    cout<<"1. Modify";
		gotoxy(34,14);    cout<<"2. Delete";
		gotoxy(34,15);    cout<<"0. Exit";

		gotoxy(31,17); cout<<"Enter your choice: ";
		ch = _getche();

		if(ch == 27)
			break;
		else if(ch == '1')
		{
			Working W;
			W.modifyBook();
		}
		else if(ch == '2')
		{
			Working W;
			W.deleteBook();
		}
		else if(ch == '0')
			break;
	}
} //End displayEditBookMenu()

// Displays Member-Edit Menu
void Menu::displayEditMemberMenu(void)
{
	char ch;
	while(1)
	{
		clrscr();
		gotoxy(29,9);  cout<<"E D I T   M E M B E R S";
		gotoxy(29,10); cout<<"-----------------------";
		gotoxy(34,13);      cout<<"1. Modify";
		gotoxy(34,14);      cout<<"2. Delete";
		gotoxy(34,15);      cout<<"0. Exit";

		gotoxy(29,17); cout<<"Enter your choice: ";
		ch = _getche();

		if(ch == 27)
			break;
		else if(ch == '1')
		{
			Working W;
			W.modifyMember();
		}
		else if(ch == '2')
		{
			Working W;
			W.deleteMember();
		}
		else if(ch == '0')
			break;
	}
} //End displayEditMemberMenu()


///////////////////////////////////////////////////
// Function definitions pertaining to Book Class //
///////////////////////////////////////////////////

// Returns 1 if book with given code is found
int Book::bookFound(int tcode)
{
	fstream file(BOOKFILE, ios::in);
	file.seekg(0, ios::beg);
	int found = 0;
	while( file.read( (char*)this, sizeof(Book) ) )
	{
		if(bookcode == tcode)
		{
			found = 1;
			break;
		}
	}
	file.close();
	return found;
} //End bookFound()

// Returns 1 if book with given name is found
int Book::booknameFound(char t1code[33])
{
	fstream file(BOOKFILE, ios::in);
	file.seekg(0, ios::beg);
	int found = 0;
	while( file.read( (char*)this, sizeof(Book) ) )
	{
		if( !strcmp(name, t1code) )
		{
			found = 1;
			break;
		}
	}
	file.close();
	return found;
} //End booknameFound()

// Returns the serial no. of given record from the data file
int Book::recordnoOf(int tcode)
{
	fstream file(BOOKFILE, ios::in);
	file.seekg(0, ios::beg);
	int count = 0;
	while( file.read( (char*)this, sizeof(Book) ) )
	{
		count++;
		if(bookcode == tcode)
			break;
	}
	file.close();
	return count;
} //End recordnoOf()

// Returns 1 if book is available
int Book::available(int tcode)
{
	fstream file(BOOKFILE, ios::in);
	file.seekg(0, ios::beg);
	int tavail = 0;
	while( file.read( (char*)this, sizeof(Book) ) )
	{
		if(bookcode == tcode)
		{
			tavail = avail;
			break;
		}
	}
	file.close();
	return tavail;
} //End available()

// Returns the total no. of copies of book
int Book::noOfCopiesOf(int tcode)
{
	fstream file(BOOKFILE, ios::in);
	file.seekg(0, ios::beg);
	int tcopies = 0;
	while( file.read( (char*)this, sizeof(Book) ) )
	{
		if(bookcode == tcode)
		{
			tcopies = copies;
			break;
		}
	}
	file.close();
	return tcopies;
} //End noOfCopiesOf()

// Returns the name of book with given code
char* Book::booknameOf(int tcode)
{
	fstream file(BOOKFILE, ios::in);
	file.seekg(0, ios::beg);
	delete tempText;
	tempText = new char[33];
	while( file.read( (char*)this, sizeof(Book) ) )
	{
		if(bookcode == tcode)
		{
			strcpy(tempText, name);
			break;
		}
	}
	file.close();
	return tempText;
} //End booknameOf()

// Returns the name of author the book with given code
char* Book::authornameOf(int tcode)
{
	fstream file(BOOKFILE, ios::in);
	file.seekg(0, ios::beg);
	delete tempText;
	char *tempText = new char[26];
	while( file.read( (char*)this, sizeof(Book) ) )
	{
		if(bookcode == tcode)
		{
			strcpy(tempText, author);
			break;
		}
	}
	file.close();
	return tempText;
} //End authornameOf()

// Returns the price of book with given code
float Book::bookpriceOf(int tcode)
{
	fstream file(BOOKFILE, ios::in);
	file.seekg(0, ios::beg);
	float tprice = 0.0;
	while( file.read( (char*)this, sizeof(Book) ) )
	{
		if(bookcode == tcode)
		{
			tprice = price;
			break;
		}
	}
	file.close();
	return tprice;
} //End bookpriceOf()

// Returns the code of the book with given name
int Book::bookcodeOf(char t1code[33])
{
	fstream file(BOOKFILE, ios::in);
	file.seekg(0, ios::beg);
	int tcode = 0;
	while( file.read( (char*)this, sizeof(Book) ) )
	{
		if( !strcmp(name, t1code) )
		{
			tcode = bookcode;
			break;
		}
	}
	file.close();
	return tcode;
} //End bookcodeOf()

// Returns the total no. of records of books
int Book::recCount(void)
{
	fstream file(BOOKFILE, ios::in);
	file.seekg(0, ios::beg);
	int count = 0;
	while( file.read( (char*)this, sizeof(Book) ) )
		count++;
	file.close();
	return count;
} //End recCount()

// Deletes record of book with given code
void Book::deleteRec(int tcode)
{
	fstream file(BOOKFILE, ios::in);
	fstream temp(TEMPFILE, ios::out);
	file.seekg(0, ios::beg);
	while( !file.eof() )
	{
		file.read( (char*)this, sizeof(Book) );
		if( file.eof() )
			break;
		if ( bookcode != tcode )
			temp.write( (char*)this, sizeof(Book) );
	}
	file.close();
	temp.close();

	ofstream fil2(BOOKFILE);
	temp.open(TEMPFILE, ios::in);
	temp.seekg(0, ios::beg);
	while( !temp.eof() )
	{
		temp.read( (char*)this, sizeof(Book) );
		if( temp.eof() )
			break;
		fil2.write( (char*)this, sizeof(Book) );
	}
	fil2.close();
	temp.close();
} //End deleteRec()

// Adds new book to data file
void Book::addNewBook(int tcode, char tname[33], char tauthor[26],
					  float tprice, int tcopies, int tavail)
{
	fstream file(BOOKFILE, ios::app);
	bookcode = tcode;
	strcpy(name, tname);
	strcpy(author, tauthor);
	price = tprice;
	copies = tcopies;
	avail = tavail;
	file.write( (char*)this, sizeof(Book) );
	file.close();
} //End addNewBook()

// Updates the no. of copies of books
void Book::updateCopies(int tcode, int tcopies, int tavail)
{
	int recno;
	recno = recordnoOf(tcode);
	fstream file(BOOKFILE, ios::out | ios::in);
	copies = tcopies;
	avail = tavail;
	int location;
	location = (recno-1) * sizeof(Book);
	file.seekp(location);
	file.write( (char*)this, sizeof(Book) );
	file.close();
} //End updateCopies()

// Modifies the book record
void Book::modify(int tcode, char tname[33], char tauthor[26],
				  float tprice)
{
	int recno;
	recno = recordnoOf(tcode);
	fstream file(BOOKFILE, ios::out | ios::ate | ios::in);
	strcpy(name, tname);
	strcpy(author, tauthor);
	price = tprice;
	int location;
	location = (recno-1) * sizeof(Book);
	file.seekp(location);
	file.write( (char*)this, sizeof(Book) );
	file.close();
} //End modify()

// Displays all the information about the book
void Book::display(int tcode)
{
	fstream file(BOOKFILE, ios::in);
	file.seekg(0, ios::beg);
	while( file.read( (char*)this, sizeof(Book) ) )
	{
		if(bookcode == tcode)
		{
			gotoxy(5,5);  cout<<"Book Code   : "<<bookcode;
			gotoxy(5,7);  cout<<"Book Name   : "<<name;
			gotoxy(5,8);  cout<<"Author Name : "<<author;
			gotoxy(5,9);  cout<<"Price       : Rs. "<<price;
			gotoxy(5,10); cout<<"Copies      : "<<copies;
			gotoxy(5,11); cout<<"Available   : "<<avail;
			break;
		}
	}
	file.close();
} //End display()

// Displays the list of all the books
void Book::displayList(void)
{
	clrscr();
	int row = 6, found = 0, flag = 0;
	char ch;

	gotoxy(34,2);                                 cout<<"LIST OF BOOKS";
	gotoxy(34,3);                                 cout<<"-------------";
	gotoxy(1,4);
	cout<<" CODE BOOK NAME                        AUTHOR                      "
		<<"PRICE  COPIES";
	gotoxy(1,5);
	cout<<"-------------------------------------------------------------------"
		<<"-------------";
	fstream file(BOOKFILE, ios::in);
	file.seekg(0, ios::beg);
	while( file.read( (char*)this, sizeof(Book) ) )
	{
		flag = 0;
		found=1;

		gotoxy(1,row);  cout<<setw(5)<<bookcode;
		gotoxy(7,row);  cout<<name;
		gotoxy(40,row); cout<<author;
		gotoxy(66,row); cout<<setw(7)<<price;
		gotoxy(77,row); cout<<setw(2)<<copies;

		textbackground(WHITE); textcolor(BLACK);
		gotoxy(40,row+1); cprintf("STATUS:");

		textcolor(BLACK);
		cprintf("%3d copies available",avail);

		textbackground(BLACK); textcolor(LIGHTGRAY);
		if(row == 22)
		{
			flag = 1;
			row = 6;

			gotoxy(1,25);
			cout<<"Press <ESC> to exit or any other key to continue...";
			ch = _getch();
			if(ch == 27)
				break;

			clrscr();
			gotoxy(34,2);                         cout<<"LIST OF BOOKS";
			gotoxy(34,3);                         cout<<"-------------";
			gotoxy(1,4);
			cout<<" CODE BOOK NAME                        AUTHOR              "
				<<"        PRICE  COPIES";
			gotoxy(1,5);
			cout<<"-----------------------------------------------------------"
				<<"---------------------";
		}
		else 
			row += 2;
	}
	if(!found)
	{
		gotoxy(5,10); cerr<<"\7Records not found";
	}
	if(!flag)
	{
		gotoxy(1,25); cout<<"Press any key to continue...";
		_getche();
	}
	file.close();
} //End displayList()


/////////////////////////////////////////////////////
// Function definitions pertaining to Member Class //
/////////////////////////////////////////////////////

// Returns 1 if member with given code is found
int Member::memberFound(int mcode)
{
	fstream file(MEMBERFILE, ios::in);
	file.seekg(0, ios::beg);
	int found = 0;
	while( file.read( (char*)this, sizeof(Member) ) )
	{
		if(memcode == mcode)
		{
			found = 1;
			break;
		}
	}
	file.close();
	return found;
} //End memberFound()

// Returns the code of the book issued to member
int Member::issuedFor(int mcode)
{
	fstream file(MEMBERFILE, ios::in);
	file.seekg(0, ios::beg);
	int missue = 0;
	while( file.read( (char*)this, sizeof(Member) ) )
	{
		if(memcode == mcode)
		{
			missue = bookcode;
			break;
		}
	}
	file.close();
	return missue;
} //End issuedFor()

// Returns the amount of fine for given member code
int Member::fineFor(int mcode)
{
	Date today;
	fstream file(MEMBERFILE, ios::in);
	file.seekg(0, ios::beg);
	int days;
	int t_fine;
	while( file.read( (char*)this, sizeof(Member) ) )
	{
		if(memcode == mcode)
		{
			days = today.diff(returnDate);
			t_fine = days * FINERATE;
			break;
		}
	}
	file.close();
	return t_fine;
} //End fineFor()

// Returns the code of the last member from the data file
int Member::lastcode(void)
{
	fstream file(MEMBERFILE, ios::in);
	file.seekg(0, ios::beg);
	int mcode = 0;
	while( file.read( (char*)this, sizeof(Member) ) )
		mcode = memcode;
	file.close();
	return mcode;
} //End lastcode()

// Returns the name of member with given code
char* Member::membername(int mcode)
{
	fstream file(MEMBERFILE, ios::in);
	file.seekg(0, ios::beg);
	delete tempText;
	char *tempText = new char[26];
	while( file.read( (char*)this, sizeof(Member) ) )
	{
		if(memcode == mcode)
		{
			strcpy(tempText, name);
			break;
		}
	}
	file.close();
	return tempText;
} //End membername()

// Returns the phone number of member with given code
char* Member::memberphone(int mcode)
{
	fstream file(MEMBERFILE, ios::in);
	file.seekg(0, ios::beg);
	delete tempText;
	char *tempText = new char[10];
	while( file.read( (char*)this, sizeof(Member) ) )
	{
		if(memcode == mcode)
		{
			strcpy(tempText, phone);
			break;
		}
	}
	file.close();
	return tempText;
} //End memberphone()

// Returns the address of member with given code
char* Member::memberaddress(int mcode)
{
	fstream file(MEMBERFILE, ios::in);
	file.seekg(0, ios::beg);
	delete tempText;
	char *tempText = new char[33];
	while( file.read( (char*)this, sizeof(Member) ) )
	{
		if(memcode == mcode)
		{
			strcpy(tempText, address);
			break;
		}
	}
	file.close();
	return tempText;
} //End memberaddress()

// Returns the serial no. of given record from the data file
int Member::recordnoOf(int mcode)
{
	fstream file(MEMBERFILE, ios::in);
	file.seekg(0, ios::beg);
	int count = 0;
	while( file.read( (char*)this, sizeof(Member) ) )
	{
		count++;
		if(memcode == mcode)
			break;
	}
	file.close();
	return count;
} //End recordnoOf()

// Deletes the record of member with given code
void Member::deleteRec(int mcode)
{
	fstream file(MEMBERFILE, ios::in);
	fstream temp(TEMPFILE, ios::out);
	file.seekg(0, ios::beg);
	while( !file.eof() )
	{
		file.read( (char*)this, sizeof(Member) );
		if( file.eof() )
			break;
		if( memcode != mcode )
			temp.write( (char*)this, sizeof(Member) );
	}
	file.close();
	temp.close();

	ofstream fil2(MEMBERFILE);
	temp.open(TEMPFILE, ios::in);
	temp.seekg(0, ios::beg);
	while( !temp.eof() )
	{
		temp.read( (char*)this, sizeof(Member) );
		if( temp.eof() )
			break;
		fil2.write( (char*)this, sizeof(Member) );
	}
	fil2.close();
	temp.close();
} //End deleteRec()

// Updates the book information of member
void Member::updateBook(int mcode, int tcode, Date ret_date)
{
	fstream file(MEMBERFILE, ios::in);
	fstream temp(TEMPFILE, ios::out);
	file.seekg(0, ios::beg);
	while( !file.eof() )
	{
		file.read( (char*)this, sizeof(Member) );
		if( file.eof() )
			break;
		if ( memcode == mcode )
		{
			bookcode = tcode;
			returnDate = ret_date;
			temp.write( (char*)this, sizeof(Member) );
		}
		else 
			temp.write( (char*)this, sizeof(Member) );
	}
	file.close();
	temp.close();

	ofstream fil2(MEMBERFILE);
	temp.open(TEMPFILE, ios::in);
	temp.seekg(0, ios::beg);
	while( !temp.eof() )
	{
		temp.read( (char*)this, sizeof(Member) );
		if( temp.eof() )
			break;
		fil2.write( (char*)this, sizeof(Member) );
	}
	fil2.close();
	temp.close();
} //End updateBook()

// Modifies the member record
void Member::modify(int mcode, char mname[26], char mphone[10],
					char maddress[33])
{
	int recno;
	recno = recordnoOf(mcode);
	fstream file(MEMBERFILE, ios::out | ios::ate | ios::in);
	strcpy(name, mname);
	strcpy(address, maddress);
	strcpy(phone, mphone);
	int location;
	location = (recno-1) * sizeof(Member);
	file.seekp(location);
	file.write( (char*)this, sizeof(Member) );
	file.close();
} //End modify()

// Adds new member to data file
void Member::addMem(int mcode, int bcode, char mname[26], char maddress[33],
					char mphone[10], Date ret_date)
{
	fstream file(MEMBERFILE, ios::app);
	memcode = mcode;
	bookcode = bcode;
	strcpy(name, mname);
	strcpy(address, maddress);
	strcpy(phone, mphone);
	returnDate = ret_date;
	file.write( (char*)this, sizeof(Member) );
	file.close();
} //End addMem

// Displays all information about the member
void Member::display(int mcode)
{
	fstream file(MEMBERFILE, ios::in);
	file.seekg(0, ios::beg);
	while( file.read( (char*)this, sizeof(Member) ) )
	{
		if(memcode == mcode)
		{
			gotoxy(5,3);  cout<<"Member Code   : "<<mcode;
			gotoxy(5,5);  cout<<"Member Name   : "<<name;
			gotoxy(5,6);  cout<<"Phone Number  : "<<phone;
			gotoxy(5,7);  cout<<"Address       : "<<address;
			break;
		}
	}
	file.close();
} //End display()

// Displays the list of all the members
void Member::displayList(void)
{
	clrscr();
	Book B;
	int row = 6, found = 0, flag = 0;
	char ch;
	gotoxy(32,2); cout<<"LIST OF MEMBERS";
	gotoxy(32,3); cout<<"---------------";
	gotoxy(1,4);
	cout<<"    CODE      BOOK CODE          NAME                              "
		<<"  PHONE      ";
	gotoxy(1,5);
	cout<<"-------------------------------------------------------------------"
		<<"-------------";
	fstream file(MEMBERFILE, ios::in);
	file.seekg(0, ios::beg);
	while( file.read( (char*)this, sizeof(Member) ) )
	{
		flag = 0;
		found=1;
		gotoxy(4,row); cout<<setw(5)<<memcode;
		gotoxy(17,row); cout<<setw(5)<<bookcode;
		gotoxy(34,row); cout<<name;
		gotoxy(66,row); cout<<setw(9)<<phone;
		textbackground(WHITE); textcolor(BLACK);
		gotoxy(7,row+1);
		if( bookcode == 0)
			cprintf("BOOK NAME: (Not Issued)");
		else
		{
			cout<<"BOOK NAME: "<<B.booknameOf(bookcode);
			gotoxy(42, row+1);
			cprintf("Date of return: ");
			textcolor(BLACK);
			returnDate.printDate();
		}
		textbackground(BLACK); textcolor(LIGHTGRAY);
		if(row == 22)
		{
			flag = 1;
			row = 6;
			gotoxy(1,25);
			cout<<"Press <ESC> to exit or any other key to continue...";
			ch = _getch();
			if(ch == 27)
				break;
			clrscr();
			gotoxy(32,2); cout<<"LIST OF MEMBERS";
			gotoxy(32,3); cout<<"---------------";
			gotoxy(1,4);
			cout<<"    CODE      BOOK CODE          NAME                      "
				<<"          PHONE      ";
			gotoxy(1,5);
			cout<<"-----------------------------------------------------------"
				<<"---------------------";
		}
		else 
			row += 2;
	}
	if(!found)
	{
		gotoxy(5,10); cerr<<"\7Records not found";
	}
	if(!flag)
	{
		gotoxy(1,25); cout<<"Press any key to continue...";
		_getche();
	}
	file.close();
} //End displayList()


//////////////////////////////////////////////////////
// Function definitions pertaining to Working Class //
//////////////////////////////////////////////////////

// To add a new book
void Working::addBook(void)
{
	if(!recCount())
	{ 
		addNewBook(0, "null", "null", 0.0, 0, 0);
		Book::deleteRec(0);
	}
	char ch;
	int tcode, tcopies, tavail;
	char tname[33], tauthor[26];
	float tprice = 0.0;
	do
	{
		int found = 0, valid = 0;
		int tc;
		float t2 = 0.0;
		char *t = NULL;
		clrscr();
		gotoxy(29,3); cout<<"ADDITION OF THE BOOKS";
		gotoxy(29,4); cout<<"---------------------";
		gotoxy(71,1); cout<<"<0> = Exit";
		gotoxy(5,25); cout<<"Enter code no. of the book";
		gotoxy(5,5); cout<<"Code no. ";
		t = new char[10];
		gets(t);
		if ( strlen(t)>8 )
			exitLM();
		tc = atoi(t);
		tcode = tc;
		delete t;
		if (tcode == 0)
			return;
		if (bookFound(tcode))
		{
			found = 1;
			gotoxy(19,8); cout<<booknameOf(tcode);
			gotoxy(19,9); cout<<authornameOf(tcode);
			gotoxy(23,10); cout<<bookpriceOf(tcode);
			gotoxy(19,12); cout<<noOfCopiesOf(tcode);
		}
		gotoxy(5,8);  cout<<"Book Name   : ";
		gotoxy(5,9);  cout<<"Author Name : ";
		gotoxy(5,10); cout<<"Price       : Rs. ";
		gotoxy(5,12); cout<<"Copies      : ";
		valid = 0;
		while(!valid && !found)
		{
			valid = 1;
			gotoxy(5,25); clreol();
			cout<<"Enter the name of the book";
			gotoxy(19,8); clreol();
			gets(tname);
			_strupr(tname);
			if(tname[0] == '0')
				return;
			if(strlen(tname) < 1 || strlen(tname) > 31)
			{
				valid = 0;
				gotoxy(5,25); clreol();
				cerr<<"\7Enter correctly (Range: 1..31)";
				_getch();
			}
		}
		valid = 0;
		while(!valid && !found)
		{
			valid = 1;
			gotoxy(5,25); clreol();
			cout<<"Enter the name of the author of the book";
			gotoxy(19,9); clreol();
			gets(tauthor);
			_strupr(tauthor);
			if(tauthor[0] == '0')
				return;
			if(strlen(tauthor) < 1 || strlen(tauthor) > 24)
			{
				valid = 0;
				gotoxy(5,25); clreol();
				cerr<<"\7Enter correctly (Range: 1..24)";
				_getch();
			}
		}
		valid = 0;
		while(!valid && !found)
		{
			valid = 1;
			gotoxy(5,25); clreol();
			cout<<"Enter the price of the book";
			gotoxy(23,10); clreol();
			t = new char[10];
			gets(t);
			if ( strlen(t)>8 )
				exitLM();			
			t2 = (float)atof(t);
			tprice = t2;
			if(t[0] == '0')
			{
				delete t;
				return;
			}
			delete t;
			if(tprice < 1 || tprice > 9999)
			{
				valid = 0;
				gotoxy(5,25); clreol();
				cerr<<"\7Enter correctly";
				_getch();
			}
		}
		valid = 0;
		while(!valid && !found)
		{
			valid = 1;
			gotoxy(5,25); clreol();
			cout<<"Enter no. of copies of book to be added";
			gotoxy(19,12); clreol();
			t = new char[10];
			gets(t);
			if ( strlen(t)>8 )
				exitLM();
			tc = atoi(t);
			tcopies = tc;
			if(t[0] == '0')
			{
				delete t;
				return;
			}
			delete t;
			if(tcopies < 1 || tcopies > 50)
			{
				valid = 0;
				gotoxy(5,25); clreol();
				cerr<<"\7Enter correctly";
				_getch();
			}
		}
		if(found)
		{
			gotoxy(5,25); clreol();
			cout<<"Press <SPACE> to change the no. of copies";
			char c=_getch();
			if(c != ' ')
				goto skipsaving;
			valid = 0;
			while(!valid)
			{
				valid = 1;
				gotoxy(5,25); clreol();
				cout<<"Enter no. of copies to be added, use minus (-) sign to "
					<<"remove copies";
				gotoxy(5,13); cout<<"Add Copies  :";
				gotoxy(19,13); clreol();
				t = new char[10];
				gets(t);
				if ( strlen(t)>8 )
					exitLM();
				tc = atoi(t);
				tcopies = tc;
				if(t[0] == '0')
				{
					delete t;
					return;
				}
				delete t;
				if(tcopies+noOfCopiesOf(tcode) < 1
					|| tcopies+noOfCopiesOf(tcode) > 50)
				{
					valid = 0;
					gotoxy(5,25); clreol();
					cerr<<"\7Enter correctly";
					_getch();
				}
			}
		}
		if(!found)
			tavail = tcopies;
		else
		{
			tavail = available(tcode) + tcopies;
			tcopies = noOfCopiesOf(tcode) + tcopies;
		}
		gotoxy(5,25); clreol();
		do
		{
			gotoxy(5,15); clreol();
			cout<<"Do you want to save (y/n): ";
			ch = _getche();
			ch = toupper(ch);
		}while(ch!='Y' && ch!='N');
		if(ch == 'Y')
		{
			if(found)
				updateCopies(tcode, tcopies, tavail);
			else
				addNewBook(tcode, tname, tauthor, tprice, tcopies, tavail);
		}
skipsaving:
		do
		{
			gotoxy(5,25); clreol();
			gotoxy(5,17); clreol();
			cout<<"Do you want to add more (y/n): ";
			ch = _getche();
			ch = toupper(ch);
		}while(ch!='Y' && ch!='N');
	}while(ch == 'Y');
} //End addBook()

// To add a new member
void Working::addMember(void)
{
	char ch;
	int mcode, bcode;
	char mname[26], mphone[10], maddress[33];
	mcode = lastcode();
	mcode++;
	do
	{
		int valid = 0;
		clrscr();
		gotoxy(28,3); cout<<"ADDITION OF THE MEMBERS";
		gotoxy(28,4); cout<<"-----------------------";
		gotoxy(71,1); cout<<"<0> = Exit";
		gotoxy(5,7); cout<<"Member Code # "<<mcode;
		gotoxy(5,8); cout<<"-------------------";
		gotoxy(5,10); cout<<"Name    : ";
		gotoxy(5,12); cout<<"Phone   : ";
		gotoxy(5,14); cout<<"Address : ";
		do
		{
			valid = 1;
			gotoxy(5,25); clreol();
			cout<<"Enter the name of the New Member";
			gotoxy(15,10); clreol();
			gets(mname);
			_strupr(mname);
			if(mname[0] == '0')
				return;
			if(strlen(mname) < 1 || strlen(mname) > 24)
			{
				valid = 0;
				gotoxy(5,25); clreol();
				cerr<<"\7Enter correctly (Range: 1..24)";
				_getch();
			}
		}while(!valid);
		do
		{
			valid = 1;
			gotoxy(5,25); clreol();
			cout<<"Enter Phone no. of the Member or Press <ENTER> for none";
			gotoxy(15,12); clreol();
			gets(mphone);
			if(mphone[0] == '0')
				return;
			if((strlen(mphone) < 7 && strlen(mphone) > 0) || strlen(mphone) > 8)
			{
				valid = 0;
				gotoxy(5,25); clreol();
				cerr<<"\7Enter correctly";
				_getch();
			}
		}while(!valid);
		if(strlen(mphone) == 0) strcpy(mphone, "-");
		do
		{
			valid = 1;
			gotoxy(5,25); clreol();
			cout<<"Enter the address of the New Member";
			gotoxy(15,14); clreol();
			gets(maddress);
			_strupr(maddress);
			if(maddress[0] == '0')
				return;
			if(strlen(maddress) < 1 || strlen(maddress) > 31)
			{
				valid = 0;
				gotoxy(5,25); clreol();
				cerr<<"\7Enter correctly (Range: 1..31)";
				_getch();
			}
		}while(!valid);
		gotoxy(5,25); clreol();
		do
		{
			gotoxy(5,17); clreol();
			cout<<"Do you want to save (y/n): ";
			ch = _getche();
			ch = toupper(ch);
			if(ch == '0')
				return;
		}while(ch!='Y' && ch!='N');
		if(ch == 'Y')
		{
			bcode = 0;
			addMem(mcode, bcode, mname, maddress, mphone, Date(0));
			mcode++;
		}
		do
		{
			gotoxy(5,19); clreol();
			cout<<"Do you want to add more (y/n): ";
			ch = _getche();
			ch = toupper(ch);
			if(ch == '0')
				return;
		}while(ch!='Y' && ch!='N');
	}while(ch == 'Y');
} //End addMember()

// To issue a book
void Working::issueBook(void)
{
	Book B;
	Member M;
	Date today;
	char t1code[33];
	char ch;
	int t2code = 0, tcode = 0, mcode = 0;
	int valid;
	do
	{
		valid = 1;
		while(1)
		{
			clrscr();
			gotoxy(5,2); cout<<"Date : "; today.printDate();
			gotoxy(71,1); cout<<"<0> = Exit";
			gotoxy(5,5); cout<<"Enter Code or Name of the book to be issued";
			gotoxy(5,6); cout<<"            or           ";
			gotoxy(5,7); cout<<"Press <ENTER> for help ";
			gets(t1code);
			if(t1code[0] == '0')
				return;
			if(strlen(t1code) == 0)
				B.displayList();
			else
				break;
		}
		t2code = atoi(t1code);
		tcode = t2code;

		if( (tcode == 0 && !booknameFound( _strupr(t1code) ) ) 
			|| (tcode != 0 && !bookFound(tcode)) )
		{
			valid = 0;
			gotoxy(5,10);
			cerr<<"\7Record not found";
			gotoxy(5,11);
			cout<<"Press <ESC> to exit or any other key to continue...";
			ch = _getch();
			if(ch == 27)
				return;
		}
	}while(!valid);
	if(tcode == 0)
		tcode = bookcodeOf(t1code);
	if(!available(tcode))
	{
		gotoxy(5,10);
		cerr<<"\7Sorry! Book ("<<booknameOf(tcode)<<") is not available";
		gotoxy(5,11);
		cout<<"Kindly issue any other Book";
		gotoxy(5,12);
		cout<<"See List of Books";
		_getch();
		return;
	}
	do
	{
		valid = 1;
		while(1)
		{
			clrscr();
			gotoxy(5,2); cout<<"Date : "; today.printDate();
			gotoxy(71,1); cout<<"<0> = Exit";
			gotoxy(5,5); cout<<"Book Name: "<<booknameOf(tcode);
			gotoxy(5,7); cout<<"Enter Code no. of the Member";
			gotoxy(5,8); cout<<"        or              ";
			gotoxy(5,9); cout<<"Press <ENTER> for help ";
			gets(t1code);
			if(t1code[0] == '0')
				return;
			if(strlen(t1code) == 0)
				M.displayList();
			else
				break;
		}
		t2code = atoi(t1code);
		mcode = t2code;
		if(mcode == 0)
		{
			valid = 0;
			gotoxy(5,25);
			cerr<<"\7Enter Correctly";
			_getch();
		}
		if( !memberFound(mcode) && valid )
		{
			valid = 0;
			gotoxy(5,13);
			cerr<<"\7Record not found";
			gotoxy(5,14);
			cout<<"Press <ESC> to exit or any other key to continue...";
			ch = _getch();
			if(ch == 27)
				return;
		}
	}while(!valid);
	if( issuedFor(mcode) )
	{
		gotoxy(5,13);
		cerr<<"\7Sorry, Member already has a book issued";
		gotoxy(5,14);
		cout<<"Press any key to continue";
		_getch();
		return;
	}
	int tcopies, tavail;
	tcopies = noOfCopiesOf(tcode);
	tavail = available(tcode) - 1;
	updateCopies(tcode, tcopies, tavail);
	today.extendDate(15);
	updateBook(mcode, tcode, today);
	gotoxy(5,13);
	cout<<"\7Book issued to "<<membername(mcode);
	gotoxy(5,15);
	cout<<"Date of Return: "; today.printDate();
	_getch();
} //End issueBook()

// To return a book
void Working::returnBook(void)
{
	Member M;
	char t1code[5];
	char ch;
	int t2code = 0, mcode = 0;
	int valid;
	Date today;
	do
	{
		valid = 1;
		while(1)
		{
			clrscr();
			gotoxy(5,2); cout<<"Date : "; today.printDate();
			gotoxy(71,1); cout<<"<0> = Exit";
			gotoxy(5,5); cout<<"Enter Code no. of the Member who wants to retu"
				<<"rn book";
			gotoxy(5,6); cout<<"                 or           ";
			gotoxy(5,7); cout<<"Press <ENTER> for help ";
			gets(t1code);
			if(t1code[0] == '0')
				return;
			if(strlen(t1code) == 0)
				M.displayList();
			else
				break;
		}
		t2code = atoi(t1code);
		mcode = t2code;
		if(mcode == 0)
		{
			valid = 0;
			gotoxy(5,25);
			cerr<<"\7Enter Correctly";
			_getch();
		}
		if( !memberFound(mcode) && valid )
		{
			valid = 0;
			gotoxy(5,13);
			cerr<<"\7Record not found";
			gotoxy(5,14);
			cout<<"Press <ESC> to exit or any other key to continue...";
			ch = _getch();
			if(ch == 27)
				return;
		}
		if( !issuedFor(mcode) && valid )
		{
			valid = 0;
			gotoxy(5,13);
			cerr<<"\7Member have no book to return";
			gotoxy(5,14);
			cout<<"Press <ESC> to exit or any other key to continue...";
			ch = _getch();
			if(ch == 27)
				return;
		}
	}while(!valid);
	int bcode, tcopies, tavail;
	bcode = issuedFor(mcode);
	gotoxy(5,13);
	cout<<"Book Code : "<<bcode;
	gotoxy(5,14);
	cout<<"Book Name : "<<booknameOf(bcode);
	tcopies = noOfCopiesOf(bcode);
	tavail = available(bcode) + 1;
	int f;
	f = fineFor(mcode);
	if(f != 0)
	{
		gotoxy(5,16);
		cout<<"You have to pay a fine of Rs. "<<f;
		gotoxy(5,17);
		cout<<"Please do not delay the Return of Book again";
	}
	updateCopies(bcode, tcopies, tavail);
	updateBook(mcode, 0, Date(0));
	gotoxy(5,19);
	cout<<"\7Book has been returned";
	_getch();
} //End returnBook()

// To modify the record of a book
void Working::modifyBook(void)
{
	Book B;
	char t1code[5], tname[33], tauthor[26], *t1 = NULL;
	char ch;
	int t2code = 0, tcode = 0;
	float t2 = 0.0, tprice = 0.0;
	int valid;
	do
	{
		valid = 1;
		while(1)
		{
			clrscr();
			gotoxy(71,1); cout<<"<0> = Exit";
			gotoxy(5,5); cout<<"Enter Code or Name of the book to be modified";
			gotoxy(5,6); cout<<"            or           ";
			gotoxy(5,7); cout<<"Press <ENTER> for help ";
			gets(t1code);
			if(t1code[0] == '0')
				return;
			if(strlen(t1code) == 0)
				B.displayList();
			else
				break;
		}
		t2code = atoi(t1code);
		tcode = t2code;

		if( (tcode == 0 && !booknameFound( _strupr(t1code) ) ) 
			|| (tcode != 0 && !bookFound(tcode)) )
		{
			valid = 0;
			gotoxy(5,10);
			cerr<<"\7Record not found";
			gotoxy(5,11);
			cout<<"Press <ESC> to exit or any other key to continue...";
			ch = _getch();
			if(ch == 27)
				return;
		}
	}while(!valid);
	if(tcode == 0)
		tcode = bookcodeOf(t1code);
	clrscr();
	gotoxy(71,1); cout<<"<0> = Exit";
	Book::display(tcode);
	do
	{
		gotoxy(5,13); clreol();
		cout<<"Do you want to modify this record (y/n) : ";
		ch = _getche();
		ch = toupper(ch);
		if(ch == '0')
			return;
	}while(ch!='Y' && ch!='N');
	if(ch == 'N')
		return;
	gotoxy(5,16);  cout<<"Book Name   : ";
	gotoxy(5,17);  cout<<"Author Name : ";
	gotoxy(5,18);  cout<<"Price       : Rs. ";
	do
	{
		valid = 1;
		gotoxy(5,25); clreol();
		cout<<"Enter the name of the book or <ENTER> for no change";
		gotoxy(19,16); clreol();
		gets(tname);
		_strupr(tname);
		if(tname[0] == '0')
			return;
		if(strlen(tname) > 31)
		{
			valid = 0;
			gotoxy(5,25); clreol();
			cerr<<"\7Enter correctly (Range: 1..31)";
			_getch();
		}
	}while(!valid);
	if(strlen(tname) == 0)
		strcpy(tname, booknameOf(tcode));
	do
	{
		valid = 1;
		gotoxy(5,25); clreol();
		cout<<"Enter the author's name or <ENTER> for no change";
		gotoxy(19,17); clreol();
		gets(tauthor);
		_strupr(tauthor);
		if(tauthor[0] == '0')
			return;
		if(strlen(tauthor) > 24)
		{
			valid = 0;
			gotoxy(5,25); clreol();
			cerr<<"\7Enter correctly (Range: 1..24)";
			_getch();
		}
	}while(!valid);
	if(strlen(tauthor) == 0)
		strcpy(tauthor, authornameOf(tcode));
	do
	{
		delete t1;
		t1 = new char[6];
		valid = 1;
		gotoxy(5,25); clreol();
		cout<<"Enter price or <ENTER> for no change";
		gotoxy(23,18); clreol();
		gets(t1);
		t2 = (float)atof(t1);
		tprice = t2;
		if(t1[0] == '0')
		{
			delete t1;
			return;
		}
		if(strlen(t1) == 0)
			break;
		if(tprice < 1 || tprice > 9999)
		{
			valid = 0;
			gotoxy(5,25); clreol();
			cerr<<"\7Enter correctly";
			_getch();
		}
	}while(!valid);
	if(strlen(t1) == 0)
		tprice = bookpriceOf(tcode);
	delete t1;
	gotoxy(5,25); clreol();
	do
	{
		gotoxy(5,20); clreol();
		cout<<"Do you want to save changes (y/n): ";
		ch = _getche();
		ch = toupper(ch);
		if(ch == '0')
			return;
	}while(ch!='Y' && ch!='N');
	if(ch == 'N')
		return;
	Book::modify(tcode, tname, tauthor, tprice);
	gotoxy(5,23); cout<<"\7Record Modified";
	_getch();
} //End modifyBook()

// To modify the record of a member
void Working::modifyMember(void)
{
	Member M;
	char m1code[10], mname[26], mphone[10], maddress[33];
	char ch;
	int m2code = 0, mcode = 0;
	int valid;
	do
	{
		valid = 1;
		while(1)
		{
			clrscr();
			gotoxy(71,1); cout<<"<0> = Exit";
			gotoxy(5,7); cout<<"Enter Code no. of the Member to be modified";
			gotoxy(5,8); cout<<"                or           ";
			gotoxy(5,9); cout<<"Press <ENTER> for help ";
			gets(m1code);
			m2code = atoi(m1code);
			mcode = m2code;
			if(m1code[0] == '0')
				return;
			if(strlen(m1code) == 0)
				M.displayList();
			else
				break;
		}
		if(mcode == 0)
		{
			valid = 0;
			gotoxy(5,25); cerr<<"\7Enter Correctly";
			_getch();
		}
		if(valid && !memberFound(mcode))
		{
			valid = 0;
			gotoxy(5,13);
			cerr<<"\7Record not found";
			gotoxy(5,14);
			cout<<"Press <ESC> to exit or any other key to continue...";
			ch = _getch();
			if(ch == 27)
				return;
		}
	}while(!valid);
	clrscr();
	gotoxy(71,1); cout<<"<0> = Exit";
	Member::display(mcode);
	do
	{
		gotoxy(5,10); clreol();
		cout<<"Do you want to modify this record (y/n) : ";
		ch = _getche();
		ch = toupper(ch);
		if(ch == '0')
			return;
	}while(ch!='Y' && ch!='N');
	if(ch == 'N')
		return;
	gotoxy(5,13);  cout<<"Name          : ";
	gotoxy(5,14);  cout<<"Phone         : ";
	gotoxy(5,15);  cout<<"Address       : ";
	do
	{
		valid = 1;
		gotoxy(5,25); clreol();
		cout<<"Enter the name of member or <ENTER> for no change";
		gotoxy(21,13); clreol();
		gets(mname);
		_strupr(mname);
		if(mname[0] == '0')
			return;
		if(strlen(mname) > 24)
		{
			valid = 0;
			gotoxy(5,25); clreol();
			cerr<<"\7Enter correctly (Range: 1..24)";
			_getch();
		}
	}while(!valid);
	if(strlen(mname) == 0)
		strcpy(mname, membername(mcode));
	do
	{
		valid = 1;
		gotoxy(5,25); clreol();
		cout<<"Enter the Phone no. of member or <ENTER> for no change";
		gotoxy(21,14); clreol();
		gets(mphone);
		if(mphone[0] == '0')
			return;
		if((strlen(mphone) < 7 && strlen(mphone) > 0) || strlen(mphone) > 8)
		{
			valid = 0;
			gotoxy(5,25); clreol();
			cerr<<"\7Enter correctly";
			_getch();
		}
	}while(!valid);
	if(strlen(mphone) == 0)
		strcpy(mphone, memberphone(mcode));
	do
	{
		valid = 1;
		gotoxy(5,25); clreol();
		cout<<"Enter the address of the member or <ENTER> for no change";
		gotoxy(21,15); clreol();
		gets(maddress);
		_strupr(maddress);
		if(maddress[0] == '0')
			return;
		if(strlen(maddress) > 31)
		{
			valid = 0;
			gotoxy(5,25); clreol();
			cerr<<"\7Enter correctly (Range: 1..31)";
			_getch();
		}
	}while(!valid);
	if(strlen(maddress) == 0)
		strcpy(maddress, memberaddress(mcode));
	gotoxy(5,25); clreol();
	do
	{
		gotoxy(5,18); clreol();
		cout<<"Do you want to save changes (y/n): ";
		ch = _getche();
		ch = toupper(ch);
		if(ch == '0')
			return;
	}while(ch!='Y' && ch!='N');
	if(ch == 'N')
		return;
	Member::modify(mcode, mname, mphone, maddress);
	gotoxy(5,23); cout<<"\7Record Modified";
	_getch();
} //End modifyMember()

// To delete the record of a book
void Working::deleteBook(void)
{
	Book B;
	char t1code[5];
	char ch;
	int t2code = 0, tcode = 0;
	int valid;
	do
	{
		valid = 1;
		while(1)
		{
			clrscr();
			gotoxy(71,1); cout<<"<0> = Exit";
			gotoxy(5,5); cout<<"Enter Code or Name of the Book to be deleted";
			gotoxy(5,6); cout<<"            or           ";
			gotoxy(5,7); cout<<"Press <ENTER> for help ";
			gets(t1code);
			if(t1code[0] == '0')
				return;
			if(strlen(t1code) == 0)
				B.displayList();
			else
				break;
		}
		t2code = atoi(t1code);
		tcode = t2code;

		if( (tcode == 0 && !booknameFound( _strupr(t1code) ) ) 
			|| (tcode != 0 && !bookFound(tcode)) )
		{
			valid = 0;
			gotoxy(5,10);
			cerr<<"\7Record not found";
			gotoxy(5,11);
			cout<<"Press <ESC> to exit or any other key to continue...";
			ch = _getch();
			if(ch == 27)
				return;
		}
	}while(!valid);
	if(tcode == 0)
		tcode = bookcodeOf(t1code);

	clrscr();
	gotoxy(71,1); cout<<"<0> = Exit";
	Book::display(tcode);
	do
	{
		gotoxy(5,13); clreol();
		cout<<"Do you want to delete this record (y/n) : ";
		ch = _getche();
		ch = toupper(ch);
		if(ch == '0')
			return;
	}while(ch!='Y' && ch!='N');
	if(ch == 'N')
		return;
	int tavail, tcopies;
	tavail = available(tcode);
	tcopies = noOfCopiesOf(tcode);
	if(tavail != tcopies)
	{
		gotoxy(5,15);
		cerr<<"\7Record cannot be deleted. This book is issued.";
		_getch();
		return;
	}
	Book::deleteRec(tcode);
	gotoxy(5,23); cout<<"\7Record Deleted";
	_getch();
} //End deleteBook()

// To delete the record of a member
void Working::deleteMember(void)
{
	Member M;
	char m1code[5];
	char ch;
	int m2code = 0, mcode = 0;
	int valid;
	do
	{
		valid = 1;
		while(1)
		{
			clrscr();
			gotoxy(71,1); cout<<"<0> = Exit";
			gotoxy(5,7); cout<<"Enter Code no. of the Member to be deleted";
			gotoxy(5,8); cout<<"                or           ";
			gotoxy(5,9); cout<<"Press <ENTER> for help ";
			gets(m1code);
			m2code = atoi(m1code);
			mcode = m2code;
			if(m1code[0] == '0')
				return;
			if(strlen(m1code) == 0)
				M.displayList();
			else
				break;
		}
		if(mcode == 0)
		{
			valid = 0;
			gotoxy(5,25); cerr<<"\7Enter Correctly";
			_getch();
		}
		if(valid && !memberFound(mcode))
		{
			valid = 0;
			gotoxy(5,13);
			cerr<<"\7Record not found";
			gotoxy(5,14);
			cout<<"Press <ESC> to exit or any other key to continue...";
			ch = _getch();
			if(ch == 27)
				return;
		}
	}while(!valid);

	clrscr();
	gotoxy(71,1); cout<<"<0> = Exit";
	Member::display(mcode);
	do
	{
		gotoxy(5,10); clreol();
		cout<<"Do you want to delete this record (y/n) : ";
		ch = _getche();
		ch = toupper(ch);
		if(ch == '0')
			return;
	}while(ch!='Y' && ch!='N');
	if(ch == 'N')
		return;
	if(issuedFor(mcode))
	{
		gotoxy(5,15);
		cerr<<"\7Record cannot be deleted. Member has a book.";
		_getch();
		return;
	}
	Member::deleteRec(mcode);
	gotoxy(5,23); cout<<"\7Record Deleted";
	_getch();
} //End deleteMember()

//////////////////////////////////////////
//                                      //
//   THE END                            //
//                                      //
//////////////////////////////////////////
