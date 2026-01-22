#include <stdio.h>
#include <string.h>

/* Global variables */
char input[100];
int isValid = 1;

int main()
{
    int i = 0;
    int len;

    printf("Enter a string: ");
    scanf("%s", input);

    len = strlen(input);

    /* Step 1: Match zero or more 'a' characters */
    while (input[i] == 'a')
    {
        i++;
    }

    /* Step 2: Check for exactly 'bb' at the end */
    if (i + 1 < len && input[i] == 'b' && input[i + 1] == 'b' && i + 2 == len)
    {
        isValid = 1;
    }
    else
    {
        isValid = 0;
    }

    /* Output result */
    if (isValid)
    {
        printf("Valid string (matches a*bb)\n");
    }
    else
    {
        printf("Invalid string (does not match a*bb)\n");
    }

    return 0;
}
