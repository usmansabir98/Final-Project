#include<windows.h>
#include<stdio.h>
#include <unistd.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>                  //contains strcmp(),strcpy(),strlen(),etc
#include<ctype.h>                   //contains toupper(), tolower(),etc
#include<dos.h>                     //contains _dos_getdate
#include<time.h>					//generate random deal according to the time
#include<math.h>
#include<graphics.h>
struct customer
{
	char name[20];
	char num[15];
	int order[5];
	int qty[5];
}cus2;
struct customer *currCus, *bestCus;

struct menu
{
	char name[30];
	int cp;
	int sp;
}item[16];
int sales[5];                                                //Sales per order
bool placeOrder=0;
int random_st=0,random_mc=3,random_bv=6,random_des=11;
char op1, op2, op3;
bool memberCode=0;

int dishCounter[16];
int finalPrice=(item[random_st].sp+item[random_mc].sp+item[random_bv].sp+item[random_des].sp)*0.9;

void man_dealOTD(int*,int*,int*,int*);     //management function to generate deal of the day
void mainMenu();		//prompts 2 options "user" and "management"
void printMessage(int x);
void userMenu();		//print a list of available options for the user
void managementMenu();	//print a list of available options for the management
void menuCard();		//displays menu card of the restaurant
void dealOfTheDay();    //already saved deal of the day
void userInterface();
void managementInterface();
void loadMenu();
void menuInterface();
void orderReview();
void itemsReview();
void changePrices();
void bill();
void Password();			//prompts password interface for management
void changePassword();
void dateTime();			//To print time and date
void cusName();
void changeOrder();
void membership();
void membershipInterface();
void userInfo();			//appending user data into userinfo.txt
void buyMem();
void loginMem();
int loadUsers();
void printUsers();
int numMatches(int *listA, int sizeA, int *listB, int sizeB);
int getPreferences(char *userName, int *prefs);
void findBestUser(char *currUser, int *prefs);
void drop(int *listA, int sizeA, int *listB, int sizeB, int *listC, int sizeC);
int getRecommendations(char *currUser, int *prefs, int *recs);
void recommendationSystem();
void loadCounter();
void barGraph();

main()
{

	int i=1;
	system("cls");
	//op1=main menu, op2=user menu, op3=management menu;
	mainMenu();
	loadMenu();

	while(i==1)
	{
		printf("\nEnter your choice: ");
		op1=getche();
		switch(op1)    //options for mainmenu
		{
			case '1':
				cusName();
				i=0;
				break;
			case '2':
				Password();
				i=0;
				break;//managementMenu();
			case '0':
				printf("\n\n");
				printMessage(0);
				exit(0);
				i=0;
				break;
			default:
				printf("Invalid choice\n");
				mainMenu();
		}
	}
}


void mainMenu()
{
    printMessage(1);

	printf("\n\nLog in as: \n");
	printf("(1)User \n");
	printf("(2)Manager \n");
	printf("(0)Exit\n");

}

void userMenu()
{
	system("cls");
	printf("Welcome to the User Interface\n\n");
	printf("(1) Place an order\n");
	printf("(2) Deal of the day\n");
	printf("(3) Review your order\n");
	printf("(4) Get Recommendations\n");
	printf("(5) Membership Area\n");
	printf("(6) Generate bill\n");
	printf("(0) Exit\n");
}

void menuCard()
{
	int total;
	system("cls");
	loadMenu();

	printf("Restaurant's Menu\n\n");
	printf("Items\t\t\tPrices\n\n");
	printf("STARTERS\n");
	printf("--------\n");
	printf("(0) %s \tRs. %d\n",item[0].name, item[0].sp);
	printf("(1) %s \t\tRs. %d\n",item[1].name, item[1].sp);
	printf("(2) %s \t\tRs. %d\n\n",item[2].name, item[2].sp);
	printf("MAIN COURSE\n");
	printf("-----------\n");
	printf("(3) %s\tRs. %d\n",item[3].name, item[3].sp);
	printf("(4) %s\t\tRs. %d\n",item[4].name, item[4].sp);
	printf("(5) %s\t\tRs. %d\n\n",item[5].name, item[5].sp);
	printf("BEVERAGES\n");
	printf("---------\n");
	printf("(6) %s\t\tRs. %d\n",item[6].name, item[6].sp);
	printf("(7) %s\t\tRs. %d\n",item[7].name, item[7].sp);
	printf("(8) %s\t\tRs. %d\n\n",item[8].name, item[8].sp);
	printf("DESSERTS\n");
	printf("--------\n");
	printf("(9) %s\t\tRs. %d\n",item[9].name, item[9].sp);
	printf("(10) %s\t\tRs. %d\n",item[10].name, item[10].sp);
	printf("(11) %s\t\tRs. %d\n\n",item[11].name, item[11].sp);
	printf("Deals\n");
	printf("-----\n");
	printf("(12)%s\t\tRs. %d\n",item[12].name, item[12].sp);
	printf("(i)  3 Prawn Soup\n");
	printf("(ii) 2 Chicken Biryani\t\n");
	printf("------------------------\n");
	printf("(13)%s\t\tRs. %d\n",item[13].name, item[13].sp);
	printf("(i) 4 Burger\n");
	printf("(ii)4 Soft Drink\n");
	printf("------------------\n");
	printf("(14)%s\t\tRs. %d\n",item[14].name, item[14].sp);
	printf("(i)  2 Malt Cakes\n");
	printf("(ii) 1 Pizza\n");
	printf("(iii)2 Milk Shake\n");
	printf("-------------------\n");
	total=item[random_st].sp+item[random_mc].sp+item[random_bv].sp+item[random_des].sp;
	finalPrice=total*0.9;
	printf("(15)%s\tRs. %d\n",item[15].name,finalPrice);
	printf("-------------------\n");
}
void dealOfTheDay()                        //Being generated for management only
{
	system("cls");
	int total;
	printf("Deal Of The Day\n");
	printf("(0)%s\t\t\t\t",item[random_st].name);
	printf("%d\n",item[random_st].sp);
	printf("(1)%s\t\t\t\t",item[random_mc].name);
	printf("%d\n",item[random_mc].sp);
	printf("(2)%s\t\t\t\t",item[random_bv].name);
	printf("%d\n",item[random_bv].sp);
	printf("(3)%s\t\t\t\t",item[random_des].name);
	printf("%d\n",item[random_des].sp);
	total=item[random_st].sp+item[random_mc].sp+item[random_bv].sp+item[random_des].sp;
	finalPrice=total*0.9;
	printf("-------------------------------------------\n");
	printf("Total\t\t\t\t\t%d\n",total);
	printf("Deal price\t\t\t\t%d\n",finalPrice);
	printf("\nPress any key to continue...");
	getche();
	userInterface();
}

void man_dealOTD(int *random_st,int *random_mc,int *random_bc,int *random_des)
{
	int deal_OTD[4][3]={0,1,2,3,4,5,6,7,8,9,10,11};  //Item No. on the menu for randomly generating a new deal every time
	srand(time(NULL));
	*random_st=deal_OTD[0][rand()%3];
	*random_mc=deal_OTD[1][rand()%3];
	*random_bc=deal_OTD[2][rand()%3];
	*random_des=deal_OTD[3][rand()%3];
	printf("Your deal has been generated\n");
	printf("Press any key to continue...");
	getche();
	managementInterface();
}

void managementMenu()
{
	system("cls");
	printf("Welcome to management menu->\n\n");
	printf("(1)Generate deal of the day\n");
	printf("(2)Generate sales graph\n");
	printf("(3)Change password\n");
	printf("(4)Review menu\n");
	printf("(5)Print customer's record\n");
	printf("(0)Exit");
}

void userInterface()
{
	int i;
	system("cls");
	userMenu();
		printf("\nEnter your choice: ");
		op2=getche();
		switch(op2)
		{
			case '1':
				menuInterface();
				break;
			case '2':
				dealOfTheDay();
				break;
			case '3':
				orderReview();
				break;
			case '4':
				recommendationSystem();
				break;
			case '5':
				membershipInterface();
				break;
			case '6':
				bill();
				break;
			case '0':
				memberCode=0;
				placeOrder=0;
				main();
				break;
			default: printf("\n\nEnter correct option");
			getche();
			userInterface();

		}
}

void managementInterface()
{
	system("cls");
	managementMenu();
	{
		printf("\nEnter your choice: ");
		op3=getche();                //op3=option for management menu
		switch(op3)
		{
			case '1':
				man_dealOTD(&random_st,&random_mc,&random_bv,&random_des);
				break;
            case '2':
                barGraph();
                managementInterface();
                break;
			case '3':
				changePassword();
				break;
			case '4':
				itemsReview();
				break;
			case '5':
				printUsers();
				break;
			case '0':
				main();
				break;
			default: printf("\n\nEnter correct choice");
			getche();
			managementInterface();
		}
	}

}

void menuInterface()
{
	char k;
	system("cls");
	menuCard();

	char category[5][15]={"starter", "main course", "beverage", "dessert","Deal"};
	for(int i=0;i<5;i++)
	{
		printf("\n\nDo you want to order %s(y/n)?", category[i]);
		k=getche();
		cus2.order[i]=16;
		if(k=='y'|| k=='Y')
		{
			printf("\nEnter %s option from the %s category: ",category[i],category[i]);
			scanf("%d",&cus2.order[i]);
			printf("Enter quantity: ");
			scanf("%d", &cus2.qty[i]);
		}

	}
	placeOrder=1;
	userInterface();
}

void Password() //for password option
{
    char password[10];
    char ch,pass[10];
    int i=0,j;
    FILE *pf;

    pf = fopen("password.txt", "r");
    printf("\nEnter Password:");

    while(ch!=13)
    {
        ch=getche();

        if(ch!=13 && ch!=8){
            printf("\b");
            putch('*');
            pass[i] = ch;
            i++;
        }
    }
    pass[i] = '\0';

    fgets(password, 20, pf);
    if(strcmp(pass,password)==0)
    {
        managementInterface();
    }
    else{
        system("cls");
        printf("Invalid Password\n");
        Password();
        }
}

void changePassword()
{
	FILE *pf;
	pf=fopen("password.txt","r");
	char password[20], pass[20], old[20];
	system("cls");
	fgets(old, 20, pf);
	printf("Enter old password:\n");
	fflush(stdin);
	gets(pass);
	printf("Enter a new password:\n");
	fflush(stdin);
	gets(password);
	fclose(pf);

	pf=fopen("password.txt","w");
	if(strcmp(pass,old)==0)
	{
		fputs(password, pf);
		printf("\nPassword Changed successfully. Your new password is '%s'", password);
		printf("\nPress any key to continue...");
		getche();
	}
	else
	{
		printf("\nYou entered a wrong password.");
		printf("\nPress any key to continue...");
		getche();
		changePassword();
		fclose(pf);
	}
	fclose(pf);
	managementInterface();
}

void dateTime()
{
	time_t timer;
    char buffer[80];
    struct tm *tm_info;

    time(&timer);
    tm_info = localtime(&timer);
	printf("Date:\t\t\t");
    strftime(buffer, 80, "%m-%d-%Y", tm_info);
    puts(buffer);
    printf("Time:\t\t\t");
    strftime(buffer, 80, "%H:%M:%S", tm_info);
    puts(buffer);
	printf("Day:\t\t\t");
	strftime(buffer, 80, "%A", tm_info);
	puts(buffer);
}

void bill()
{
	int i,j,sum=0,g_total,dis=0,k=1;
	system("cls");
	printf("Welcome to Papa Jee\n");
	printf("You deserve a break today...at Papa Jee\n\n");
	printf("Order No:\t\t112\n");
	dateTime();
	printf("Customer Name:\t\t%s\n",cus2.name);
	printf("Phone No:\t\t%s\n",cus2.num);
	printf("\n\nItems\t\t\tQty\tPrice\n");
	printf("-------------------------------------\n\n");
	for(i=0;i<5;i++)
	{
		if(cus2.order[i]==16)
			continue;
		else if(cus2.order[i]==15)
		{
			j=cus2.order[i];
			sales[i]=cus2.qty[i]*finalPrice;
			printf("(%d)%s\t%d\t%d\n",k,item[j].name,cus2.qty[i],sales[i]);
			sum=sum+sales[i];
			k++;
		}
		else
		{
			j=cus2.order[i];
			sales[i]=cus2.qty[i]*item[j].sp;
			printf("(%d)%s\t\t%d\t%d\n",k,item[j].name,cus2.qty[i],sales[i]);
			sum=sum+sales[i];
			k++;
		}
	}
	g_total=sum;
	if(memberCode)
	{
		dis=sum*0.25;
		g_total=sum-dis;
	}
		printf("-------------------------------------\n");
		printf("Total\t\t\t\t%d\n",sum);
		printf("Membership Discount\t\t%d\n",dis);
		printf("Grand Total\t\t\t%d\n",g_total);
		printf("-------------------------------------\n");
		loadCounter();
		printf("\nPress any key to continue...");
		getche();
		userInfo();
		userInterface();

}

void itemsReview()
{
	system("cls");
	FILE *fp;
	fp=fopen("items record.txt", "r");
	printf("Dish Items\tCost\tSelling Price\n\n");
	for(int i=0;i<15;i++)
	{
		fscanf(fp,"%s\t%d\t%d", item[i].name, &item[i].cp, &item[i].sp);
		printf("%d)",i);
		printf("%s \t %d \t %d\n", item[i].name, item[i].cp, item[i].sp);
	}

	fclose(fp);
	changePrices();
}

void changePrices()
{
	int index, newCP, newSP,change_p;
	printf("\nDo you want to change prices(y/n)->");
	change_p=getche();
	printf("\n");
	while(change_p=='y'||change_p=='Y')
	{
		printf("\nEnter item number(0-14)-> ");
		scanf("%d", &index);
		printf("\nEnter new cost price-> ");
		scanf("%d", &newCP);
		printf("\nEnter new selling price-> ");
		scanf("%d", &newSP);

		FILE *fp;
		fp=fopen("items record.txt", "r");

		for(int i=0;i<15;i++)
			fscanf(fp, "%s %d %d", item[i].name, &item[i].cp, &item[i].sp);
		fclose(fp);

		item[index].cp=newCP;
		item[index].sp=newSP;

		fp=fopen("items record.txt", "w");
		for(int i=0;i<15;i++){
			fprintf(fp, "%s \t %d \t %d\n", item[i].name, item[i].cp, item[i].sp);}
		fprintf(fp,"Today's-Special");
		fclose(fp);
		changePrices();
	}
	printf("\nPress any key to continue...");
	getche();
	managementInterface();
}

void loadMenu()
{
	int i;
	FILE *fp;
	fp=fopen("items record.txt","r");
	for(i=0;i<16;i++)
	{
		fscanf(fp,"%s %d %d",item[i].name,&item[i].cp,&item[i].sp);
	}
	fclose(fp);
}

void cusName()
{
	system("cls");
	int flag=1, f;
	printf("Customer's Detail:\n\n");
	while(flag)
	{
		printf("Enter your name: ");
        scanf("%s",cus2.name);
		f=strlen(cus2.name);
		if(f==0)
        {
            printf("\nERROR\n");
            continue;
        }
		for(int i=0;i<f;i++)
		{
			if((cus2.name[i]>='a'||cus2.name[i]>='A') && (cus2.name[i]<='z'||cus2.name[i]<='Z'))
			{
				flag=0;
			}
			else
			{
				printf("\nERROR\n");
				flag=1;
				break;
			}
		}
	}
	flag=1;
	while(flag)
	{
		printf("Enter your phone number:");
        scanf("%s",cus2.num);
		f=strlen(cus2.num);
		if(f==0 || f!=11)
        {
            printf("\nERROR\n");
            continue;
        }
		for(int i=0;i<f;i++)
		{
			if(cus2.num[i]>='0' && cus2.num[i]<='9')
			{
				flag=0;
			}
			else
			{
				printf("\nERROR\n");
				flag=1;
				break;
			}
		}
	}

	userInterface();
}
void orderReview()
{
	system("cls");
	char category[5][15]={"Starter", "Main course", "Beverage", "Dessert","Deal"};
	int i,j,sum=0;
	printf("You have ordered the following items:\n\n");
	printf("Items\t\t\tQty\tPrice\n");
	printf("-------------------------------------\n\n");

	for(i=0;i<5;i++)
	{	if(cus2.order[i]==16 || placeOrder==0)
	{
		printf("%s\n",category[i]);
		printf("-------------------------------------\n");
		printf("(%d)None\t\t\t-\t-\n\n",i);
	}
	else if(cus2.order[i]==15)
	{
		j=cus2.order[i];
		sales[i]=cus2.qty[i]*finalPrice;
		printf("%s\n",category[i]);
		printf("-------------------------------------\n");
		printf("(%d)%s\t%d\t%d\n\n",i,item[j].name,cus2.qty[i],sales[i]);
		sum=sum+sales[i];
	}
	else
	{
		j=cus2.order[i];
		sales[i]=cus2.qty[i]*item[j].sp;
		printf("%s\n",category[i]);
		printf("-------------------------------------\n");
		printf("(%d)%s\t\t%d\t%d\n\n",i,item[j].name,cus2.qty[i],sales[i]);
		sum=sum+sales[i];
	}
	}
	changeOrder();
	printf("\nPress any key to continue...");
	getche();
	userInterface();
}

void changeOrder()
{
	char category[5][15]={"starter", "main course", "beverage", "dessert","Deal"};
	char change_or;
	int index;
	printf("\nDo you want to change your order(y/n):");
	change_or=getche();
	while(change_or=='y'||change_or=='Y')
	{
		printf("\nEnter item number:");
		scanf("%d",&index);
		system("cls");
		menuCard();
		printf("\nEnter %s number:", category[index]);
		scanf("%d",&cus2.order[index]);
		printf("\nEnter quantity:");
		scanf("%d",&cus2.qty[index]);
		printf("\nPress any key to continue...");
		getche();
		system("cls");
		orderReview();
	}
}

void userInfo()
{
	FILE *fp;
	fp=fopen("stored users.txt","a");
	fprintf(fp,"\n");
	fprintf(fp,"%s %s",cus2.name,cus2.num);
	fprintf(fp," %d %d %d %d %d",cus2.order[0], cus2.order[1], cus2.order[2], cus2.order[3], cus2.order[4]);
	fprintf(fp," %d %d %d %d %d",cus2.qty[0], cus2.qty[1], cus2.qty[2], cus2.qty[3], cus2.qty[4]);
	fclose(fp);
}


//**********************************//
//----------------------------------//
//		RECOMMENDATION SYSTEM		//
//----------------------------------//
//**********************************//
void recommendationSystem()
{
	system("cls");
	int prefs[5], recs[5]={16,16,16,16,16};
    int found;
	printf("<--GET RECOMMENDATIONS-->\n\n");
	printf("Did you take a break at Papa Jee before? We keep an eye at your preferences\n");
    found=getPreferences(cus2.num, prefs);	//here prefs is empty array

	getRecommendations(cus2.num, prefs, recs);	//here prefs contain orders of customer "name" and recs is empty

	if(recs[0]==16 || found==0)
	{
		printf("\nSorry! No recommendations for you");
	}

	else
	{

		printf("\nHaving known your taste, we recommend you-> \n");
		for(int i=0; recs[i]!=16;i++)
		{
			printf("%s \n", item[recs[i]].name);
		}
	}
	printf("\nPress any key to continue...");
	getche();
	userInterface();
}

void printUsers()
{

	system("cls");
	int i=0,k, itemNo;
	FILE *fp;
	fp=fopen("stored users.txt", "r");
    struct customer *c1;
	while(!feof(fp))
	{
		c1=(struct customer *)malloc(sizeof(struct customer));
		fscanf(fp, "%s %s ", c1->name, c1->num);
		for(int j=0;j<5;j++)
		{
			fscanf(fp, "%d", &c1->order[j]);
		}
		for(int j=0;j<5;j++)
		{
			fscanf(fp, "%d", &c1->qty[j]);
		}
		itemNo=1;
		printf("Record No. %d\n",i+1);
		printf("-------------");
		printf("\nName=%s\nPhone=%s\nPreferences\tQuantity\n", c1->name, c1->num);
		for(int j=0;j<5;j++)
		{
			k=c1->order[j];
			if(c1->order[j]!=16)
			{
				printf("%d) %s\t%d\n",itemNo,item[k].name, c1->qty[j]);
				itemNo++;
			}
		}
		printf("-------------\n");
		i++;
	}
	fclose(fp);
	printf("Press any key to continue...");
	getche();
	managementInterface();

}

int numMatches(int *listA, int sizeA, int *listB, int sizeB)
{

	/* returns max number of matches between two lists*/
	int count=0;

	for(int i=0;i<sizeA;i++)
	{
		if(*(listA+i)==16)
			continue;
		for(int j=0;j<sizeB;j++)
		{
			if(*(listA+i)==*(listB+j))
				count++;
		}
	}
	return count;
}

int getPreferences(char *userName, int *prefs) //returns 1 if record found and 0 if not
{
	int i,j, found=0;
	FILE *fp;
	fp=fopen("stored users.txt", "r");

	while(!feof(fp))
	{
		currCus=(struct customer *)malloc(sizeof(struct customer));
		fscanf(fp, "%s %s ", currCus->name, currCus->num);
		for(int j=0;j<5;j++)
		{
			fscanf(fp, "%d", &currCus->order[j]);
		}
		for(int j=0;j<5;j++)
		{
			fscanf(fp, "%d", &currCus->qty[j]);
		}
		if(strcmp(userName, currCus->num)==0)
		{
			found=1;
			for(int j=0;j<5;j++)
			{
				*(prefs+j)=currCus->order[j];
			}
			break;
		}
		else
        {
            free(currCus);
        }
	}
	fclose(fp);

    if(found)
    {
        printf("\n%s\nYour preferences--> \n", currCus->name);
        for(j=0;j<5;j++)
        {
            if(*(prefs+j)!=16)
                printf("%s \n", item[*(prefs+j)].name);
        }
    }
	return found;

}
void findBestUser(char *currUser, int *prefs)
{
	int max_matches = 0, curr_matches;
	int i,j;

	struct customer *c3;
	bestCus=(struct customer *)malloc(sizeof(struct customer));
    FILE *fp=fopen("stored users.txt", "r");
    while(!feof(fp))
    {
        c3=(struct customer *)malloc(sizeof(struct customer));
		fscanf(fp, "%s %s ", c3->name, c3->num);
		for(int j=0;j<5;j++)
		{
			fscanf(fp, "%d", &c3->order[j]);
		}
		for(int j=0;j<5;j++)
		{
			fscanf(fp, "%d", &c3->qty[j]);
		}

		curr_matches = numMatches(prefs, 5, c3->order, 5);

		if(curr_matches>max_matches && strcmp(currUser,c3->num)!=0)//so the user does not matches his own record
		{
			for(i=0;i<5;i++)
            {
                bestCus->order[i]=c3->order[i];
            }
			max_matches=curr_matches;

		}
		free(c3);
    }

    fclose(fp);
}

void drop(int *listA, int sizeA, int *listB, int sizeB, int *listC, int sizeC)
{
	int i=0,j=0,k=0;

	for(i=0;i<sizeA;i++)
	{
		for(j=0;j<sizeB;j++)
		{
			if(*(listB+i)==*(listA+j))
				break;
		}
		if(j==sizeB)	//element not found
		{
			*(listC+k)=*(listB+i);
			k++;
		}
	}

}


int getRecommendations(char *currUser, int *prefs, int *recs)
{
	findBestUser(currUser, prefs);
	drop(prefs,5,bestCus->order, 5, recs, 5);
}

//**********************************//
//----------------------------------//
//			MEMBERSHIP AREA			//
//----------------------------------//
//**********************************//

void membershipMenu()
{
	system("cls");
	printf("Membership Menu\n\n");
	printf("(1)Buy membership\n");
	printf("(2)Enter membership key\n");
	printf("(0)Exit\n\n");
}


void membershipInterface()
{
	system("cls");
	membershipMenu();
	char op;
	printf("Enter your choice:");
	op=getche();
	switch(op)
	{
		case '1':
			buyMem();
			break;
		case '2':
			loginMem();
			break;
		case '0':
			userInterface();
			break;
		default:
			printf("\n\nEnter correct choice");
			getche();
			membershipInterface();
	}
}

void buyMem()
{
	system("cls");
	int key;
	FILE *fp;
	fp=fopen("codes.txt","r");
	fseek(fp,-4,SEEK_END);
	fscanf(fp,"%d",&key);
	fclose(fp);
	key=key+1;
	printf("Your membership ID is %d\nThank you for becoming a member at Papa Jee...Enjoy!\n\n",key);
	fp=fopen("codes.txt","a");
	fprintf(fp,"\n");
	fprintf(fp,"%d",key);
	fclose(fp);
	printf("Press any key to continue...");
	getche();
	membershipInterface();
}

void loginMem()
{
	system("cls");
	int codes[100],i=0,key;
	FILE *fp;
	fp=fopen("codes.txt","r");
	while(!feof(fp))
	{
		fscanf(fp,"%d",&codes[i]);
		i++;
	}
	fclose(fp);
	printf("Enter your membership ID:");
	scanf("%d",&key);
	for(i=0;i<100;i++)
	{
		if(key==codes[i])
		{
			printf("Key is valid!\n\n");
			memberCode=1;
			break;
		}
	}
	if(i==100)
	{
		printf("Invalid Key!\n\n");}

	printf("Press any key to continue...");
	getche();
	userInterface();
}

void loadCounter()
{
    FILE *fp;
    int i,dishIndex;
    fp=fopen("counter.txt","r+");
    for(i=0;i<16;i++)
    {
        fscanf(fp,"%d",&dishCounter[i]);
    }
    rewind(fp);

    for(i=0;i<5;i++)
    {
    	dishIndex=cus2.order[i];
    	if(dishIndex!=16)
		{
			dishCounter[dishIndex]+=cus2.qty[i];
		}
	}

	for(i=0;i<16;i++)
    {
        fprintf(fp,"%d\n",dishCounter[i]);
    }
    fclose(fp);
}

void barGraph()
{
    loadCounter();
    int gd=DETECT;
    int gm;
    int x[16],i;

    for(i=0;i<16;i++)
        x[i]=550-dishCounter[i]*0.5;

    initgraph(&gd,&gm,"C:\\TC\\BGI");
    setbkcolor(WHITE);

    line(100,550,950,550); //x axis
    line(100,25,100,550);  //y axis
    line(950,550,940,540); //x axis arrow
    line(950,550,940,560); //x axis arrow
    line(100,25,110,35); //y axis arrow
    line(100,25,90,35); //y axis arrow

    setfillstyle(SOLID_FILL,15);
    bar(110,550,150,x[0]);
    setfillstyle(SOLID_FILL,1);
    bar(160,550,200,x[1]);
    setfillstyle(SOLID_FILL,2);
    bar(210,550,250,x[2]);
    setfillstyle(SOLID_FILL,3);
    bar(260,550,300,x[3]);
    setfillstyle(SOLID_FILL,4);
    bar(310,550,350,x[4]);
    setfillstyle(SOLID_FILL,5);
    bar(360,550,400,x[5]);
    setfillstyle(SOLID_FILL,6);
    bar(410,550,450,x[6]);
    setfillstyle(SOLID_FILL,7);
    bar(460,550,500,x[7]);
    setfillstyle(SOLID_FILL,8);
    bar(510,550,550,x[8]);
    setfillstyle(SOLID_FILL,9);
    bar(560,550,600,x[9]);
    setfillstyle(SOLID_FILL,10);
    bar(610,550,650,x[10]);
    setfillstyle(SOLID_FILL,11);
    bar(660,550,700,x[11]);
    setfillstyle(SOLID_FILL,12);
    bar(710,550,750,x[12]);
    setfillstyle(SOLID_FILL,13);
    bar(760,550,800,x[13]);
    setfillstyle(SOLID_FILL,14);
    bar(810,550,850,x[14]);
    setfillstyle(SOLID_FILL,15);
    bar(860,550,900,x[15]);

    setcolor(BLACK);
    outtextxy(110,560," S1");
    outtextxy(160,560," S2");
    outtextxy(210,560," S3");
    outtextxy(260,560," MC1");
    outtextxy(310,560," MC2");
    outtextxy(360,560," MC3");
    outtextxy(410,560," B1");
    outtextxy(460,560," B2");
    outtextxy(510,560," B3");
    outtextxy(560,560," D1");
    outtextxy(610,560," D2");
    outtextxy(660,560," D3");
    outtextxy(710,560," PJ1");
    outtextxy(760,560," PJ2");
    outtextxy(810,560," PJ3");
    outtextxy(860,560," TS");


    outtextxy(90,550,"0");
    outtextxy(50,500,"100");
    outtextxy(50,450,"200");
    outtextxy(50,400,"300");
    outtextxy(50,350,"400");
    outtextxy(50,300,"500");
    outtextxy(50,250,"600");
    outtextxy(50,200,"700");
    outtextxy(50,150,"800");
    outtextxy(50,100,"900");
    outtextxy(50,50,"1000");

    settextstyle(BOLD_FONT,HORIZ_DIR,2);

    outtextxy(940,580,"X");
    outtextxy(20,25,"Y");
    outtextxy(400,580,"Dishes");

    settextstyle(BOLD_FONT,VERT_DIR,2);
    outtextxy(30,300,"Sales");
    getch();
    closegraph();
}

void printMessage(int x)
{
    int i;
	char str1[] = {"**********WELCOME TO PAPA JEE RESTATURANT**********"};
	char str2[] = "**********THANK YOU FOR VISITING US**********";
    int len;

    if(x==1)    //for welcome
    {
        len = strlen(str1);
        for(i=0;i<len;i++)
        {
            putchar(str1[i]);
            Sleep(50);
        }
    }
    if(x==0)    //for exit
    {
        len = strlen(str2);
        for(i=0;i<len;i++)
        {
            putchar(str2[i]);
            Sleep(50);
        }
    }
}
