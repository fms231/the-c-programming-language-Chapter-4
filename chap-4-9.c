#include <stdio.h>

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getch(){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int main(){
    char s[] = "hello, world!";
    int i;
    for (i = 0; s[i] != '\0'; i++)
        ungetch(s[i]);
    int c;
    while ((c = getch()) != EOF)
        putchar(c);
    return 0;
}