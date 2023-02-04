#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
#include <errno.h>
#define MAX_SIZE 1000

char *clipboard;
int  position;
int check_path(char *path)
{
    char *pointer;
    pointer =strrchr(path,'/');
    *pointer='\0';
    DIR *dr=opendir(path);
    *pointer='/';
    if (dr==NULL)
    {
        printf("masir peyda nakrdm");

        return -1;
    }

    closedir(dr);
    return 0;
}
int check_file(char *path)
{
    FILE *f=fopen(path,"r");
    if (f==NULL)
    {
        printf("file peyda nashod");
        return -1;
    }
    fclose(f);
    return 0;
}
char Readname(char path[])
{
    path[0] = getchar();
    while (path[0]==' ')
    {
        path[0]=getchar();
    }
    if (path[0] != '"')
    {
        ungetc(path[0], stdin);
        int i = 0;
        while (1)
        {
            path[i] = getchar();
            if (path[i] == ' ' || path[i] == '\n' || path[i] == EOF)
            {
                char tmp = path[i];
                path[i] = '\0';
                return tmp;

            }
            else if (path[i] == '\\')
            {
                char ch = getchar();
                if (ch == 'n') path[i] = '\n';
                else if (ch == '"') path[i] = '"';
                else if (ch == '\\') path[i] = '\\';
                else path[++i] = ch;
                i++;
            }
            else
            {
                i++;
            }
        }
    }
    else
    {
        int i = 0;
        while (1)
        {
            path[i] = getchar();
            if (path[i] == '"')
            {
                path[i] = '\0';
                break;
            }
            else if (path[i] == '\\')
            {
                char ch = getchar();
                if (ch == 'n') path[i] = '\n';
                else if (ch == '"') path[i] = '"';
                else if (ch == '\\') path[i] = '\\';
                else path[++i] = ch;
                i++;
            }
            else
            {
                i++;
            }
        }

        return getchar();
    }
}

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
    rewind(file);
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
    for(;str[i+1]!='\0';i++)
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
        printf("sakhtam amr digei dari darkhedmtm :)\n");
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
    if (check_path(filename)==-1)
    {
        return;
    }
    if (check_file(filename)==-1)
    {
        return;
    }
    f=fopen(filename,"r");
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
    if (check_path(filename)==-1)
    {
        return;
    }
    if (check_file(filename)==-1)
    {
        return;
    }

    f=fopen(filename,"r");
        while(a!=EOF)
        {
            a=fgetc(f);
            printf("%c",a);
        }
        printf("dighe chikar konm barat mohandes:\n ");

    fclose(f);
}

void remove1(char filename[],int line_of_start,int char_of_start,int size,char flag)

{
    FILE *f = fopen(filename, "r");
    if (check_path(filename)==-1)
    {
        return;
    }
    if (check_file(filename)==-1)
    {
        return;
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
    if (check_path(filename)==-1)
    {
        return;
    }
    if (check_file(filename)==-1)
    {
        return;
    }
    if (flag=='f')
    {
        free(clipboard);
        clipboard=malloc((size+1)*sizeof(char));
        memset(clipboard, 0, size+1);
        FILE *f=fopen(filename,"r");
        position=change_position_to_char(f,line_of_start,char_of_start);
        fseek(f,0,SEEK_SET);
        if (position!=-1)
        {
            if (position+size<= size_of_file(f))
            {
                position=10;
                fseek(f, position, SEEK_SET);
                fread(clipboard, sizeof(char), size, f);
                printf("%d %d %d\n",clipboard[0],size,position);

            }
            else
            {
                printf("error indecx\n");
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
                printf("error index\n");
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

void find(char filename[],char string_to_find[])
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
    if (check_path(filename)==-1)
    {
        return 0;
    }
    if (check_file(filename)==-1)
    {
        return 0;
    }
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
    if (check_path(filename1)==-1)
    {
        return;
    }
    if (check_file(filename1)==-1)
    {
        return;
    }
    if (check_path(filename2)==-1)
    {
        return;
    }
    if (check_file(filename2)==-1)
    {
        return;
    }
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
    if (check_path(filename)==-1)
    {
        return;
    }
    if (check_file(filename)==-1)
    {
        return;
    }
    chang_filename_to_backupname(filename,ans);
    FILE*f=fopen(ans,"r");
    if (f==NULL)
    {
        printf("taghirnadadi chio barghardonm?\n");
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

void tree(char path[],int tab_num, int depth)
{
    if (depth<-1)
    {
        printf("dari eshteba mizani\n");
        return;
    }
    if (tab_num<depth)
    {
        return;
    }
    chdir(path);
    struct dirent *de;
    DIR* dir=opendir(".");


    if (dir==NULL)
    {
        printf("nemitonm baz konm\n");
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

            tree(de->d_name,tab_num+1,depth);

        }
        chdir("..");

    }

    closedir(dir);
}

void uto_index(char filename[])
{
    FILE *f=fopen(filename,"r");
    while (1)
    {
        int ch;
        ch=fgetc(f);
        if (ch == EOF)
        {
            return;
        }
        if (ch =='{')
        {
            while (1)
            {
                int ch2;
                ch2=fgetc(f);

            }
        }
    }
}


void parser()
{
    while(1)
    {
        char dastorat[100];
        scanf("%s",dastorat);
        if (strcmp(dastorat,"createfile")==0)
        {
            char samp[20];
            scanf("%s",samp);
            char path[MAX_SIZE];
            Readname(path);
            replace_root(path);
            create_file(path);

        }
        else if(strcmp(dastorat,"insert")==0)
        {
            char samp[20];
            char samp2[20];
            char samp3[20];
            char path_file[MAX_SIZE];
            char path_str[MAX_SIZE];
            int line_of_start;
            int char_of_start;
            scanf("%s",samp);
            Readname(path_file);
            replace_root(path_file);
            scanf("%s",samp2);
            Readname(path_str);
            scanf("%s",samp3);
            scanf("%d",&line_of_start);
            getchar();
            scanf("%d",&char_of_start);
            insert(path_str,path_file,line_of_start,char_of_start);

        }


    else if(strcmp(dastorat,"cat")==0)
    {
        char samp[20];
        scanf("%s",samp);
        char path[MAX_SIZE];
        Readname(path);
        replace_root(path);
        cat(path);

    }
    else if (strcmp(dastorat,"removestr")==0)
    {
        char samp[20];
        char samp2[20];
        char samp3[20];
        char samp4[20];
        char samp5[20];
        char path_file[MAX_SIZE];
        int line_of_start;
        int char_of_start;
        int number_of_char;
        char flag;
        scanf("%s",samp);
        Readname(path_file);
        replace_root(path_file);
        scanf("%s",samp2);
        scanf("%d",&line_of_start);
        getchar();
        scanf("%d",&char_of_start);
        scanf("%s",samp3);
        scanf("%d",&number_of_char);
        getchar();
        getchar();
        scanf("%c",&flag);
        printf("%c",flag);
        remove1(path_file,line_of_start,char_of_start,number_of_char,flag);

    }
    else if(strcmp(dastorat,"copystr")==0)
    {
        char samp[20];
        char samp2[20];
        char samp3[20];
        char samp4[20];
        char samp5[20];
        char path_file[MAX_SIZE];
        int line_of_start;
        int char_of_start;
        int number_of_char;
        char flag;
        scanf("%s",samp);
        Readname(path_file);
        replace_root(path_file);
        scanf("%s",samp2);
        scanf("%d",&line_of_start);
        getchar();
        scanf("%d",&char_of_start);
        scanf("%s",samp3);
        scanf("%d",&number_of_char);
        getchar();
        getchar();
        scanf("%c",&flag);
        copy(path_file,line_of_start,char_of_start,number_of_char,flag);
        printf("%s",clipboard);
    }

    else if(strcmp(dastorat,"cutstr")==0)
    {
        char samp[20];
        char samp2[20];
        char samp3[20];
        char samp4[20];
        char samp5[20];
        char path_file[MAX_SIZE];
        int line_of_start;
        int char_of_start;
        int number_of_char;
        char flag;
        scanf("%s",samp);
        Readname(path_file);
        replace_root(path_file);
        scanf("%s",samp2);
        scanf("%d",&line_of_start);
        getchar();
        scanf("%d",&char_of_start);
        scanf("%s",samp3);
        scanf("%d",&number_of_char);
        getchar();
        scanf("%c",&flag);
        cut(path_file,line_of_start,char_of_start,number_of_char,flag);
    }
    else if (strcmp(dastorat,"pastestr")==0)
    {
        char samp[20];
        char samp2[20];
        char path_file[MAX_SIZE];
        int line_of_start;
        int char_of_start;
        scanf("%s",samp);
        Readname(path_file);
        replace_root(path_file);
        scanf("%s",samp2);
        scanf("%d",&line_of_start);
        getchar();
        scanf("%d",&char_of_start);
        printf("%s",clipboard);
        paste(path_file,line_of_start,char_of_start);

    }

    else if (strcmp(dastorat,"find")==0)
    {
        char samp[20];
        char samp2[20];
        char path_file[MAX_SIZE];
        char path_str[MAX_SIZE];
        scanf("%s",samp);
        Readname(path_file);
        replace_root(path_file);
        scanf("%s",samp2);
        Readname(path_str);
        find(path_file,path_str);
    }

    else if (strcmp(dastorat,"replace")==0)
    {
        char samp[20];
        char samp2[20];
        char  samp3[20];
        char path_str1[MAX_SIZE];
        char path_str2[MAX_SIZE];
        char path_file[MAX_SIZE];
        char flag[2];
        scanf("%s",samp);
        Readname(path_str1);
        scanf("%s",samp2);
        Readname(path_str2);
        scanf("%s",samp3);
        Readname(path_file);
        replace_root(path_file);
        getchar();
        scanf("%s",flag);

    }

    else if (strcmp(dastorat,"grep")==0)

    {
        char option[20];
        char samp[20];
        char samp2[20];
        char path_str[MAX_SIZE];
        int counter=0;
        scanf("%s",option);
        if (strcmp(option,"-c")==0)
        {
            scanf("%s",samp);
            Readname(path_str);
            scanf("%s",samp2);
            while(1)
            {
                char path_file[MAX_SIZE];
                char temp;
                temp= Readname(path_file);
                replace_root(path_file);
                counter+=grep_for_one_file(path_file,path_str,0);
                if (temp=='\n')
                {
                    break;
                }
            }
                printf("%d",counter);

        }
        else if (strcmp(option,"-l")==0)
        {
            scanf("%s",samp);
            Readname(path_str);
            scanf("%s",samp2);
            while(1)
            {
                char path_file[MAX_SIZE];
                char temp =Readname(path_file);
                replace_root(path_file);
                printf("%s\n",path_file);
                if (temp=='\n')
                {
                    break;
                }

            }
        }
        else if (strcmp(option,"--str")==0)
        {
            Readname(path_str);
            scanf("%s",samp2);
            while(1)
            {
                char path_file[MAX_SIZE];
                char temp=Readname(path_file);
                replace_root(path_file);
                grep_for_one_file(path_file,path_str,1);
                if (temp=='\n')
                {
                    break;
                }


            }
        }

    }
        else
        {
            printf("%s\n",dastorat);
            printf("chi mighi zabon baste");
        }
}
}



int main ()
{
   /* char filename[20]="/root/mff.txt";
    replace_root(filename);
    int line =3;
    int char_of_strt=0;
    int size =4;
    char a='f';
    copy(filename,line,char_of_strt,size,a);
    printf("%s",clipboard);*/
    FILE *f = fopen("root/mff.txt", "r");
    for (int i = 0; i < 20; i++)
    {
        char ch = fgetc(f);
        printf("%d ", ch);
    }
    printf("\n");
    fseek(f,11,SEEK_SET);
    printf("%d\n",fgetc(f));
    int y=change_position_to_char(f,2,0);
    printf("%d",y);
    fclose(f);
}

