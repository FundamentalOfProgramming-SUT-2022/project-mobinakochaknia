#include <stdio.h>
#include<string.h>
#include<stdlib.h>
int change_position(FILE * file,int shomare_khat ,int mogheiyat)
{
    int counter=0;
    int counter_of_char=0;
    char ch;

    for (int i=0;counter<shomare_khat-1;i++)
    {
        ch=fgetc(file);
        counter_of_char++;
        if (ch=='\n')
        {
            counter++;


        }
    }
    counter_of_char=counter_of_char+mogheiyat;

    return counter_of_char;
}
int size_of_file(FILE *f)
{
    long long int size_file
    fseek(f,0L, SEEK_END);
    size_file= ftell(f);
    return  size_file;
}
void replace_root(char str[])
{   char str2[500];
    int i=4;
    strcpy(str2,"root");
    for(;str[i+1]!=NULL;i++)
    {
        str2[i]=str[i+1];

    }
    str2[i]='\0';
    strcpy(str,str2);
}
void create_file(char *str)
{
    char str2[500];
    str2[0] = 0;
    char *token = strtok(str, "/");
    while (token != NULL)
    {
        char *newtoken = strtok(NULL, "/");
        if (newtoken != NULL)
        {
            strcat(str2, token);
            mkdir(str2);
            strcat(str2, "/");
        }
        else
        {
            break;
        }
        token = newtoken;
    }
    strcat(str2, token);

    FILE *fp = fopen(str2, "r");
    if (fp == NULL)
    {
        FILE *fp2 = fopen(str2, "w");
        printf("sakhtam amr digei dari darkhedmtm :)");
        fclose(fp2);
    }
    else
    {
        printf("File vojod dare mohandes\n");
        fclose(fp);
    }
}
void insert(char string[],char filename[],int khat ,int jayghah)
{
    FILE *f;
    f=fopen(filename,"w");
    long long int size=size_of_file(f);
    char *reserv= malloc((size+strlen(string))*sizeof(char));

    for (int i=1,i<=khat,i++)
    {

    }
    for (int i=jayghah;string[i]!='/0';i++)
    {
        fputs(string[i],f);
    }

    fclose(f);
}
void cat (char filename[])
{   int  a=0;
    FILE *f;
    f=fopen(filename,"r");
    if (f==NULL)
    {
        printf("sharmnade akhlagh varzeshitam file peida nakardm amr dighe: ");
    }
    else
    {
        while(a!=EOF)
        {
            a=fgetc(f);
            printf("%c",a);
        }
        printf("dighe chikar konm barat mohandes: ");
    }
    fclose(f);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", n);
    return 0;
}
