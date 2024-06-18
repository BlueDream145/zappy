/*
** EPITECH PROJECT, 2019
** utils.c
** File description:
** utils
*/

#include "zappy_server.h"

static int number_digits(int nbr)
{
    int n = 1;
    int po = 10;

    if (nbr < 0)
        nbr = -nbr;
    while (nbr >= po) {
        n++;
        if (po > 214748364)
            break;
        po *= 10;
    }
    return (n);
}

char *my_strcat(char *dest, const char *src)
{
    int dest_len = strlen(dest);
    int j = 0;

    if (!dest || !src)
        return (NULL);
    for (j = 0; src[j] != '\0'; j++)
        dest[dest_len + j] = src[j];
    dest[dest_len + j] = '\0';
    return (dest);
}

char *my_itc(int nbr)
{
    int len = number_digits(nbr);
    char *result;

    result = malloc(sizeof(char) * (len + 1));
    if (!result)
        return (NULL);
    result[len] = '\0';
    while (len--) {
        result[len] = nbr % 10 + '0';
        nbr /= 10;
    }
    return (result);
}
