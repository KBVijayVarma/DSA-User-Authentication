#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining a struct node which calls itself(Linked List)
typedef struct node
{
  char *usn;
  char *pd;
  struct node *next;
}node;

// Defining a Universal Hash Table containing 4000 nodes(Linked Lists)
node* table[4000];

// Function to return Hash Value of a given string
int hash_func(char *str)
{
  int sum = 0;
  for(int i=0;i<strlen(str);i++)
  {
    sum += str[i];
  }
  return sum;
}

// Function which inserts the given key and val into the Hash Table
void insert(char *key,char *val)
{
  int ind = hash_func(key);
  
  node* n = malloc(sizeof(node));
  n->usn = key;
  n->pd = val;
  n->next = NULL;
  if(table[ind] == NULL)
  {
    table[ind] = n;
  }
  else
  {
    node* tmp = table[ind];
    while(tmp->next)
    {
      tmp = tmp->next;
    }
    tmp->next = n;
  }
}

// Function which searches if given Username key is in the Hash Table
int usn_search(char* key)
{
  int ind = hash_func(key);
  node* tmp = table[ind];
  if(tmp == NULL)
  {
    return 0;
  }
  do
  {
    if(!strcmp(tmp->usn,key))
    {
      return 1;
    }
    tmp = tmp->next;
  }
  while(tmp->next != NULL);
  return 0; 
}

// Function which checks if the given password(val) is valid for given username(key)
int search(char* key, char* val)
{
  int ind = hash_func(key);
  node* tmp = table[ind];
  do
  {
    if(!strcmp(tmp->pd,val)) return 1;
    tmp = tmp->next;
  }
  while(tmp->next != NULL);
  return 0;
}

int main()
{
    // Declaring name and pswd char arrays
    char *name[20000];
    char *pswd[20000];
    
    for(int p = 0;p<20000;p++)
    {
      name[p] = (char*)calloc(100,sizeof(char));
      pswd[p] = (char*)calloc(100,sizeof(char));
    }

    // Opening the file

    FILE *fp = fopen("userInfo.csv","r");

    char* line;
    line = (char*)calloc(100,sizeof(char));

    int i = 0;
    int s = fscanf(fp, "%s",line);

    // Reading the file into the arrays
    while(s != 0 && s!= -1)
    {
      int j=0;
      for(;line[j] != ',';j++)
      {
        name[i][j] = line[j];
      }
      for(int k = j+1;k<strlen(line);k++)
      {
        pswd[i][k-j-1] = line[k];
      }
      i++;
      s = fscanf(fp, "%s",line);
    }
    
    // Assigning NULL Values to Hash Table Pointers
    for(int z=0;z<4000;z++)
    {
      table[z] = NULL;
    }
    
    // Inserting Name and Password into the Hash Table
    for(int v=0;v<20000;v++)
    {
      insert(name[v],pswd[v]);
    }

    char username[50];
    char password[50];
    
    // Taking Input for User Name
    printf("Enter User Name: ");
    scanf("%s",username);

    // Checking if the Given Username is in the Hash Table
    if(usn_search(username) == 0)
    {
      printf("Name Not Found\n");
      return 1;
    }
    
    // Taking Input for Password
    printf("Enter the Password: ");
    scanf("%s",password);
    
    // Checking if the Given Password is correct for given Username in the Hash Table
    if(search(username,password) == 0)
    {
      printf("Login Unsuccessful\n");
    }
    else
    {
      printf("Login Successful\n");
    }

    // Closing the file
    fclose(fp);
    return 0;
}
