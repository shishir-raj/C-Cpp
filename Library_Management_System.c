#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

//defining the properties of the fields used in the program


#define IN 1
#define OUT 0

//Declaring various functions used in the code. THEIR DEFINITIONS ARE AT THE END OF THE MAIN FUNCTION TO MAKE CODE LOOK MORE SIMPLIFIED.  
void Addbook();
void Searchbook();
void Displaybook();
void MemberRecords();
void Author();
void Titlelist();
void Stock();
void Issue();
void bookret();
void Addmembr();
void Exit();

char info[500];

//Declaration of a book structure
struct
{
	int bid;
	char bname[25];
	char author[25];
	int nooftitles;
	char titles[500];
	int status;
}book;
//Declaration of a member structure
struct
{
	int mid;
	char mname[25];
	char department[25];
	int availibcard;
	int phno;

}membr;

//initializing the files used in the program

FILE *librecord;
FILE *membrrecord;
FILE *fp1;
FILE *fp2;
FILE *temp1;
FILE *temp2;
void main()
{
	int choice = 0, i;
    char a,b,username[30],password[30];
    //welcome screen
	printf("\n\t\t<<LIBRARY MANAGEMENT SYSTEM>>(Beta version ) \n\n**********WELCOME**********\n");
	do
	{
		printf("\nAre you\n1)Administrator\n2)Member\n3)Non-Member\n\n\n4)Exit\n\nPlease enter your choice<1-4> ");
		//selection of type of user
        scanf(" %c",&a);
		switch (a)
		{
		x:
		case '1':
        //ADMIN LOGIN 
		printf("\nEnter username:  ");
		scanf("%s", &username);
		printf("\nEnter password:  ");
		scanf("%s", &password);
			if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)//TO CHANGE PASSWORD: ENTER NEW PASSWORD WHERE SHOWN STRCMP(PASSWORD,"NEW_PASSWORD_HERE")
			{
				printf("\nWelcome admin \n1)Add a book\n2)Add a member\n3)List Count of Books (Issued & In Stock)\n4)Display member database\n5)Exit\nplease enter your choice<1-5> ");
				scanf(" %c",&b);
				switch (b)
				{
				case '1':
				Addbook();
				break;

				case '2':
				Addmembr();
				break;

				case '3':
				Stock();
				break;

				case '4':
 				MemberRecords();
				break;

				case '5':
				Exit();
				break;

				default:
				printf(" ! Invalid Input...\n");
				}
			}
			else
			{
				printf("\nInvalid credentials...Please try again\n");
				goto x;
			}
			break;
		case '2':
            //MEMBER LOGIN			
			printf("\n1)Search for a book\n2)Search book by author\n3)Display all books available\n4)Book issue request\n5)Return a book\n6)Exit\n\nPlease enter your choice<1-6> ");
            scanf(" %c", &b);
			switch (b)
			{
			case '1':
			Searchbook();
			break;

            case '2':
            Author();
            break;
            
			case '3':
			Displaybook();
			break;

			case '4':
			Issue();
			break;

			case '5':
			bookret();
			break;

			case '6':
			Exit();

			default:
			printf("\nPlease enter a valid input<1-4>(Integer)");


			}
			break;

		case '3':
			//NON MEMBER LOGIN
			printf("\n1)Search for a book\n2)Search book by author\n3)Display all books available\n4)Exit\n\nPlease enter your choice<1-4> ");
			scanf(" %c", &b);
			switch (b)
			{
			case '1':
			Searchbook();
			break;

            case '2':
            Author();
            break;
            
			case '3':
			Displaybook();
			break;

			case '4':
			Exit();

			default:
			printf("Please enter a valid input: Integer<1-3> ");

			}
			break;
		case '4':
			exit(0);
		default:
			printf("ERROR !Please enter a valid input(Integer<1-3>) and Try Again! ");

		}
	getch();
	}while (a>='1' && a<='5'); 
getch();
}



//BELOW ARE THE VARIOUS FUNCTIONS USED IN THE CODE


void Addbook()
{
	int i; book.status = IN;
	//opening the librecord file
	librecord = fopen("librecord.txt", "a+");
	printf("Enter The uniqueid of The Book :(Integer) \n");
	scanf("%d", &book.bid);
	printf("Enter The Name of The Book :\n");
	scanf("%s", book.bname);
	printf("Enter The Name of Author :\n");
	scanf("%s", book.author);
	printf("Enter The Number of Titles Of The Book:(Integer)\n");
	scanf("%d", &book.nooftitles);
	fprintf(librecord, "\n%d\t%s\t%s\t%d\t%d\t", book.bid, book.bname, book.author, book.status, book.nooftitles);
	printf("Enter The Titles Of The Book : \n");
	for (i = 0; i<book.nooftitles; i++)
	{
		scanf("%s", book.titles);
		fprintf(librecord, "%s\t", book.titles);
	}
	fclose(librecord);
	printf(" (' ' ) A New Book has been Added Successfully...\n");

}

void Displaybook()
{
	librecord = fopen("librecord.txt", "a+");
	printf("\nBookid\tName\tAuthor\tStatus\tTitles\n", info);
	do
	{
		fgets(info, 500, librecord);
		printf("%s\n", info);
	} while (!feof(librecord));
	fclose(librecord);	

}

void MemberRecords()
{
    membrrecord = fopen("membrrecord.txt", "a+");
	printf("\nMid\tName\tDept\tPh.no\tAvailablecards\n");
	do
	{
		fgets(info, 500, membrrecord);
		printf("%s\n", info);
	} while (!feof(membrrecord));
	fclose(membrrecord);
}

void Searchbook()
{
	int i;
	char Target[25], stats[4];
	int Found = 0;
	if ((librecord = fopen("librecord.txt", "r")) == NULL)
		printf(" ! The File is Empty...\n\n");
	else
	{
		printf("\nEnter The Name Of Book : ");
		scanf("%s", Target);
		while (!feof(librecord) && Found == 0)
		{
			fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
			if (strcmp(Target, book.bname) == 0)
				Found = 1;
			for (i = 0; i<book.nooftitles; i++)
				fscanf(librecord, "%s", book.titles);
		}
		if (Found)
		{
			if (book.status == IN)
				strcpy(stats, "IN");
			else
				strcpy(stats, "OUT");

			printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\n\n", book.bid, book.bname, book.author, stats);
		}
		else if (!Found)
			printf("! There is no such Entry...\n");
		fclose(librecord);
	}

}

void Author()
{
	int i;
	char Target[500];
	int Found = 0;
	if ((librecord = fopen("librecord.txt", "r")) == NULL)
		printf(" ! The file is empty... \n\n");
	else
	{
		printf("\nEnter The Name Of Author : ");
		scanf("%s", Target);
		printf("\nBooks:");
		while (!feof(librecord))
		{
			fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
			if (strcmp(Target, book.author) == 0)
			{
				Found = 1;
				printf("\n\t%s", book.bname);
			}
			for (i = 0; i<book.nooftitles; i++)
				fscanf(librecord, "%s", book.titles);
		}
		if (!Found)
			printf(" ! There is no such Entry...\n");
		fclose(librecord);
	}

}

//USED TO SEARCH THE BOOK BY TITLE FIELDS
void Titlelist()
{
	int i;
	char Target[500];
	int Found = 0;
	if ((librecord = fopen("librecord.txt", "r")) == NULL)
		printf(" ! The file is empty...\n\n");
	else
	{
		printf("\nEnter The Book TITLE :");
		scanf("%s", Target);
		while (!feof(librecord) && Found == 0)
		{
			fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
			if (strcmp(Target, book.bname) == 0)
			{
				Found = 1;
				break;
			}
			for (i = 0; i<book.nooftitles; i++)
				fscanf(librecord, "%s", book.titles);
		}
		if (Found)
		{
			
			printf("\nThe Titles:\n");
			for (i = 0; i<book.nooftitles; i++)
			{
				fscanf(librecord, "%s", book.titles);
				printf("%d.%s......\n", i + 1, book.titles);
			}
		}
		else if (!Found)
			printf(" ! There is no such Entry...\n");
		fclose(librecord);
	}

}

//DISPLAYS THE COUNT OF BOOKS IN THE LIBRARY(BOTH ISSUED AND NON ISSUED) 
void Stock()
{
	int i, issuecount = 0, stockcount = 0;
	char Issued[100][20];
	int Found = 0;
	if ((librecord = fopen("librecord.txt", "r")) == NULL)
		printf(" ! The file is empty...\n\n");
	else
	{
		while (!feof(librecord))
		{
			fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
			if (book.status == IN)
			{
				stockcount++;
			}
			else
			{
				issuecount++;
			}
			for (i = 0; i<book.nooftitles; i++)
				fscanf(librecord, "%s", book.titles);
		}
		fclose(librecord);
		printf("\nCount of issued Books:%d\nCount of Books in Stock:%d\n", issuecount, stockcount - 1);
	}

}
void Addmembr()
{
	int i;

	membrrecord = fopen("membrrecord.txt", "a+");
	printf("Enter The userid of the Member(Integer) :\n");
	scanf("%d", &membr.mid);
	printf("Enter The Name of the Member :\n");
	scanf("%s", membr.mname);
	printf("Enter The Department\n");
	scanf("%s", membr.department);

	printf("Enter The phone number of the member:\n");
	scanf("%d", &membr.phno);
	membr.availibcard = 5;
	fprintf(membrrecord, "\n%d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
	fclose(membrrecord);
	printf("\n (' ') Added  A New member Successfully...\n");


}

//ISSUE A NEW BOOK
void Issue()
{
	int mid, i, Found1 = 0, Found2 = 0; char issubookname[20];
	//temp1=librecord;temp2=membrrecord;
	printf("\nEnter The userid of the Member : \n");
	scanf("%d", &mid);
	if ((membrrecord = fopen("membrrecord.txt", "r")) == NULL)
		printf(" ! The file is empty...\n\n");
	else
	{
		while (!feof(membrrecord) && Found1 == 0)
		{
			fscanf(membrrecord, "%d %s %s %d %d ", &membr.mid, membr.mname, membr.department, &membr.phno, &membr.availibcard);
			if (mid == membr.mid)
			{
				Found1 = 1;
			}
		}
		if (Found1)
		{
			if (membr.availibcard<1)
			{
				printf(" ! Library card not available...\n");
			}
			else
			{
				printf("\nEnter The Name of book :");
				scanf("%s", issubookname);
				if ((librecord = fopen("librecord.txt", "r")) == NULL)
					printf(" ! The file is empty...\n\n");
				else
				{
					while (!feof(librecord) && Found2 == 0)
					{
						fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
						if (strcmp(issubookname, book.bname) == 0)
							Found2 = 1;
						for (i = 0; i<book.nooftitles; i++)
							fscanf(librecord, "%s", book.titles);
					}
					if (Found2)
					{
						if (book.status == 0)
						{
							printf(" ! Book already issued...\n");
						}
						else
						{

							fp2 = fopen("fp2.txt", "w");
							if ((temp2 = fopen("membrrecord.txt", "r")) == NULL)
								printf(" ! The file is empty...\n\n");
							else
							{
								while (!feof(temp2))
								{
									fscanf(temp2, "%d %s %s %d %d ", &membr.mid, membr.mname, membr.department, &membr.phno, &membr.availibcard);


									if (mid == membr.mid)
									{
										membr.availibcard--;
										fprintf(fp2, "\n %d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
									}
									else{
										fprintf(fp2, "\n %d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
									}
									if (feof(temp2))
										break;
								}
							}
							fclose(temp2);
							fclose(fp2);


							fp1 = fopen("fp1.txt", "w");
							if ((temp1 = fopen("librecord.txt", "r")) == NULL)
								printf(" ! The file is empty...\n\n");
							else
							{
								while (!feof(temp1))
								{
									fscanf(temp1, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
									if (feof(temp1))
										break;
									if (strcmp(issubookname, book.bname) != 0)
									{
										fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d    \t", book.bid, book.bname, book.author, book.status, book.nooftitles);
									}
									else
									{
										fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", book.bid, book.bname, book.author, 0, book.nooftitles);
									}
									for (i = 0; i<book.nooftitles; i++)
									{
										fscanf(temp1, "%s", book.titles);
										fprintf(fp1, "%s\t", book.titles);
									}
								}
							}
							fclose(temp1);
							fclose(fp1);
							fclose(librecord);
							fclose(membrrecord);
							remove("librecord.txt");
							rename("fp1.txt", "librecord.txt");
							remove("membrrecord.txt");
							rename("fp2.txt", "membrrecord.txt");
							printf(" (' ') Book Successfully issued...\n");
						}
					}
					else if (!Found2)
						printf(" ! There is no such Book...\n");

				}
			}
		}
		else if (!Found1)
			printf(" ! Invalid User id...\n");


	}

}

//RETURN THE ISSUED BOOK
void bookret()
{
	int mid, i, Found1 = 0, Found2 = 0, flag = 0; char retbookname[20];
	temp1 = librecord; temp2 = membrrecord;
	printf("\nEnter The userid of the Member :\n");
	scanf("%d", &mid);
	if ((membrrecord = fopen("membrrecord.txt", "r")) == NULL)
		printf(" ! The file is empty...\n\n");
	else
	{
		while (!feof(membrrecord) && Found1 == 0)
		{
			fscanf(membrrecord, "%d %s %s %d %d ", &membr.mid, membr.mname, membr.department, &membr.phno, &membr.availibcard);
			if (mid == membr.mid)
			{
				Found1 = 1;
			}
		}
		if (Found1)
		{
			if (membr.availibcard >= 5)
			{
				printf(" ! Error...\n");
			}
			else
			{
				printf("\nEnter The Name of book :");
				scanf("%s", retbookname);
				if ((librecord = fopen("librecord.txt", "r")) == NULL)
					printf(" ! The file is empty\n\n");
				else
				{
					while (!feof(librecord) && Found2 == 0)
					{
						fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
						if (strcmp(retbookname, book.bname) == 0)
							Found2 = 1;
						for (i = 0; i<book.nooftitles; i++)
							fscanf(librecord, "%s", book.titles);
					}
					if (Found2)
					{
						if (book.status == 1)
						{
							printf(" ! Error:Book already in stock...\n");
						}
						else
						{

							fp2 = fopen("fp2.txt", "w");
							if ((temp2 = fopen("membrrecord.txt", "a+")) == NULL)
								printf(" ! The file is empty...\n\n");
							else
							{
								while (!feof(temp2))
								{
									fscanf(temp2, "%d %s %s %d %d ", &membr.mid, membr.mname, membr.department, &membr.phno, &membr.availibcard);


									if (mid == membr.mid)
									{
										membr.availibcard++;
										fprintf(fp2, "\n %d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
									}
									else
									{
										fprintf(fp2, "\n %d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
									}
									if (feof(temp2))
										break;
								}
							}
							fclose(temp2);
							fclose(fp2);


							fp1 = fopen("fp1.txt", "w");
							if ((temp1 = fopen("librecord.txt", "r")) == NULL)
								printf(" ! The file is empty...\n\n");
							else
							{
								while (!feof(temp1))
								{
									fscanf(temp1, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
									if (feof(temp1))
										break;
									if (strcmp(retbookname, book.bname) != 0)
									{
										fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d    \t", book.bid, book.bname, book.author, book.status, book.nooftitles);
									}
									else
									{
										fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", book.bid, book.bname, book.author, 1, book.nooftitles);
									}
									for (i = 0; i<book.nooftitles; i++)
									{
										fscanf(temp1, "%s", book.titles);
										fprintf(fp1, "%s\t", book.titles);
									}
								}
							}
							fclose(temp1);
							fclose(fp1);
							fclose(librecord);
							fclose(membrrecord);
							printf("('') Book Successfully Returned...\n");
							remove("librecord.txt");
							rename("fp1.txt", "librecord.txt");
							remove("membrrecord.txt");
							rename("fp2.txt", "membrrecord.txt");

						}
					}
					else if (!Found2)
						printf("! There is no such Book...\n");

				}
			}
		}
		else if (!Found1)
			printf("! Invalid User id...\n");


	}

}
void Exit()
{
	exit(0);
}
