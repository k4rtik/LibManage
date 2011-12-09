////////////////////////////////////////
//                                    //
// LibManage                          //
// Library Management Sytem           //
//                                    //
// Copyright (c) 2007 Kartik Singhal. //
// kartiksinghal@gmail.com            //
// All rights reserved.               //
//                                    //
////////////////////////////////////////


#define _CRT_SECURE_NO_WARNINGS //to eliminate deprecation warnings


// Included header files
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cctype>
#include <iomanip>
#include "conio2.h"
#include "date.h"

using namespace std;

// To exit the program incase memory error occurs
void exitLM(void)
{
	clrscr();
	gotoxy(28,13);
	cerr<<"Memory error! Exiting...";
	_getch();
	exit(0);
} //End exitLM()

//////////////////////////////////////
//          The Book Class          //
//////////////////////////////////////
class Book                  //76 bytes
{
public:
	void displayList(void);
	char* booknameOf(int);

protected:
	void addNewBook(int, char[], char[], float, int, int);
	void updateCopies(int, int, int);
	void modify(int, char[], char[], float);
	int bookFound(int);
	int booknameFound(char[]);
	int recordnoOf(int);
	int available(int);
	char* authornameOf(int);
	float bookpriceOf(int);
	int noOfCopiesOf(int);
	int bookcodeOf(char[]);
	void display(int);
	int recCount(void);
	void deleteRec(int);

private:
	int bookcode, copies;
	char name[33], author[26];
	float price;
	int avail;
}; //Book class ends


////////////////////////////////////////
//          The Member Class          //
////////////////////////////////////////
class Member                 //108 bytes
{
public:
	void displayList(void);

protected:
	void addMem(int, int, char[], char[], char[], Date);
	void modify(int, char[], char[], char[]);
	int memberFound(int);
	void updateBook(int, int, Date);
	char* membername(int);
	char* memberphone(int);
	char* memberaddress(int);
	int recordnoOf(int);
	int lastcode(void);
	int issuedFor(int);
	int fineFor(int);
	void display(int);
	void deleteRec(int);

private:
	int memcode, bookcode;
	char name[26], phone[10], address[33];
	Date returnDate;
}; //Member class ends


//////////////////////////////////////
//          The Menu Class          //
//////////////////////////////////////
class Menu
{
public:
	void displayMainMenu(void);
	void displayIntroduction(void);

private:
	void displayEditMenu(void);
	void displayEditBookMenu(void);
	void displayEditMemberMenu(void);
}; //Menu class ends


//////////////////////////////////////////
//           The Working Class          //
//////////////////////////////////////////
class Working : public Book, public Member
{
public:
	void issueBook(void);
	void returnBook(void);
	void addBook(void);
	void addMember(void);
	void modifyBook(void);
	void modifyMember(void);
	void deleteBook(void);
	void deleteMember(void);
}; //Working class ends

//////////////////////////////////////////
//                                      //
//   THE END                            //
//                                      //
//////////////////////////////////////////
