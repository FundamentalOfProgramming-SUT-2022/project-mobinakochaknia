#include<stdio.h>
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
int main (void)
{
    char filename[100]="kk.txt";
    cat(filename);
}
