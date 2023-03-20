#include<iostream>
#include<iomanip>
#include<cctype>
#include<fstream>


using namespace std;
    class account
{
	int an;//account number
	int *p=&an;
	char name[30];
	int deposit;
	char type;
public:
    void da();
	void ca();	//create account
	void sa() const;//show account
	void dep(int);	//function to accept amount and add to balance amount
	void as(int);	//amount substract from account
	void report() const;	//report
	int rac() const;	//report account number
	int rd() const;	//report deposite
	char rt() const;	//report type
};
void write_account();
void display_sp(int);

void deposit_withdraw(int, int);
int main()
{
    system("color 3e");
    char ch;
    int num;
    do{
		system("cls");
		    i:
		cout<<"\n\n\t\t---------------------------WELCOME TO KY BANK SYSTEM--------------------------------\n\n";
		cout<<"\t\t\t****************************MAIN MENU****************************";
		cout<<"\n\t\t\t\t| 1. NEW ACCOUNT                              |";
		cout<<"\n\t\t\t\t| 2. DEPOSIT AMOUNT                           |";
		cout<<"\n\t\t\t\t| 3. WITHDRAW AMOUNT                          |";
		cout<<"\n\t\t\t\t| 4. BALANCE ENQUIRY                          |";
		cout<<"\n\t\t\t\t| 5. EXIT                                     |\n";
		cout<<"\n\t\t\t*****************************************************************";
		cout<<"\n\t--------------------------------------------------------------------------------------------------------";
		cout<<"\n\t\t\t-ENTER YOUR CHOICE : ";
   cin>>ch;

		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
		    l:
		        cout<<"\n\t\t\t***********DEPOSIT***************";
			cout<<"\n\n\t\t-ENTER THE ACCOUNT NUMBER : ";
			cin>>num;
			deposit_withdraw(num, 1);
			break;



		case '3':
		    cout<<"\n\t\t\t***********WITHDRAW***************";
			cout<<"\n\n\t\t-ENTER THE ACCOUNT NUMBER : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
		    cout<<"\n\t\t\t***********BALANCE ENQUIRY***************";
			cout<<"\n\n\t\t-ENTER THE ACCOUNT NUMBER : "; cin>>num;
			display_sp(num);
			break;
		 case '5':
			cout<<"\n\n\n\t\t********************THANKS FOR VISITING US**********************";
			break;
		 default :
		   cout<<"\n\n\t\t\t\t--------------INVALID INPUT TRY AGAIN----------------";
		     goto i;
		}
		cin.ignore();
		cin.get();
	}while(ch!='5');
	return 0;

}

void account::ca()
{
    int r;
    r:
        int *p=&an;
    cout<<"\n\t\t*********************WE ARE HAPPY TO SEE YOU***********************"<<endl;
    cout<<"\n\t\t\t\t***CREATE NEW ACCOUNT***\n";
	cout<<"\n\n\t\t\t- ENTER ACCOUNT NUMBER : ";
	cin>>*p;
	cout<<"\n\t\t\t- ENTER YOUR NAME : ";
	cin.ignore();
	cin.get(name,30);
    k:
	cout<<"\n\t\t\t- TYPES OF ACCOURNT(CURRENT(C)/SALARY(S) : ";
	cin>>type;
	if(type=='c'||type=='s' || type=='C'||type=='S'){
	type=toupper(type);
	}
	else{
        cout<<"\t\t\t* INVALID INPUT PLEASE CHOOSE THE LETTER C OR S \n";
        goto k;
	}
	i:
	cout<<"\n\t\t\t- ENTER THE ENITIAL AMOUNT : ";
	cin>>deposit;
	if(deposit<500){

        cout<<"\t\t\t*THE ENITIAL AMOUNT MUST BE >=500\n";
    goto i;
	}
    else{

        cout<<"\n\t\t-----WELCOM "<<name<<" YOUR ACCOUNT IS CREATED SUCCESSFULLY------";
    }

}


void account::sa() const
{
    cout<<"\n\t\t\t*********ACCOUNT INFORMATION********";
	cout<<"\n\t\t-ACCOUNT NUMBER : "<<an;
	cout<<"\n\t\t-NAME : ";
	cout<<name;
	cout<<"\n\t\t-TYPE OF ACCOUNT : "<<type;
	cout<<"\n\t\t-BALANCE AMOUNT : "<<deposit;
	cout<<"\n\t\t------------------------------------------------------";
}

void account::dep(int x)
{
	deposit+=x;
}

void account::as(int x)
{
	deposit-=x;
}

void account::report() const
{
	cout<<*p<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}


int account::rac() const
{
	return an;
}

int account::rd() const
{
	return deposit;
}

char account::rt() const
{
	return type;
}



void write_account()//to add the user info in our database
{
    account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);//we store the data in binary format
	ac.ca();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}
void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\n\t\t*******INVALID NUMBER CREATE ACCOUNT*************";
		return;
	}


    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.rac()==n)
		{
			ac.sa();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\t\t********ACCOUNT NUMBER DOESNT EXIST***********";

}
void deposit_withdraw(int n, int option)
{
	int a;//amount
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"\n\t\t*******INVALID NUMBER CREATE ACCOUNT*************";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.rac()==n)
		{

			ac.sa();
			if(option==1)
			{
			    j:


				cout<<"\n\n\t\tENTER THE AMOUNT TO DEPOSITE : ";
				cin>>a;
				ac.dep(a);
			}
			if(option==2)
			{



				cout<<"\n\n\tENTER THE AMOUNT TO WITHDRAW : ";
				cin>>a;//amount
				int bal=ac.rd()-a;//-amount
				if((bal<500 && ac.rt()=='S') || (bal<500 && ac.rt()=='C'))

                    cout<<"\n\t\t*********YOU CAN'T WITHDRAW THIS AMOUNT, YOU MUST HAVE 500 BIRR AFTER WITHDRAW***********"<<endl<<"\n\n\t\t\t\t\t*****INSUFFICIENT BALANCE*****";

				else
                       ac.as(a);


			}


			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<" ";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n\t***************NO SAME ACCOUNT FOUND PLEASE TRY AGAIN***************";

}




