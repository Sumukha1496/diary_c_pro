#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>
#include<alloc.h>
#include<conio.h>
 struct diary
{
    char type;
    char day[15];
    char det[100];
    float amt;

};
     struct node
    {
     struct diary a;
     struct node *next ,*prev;
    };


	void preview();
	struct node * getnode()
	{
	return (struct node *)malloc(sizeof(struct node));
	}


			int getcount(FILE *f)
			{
			 int n=0;
			 f = fopen("My_Diary.txt","r");
			 fseek(f,0,2);
			 n =ftell(f)/sizeof(struct node );
			 fseek(f,0,0);
			 fclose(f);
			 return n;
			}

  struct node *add( struct node *H )
	{
	  struct node *N,*T;
	  char typ;
	  float amnt=0;
	  /*char dat[15],mon[4];*/
	  //int d,m,y;
	  N = getnode();
	  fflush(stdin);
	  printf("Enter details\n");
	  gets(N->a.det);
entertyp:printf("\nEnter the type: [S]PENT or [I]ncome: ");
	  fflush(stdin);
	  scanf("%c",&typ);
	  if((typ=='s')||(typ=='S')||(typ=='I')||(typ=='i'))
	  {
	  fflush(stdin);
	  N->a.type=typ;
	  }
	  else
	  {
	  fflush(stdin);
	  goto entertyp;
	  }
	  fflush(stdin);
	  printf("Enter the amount:\n");
	  scanf("%f",&amnt);
	  N->a.amt=amnt;
	  strcpy(N->a.day,__DATE__);
	 /* strcpy(dat,__DATE__);
	  scanf(dat,"%s %d %d",mon,&d,&y);*/
	  if( H == NULL )
	  {
		H = N;
		H->prev = H;
		H->next = H;
	  }
	   else
	   {
		T = H->prev;  // goto last
		T->next = N;
		N->prev = T;
		N->next = H;
		H->prev = N;
	    }
	  return H;
	}
	///////////add again///////////
	struct node* ad_again(struct node *H,FILE *f,int f2)
	{
	struct node *N,*temp;
		int i;
	struct diary b;

	for(i=0;i<f2;i++)
		{
		N=getnode();
		if(fread(&b , sizeof(b),1,f))
		{
	 if( H == NULL )
	  {
		H = N;
		H->prev = H;
		H->next = H;
		H->a=b;
      }
	   else
	   {
		temp = H->prev;  // goto last
		temp->next = N;
		N->prev = temp;
		N->next  = H;
		H->prev = N;
		N->a=b;
	}
		fseek( f , sizeof(b) , 1);

		}
		else
			break;
		}
	return H;
	}

	//////////////////////////////
	void write(FILE *f,struct node *H)
	{
		struct diary b;
		struct node *T;
		T=H;
		do
		{
			b=T->a;
			fwrite( &b , sizeof(b),1,f);
			fseek( f , sizeof(b) , 1);
			T=T->next;
		}while(T!=H);
	}
	////////////////////////////


	void displayall( struct node *T )
	{
	    struct node *temp;
	    char q;
	    int i=0;
	    temp=T;
	    if(temp==NULL)
	    {
		printf("\nFile is empty: \n<--------------------------------------------->\n");
		getch();
	    }
	    else
	    {
	    i=1;
	     while( 1 )
	      {
		clrscr();
		printf("You have a total of %d record/s stored in your file\n",getnum(T,'a'));
		printf("<-------------------------------------------------->\n\n");
		printf("%-8s","SL.NO.");
		printf(" %-15s","DATE");
		printf("%-25s","DETAILS");
		printf("%-8s","TYPE");
		printf("%-15s","AMOUNT");
		printf("\n%d%-8s",i);
		printf("%-15s",temp->a.day);
		printf("%-25s",temp->a.det);
		if((temp->a.type=='s')|| (temp->a.type=='S'))
		printf("%-8s","SPENT");
		else
		printf("%-8s","INCOME");
		printf("%f%-15s\n",temp->a.amt);
		fflush(stdin);
		sound(800);
		delay(100);
		nosound();
		printf("\n\n\n\t[P]rev  [N]ext   [Q]uit\n");
		q = getch();
		if( q == 'N' || q == 'n' )
		{
			temp = temp->next;
			if(i==getnum(T,'a'))
			i=1;
			else
			i++;
		}
		else if( q == 'P' || q == 'p')
		{
			temp = temp->prev;
			if(i==1)
			i=getnum(T,'a');
			else
			i--;
		}
		else if( q == 'Q' || q == 'q' )
			break;
	    }
	   }
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////


	void displayspent( struct node *T )
	{
	    struct node *temp;
	    char q;
	    int f=0;
	    int i=0;
	    temp=T;
	   if(T==NULL)
	   {
	      printf("\nFile is empty \n<--------------------------------------------------->\n");
	      getch();
	   }
	   else
	   {
	   do
	   {
	      if(temp->a.type=='s')
	      {
	      f=1;
	      break;
	      }
	    temp=temp->next;
	   }while(temp!=T);
	   if(f==0)
	   {
	   printf("\nYou dont have any records of this type \n");
	   delay(1000);
	   goto nospent;
	   }
	   i=1;
	   while( 1 )
	   {
		clrscr();
		printf("\nMONEY SPENT : DETAILS\n");
		printf("\nYou have %d record/s of this type\n",getnum(T,'s'));
		printf("<----------------------------------->\n\n");
		printf("%-8s","SL.NO.");
		printf(" %-15s","DATE");
		printf("%-25s","DETAILS");
		printf("%-8s","TYPE");
		printf("%-15s","AMOUNT");
		printf("\n%d%-8s",i);
		printf("%-15s",temp->a.day);
		printf("%-25s",temp->a.det);
		printf("%-8s","SPENT");
		printf("%f%-15s\n",temp->a.amt);
		fflush(stdin);
		sound(800);
		delay(100);
		nosound();
		fflush(stdin);
		printf("\n\n\n[P]rev  [N]ext   [Q]uit\n");
		q = getch();
		if( q == 'N' || q == 'n' )
		{
			while(1)
			{
			 if(temp->next->a.type=='S' || temp->next->a.type=='s')
			 {
			  temp = temp->next;
			  if(i==getnum(T,'s'))
			  i=1;
			  else
			  i++;
			  break;
			 }
			 else
			 temp=temp->next;
			}
		}
		else if( q == 'P' || q == 'p')
		{
			while(1)
			{
			 if(temp->prev->a.type=='S' || temp->prev->a.type=='s')
			 {
			   temp = temp->prev;
			   if(i==1)
			   i=getnum(T,'s');
			   else
			   i--;
			   break;
			 }
			 else
			 temp=temp->prev;
			}
		}
		else if( q == 'Q' || q == 'q' )
			break;
		}
	   }
	   nospent:
	}


////////////////////////////////////////////////////////////////////////////////////////////////////////


	void displayincome( struct node *T )
	{
	    struct node *temp;
	    char q;
	    int f=0;
	    int i=0;
	    temp=T;
	    if(T==NULL)
	    {
	    printf("\nFile is empty\n<----------------------------------------------------------->\n");
	    getch();
	    }
	    else
	    {
	     do
	   {
	      if(temp->a.type=='i')
	      {
	      f=1;
	      break;
	      }
	     temp=temp->next;
	   }while(temp!=T);
	   if(f==0)
	   {
	     printf("\nYou dont have records of this type\n");
	     delay(1000);
	     goto noincome;
	   }
	    i=1;
	    while( 1 )
	    {
		clrscr();
		printf("\nMONEY INCOME : DETAILS\n");
		printf("\nYou have %d record/s of this type\n",getnum(T,'i'));
		printf("<---------------------------------->\n\n");
		printf("%-8s","SL.NO.");
		printf(" %-15s","DATE");
		printf("%-25s","DETAILS");
		printf("%-8s","TYPE");
		printf("%-15s","AMOUNT");
		printf("\n%d%-8s",i);
		printf("%-15s",temp->a.day);
		printf("%-25s",temp->a.det);
		printf("%-8s","INCOME");
		printf("%f%-15s\n",temp->a.amt);
		fflush(stdin);
		sound(800);
		delay(100);
		nosound();
		printf("\n\n\n[P]rev  [N]ext   [Q]uit\n");
		q = getch();
		if( q == 'N' || q == 'n' )
		{
			while(1)
			{
			 if(temp->next->a.type=='I' || temp->next->a.type=='i')
			 {
			  temp = temp->next;
			  if(i==getnum(T,'i'))
			  i=1;
			  else
			  i++;
			  break;
			 }
			 else
			 temp=temp->next;
			}
		}
		else if( q == 'P' || q == 'p')
		{
			while(1)
			{
			 if(temp->prev->a.type=='I' || temp->prev->a.type=='i')
			 {
			  temp = temp->prev;
			  if(i==1)
			  i=getnum(T,'i');
			  else
			  i--;
			  break;
			 }
			 else
			 temp=temp->prev;
			}
		}
		else if( q == 'Q' || q == 'q' )
			break;
		}
	     }
	     noincome:
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////

	int getnum(struct node *H,char ch)
	{
	  struct node *temp;
	  int count=0;
	  temp=H;
	  if(ch=='a')
	  return ((getnum(H,'s'))+(getnum(H,'i')));
	  else
	  {
	  do
	  {
	    if(ch==temp->a.type)
	    count++;
	    temp=temp->next;
	  }while(temp!=H);
	return count;
	}
	}


///////////////////////////////////////////////////////////////summary//////////////////////////////////////
	void summary(struct node *H)
	{
		struct node *T;
		float totalspent=0,totalincome=0,net=0;
		T=H;
		if(T==NULL)
		{
		printf("\nFile is empty\n<----------------------------------------------------------->\n");
		getch();
		}
		else
		{
		do
		{
			if(T->a.type=='S' || T->a.type=='s')
			{
				totalspent+=T->a.amt;
			}
			else
			{
				totalincome+=T->a.amt;
			}
			T=T->next;
		}while(T!=H);

		printf("\n SUMMARY\n");
		printf("Total amount spent is: %f\t\n",totalspent);
		printf("Total income is: %f\t\n",totalincome);
		printf("----------------------------------------");
		net=totalincome-totalspent;
		if(net>0)
		printf("\nRESULT:::: Your income is equal to : %f \n",net);
		else if(net<0)
		printf("\nRESULT:::: You have spent an amount equal to : %f \n",(-1*net));
		else
		printf("\nRESULT:::: amount spent is Equal to the income = %f\n",totalspent);
		printf("\n<------------------------------------------------------------>");
		T=H;
		getch();
		}
	}

///////////get month number/////////////////////
	int getmonth(char * month)
	{
		int m;
		if(strcmp(month,"Jan")==0)
			m=1;
		if(strcmp(month,"Feb")==0)
			m=2;
		if(strcmp(month,"Mar")==0)
			m=3;
		if(strcmp(month,"Apr")==0)
			m=4;
		if(strcmp(month,"May")==0)
			m=5;
		if(strcmp(month,"Jun")==0)
			m=6;
		if(strcmp(month,"Jul")==0)
			m=7;
		if(strcmp(month,"Aug")==0)
			m=8;
		if(strcmp(month,"Sep")==0)
			m=9;
		if(strcmp(month,"Oct")==0)
			m=10;
		if(strcmp(month,"Nov")==0)
			m=11;
		if(strcmp(month,"Dec")==0)
			m=12;
		return m;
	}

int main()
{
    int m,i,j,num=0;
    struct node *F;
    FILE *fp;
    int ch;
    char n[10],c;
    preview();
    clrscr();
    fp = fopen("My_Diary.txt","r");
    if(fp==NULL)
       {
	 F=NULL;
       }
    else
    {
		F=NULL;
		fclose(fp);
		m=getcount(fp);
		fp = fopen("My_Diary.txt","r");
		F=ad_again(F,fp,m);

    }
	fclose(fp);

	  while(1)
	  {
		clrscr();
		num=getnum(F,'a');
		printf("You have a total of %d records in your file\n",num);
		printf("<------------------------------------------>\n\n");
		printf("1. Add new transaction details\n");
		printf("2. Display all records\n");
		printf("3. Display the details of money spent\n");
		printf("4. Display the details of income\n");
		printf("5. Display Summary\n");
		printf("6. Exit\n");
		scanf("%d", &ch);
		switch( ch )
		{
		case 1:
			F = add( F );
			break;

		case 2:
			for(i=0;i<3;i++)
				{
				clrscr();
				printf("LOADING FILES");
				for(j=0;j<3;j++)
				{
				   printf(".");
				   delay(100);
				}
				}
			displayall(F);
			break;

		case 3:
			for(i=0;i<3;i++)
				{
				clrscr();
				printf("LOADING FILES");
				for(j=0;j<3;j++)
				{
				   printf(".");
				   delay(100);
				}
				}
			displayspent(F);
			break;

		case 4: for(i=0;i<3;i++)
				{
				clrscr();
				printf("LOADING FILES");
				for(j=0;j<3;j++)
				{
				   printf(".");
				   delay(100);
				}
				}
					displayincome(F);
					break;

		case 5:
				summary(F);
				break;


		case 6:  printf("\nAre you sure. You want to save the recent details?\n");
			 printf("[Y]es  [N]0\n");
			 c=getch();
			 if(c=='y'||c=='Y')
			 {
			 fp = fopen("My_diary.txt","w");
			 write(fp,F);
			 fclose(fp);
			 }
			 clrscr();
			 printf("\n\n\n\n\nTHANK YOU FOR USING THIS APPLICATION\n");
			 getch();
			 return 0;
		}
	}
}



		 void preview()
		 {
		   clrscr();
		   printf("\n<--------------WELCOME---------------->\n");
		   getch();
		   fflush(stdin);
		   getch();
		   fflush(stdin);
		   printf("\nPROJECT NAME : MY DIARY \n");
		   getch();
		   fflush(stdin);
		   clrscr();
		   printf("\n\n\n\n\n\n\n");
		   printf("MY DIARY IS AN APPLICATION WHICH ALLOWS YOU TO RECORD YOUR DAILY EXPENSES AND\n HELPS YOU IN MANAGING MONEY IN AN EFFICIENT MANNER\n");
		   getch();
		   fflush(stdin);
		   clrscr();
		   printf("\nNOTE: THE DETILS YOU ARE GOING TO ENTER ARE ONCE WRITABLE. SO PLEASE BE CAREFUL WHILE ENTERING THE DETAILS\n");
		   getch();
		   fflush(stdin);
		   clrscr();
		   printf("\nPRESS ANY KEY TO START USING THE APPLICATION\n");
		   getch();
		 }







