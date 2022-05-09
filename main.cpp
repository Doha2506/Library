#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


FILE *file;
int i,j;

struct Data
{
    char name[20];
    int id;
    int  quantity;
}books[50];

int file_size(void) // Done
{
    int size;
    file=fopen("Book.txt","r");
    if(file=='\0')
        printf("Can't open the file");
    else
    {
        fseek( file, 0, SEEK_END );
        size = ftell( file );

        fclose( file );

    }

    return size;
}

void insert_book(Data *arr,int n) // Done
{
    printf("Enter the id : ");
    scanf("%d",&arr[n-1].id);
    printf("Enter the quantity : ");
    scanf("%d",&arr[n-1].quantity);
    printf("Enter the name : ");
    fflush(stdin);
    gets(arr[n-1].name);

    file=fopen("Book.txt","a");
    if(file=='\0')
        printf("Can't open the file");
    else
    {
        fprintf(file,"\n%d\t%d\t%s\n",arr[n-1].id,arr[n-1].quantity,arr[n-1].name);
        fclose(file);
    }
}

void del_book(Data *arr,int n) // Done
{
    int id_no;
    printf("Enter the id you want to delete : ");
    scanf("%d",&id_no);

    for(i=0;i<n;i++)
    {
        if(id_no == arr[i].id)
        {
            file=fopen("Book.txt","w+");
            if(file == '\0')
                printf("Can't open the file");
            else
            {
                j=0;
                while(j<n)
                {
                    if(i!=j)
                    {

                        fprintf(file,"%d %d %s\n",arr[j].id,arr[j].quantity,arr[j].name);
                        printf("%d %d %s\n",arr[j].id,arr[j].quantity,arr[j].name);
                    }
                    j++;
                }
                fclose(file);
            }
        }
    }
}

void search_id(Data *arr,int n,int id,int index) // Done
{
    while(index!=n)
    {

        if(id == arr[index].id)
        {
             printf("Name: %s\nQuantity: %d",arr[index].name,arr[index].quantity);
             return ;
        }

        return search_id(arr,n,id,index+1);

    }
    printf("Not Found .. ");



}

void search_name(Data *arr,int low,int high) // Done
{
    Data temp;
    for(i=0;i<high;i++)  // for loop to sort the array
    {
        for(int j=i+1;j<high;j++)
        {
            if(strcmp(arr[i].name,arr[j].name)>0)
            {
                strcpy(temp.name,arr[i].name);
                strcpy(arr[i].name,arr[j].name);
                strcpy(arr[j].name,temp.name);

                temp.id=arr[i].id;
                arr[i].id=arr[j].id;
                arr[j].id=temp.id;

                temp.quantity=arr[i].quantity;
                arr[i].quantity=arr[j].quantity;
                arr[j].quantity=temp.quantity;
            }
        }
    }
    char name[20];
    printf("Enter the book name you want to search : ");
    scanf("%s",name);

    while(low <= high)  // Loop to search the book
    {
        int middle=(low+high)/2;
        if(strcmp(name,arr[middle].name) == 0)
        {
            printf("\nIts id: %d \nIts Quantity: %d",arr[middle].id,arr[middle].quantity);
            return ;
        }
        else if(strcmp(name,arr[middle].name) < 0)
            high=middle-1;
        else
            low=middle+1;
    }
    printf("Not found .. ");
}

void display_sorted(Data *arr,int n) // Done
{

    Data temp;
    for(i=0;i<n;i++)  // for loop to sort the array
    {
        for(int j=i+1;j<n;j++)
        {
            if(strcmp(arr[i].name,arr[j].name) > 0)
            {
                strcpy(temp.name,arr[i].name);
                strcpy(arr[i].name,arr[j].name);
                strcpy(arr[j].name,temp.name);

                temp.id=arr[i].id;
                arr[i].id=arr[j].id;
                arr[j].id=temp.id;

                temp.quantity=arr[i].quantity;
                arr[i].quantity=arr[j].quantity;
                arr[j].quantity=temp.quantity;


            }

        }
    }
    printf("\nAfter sorting .. ");
    printf("\nName\tId\tQuantity\n");
    for(i=0;i<n;i++)
    {
        printf("\n%s\t%d\t%d\n",arr[i].name,arr[i].id,arr[i].quantity);

    }

}

void display_unsorted(Data *arr,int n) // Done
{
    printf("Name\tId\tQuantity\n");
    for(i=0;i<n;i++)
    {
        printf("%s\t%d\t%d\n",books[i].name,books[i].id,books[i].quantity);
    }
}


int main()
{
    file=fopen("Book.txt","w+");
    if(file=='\0')
        printf("Can't open the file");
    else
    {
        fputs("100\t4\tColors\n",file);
        fputs("200\t6\tAnimals\n",file);
        fputs("300\t3\tFruits\n",file);

        rewind(file);

        for(i=0;i<50;i++)
        {
            fscanf(file,"%d %d %[^\n]",&books[i].id,&books[i].quantity,books[i].name);
        }

        fclose(file);

    }
    for(i=0;i<3;i++)
    {
       printf("%d %d %s\n",books[i].id,books[i].quantity,books[i].name) ;
    }

    int fsize=file_size();
    int arr_size = fsize/14; // Which 14 is the size of one line

    char answer; int menu; int id_no;
    printf("\nThe menu is :\n1 to insert a book\n2 to delete a book\n3 to search a book by id\n4 to search a book by name\n5 to display books sorted\n6 to display books un sorted");

    do
    {
        printf("\nEnter the number of the operation : ");
        scanf("%d",&menu);
        switch(menu)
        {
            case 1:
                insert_book(books,arr_size);
                break;
            case 2:
                del_book(books,arr_size);
                break;
            case 3:
                printf("Enter the id you want to search : ");
                scanf("%d",&id_no);
                search_id(books,arr_size,id_no,0);
                break;
            case 4:
                search_name(books,0,arr_size);
                break;
            case 5:
                display_sorted(books,arr_size);
                break;
            case 6:
                display_unsorted(books,arr_size);
                break;
            default: printf("Unvalid case");

        }
        printf("\nDo you want to perform any additional operation ?? ");
        scanf(" %c",&answer);
    }
    while(answer == 'y');
}









