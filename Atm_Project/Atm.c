//You can use # as enter while enter money withdraw, money deposit and money transfer
//It can be used in Notepad++.

//Muhammed Said Gülberk
//17050211004

//Atm Module Design

#include "TM4C123GH6PM.h"		//TM4C123GH6PM card adresses 
#include <stdio.h>				//defines three variable types, several macros, and various functions for performing input and output.
#include <stdlib.h>    			//defines four variable types, several macros, and various functions for performing general functions.
#include <string.h>				//defines one variable type, one macro, and various functions for manipulating arrays of characters.
#include <math.h>				//defines various mathematical functions and one macro
#include <stdbool.h>			//defines bool true false

//FUNCTIONS

void Delay(unsigned long counter);			//Delay function
//void Delay1(int sec);						//Delay v2
void initUART(void);						//UART intilization
void UARTTransmitter(unsigned char data);	//To transmit data to Pc
void printstring(char* str);				//To take keys as char from keypad

void keypad_Init(void);						//Keypad initilization
char keypad_takekey(void);					//To use as scanf

void mainMenu(void);						//To print entry menu (just called one time but there was a lot of print function)

void moneyDeposit(void);					//To deposst money to account(1)
void moneyWithdraw(void);					//To take money from account(1)
void menuExit(void);						//To exit from account(4)
void passwordChange(void);					//To change password account
void moneyTransfer(void);					//To transfer money to another account


//GLOBAL VARIABLES

//Amount of Money In Atm
int _5TL = 10;
int _10TL = 10;
int _20TL = 10;
int _50TL = 10;
int _100TL = 10;


//Where our prints placed
char message[100];


//Our Keypad Order                                                               
unsigned const char symbol[4][3] = { {'1', '2', '3'},
								   { '4', '5', '6'},
								   { '7', '8', '9'},
								   { '*', '0', '#'} };


//Where Our account informations linked as struct 
struct accounts {

	int password;
	int ID;
	int balance;

} s[3];


int  k = 0;			//Input while loop
int  y = 0;

bool again2;		//To exit from account

int m;				//Used as account identfier

int main(void)
{
	//Local Declarations
	int option;				//To switch between the cases in the menu
	int select;				//To select between submenu of withdraw/deposit

	char optionn[1]; 		//For card (because we take input as characters we also make char variables then convert it to integers)
	char selectt[1]; 	    //For card  (because we take input as characters we also make char variables then convert it to integers)

	int passwordTry;		//To make user to allow up to 3 try while trying password
	char passwordTryy[4];	//For card  (because we take input as characters we also make char variables then convert it to integers)

	int tries = 3;			//Number of password try
	int i;					//To use at for loops


	initUART();      		//We call UART intialization function
	keypad_Init();			//We call Keypad initiazlition function


	//Account Datas
	s[0].password = 1237;
	s[0].ID = 2345167;
	s[0].balance = 600;

	s[1].password = 1236;
	s[1].ID = 2345168;
	s[1].balance = 700;

	s[2].password = 1235;
	s[2].ID = 2345169;
	s[2].balance = 800;




	while (1) {



		bool passTry = true;	//To try password
		again2 = false;        //To make it usable exit function


		while (passTry) {
			// printf("Please Enter your password:\n");
			// scanf("%d", &passwordTry);

			sprintf(message, "\r\n Please Enter your password:\n");
			printstring(message);

			//Used as similar to scanf by getting input char
			while (k < 4)
			{

				passwordTryy[k] = keypad_takekey(); 			//Just getting one character 
				Delay(1000);
				sprintf(message, "%c", passwordTryy[k]);		//To view what you are writing on screen
				printstring(message);						//To view what you are writing on screen
				k++;										//Increment of character

			}

			k = 0;											//To make it usable again as loop increment
			passwordTry = atol(passwordTryy);				//To convert it to integer

			for (i = 0; i < 3; i++) {						//To loop through accounts

				if (passwordTry == s[i].password) {			//To found which account it is and is password correct


					m = i;										//Because it is a for loop i will change so we save correct account number in m 
					again2 = true;								//To make it possible to enter menu
					passTry = false;							//To make it exitable from current while loop


					tries++;									//If we do not increase it, In the last try even if we enter true password it make our try count zero so we can not go in


				}

			}

			tries--;										//Every turn it decrases the try count

			if (passTry == true) {

				//printf("Please try again. You have %d attempts left!\n", tries);
				sprintf(message, "\r\n Please try again. You have %d attempts left!\n", tries);
				printstring(message);

			}

			if (tries == 0) {

				//printf("Game Over!\n");
				sprintf(message, "\r\n Game Over!\n");
				printstring(message);
				return 0;

			}

		}

		while (again2) {

			mainMenu();																	//Print menu on screen

			//printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			sprintf(message, "\r\n =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			printstring(message);



			//printf("Your Selection:\t");
			//scanf("%d", &option);
			sprintf(message, "\r\n Your Selection:\t");
			printstring(message);

			while (k < 1)											//Menu option selcetion
			{

				optionn[k] = keypad_takekey();
				Delay(1000);
				sprintf(message, "%c", optionn[k]);
				printstring(message);
				k++;

			}

			k = 0;
			option = atol(optionn);


			switch (option) {											//Menu Access

			case 1:												//withdraw/deposit 
			//system("CLS");


				//printf("< 1 >  Withdraw\n");
				//printf("< 2 >  Deposit\n");
				//scanf("%d", &select);
				sprintf(message, "\r\n < 1 >  Withdraw\n");
				printstring(message);

				sprintf(message, "\r\n < 2 >  Deposit\n");
				printstring(message);

				while (k < 1)										//selection for withdraw or deposit
				{

					selectt[k] = keypad_takekey();
					Delay(1000);
					sprintf(message, "%c", selectt[k]);
					printstring(message);
					k++;

				}
				k = 0;
				select = atol(selectt);



				if (select == 1) {

					moneyWithdraw();

				}

				if (select == 2) {

					moneyDeposit();

				}

				break;

			case 2:												//Change pin password
				//system("CLS");
				passwordChange();
				break;

			case 3:												//Money Transfer
				//system("CLS");
				moneyTransfer();
				break;

			case 4:												//Exit
				//system("CLS");
				menuExit();
				break;

			default:
				//errorMessage();
				break;

			}

		}

	}


}





void initUART(void)
{

	SYSCTL->RCGCUART |= 0x20;   // enable clock to UART5 
	SYSCTL->RCGCGPIO |= 0x10;   // enable clock to PORTE for PE4/Rx and RE5/Tx
	Delay(1);				    // gives time to enable clock



	// UART0 initialization

	UART5->CTL = 0;         	// UART5 module disable
	UART5->IBRD = 104;     	// for 9600 baud rate, integer = 104
	UART5->FBRD = 11;       	// for 9600 baud rate, fractional
	UART5->CC = 0;          	//select system clock
	UART5->LCRH = 0x60;     	// data lenght 8-bit, not parity bit, no FIFO
	UART5->CTL = 0x301;     	// Enable UART5 module, Rx and Tx



	// UART5 TX5 and RX5 use PE4 and PE5. Configure them digital and enable alternate

	GPIOE->DEN = 0x30;      	 // set PE4 and PE5 as digital 
	GPIOE->AFSEL = 0x30;   	 // Use PE4,PE5 alternate function
	GPIOE->AMSEL = 0;    	 // Turn off analg function
	GPIOE->PCTL = 0x00110000;  	 // configure PE4 and PE5 for UART

}


void UARTTransmitter(unsigned char data)
{

	while ((UART5->FR & (1 << 5)) != 0); 	 // wait until Tx buffer not full
	UART5->DR = data;  			// before giving it another byte

}


void printstring(char* str)
{

	while (*str)
	{

		UARTTransmitter(*(str++));

	}

}


void Delay(unsigned long counter)
{

	unsigned long i = 0;

	for (i = 0; i < counter * 1000; i++);

}

/*void Delay1(int sec)
{
	int  d=1 ;

	while(d<=3500000 )
	{

		if(GPIOC->DATA == 0x80 && GPIOD->DATA == 0x08){

			sprintf(message,"\r\n You canceled the transaction.\n");
			printstring(message);

			d=3500000;
		}

	d++;

	}

}*/

// Keypad_Init() configures PORTC and PORTE to scan keypad keys
void keypad_Init(void)
{

	SYSCTL->RCGCGPIO |= 0x0C;            //Enable clock to PORTC and PORTD
	while ((SYSCTL->RCGCGPIO & 0x0C) == 0);  //wait for clock to be setted
	GPIOD->LOCK = 0x4C4F434B;
	GPIOC->CR |= 0xE0; 				   //Allow settings for all pins of PORTC            		 
	GPIOD->CR |= 0x0F;                  //Allow settings for all pins of PORTD
	GPIOC->DIR |= 0xE0;                  //PE1-PE4 are used with row and set them as digital
	GPIOD->DIR |= 0x00;
	GPIOD->PDR |= 0x0F;                  //Enable pull down resistor on PORTD
	GPIOC->DEN |= 0xE0;                  //Set PORTC as digital pins
	GPIOD->DEN |= 0x0F; 				   //Set PORTD as digital pins

}

// keypad_getkey() function returns the value of key pressed by the user by traversing columns and rows respectivley
char keypad_takekey(void)
{
	while (1)
	{

		int i = 0;
		int j = 0;

		for (i = 0; i < 3; i++)        						//Scan columns loop                
		{

			GPIOC->DATA = (1 << (i + 5));
			Delay(2);

			for (j = 0; j < 4; j++)                    		//Scan rows loop 
			{

				if ((GPIOD->DATA & 0x0F) & (1 << j))
				{

					return symbol[j][i];

				}

			}

		}

	}
}


void mainMenu(void) {

	//printf("\n******************Hello!*******************\n");
	sprintf(message, "\r\n ******************Hello!*******************\n");
	printstring(message);
	//printf("**********Welcome to ATM Banking***********\n\n");
	sprintf(message, "\r\n **********Welcome to ATM Banking***********\n\n");
	printstring(message);

	//printf("****Please choose one of the options below****\n\n");
	sprintf(message, "\r\n ****Please choose one of the options below****\n\n");
	printstring(message);

	//printf("< 1 >  Withdraw/Deposit\n");
	sprintf(message, "\r\n < 1 >  Withdraw/Deposit\n");
	printstring(message);

	//printf("< 2 >  Change Pin Password\n");
	sprintf(message, "\r\n < 2 >  Change Pin Password\n");
	printstring(message);

	//printf("< 3 >  Money Transfer\n");
	sprintf(message, "\r\n < 3 >  Money Transfer\n");
	printstring(message);

	//printf("< 4 >  Exit\n\n");
	sprintf(message, "\r\n < 4 >  Exit\n\n");
	printstring(message);
}

void moneyDeposit(void) {

	//The Amount Of Money You Want To Deposit
	int d_100TL;
	int d_50TL;
	int d_20TL;
	int d_10TL;
	int d_5TL;

	char d_100TLL[10];
	char d_50TLL[10];
	char d_20TLL[10];
	char d_10TLL[10];
	char d_5TLL[10];

	//To exit from input part by pressing #
	bool enter1 = true;
	bool enter = true;
	bool enter2 = true;
	bool enter3 = true;
	bool enter4 = true;

	//printf("You choose to Deposit a money.\n");
	sprintf(message, "\r\n You choose to Deposit a money.\n");
	printstring(message);



	//printf("$$$$Your Balance is: $%d\n\n", s[m].balance);
	sprintf(message, "\r\n $$$$Your Balance is: $%d\n\n", s[m].balance);
	printstring(message);




	//printf("****Enter your amount to Deposit 100TL.\n");
	//scanf("%d", &d_100TL);
	sprintf(message, "\r\n ****Enter your amount to Deposit 100TL.\n");
	printstring(message);


	while (k < 10 && enter1)
	{

		d_100TLL[k] = keypad_takekey();

		if (d_100TLL[k] == '#') {              //when you press # it exit from input status(like pressing enter in PC)

			enter1 = false;						//To exit from loop

		}

		Delay(1000);
		sprintf(message, "%c", d_100TLL[k]);
		printstring(message);
		k++;

	}
	k = 0;
	d_100TL = atol(d_100TLL);



	s[m].balance += d_100TL * 100;		//It adds money to balance (amount of 100TL * 100)
	_100TL += d_100TL; 				//It adds money to atm (amount of 100TL)

	//printf("****Enter your amount to Deposit 50TL\n");
	//scanf("%d", &d_50TL);
	sprintf(message, "\r\n ****Enter your amount to Deposit 50TL.\n");
	printstring(message);


	while (k < 10 && enter)
	{

		d_50TLL[k] = keypad_takekey();

		if (d_50TLL[k] == '#') {

			enter = false;

		}

		Delay(1000);
		sprintf(message, "%c", d_50TLL[k]);
		printstring(message);
		k++;

	}
	k = 0;
	d_50TL = atol(d_50TLL);




	s[m].balance += d_50TL * 50;
	_50TL += d_50TL;

	//printf("****Enter your amount to Deposit 20TL\n");
	//scanf("%d", &d_20TL);
	sprintf(message, "\r\n ****Enter your amount to Deposit 20TL.\n");
	printstring(message);


	while (k < 10 && enter2)
	{

		d_20TLL[k] = keypad_takekey();

		if (d_20TLL[k] == '#') {

			enter2 = false;

		}

		Delay(1000);
		sprintf(message, "%c", d_20TLL[k]);
		printstring(message);
		k++;

	}
	k = 0;
	d_20TL = atol(d_20TLL);




	s[m].balance += d_20TL * 20;
	_20TL += d_20TL;

	//printf("****Enter your amount to Deposit 10TL\n");
	//scanf("%d", &d_10TL);
	sprintf(message, "\r\n ****Enter your amount to Deposit 10TL.\n");
	printstring(message);


	while (k < 10 && enter3)
	{

		d_10TLL[k] = keypad_takekey();

		if (d_10TLL[k] == '#') {

			enter3 = false;

		}

		Delay(1000);
		sprintf(message, "%c", d_10TLL[k]);
		printstring(message);
		k++;

	}
	k = 0;
	d_10TL = atol(d_10TLL);



	s[m].balance += d_10TL * 10;
	_10TL += d_10TL;

	//printf("****Enter your amount to Deposit 5TL\n");
	//scanf("%d", &d_5TL);
	sprintf(message, "\r\n ****Enter your amount to Deposit 5TL.\n");
	printstring(message);


	while (k < 10 && enter4)
	{

		d_5TLL[k] = keypad_takekey();

		if (d_5TLL[k] == '#') {

			enter4 = false;

		}

		Delay(1000);
		sprintf(message, "%c", d_5TLL[k]);
		printstring(message);
		k++;

	}
	k = 0;
	d_5TL = atol(d_5TLL);




	s[m].balance += d_5TL * 5;
	_5TL += d_5TL;



	//printf("\n****Your New Balance is:   $%d\n\n", s[m].balance);
	sprintf(message, "\r\n ****Your New Balance is:   $%d\n\n", s[m].balance);
	printstring(message);


}

void moneyWithdraw(void) {
	//How much money user will take it
	int withdraw;
	char withdraww[10];

	//To Enter And Exit From While Loops
	bool back = true;
	bool back1 = false;
	bool enter = true;

	while (back) {

		//printf("You choose to Withdraw a money\n");
		//printf("$$$$Your Balance is: $%d\n\n", s[m].balance);
		sprintf(message, "\r\n You choose to Withdraw a money\n");
		printstring(message);

		sprintf(message, "\r\n $$$$Your Balance is: $%d\n\n", s[m].balance);
		printstring(message);

		if (s[m].balance == 0) {

			//printf ("You have no money to withdraw!");
			sprintf(message, "\r\n You have no money to withdraw!");
			printstring(message);

			back = false;
		}

		//printf("Enter your amount to withdraw:\n");
		//scanf("%d", &withdraw);

		enter = true;
		k = 0;
		while (k < 6 && enter)
		{

			withdraww[k] = keypad_takekey();

			if (withdraww[k] == '#') {

				enter = false;

			}

			Delay(1000);
			sprintf(message, "%c", withdraww[k]);
			printstring(message);
			k++;

		}

		k = 0;
		withdraw = atol(withdraww);

		//User Only Enter Number That Is Divisible by 5
		if ((withdraw % 5 != 0)) {

			//printf("Please enter a number that divisible by 5!\n");
			sprintf(message, "\r\n Please enter a number that divisible by 5!\n");
			printstring(message);
			back = true;
			back1 = false;

		}

		else {
			//Exit From This Loop And Enter Next While Loop
			back = false;
			back1 = true;

		}

	}


	while (back1) {
		//
		if ((s[m].balance >= 0) || (withdraw % 5 == 0)) {  	//This is for to be sure that withdraw will not take place in case of there is no balance 
															//in account and user entered input that is visible by 5


			//Atm Will Give 100 then 50 then 20 then 10 then 5	In Order 				
			int x = (withdraw / 100);
			int y = (withdraw / 50);
			int z = (withdraw / 20);
			int a = (withdraw / 10);
			int b = (withdraw / 5);


			while ((_100TL != 0) && (x != 0) && (s[m].balance >= 100) && withdraw >= 100) { //If there is 100Tl banknotes in atm and it can divide by 100
																							//If balance more than 100 and withdraw more than 100
				_100TL -= 1;			//Atm 100TL bonaknote decreases by 1				//Atm will give 100 banknote one at a time
				withdraw -= 100;		//Withdraw decrease 100TL 
				s[m].balance -= 100;	//Balance decrase 100Tl

				x = (withdraw / 100);		//We check if it is still divisible by 100(It allow us to loop right amount of time)

			}


			while ((_50TL != 0) && (y != 0) && (s[m].balance >= 50) && withdraw >= 50) {

				_50TL -= 1;
				withdraw -= 50;
				s[m].balance -= 50;

				y = (withdraw / 50);

			}


			while ((_20TL != 0) && (z != 0) && (s[m].balance >= 20) && withdraw >= 20) {

				_20TL -= 1;
				withdraw -= 20;
				s[m].balance -= 20;

				z = (withdraw / 20);

			}


			while ((_10TL != 0) && (a != 0) && (s[m].balance >= 10) && withdraw >= 10) {

				_10TL -= 1;
				withdraw -= 10;
				s[m].balance -= 10;

				a = (withdraw / 10);

			}


			while ((_5TL != 0) && (b != 0) && (s[m].balance >= 5) && withdraw >= 5) {

				_5TL -= 1;
				withdraw -= 5;
				s[m].balance -= 5;

				b = (withdraw / 5);

			}


			if ((_100TL && _50TL && _20TL && _10TL && _5TL) == 0) {				//If In Atm There is no any banknote it will print error

				//printf("There is no enough money in this atm!");
				sprintf(message, "\r\n There is no enough money in this atm!");
				printstring(message);

			}


			if ((s[m].balance == 0) && (withdraw != 0)) {							//If there is still amount of money left and you dont have 
																					//balance in your account it will print error
				//printf("You have no money left in your account!");
				sprintf(message, "\r\n You have no money left in your account!");
				printstring(message);

			}

		}

		//printf("\n****Your New Balance is:   $%d\n\n", s[m].balance);
		sprintf(message, "\r\n ****Your New Balance is:   $%d\n\n", s[m].balance);	//It will print new balance values in your account
		printstring(message);



		back1 = false;

	}



}

void menuExit() {

	//printf("--------------Take your receipt!!!------------------\n");
	//printf("-----Thank you for using ATM Banking Machine!!!-----\n");

	sprintf(message, "\r\n --------------Take your receipt!!!------------------\n");
	printstring(message);

	sprintf(message, "\r\n -----Thank you for using ATM Banking Machine!!!-----\n");
	printstring(message);

	again2 = false;				//It make it exit from menu loop and it go backs to input password state

}

void passwordChange() {

	int exit = 1;
	int exit2 = 1;

	while (exit2) {

		//Variables for you input as new password	
		char Try11[4];
		int Try1;
		char Try2[4];

		exit = 0;

		//printf("Enter your new password:\n");    
		//scanf("%d", &Try1);
		sprintf(message, "\r\n Enter your new password:\n");
		printstring(message);

		while (y < 4)									//New password input
		{

			Try11[y] = keypad_takekey();
			Delay(1000);
			sprintf(message, "%c", Try11[y]);
			printstring(message);
			y++;

		}
		y = 0;
		Try1 = atol(Try11);

		//Try2[] take value also from Try1[] when i dont zero them(I do not know why it does that. I think it shouldnt behave like that) 
		Try11[0] = 0;
		Try11[1] = 0;
		Try11[2] = 0;
		Try11[3] = 0;


		//printf("Enter your new password again:\n");
		//scanf("%s", &Try2);
		sprintf(message, "\r\n Enter your new password again:\n");
		printstring(message);



		while (k < 4)									//New password input again
		{

			Try2[k] = keypad_takekey();
			Delay(1000);
			sprintf(message, "%c", Try2[k]);
			printstring(message);
			k++;

		}
		k = 0;

		//We dont convert the second input because we use this input to check if it has same number 



		//len = strlen(Try2);


		//if (len != 4) 

		//	printf("Please make your password positive 4 digit number!\n");
		//	exit = 1;

		//



		/*if ( exit == 0 ){

			while (len > 0 && isspace(Try2[len - 1]) ){

				len--;     // strip trailing newline or other white space

			}

			int k;

			for (k = 0; k < len; ++k){

				if (!isdigit(Try2[k])){

					//printf("Please enter digits!\n");
					sprintf(message,"\r\n Please enter digits!\n");
					printstring(message);


					exit = 1;
					break;

				}

			}

		} */




		if (exit == 0) {

			if (Try2[0] == Try2[1] || Try2[0] == Try2[2] || Try2[0] == Try2[3] || Try2[1] == Try2[2] || Try2[1] == Try2[3] || Try2[2] == Try2[3]) {

				//printf("Please dont use same digits in password!\n");
				sprintf(message, "\r\n Please dont use same digits in password!\n");
				printstring(message);

				exit = 1;															//It returns to new password input

			}

		}

		sprintf(message, "\r\n %d\n", Try1);
		printstring(message);

		sprintf(message, "\r\n %s\n", Try2);
		printstring(message);

		if (exit == 0) {

			int Try2Integer = atol(Try2);    									    //After check it and there is no problem we convert it to integer


			if (Try1 == Try2Integer) {												//Checks if two input is same

				s[m].password = Try2Integer;										//It changes the password 


				//printf("\nYour password successfully changed.\n");
				sprintf(message, "\r\n Your password successfully changed.\n");
				printstring(message);



				exit2 = 0;															//It exits from password state and goes back to menu
			}

		}

	}

}


void moneyTransfer() {

	int transferID;
	char transferIDD[7];

	int transferMoney;
	char transferMoneyy[10];

	int k = 0;

	bool tryTransfer = true;
	bool enter = true;

	while (tryTransfer) {


		//printf("\n  Enter the account ID that you want to transfer:\n");
		//scanf("%d",&transferID);
		sprintf(message, "\r\n Enter the account ID that you want to transfer:\n");
		printstring(message);

		k = 0;
		while (k < 7)													//Takes 7 digit ID input
		{

			transferIDD[k] = keypad_takekey();
			Delay(1000);
			sprintf(message, "%c", transferIDD[k]);
			printstring(message);
			k++;

		}
		k = 0;
		transferID = atol(transferIDD);



		if (s[m].ID == transferID) {									 //If entered ID same with current account ID it gives an error

			//printf("\nYou can not transfer money to same account. Please enter another account ID!\n");
			sprintf(message, "\r\n You can not transfer money to same account. Please enter another account ID!\n");
			printstring(message);

		}

		for (k = 0; k <= 2; k++) {  									 									//Loop through account IDs

			int c = 0;

			if (s[k].ID == transferID && s[m].ID != transferID) {

				bool trying = true;


				while (trying) {

					//printf("\nEnter the amount of money that you want to transfer:\n");
					//scanf("%d", &transferMoney);
					sprintf(message, "\r\n Enter the amount of money that you want to transfer:\n");
					printstring(message);



					while (c < 10 && enter)										//Takes amount of money you want to transfer as input
					{

						transferMoneyy[c] = keypad_takekey();

						//	sprintf(message,"%s", transferMoneyy);//debug
						//printstring(message);


						if (transferMoneyy[c] == '#') {

							enter = false;
							transferMoneyy[c] = 0;

						}


						Delay(1000);
						sprintf(message, "%c", transferMoneyy[c]);
						printstring(message);
						c++;

					}
					c = 0;
					transferMoney = atol(transferMoneyy);



					if (transferMoney > s[m].balance) {				//Checks if transfer money you entered is bigger than your balance and if it is it gives an error

						//printf("You do not know that much money in your account. Please enter the money you can transfer!\n\n");
						sprintf(message, "\r\n You do not have that much money in your account. Please enter the money you can transfer!\n\n");
						printstring(message);
					}


					else if (transferMoney <= s[m].balance) {		//If you have enough money it enters to state that transfer the money to other account


						bool canceled = false;
						int d = 0;

						//printf("Transfer will take 30 second to complete.\n");
						//printf("You can cancel the transaction within this time by pressing 1.\n");
						//scanf("%d", &cancel);
						sprintf(message, "\r\n Transfer will take 30 second to complete.\n");
						printstring(message);

						sprintf(message, "\r\n You can cancel the transaction within this time by pressing #.\n");
						printstring(message);

						while (d <= 35000000) 																//Delay 30sec
						{

							if (GPIOC->DATA == 0x80 && GPIOD->DATA == 0x08) {									//If # pressed it will change these datas

								sprintf(message, "\r\n You canceled the transaction.\n");
								printstring(message);

								d = 3500000;																	//When pressed # it exit from delay
								canceled = true;															//To enter cancel if statement
							}

							d++;

						}


						if (canceled == true) {																		//cancel state

							sprintf(message, "\r\n Transfer is canceled\n");
							printstring(message);

							sprintf(message, "\r\n Your money in your account is %d$.\n", s[m].balance);
							printstring(message);

							trying = false;
							tryTransfer = false;

						}



						if (canceled == false) {

							s[m].balance -= transferMoney;															//It reduces money from current account
							s[k].balance += transferMoney;															//It adds money to other account


							//printf("Transfer is successful\n");
							//printf("You transfered %d$.\n", transferMoney);
							//printf("Your money in your account is %d$.\n", s[m].balance);

							sprintf(message, "\r\n Transfer is successful\n");
							printstring(message);

							sprintf(message, "\r\n You transfered %d$.\n", transferMoney);
							printstring(message);

							sprintf(message, "\r\n Your money in your account is %d$.\n", s[m].balance);
							printstring(message);

							trying = false;																	//it exits from current two while loop and goes back to menu
							tryTransfer = false;

						}

					}

				}

			}

		}

	}

}