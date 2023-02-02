#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
#include <errno.h>
char *clipboard;
int  position;


int isFile(const char* name)
{
    DIR* directory = opendir(name);

    if(directory != NULL)
    {
        closedir(directory);
        return 0;
    }

        return 1;

}

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

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


int  grep_for_one_file (char filename[],char string[],int flag_print)
{
    FILE* f=fopen(filename,"r");
   char *temp=NULL;
    unsigned long long size=0;
    int ans=0;
    int counter=0;
  while(1)
  {
      ans=getline(&temp,&size,f);

      if (ans==-1)
      {
          free(temp);
          break;

      }

      if(  strstr(temp,string)!=NULL)
      {
         if (flag_print==1)
         {
             printf("%s",temp);
         }
          counter++;
      }


      size=0;
      free(temp);
      temp=NULL;

  }
    return counter;
}


void comper(char filename1[],char filename2[])
{
    FILE *f1=fopen(filename1,"r");
    FILE *f2=fopen(filename2,"r");
    char *ans1;
    char *ans2;
    int line_number=0;
    char *str1=NULL,*str2=NULL;
    unsigned long long  size1=0,size2=0;
    int result1=0,result2=0;

    while (1)
    {

        result1=getline(&str1,&size1,f1);
        result2=getline(&str2,&size2,f2);
        line_number++;
        if (result2==-1 || result1==-1)
        {
            break;
        }
        if (strcmp(str2,str1)!=0) {
            for (int i = 0; i < 5; i++) {
                printf("=");
            }
            printf("%d", line_number);
            for (int i = 0; i < 5; i++) {
                printf("=");
            }
            printf("\n");
            printf("%s", str1);
            printf("%s", str2);


            free(str1);
            free(str2);
            size1 = 0;
            size2 = 0;
            str1 = NULL;
            str2 = NULL;
        }
    }

    if (result1==-1 && result2!=-1)
    {
        int line_of_end=line_number;
        int ch1=0;
        int ch2=0;
        int cersor2;
        cersor2=ftell(f2);
        for (;;)
        {
           ch1 = fgetc(f2);

            if (ch1=='\n')
            {
                line_of_end++;
            }

            if (ch1 == EOF)
            {
                if (ch2=='\n')
                {
                    break;
                }
                else
                {
                    line_of_end++;
                    break;
                }

            }
            ch2=ch1;
        }
        fseek(f2,cersor2,SEEK_SET);
        for (int i=0;i<=5;i++)
        {
            printf(">");
        }
        printf("%d",line_number);
        printf("_");
        printf("%d",line_of_end);
        for (int i=0;i<=5;i++)
        {
            printf(">");
        }
        printf("\n");
        printf("%s",str2);
       for(int i=0;;i++)
       {
           int ch ;
           ch=fgetc(f2);
           if (ch==EOF)
           {
               break;
           }
           else
           {
               printf("%c",ch);
           }
       }

    }
    if (result2==-1 && result1!=-1)
    {
        int line_of_end=line_number;
        int ch1=0;
        int ch2=0;
        int cersor1;
        cersor1=ftell(f1);
        for (;;)
        {
            ch1 = fgetc(f1);

            if (ch1=='\n')
            {
                line_of_end++;
            }

            if (ch1 == EOF)
            {
                if (ch2=='\n')
                {
                    break;
                }
                else
                {
                    line_of_end++;
                    break;
                }
            }
            ch2=ch1;
        }
        fseek(f1,cersor1,SEEK_SET);
        for (int i=0;i<=5;i++)
        {
            printf("<");
        }
        printf("%d",line_number);
        printf("_");
        printf("%d",line_of_end);
        for (int i=0;i<=5;i++)
        {
            printf("<");
        }
        printf("\n");
        printf("%s",str1);
        for(int i=0;;i++)
        {
            int ch ;
            ch=fgetc(f1);
            if (ch==EOF)
            {
                break;
            }
            else
            {
                printf("%c",ch);
            }
        }

    }

}

char*  chang_filename_to_backupname(char filename[],char ans[])
{
    char * pointer1;
    char *pointer2=&filename[0];
    pointer1=strrchr(filename,'/');
    int index=pointer1-pointer2;
    int i=0;
    for (;i<index;i++)
    {
        ans[i]=filename[i];
    }
    ans[i]=0;
    char *pointer3=filename+i+1;
    strcat(ans,"/.");
    strcat(ans,pointer3);



    return ans;

}

void create_backup(char filename[])
{
    char ans[10000];
    chang_filename_to_backupname(filename,ans);
    FILE* f1=fopen(filename,"r");
    FILE* f2=fopen(ans,"w");
    for (int i=0;;i++)
    {
        int ch=0;
        ch =fgetc(f1);
        if (ch==EOF)
        {
            break;
        }
        fputc(ch,f2);
    }
    fclose(f1);
    fclose(f2);
}

void undo(char filename[])
{
    char ans[100000];
    chang_filename_to_backupname(filename,ans);
    FILE*f=fopen(ans,"r");
    if (f==NULL)
    {
        printf("taghirnadadi chio barghardonm?");
        return;
    }
    FILE *f1=fopen(filename,"r");
    FILE *f2;
    long long size=size_of_file(f1);
   char *temp=malloc(size_of_file(f1)*sizeof(char));
   int ch=0;
   for(int i=0;i<size;i++)
   {
       ch=fgetc(f1);
       temp[i]=ch;
       printf("%c",temp[i]);
   }

   fclose(f1);
   f2=fopen(ans,"r");
   f1=fopen(filename,"w");
   for(int i;;i++)
   {
       int a=0;
       a=fgetc(f2);
       if(a==EOF)
       {
           break;
       }

       fputc(a,f1);
   }
   fclose(f2);
   fclose(f1);
   f2=fopen(ans,"w");
   for(int i=0;i<size;i++)
   {
       fputc(temp[i],f2);
   }
   fclose(f2);
   free(temp);


}

void tree(char path[],int tab_num)
{
    chdir(path);
    struct dirent *de;
    DIR* dir=opendir(".");


    if (dir==NULL)
    {
        printf("nemitonm baz konm");
        return ;
    }
    while((de=readdir(dir))!=NULL)
    {

        if (de->d_name[0]=='.')
        {
            continue;
        }
        else
        {
            for (int i=0;i<tab_num;i++)
            {
                printf("\t");
            }
            printf("%s\n", de->d_name);

            if (isFile(de->d_name))
            {

                continue;
            }

            tree(de->d_name,tab_num+1);

        }
        chdir("..");

    }

    closedir(dir);
}

int main() {
    char filename[]="/root/";
    char filename2[]="/root/test2.txt";
    char str[5]="slm";
    char a='f';
    replace_root(filename);
    replace_root(filename2);
    int khat=1;
    int makan=0 ;
    int size;
    char ans[1000];
   tree(filename,0);
   
}


