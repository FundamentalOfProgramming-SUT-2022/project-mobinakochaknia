#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
char *clipboard;
int  position;
int change_position_to_char(FILE * file,int shomare_khat ,int mogheiyat)
{
    int counter=0;
    int counter_of_char=0;
    int  ch;
    int counter2=0;

    for (int i=0;counter<shomare_khat-1;i++)
    {
        ch=fgetc(file);
        counter_of_char++;
        if (ch==EOF)
        {
            printf("pasgardni mikhaya \n");
            return -1;
        }
        if (ch=='\n')
        {
            counter++;


        }
    }
    for (;;counter2++)
    {
        ch =fgetc(file);
        if (ch==EOF || ch=='\n')
        {
            break;
        }
    }
    if (counter2<mogheiyat)
    {
        printf("rakab khordi abosofyan\n");
        return -1;
    }
    counter_of_char=counter_of_char+mogheiyat;
    rewind(file);
    return counter_of_char;
}

int size_of_file(FILE *f)
{
    long long int size_file;
    fseek(f,0L, SEEK_END);
    size_file= ftell(f);
    rewind(f);
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

void insert(char string[],char filename[],int khat ,int mogheiyat)
{
    FILE *f;
    f=fopen(filename,"r");
    if (f==NULL)
    {
        printf("e bakhty fil vojod nadasht");
        return;
    }
    int i=0;
    int counter=0;
    long long int size=size_of_file(f);
    char *reserv= malloc((size+strlen(string))*sizeof(char));
    int number_of_char=change_position_to_char(f,khat,mogheiyat);
    if (number_of_char!=-1) {
        for (; i < number_of_char; i++) {
            reserv[i] = fgetc(f);
        }
        for (i; string[counter] != '\0'; i++) {
            reserv[i] = string[counter];
            counter++;
        }
        for (i;; i++) {
            int a = fgetc(f);
            if (a != EOF) {
                reserv[i] = a;
            } else {
                break;
            }
        }
        fclose(f);
        f = fopen(filename, "w");
        fwrite(reserv, sizeof(char), i, f);
        fclose(f);
    }
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

void remove1(char filename[],int line_of_start,int char_of_start,int size,char flag)

{
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("chio remove konm vaghti fili nist ://");
    }
    long long int size_new_file = size_of_file(f) - size;

    if (flag == 'f') {
        int i = 0;

        char *reserv = malloc(size_new_file * sizeof(char));
        int number_of_char_start = change_position_to_char(f,line_of_start, char_of_start);
        if (number_of_char_start!=-1 ) {
            if ( number_of_char_start+size<= size_of_file(f)) {
                for (i; i < number_of_char_start; i++) {
                    reserv[i] = fgetc(f);
                }
                for (i; i < number_of_char_start + size; i++) {
                    fgetc(f);
                }
                for (i;; i++) {
                    int ans = fgetc(f);
                    if (ans == EOF) {
                        break;
                    }
                    reserv[i - size] = ans;

                }
                fclose(f);
                f = fopen(filename, "w");
                fwrite(reserv, sizeof(char), size_new_file, f);
                fclose(f);
            }
            else
            {
                printf("vase hamine ke riazi1 pas nashodi dige \n");
                return;
            }
        }
    }
    if (flag == 'b')
    {
        char *reserv = malloc(size_new_file * sizeof(char));
        int number_of_char_start = change_position_to_char(f,line_of_start, char_of_start);
        int i = 0;
        if (number_of_char_start!=-1 ) {
            if ( number_of_char_start-size>= 0) {
                for (i; i <= number_of_char_start - size; i++) {
                    reserv[i] = fgetc(f);
                }
                for (i; i <= number_of_char_start; i++) {
                    fgetc(f);
                }
                for (i;; i++) {
                    int ans = fgetc(f);
                    if (ans == EOF) {
                        break;
                    }
                    reserv[i - size] = fgetc(f);

                }
                fclose(f);
                f = fopen(filename, "w");
                fwrite(reserv, sizeof(char), size_new_file, f);
                fclose(f);
            }
            else
            {
                printf("majid deghat kon");
            }
        }
    }
}


void copy(char filename[],int line_of_start,int char_of_start,int size, char flag )
{
    if (flag=='f')
    {
        free(clipboard);
        clipboard=malloc((size+1)*sizeof(char));
        memset(clipboard, 0, size+1);
        FILE *f=fopen(filename,"r");
        position=change_position_to_char(f,line_of_start,char_of_start);
        if (position!=-1)
        {
            if (position+size<= size_of_file(f))
            {

                fseek(f, position, SEEK_SET);
                fread(clipboard, sizeof(char), size, f);

            }
            else
            {
                printf("error indecx");
            }
        }
        fclose(f);

    }

    if (flag=='b')
    {
        free(clipboard);
        clipboard=malloc((size+1)*sizeof(char));
        memset(clipboard, 0, size+1);
        FILE *f=fopen(filename,"r");
        int position=change_position_to_char(f,line_of_start,char_of_start)-size;
        if (position!=-1) {
            if (char_of_start -size>= 0)
            {
                fseek(f, position, SEEK_SET);
                fread(clipboard, sizeof(char), size, f);
            }
            else
            {
                printf("error index");
            }
        }
        fclose(f);
    }

}


void cut(char filename[],int line_of_start,int char_of_start,int size , char flag)
{
    copy(filename,line_of_start,char_of_start,size,flag);
    remove1(filename,line_of_start,char_of_start,size,flag);
}

void paste(char filename[],int line_of_start,int char_of_start)
{
    insert(clipboard,filename,line_of_start,char_of_start);
}

void find(char filename[],char string_to_find)
{
    FILE*f=fopen(filename,"r");


}
void 
int main() {
    char filename[]="/root/mff.txt";
    char a='f';
    replace_root(filename);
    int khat=1;
    int makan=0 ;
    int size=3;
    copy(filename,khat,makan,size,a);
    printf("%s",clipboard);
    paste(filename,khat,makan);

    printf("\n");

}
