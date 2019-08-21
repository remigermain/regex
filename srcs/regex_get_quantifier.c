/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:48:43 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 20:35:56 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

static int  get_quantifier_number(int *number, int *isset , int set, char *reg)
{
    int i;

    i = 0;
    if (*reg && *reg != ',' && *reg != '}')
    {
        *number = ft_atoi(reg);
        *isset |= set;
        i += ft_spantype(reg, ft_isdigit);
    }
    return (i);
}

int         get_quantifier(t_reg_quan *st, const char *reg)
{
    int i;

    i = 0;
    ft_bzero(st, sizeof(*st));
    i += get_quantifier_number(&st->number_1, &st->isset, QUAN_MIN, (char*)reg + i);
    i += ft_spantype((char*)reg + i, ft_isspace);
    if (*(reg + i) != ',')
        st->isset |= QUAN_EX;
    else
        i++;
    i += get_quantifier_number(&st->number_2, &st->isset, QUAN_MAX, (char*)reg + i);
    i += ft_spantype((char*)reg + i, ft_isspace) + 1;
    return (i);
}

t_bool      verif_quantifier(t_reg_quan *st, int i)
{
    if (st->isset & QUAN_EX && st->number_1 != i)
        return (FALSE);
    else if (st->isset & QUAN_MIN && st->number_1 > i)
        return (FALSE);
    else if (st->isset & QUAN_MAX && st->number_2 < i)
        return (FALSE);
    return (TRUE);
}
