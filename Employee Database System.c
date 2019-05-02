#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <windows.h> ///for sleep()
#include <string.h>  ///string operations

/* Global Variables */

/*Employee Structure*/

struct emp
    {
        int id;
		char name[20];
		char designation[20]; 
        short int age; 
        char address[20];
        float bs; 
    }e;

FILE *fp, *ft; /// file pointers
COORD coord = {0,0}; /// top-left corner of window
unsigned int recsize=sizeof(e); /// size of each record of employee
char another; //repeat call

/* Moves cursor to specific location*/

void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void createBinaryFile()
{
	/** open the file in binary read and write mode
    * if the file EMP.DAT already exists then it open that file in read write mode
    * if the file doesn't exit it simply create a new copy
    */
    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }

}

/*Login Function*/

void login()
{
	int a=0,i=0;
    char uname[10],c=' '; 
    char pword[10],code[10];
    char user[10]="user";
    char pass[10]="pass";
    do
{
	system("CLS");
    printf("\n  ---------------------------  LOGIN FORM  ---------------------------  ");
    printf("\n\n                          ENTER USERNAME:");
	scanf("%s", &uname); 
	printf("\n                          ENTER PASSWORD:");
	while(i<10)
	{
	    pword[i]=getch();
	    c=pword[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	pword[i]='\0';
	
	i=0;

	
	if(!strcmp(uname,"user") && !strcmp(pword,"pass"))
	{
		
	printf("  \n\n\n       WELCOME TO EMPLOYEE DATABASE SYSTEM !!!! LOGIN IS SUCCESSFUL");
	printf("\n LOADING PLEASE WAIT...");
    for(i=0; i<5; i++)
    {
        printf(".");
        Sleep(500);
    }
    
	printf("\n\n\n\t\t\tPress any key to continue...");
	getch();//holds the screen
	break;
	}
	
	else
	{
		printf("\n\n\t\t\tSORRY! LOGIN IS UNSUCESSFUL\n\t\t\t        TRY AGAIN");
		a++;
		getch();//holds the screen
		
	}
}while(a<=2);

	if (a>2)
	{
		printf("\n\nSorry you have entered the wrong information for three times in a row!");
		getch();
		exit(0);
    }
}

char frontDisplay()
{
	system("cls"); ///clear the console window 
        
        printf(" \n  ::::::::::::::::::::::::::  |EMPLOYEES DATABASE SYSTEM|  :::::::::::::::::::::::::: \n");
        gotoxy(30,05); /// move the cursor to postion 30, 10 from top-left corner
		printf("1> Add Employee Records"); 
        gotoxy(30,07);
        printf("2> Display Employee Records"); 
        gotoxy(30,9);
        printf("3> Modify Employee Records"); 
        gotoxy(30,11);
        printf("4> Delete Employee Records"); 
        gotoxy(30,13);
        printf("5> Exit System"); /// exit from the program
        gotoxy(30,15);
        printf("Your Choice: "); /// enter the choice 1, 2, 3, 4, 5
        fflush(stdin); /// flush the input buffer
        char choice  = getche(); /// get the input from keyboard
        return choice;    
}

void addEmpRecord()
{
            fseek(fp,0,SEEK_END); /// search the file and move cursor to end of the file
            /// here 0 indicates moving 0 distance from the end of the file

            char another = 'y';
            while(another == 'y')  /// if user want to add another record
            {
                system("cls");
				gotoxy(30,03);
				printf("Enter Employee ID:");
                scanf("%d",&e.id);
				gotoxy(30,05);
				printf("Enter Name:");
                scanf("%s",e.name);
                gotoxy(30,07);
                printf("Enter Designation:");
                scanf("%s", &e.designation);
                gotoxy(30,9);
                printf("Enter Age:");
                scanf("%d", &e.age);
                gotoxy(30,11);
                printf("Enter Address:");
                scanf("%s",e.address);
                gotoxy(30,13);
                printf("Enter Basic Salary:");
                scanf("%f", &e.bs);

                fwrite(&e,recsize,1,fp); /// write the record in the file

                printf("\n\nAdd Another Record(y/n):");
                fflush(stdin);
                another = getche();
            }
}

void displayEmpRecord()
{
  system("cls");
  int i=3,j; 
            printf("EMPLOYEE RECORD LIST\n");
            gotoxy(0,2); printf("ID");
            gotoxy(10,2); printf("Name");
            gotoxy(30,2); printf("Designation");
            gotoxy(50,2); printf("Age");
            gotoxy(60,2); printf("Address");
            gotoxy(80,2); printf("Salary");
            gotoxy(0,3);
            for(j=0;j<90;j++)
                printf("_");
            rewind(fp); ///this moves file cursor to start of the file
            while(fread(&e,recsize,1,fp)==1)  /// read the file and fetch the record one record per fetch
            {	
              gotoxy(0,i+2); printf("%d",e.id);
              gotoxy(10,i+2); printf("%s",e.name);
              gotoxy(30,i+2); printf("%s",e.designation);
              gotoxy(50,i+2); printf("%d",e.age);
              gotoxy(60,i+2); printf("%s",e.address);
              gotoxy(80,i+2); printf("%.2f",e.bs);
              i++;
            }
            getch(); 	
}

void modifyEmpRecord()
{
	system("cls");
	int empid,flag=0; 
            another = 'y';
            while(another == 'y')
            {
                system("cls");
				printf("\nEnter Employee Id to be Modified:");
                scanf("%d",&empid);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1)  /// fetch all record from file
                {
                    if(empid==e.id)  ///if entered id matches with that in file
                    {
                        printf("\nMatch Found");
                        flag=1;
   					gotoxy(30,05);
					printf("Enter Name:");
                	scanf("%s",e.name);
                	gotoxy(30,07);
                	printf("Enter Designation:");
                	scanf("%s", &e.designation);
                	gotoxy(30,9);
                	printf("Enter Age:");
                	scanf("%d", &e.age);
                	gotoxy(30,11);
                	printf("Enter Address:");
                	scanf("%s",e.address);
                	gotoxy(30,13);
                	printf("Enter Basic Salary:");
                	scanf("%f", &e.bs);
                        fseek(fp,-recsize,SEEK_CUR); /// move the cursor 1 step back from current position
                        fwrite(&e,recsize,1,fp); /// override the record
                        break;
                    }
                }
                if(!flag)
                    printf("\nRecord Not Found");
                printf("\nModify Another Record?(y/n):");
                fflush(stdin);
                another = getche();
            }
}

void deleteEmpRecord()
{
	  system("cls");
	  int empid,flag=0;; 
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter Employee ID to be deleted:");
                scanf("%d",&empid);
                ft = fopen("Temp.dat","wb");  /// create a intermediate file for temporary storage
                rewind(fp); /// move record to starting of file
                while(fread(&e,recsize,1,fp) == 1)  /// read all records from file
                {
                    if(e.id!=empid)  /// if the entered record match
                        fwrite(&e,recsize,1,ft); /// move all records except the one that is to be deleted to temp file
                    else
                       {
						 flag=1;
						 printf("Deleted Record: %s",e.name);
					   }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT"); /// remove the orginal file
                rename("Temp.dat","EMP.DAT"); /// rename the temp file to original file name
                fp = fopen("EMP.DAT", "rb+");
                if(!flag)
                printf("\nRecord not found");
                printf("\nDelete Another Record(y/n):");
                fflush(stdin);
                another = getche();
            }
}

int main()
{
	int i=0;
	login();
    char choice;

    createBinaryFile();
   
    while(1)
    {
        switch(frontDisplay())
        {
        case '1':  addEmpRecord(); 
                   break;
                   
        case '2':  displayEmpRecord(); 
                   break;

        case '3':  modifyEmpRecord();
                   break;
                   
        case '4':  deleteEmpRecord(); 
                   break;
                   
        case '5':
            fclose(fp);  /// close the file
            exit(0); /// exit from the program
        }
    }
    return 0;
}
