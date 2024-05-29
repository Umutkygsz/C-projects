#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showallrecords();
void searchpatient();
void newpatient();
void deleterecord();
void updaterecord();
void searchbyid();
void searchbyname();
void searchbysurname();
void writefile();
void readfile();

struct patient
{
    char name[20];
    char surname[20];
    char birthday[15];
    char mail[40];
    char department[20];

}p[100];

int numberofpatients;


void readfile()
{
    FILE *patientfile;
    patientfile=fopen("patientrecords.txt","r");
    if(patientfile==NULL)
    {
        patientfile=fopen("patientrecords.txt","w");
        fclose(patientfile);
    }

    numberofpatients=fread(p,sizeof(struct patient),100,patientfile);
    fclose(patientfile);
}

void writefile()
{
    FILE *patientfile;

    patientfile=fopen("patientrecords.txt","w");

    fwrite(p,sizeof(struct patient),numberofpatients,patientfile);

    fclose(patientfile);

}

int main()
{
    readfile();
    int optionnumber;

    printf("--- Welcome to the Hospital Management System ---\n");
    printf("-------------------------------------------------\n\n");

    do{
        printf("\n\n0: Exit | 1: Show All Records | 2: Search Patient | 3: New Patient");
        printf("\nPlease select an option: ");
        scanf("%d",&optionnumber);

        switch(optionnumber)
        {
            case 1:
                showallrecords();
                break;
            case 2:
                searchpatient();
                break;
            case 3:
                newpatient();
                break;
            case 0:
                writefile();
                printf("\n---------------------------------------------------");
                break;
            default:
                printf("\n\nInvalid selection! Please Try Again.\n\n\n");
        }

    }while(optionnumber != 0);
}

void showallrecords()
{
    int i,suboption;

	printf("\n\nPATIENT RECORDS:\n\n");

	for(i=0;i<numberofpatients;i++)
    {
        printf("\n\n%d\t%-10s\t%-15s\t%-15s\t%-20s\t%-15s\n\n", i+1, p[i].name, p[i].surname, p[i].birthday, p[i].mail, p[i].department);
	}

	do
    {
        printf("\n\n0: Return the Main Menu | 1: Delete Record | 2: Update Record\n");
        printf("Please select an option: ");
        scanf("%d",&suboption);

        switch(suboption)
        {
            case 1:
                deleterecord();
                break;
            case 2:
                updaterecord();
                break;
            case 0:
                break;
            default:
                printf("\n\nInvalid selection! Please Try Again.\n\n\n");
        }

    }while(suboption != 0);

}

void deleterecord()
{

    int deleteidin,deleteid;

    printf("\nPatient ID: ");
    scanf("%d",&deleteidin);

    deleteid=deleteidin-1;

    if(deleteid<numberofpatients)
    {
        while(deleteid<numberofpatients)
        {
            strcpy( p[deleteid].name , p[deleteid+1].name );
            strcpy( p[deleteid].surname , p[deleteid+1].surname);
            strcpy( p[deleteid].birthday , p[deleteid+1].birthday);
            strcpy( p[deleteid].mail , p[deleteid+1].mail);
            strcpy( p[deleteid].department , p[deleteid+1].department);
            deleteid++;
        }

        numberofpatients--;

        printf("\n\nPatient record is deleted...\n\n");

    }
    else
    {
        printf("Patient not found!");
    }

}

void updaterecord()
{
    int updateid;

    printf("\nPatient Id: ");
    scanf("%d",&updateid);

    if(updateid<=numberofpatients && updateid>0)
    {
        fflush(stdin);
        printf("\n\nEnter Name (Old: %s): ", p[updateid-1].name);
        gets(p[updateid-1].name);
        fflush(stdin);
        printf("\nEnter Surname (Old: %s): ", p[updateid-1].surname);
        gets(p[updateid-1].surname);
        fflush(stdin);
        printf("\nEnter Birthday  (Old: %s): ", p[updateid-1].birthday);
        gets(p[updateid-1].birthday);
        fflush(stdin);
        printf("\nEnter E-Mail (Old: %s): ", p[updateid-1].mail);
        gets(p[updateid-1].mail);
        fflush(stdin);
        printf("\nEnter Department (Old: %s): ", p[updateid-1].department);
        gets(p[updateid-1].department);
        printf("\n\nPatient record is updated...\n\n");
    }
    else
    {
        printf("\n\nPatient not found!\n\n");
    }
}

void searchpatient()
{
    int suboption;

    do
    {
        printf("\n\n0: Return the Main Menu | 1: Search By Id | 2: Search By Name | 3: Search By Surname\n");
        printf("Please select an option: ");
        scanf("%d",&suboption);

        switch(suboption)
        {
            case 1:
                searchbyid();
                break;
            case 2:
                searchbyname();
                break;
            case 3:
                searchbysurname();
                break;
            case 0:
                break;
            default:
                printf("\n\nInvalid selection! Please Try Again.\n\n");
        }

    }while(suboption != 0);

}

void searchbyid()
{

	int searchid,i,checkfound=0;

	printf("Patient Id: ");
	scanf("%d",&searchid);

	printf("\n\nSearching...\n\n");

    if(searchid<=numberofpatients && searchid>0)
    {
        printf("%d\t%-10s\t%-15s\t%-15s\t%-20s\t%-15s\n",searchid,p[searchid-1].name,p[searchid-1].surname,p[searchid-1].birthday,p[searchid-1].mail,p[searchid-1].department);
        checkfound++;
    }


    printf("\nSearch completed. %d patient(s) are found...\n\n",checkfound);

}

void searchbyname()
{
    int i;
	char searchname[20],checkfound=0;

	printf("Patient Name: ");
	fflush(stdin);
	gets(searchname);
	fflush(stdin);

	printf("\n\nSearching...\n\n");

    for(i=0;i<numberofpatients;i++)
    {
        if(strcmp( p[i].name , searchname) == 0)
        {
            printf("%d\t%-10s\t%-15s\t%-15s\t%-20s\t%-15s\n\n",i+1,p[i].name,p[i].surname,p[i].birthday,p[i].mail,p[i].department);
            checkfound++;
        }
    }

    printf("\nSearch completed. %d patient(s) are found...\n\n",checkfound);

}

void searchbysurname()
{
    int i;
	char searchsurname[20],checkfound=0;

	printf("Patient Surname: ");
	fflush(stdin);
	gets(searchsurname);
	fflush(stdin);

	printf("\n\nSearching...\n\n");


    for(i=0;i<numberofpatients;i++)
    {
        if(strcmp( p[i].surname , searchsurname) == 0)
        {
            printf("%d\t%-10s\t%-15s\t%-15s\t%-20s\t%-15s\n",i+1,p[i].name,p[i].surname,p[i].birthday,p[i].mail,p[i].department);
            checkfound++;
        }
    }

    printf("\n\nSearch completed. %d patient(s) are found...\n\n",checkfound);

}


void newpatient()
{
    fflush(stdin);
    printf("\nEnter Name: ");
    gets(p[numberofpatients].name);
    fflush(stdin);
    printf("\nEnter Surname: ");
    gets(p[numberofpatients].surname);
    fflush(stdin);
    printf("\nEnter Birthday (dd/mm/yyyy): ");
    gets(p[numberofpatients].birthday);
    fflush(stdin);
    printf("\nEnter E-Mail: ");
    gets(p[numberofpatients].mail);
    fflush(stdin);
    printf("\nEnter Department: ");
    gets(p[numberofpatients].department);
    fflush(stdin);

    numberofpatients++;

    printf("\nNew patient has been recorded...\n");

}



