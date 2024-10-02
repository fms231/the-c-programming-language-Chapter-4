#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100
#define NUMBER '0'

int Getline(char line[], int maxline){
    int c, i;

    i = 0;
    while (--maxline > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}

int li = 0;
char line[MAXLINE];

int getop(char s[]){
    int c, i;

    if (line[li] == '\0')
        if (Getline(line, MAXLINE) == 0)
            return EOF;
        else
            li = 0;

    while ((s[0] = c = line[li++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;

    i = 0;

    if (isdigit(c))
        while (isdigit(s[++i] = c = line[li++]))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = line[li++]))
            ;

    s[i] = '\0';

    li--;

    return NUMBER;
}

int main(){
    char s[MAXLINE];
    int type;

    while ((type = getop(s)) != EOF){
        printf("%c\n", type);
        printf("%s\n", s);
    }


    return 0;
}