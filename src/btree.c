/*
** EPITECH PROJECT, 2019
** mysh
** File description:
** mysh loop
*/

#include "my.h"

int my_check_sep(char *cmd)
{
    int i = 0;

    if (my_str_str(cmd, ";") != NULL)
        i++;
    if (my_str_str(cmd, "&&") != NULL)
        i++;
    if (my_str_str(cmd, "||") != NULL)
        i++;
    if (i != 0)
        return (1);
    return (0);
}

int my_cond(mysh_t *info, btree_t *node)
{
    int n = 0;

    if (my_strcmp(node->sep, "||") == 0) {
        n = exec_btree(info, node->left);
        if (n == -1)
            exec_btree(info, node->right);
    } else {
        if (node->cmd != NULL)
            n =  check_exec(info, node->cmd);
        return (n);
    }
    return (0);
}

int    exec_btree(mysh_t *info, btree_t *node)
{
    int n = 0;

    if (my_strcmp(node->sep, ";") == 0) {
        exec_btree(info, node->left);
        exec_btree(info, node->right);
    } else if (my_strcmp(node->sep, "&&") == 0) {
        n = exec_btree(info, node->left);
        if (n != -1)
            exec_btree(info, node->right);
    } else
        return (my_cond(info, node));
    return (0);
}
