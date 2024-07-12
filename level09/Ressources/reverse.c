#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
    int i = 0;
    char c;

    while (i < strlen(av[1]))
    {
        c = av[1][i];
        printf("%c", c - i);
        i++;
    }
    printf("\n");
    return 0;
}
