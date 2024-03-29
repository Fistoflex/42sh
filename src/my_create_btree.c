/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>
#include "btree.h"
#include "my.h"

char **my_cut(char *str, char *sep)
{
    char *save = NULL;
    char **tab = malloc(sizeof(char *) * 3);
    char *rest;

    tab[2] = NULL;
    if (sep == NULL)
        return (NULL);
    rest = my_strstr(str, sep, &save);
    if (rest == NULL)
        return (NULL);
    if (rest[0] != 0 && (sep[0] == '&' || (sep[0] == '|' && sep[1] == '|')
    || (sep[0] == '>' && sep[1] == '>') || (sep[0] == '<' && sep[1] == '<')))
        rest += 2;
    save = clean_str(save, FREE);
    rest = (rest[0] == 0) ? NULL : clean_str(rest, FREE);
    tab[0] = my_strdup(save, KEEP);
    tab[1] = (rest == NULL) ? NULL : my_strdup(rest, KEEP);
    return (tab);
}

int set_state(char *str, int i)
{
    char s = 0;

    if (str[i] == '\"' || str[i] == '\'' || str[i] == '`') {
        s = str[i];
        i++;
        while (str[i] != s && str[i] != '\0')
            i++;
        i++;
    }
    return (i);
}

char *operator(char *str, char **tab, int x)
{
    int i = 0;

    for (i = 0; str[i] != '\0'; i++) {
        i = set_state(str, i);
        if (str[i] == tab[x][0] && tab[x][1] == str[i + 1])
            return (tab[x]);
    }
    return (NULL);
}

char *my_find_sep(char *str)
{
    int i = 0;
    char *ptr = NULL;
    char *tab[] = {my_strdup(";", KEEP), my_strdup("&&", KEEP),
                    my_strdup("||", KEEP), NULL};

    if (str == NULL)
        return (NULL);
    for (i = 0; str[i] != '\0'; i++) {
        i = set_state(str, i);
        if (str[i] == tab[0][0])
            return (tab[0]);
    }
    if ((ptr = operator(str, tab, 1)) != NULL)
        return (ptr);
    else if ((ptr = operator(str, tab, 2)) != NULL)
        return (ptr);
    return (NULL);
}

void    my_btree_create_new_node(btree_t **node, char *str)
{
    char *sep = my_find_sep(str);
    char **tab = my_cut(str, sep);

    (*node) = malloc(sizeof((**node)));
    (*node)->sep = NULL;
    (*node)->cmd = NULL;
    (*node)->left = NULL;
    (*node)->right = NULL;
    if (sep != NULL) {
        (*node)->sep = sep;
        my_btree_create_new_node(&(*node)->left, tab[0]);
        my_btree_create_new_node(&(*node)->right, tab[1]);
    } else
        (*node)->cmd = my_strdup(str, KEEP);
}
