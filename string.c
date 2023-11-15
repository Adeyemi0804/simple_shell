#include "kade.h"

/**
 * kade_strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int kade_strlen(char *s) {
    int i = 0;

    if (!s)
        return 0;

    while (*s++)
        i++;
    return i;
}

/**
 * kade_strcmp - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int kade_strcmp(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return 0;
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * kade_starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *kade_starts_with(const char *haystack, const char *needle) {
    while (*needle) {
        if (*needle++ != *haystack++)
            return NULL;
    }
    return (char *)haystack;
}

/**
 * kade_strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *kade_strcat(char *dest, char *src) {
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return ret;
}
