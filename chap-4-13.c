#include <string.h>
#include <stdio.h>

void reverser(char s[], int i, int len) {
    int c, j;
    j = len - (i + 1);
    if (i < j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        reverser(s, ++i, len);
    }
}

void reverse(char s[]) {
    reverser(s, 0, strlen(s));
}


int main() {
    char s[] = "hello";
    reverse(s);
    printf("%s\n", s);
    return 0;
}