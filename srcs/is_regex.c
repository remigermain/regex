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

t_bool      is_metachar(t_regex *st, char *reg)
{
    int i;

    i = 0;
    while (reg - i - 1 >= st->reg && *(reg - i - 1) == '\\')
        i++;
    if (i % 2)
        return (FALSE);
    return (TRUE);
}

t_bool      is_enclose(t_regex *st, char *reg)
{
    if (ft_strchr(ENCLOSE, *reg) && is_metachar(st, reg))
        return (TRUE);
    return (FALSE);    
}

t_bool      is_quantifier(t_regex *st, char *reg)
{
    if (ft_strchr(QUANTIFIER, *reg) && is_metachar(st, reg))
        return (TRUE);
    return (FALSE);
}

t_bool      is_delimiter(t_regex *st, char *reg, char delimiter)
{
    if (delimiter == *reg && is_metachar(st, reg))
        return (TRUE);
    return (FALSE);
}

int         convert_metachar(t_regex *st, char *reg)
{
    int c;

    c = *reg;
    if (!is_metachar(st, reg))
    {
        if (*reg == 'n')
            c = '\n';
        else if (*reg == 't')
            c = '\t';
        else if (*reg == 'v')
            c = '\v';
        else if (*reg == '0')
        {
            if (ft_tolower(*(reg + 1)) == 'x')
                c = ft_atoi_base(reg + 2, 16);
            else if (ft_tolower(*(reg + 1)) == 'b')
                c = ft_atoi_base(reg + 2, 2);
            else
                c = ft_atoi_base(reg, 8);
        }
        else if (ft_isdigit(*reg))
            c = ft_atoi_base(reg, 10);
    }
    return (c);
}