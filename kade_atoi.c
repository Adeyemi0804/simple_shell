#include "kade.h"

/**
 * kade_interactive - returns true if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int kade_interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * kade_is_delim - checks if character is a delimiter
 * @c: the char to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int kade_is_delim(char c, char *delim)
{
    for (; *delim != '\0'; delim++) {
        if (*delim == c)
            return (1);
    }
    return (0);
}

/**
 * kade_isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int kade_isalpha(int c) {
    int i;
    /* Loop through the range of lower and upper case alphabets */
    for (i = 'a'; i <= 'z' || i <= 'Z'; i++) {
        if (c == i) {
            return 1; /* Return 1 if alphabetic */
        }
    }
    return 0; /* Return 0 if not alphabetic */
}

/**
 * kade_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int kade_atoi(char *s) {
    int sign = 1, output = 0;
    unsigned int result = 0;
    int flag = 0, i = 0;

    for (i = 0; s[i] != '\0' && flag != 2; i++) {
        if (s[i] == '-') {
            sign *= -1; /* Change the sign */
        }
        if (s[i] >= '0' && s[i] <= '9') {
            flag = 1;
            result *= 10;
            result += (s[i] - '0'); /* Calculate the integer value */
        } else if (flag == 1) {
            flag = 2; /* Stop at the end of the number */
        }
    }

    if (sign == -1) {
        output = -result; /* Apply the sign to the result */
    } else {
        output = result; /* Result without sign change */
    }

    return output; /* Return the final integer */
}