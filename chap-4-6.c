#include <stdio.h>
#include <ctype.h>

#define MAXOP 100
#define MAXVAL 100
#define NUMBER '0'
#define BUFSIZE 100

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

double atof(char s[]){
    double val, power;
    int exp, i, sign;

    for (i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++){
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    val = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E'){
        sign = (s[++i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        for (exp = 0; isdigit(s[i]); i++)
            exp = 10 * exp + (s[i] - '0');
        if (sign == 1)
            while (exp-- > 0)
                val *= 10;
        else
            while (exp-- > 0)
                val /= 10;
    }

    return val;
}

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int main(){
    int i, type, var = 0;
    double op2, v;
    char s[MAXOP];
    double variable[26];

    for (i = 0; i < 26; i++)
        variable[i] = 0.0;

    while ((type = getop(s)) != EOF){
        switch (type){
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '=':
                pop();
                if ('A' <= var && var <= 'Z')
                    variable[var - 'A'] = pop();
                else
                    printf("error: no variable name\n");
                break;
            case '\n':
                v = pop();
                printf("\t%.8g\n", v);
                break;
            default:
                if ('A' <= type && type <= 'Z')
                    push(variable[type - 'A']);
                else if (type == 'v')
                    push(v);
                else
                    printf("error: unknown command %s\n", s);
                break;
        }
        var = type;
    }
    return 0;
}

int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int getop(char s[]){
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

void push(double f){
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void){
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}