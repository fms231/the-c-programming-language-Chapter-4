#include <string.h>
#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

void ungetch(int);

void ungets(char s[]){
    int len = strlen(s);
    while (len > 0)
        ungetch(s[--len]);
}

void ungetch(int c){
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int main(){
    char s[] = "hello, world!";
    ungets(s);
    printf("%s\n", buf);
}