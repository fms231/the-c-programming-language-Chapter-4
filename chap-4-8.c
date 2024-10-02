#include <stdio.h>

char buf = 0;

int getch(){
    int c;
    if (buf != 0){
        c = buf;
    }
    else {
        c = getchar();
    }
    buf = 0;
    return c;
}

void ungetch(int c){
    if (buf != 0)
        printf("ungetch: too many characters\n");
    else
        buf = c;
}

int main(){
    int c;
    c = getch();
    printf("%c\n", c);
    ungetch(c);
    c = getch();
    printf("%c\n", c);
    return 0;
}