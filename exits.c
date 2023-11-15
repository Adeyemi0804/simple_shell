#include "kade.h"

/**
 **kade_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *kade_strncpy(char *dest, char *src, int n) {
    int i, j;
    char *s = dest;

    i = 0;
    for (i = 0; src[i] != '\0' && i < n - 1; i++) {
        dest[i] = src[i];
    }

    if (i < n) {
        j = i;
        while (j < n) {
            dest[j] = '\0';
            j++;
        }
    }

    return (s);
}

/**
 **kade_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *kade_strncat(char *dest, char *src, int n) {
    int i, j;
    char *s = dest;

    i = 0;
    j = 0;

    while (dest[i] != '\0') {
        i++;
    }

    while (src[j] != '\0' && j < n) {
        dest[i] = src[j];
        i++;
        j++;
    }

    if (j < n) {
        dest[i] = '\0';
    }

    return (s);
}

/**
 **kade_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *kade_strchr(char *s, char c) {
    do {
        if (*s == c) {
            return (s);
        }
    } while (*s++ != '\0');

    return (NULL);
}