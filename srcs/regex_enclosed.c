/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_enclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/22 16:40:34 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

t_bool  regex_enclosed(t_regex *st, const char *s1, const char *reg)
{
    t_reg_quan  quan;
    t_reg_work  work;

    work.occur = 0;
    work.tmp = (char*)reg;
    work.span = ft_spanchar_reg(st, work.tmp, ")") + 1;
    if (is_delimiter(st, (char*)(reg + work.span), '{'))
        work.span += get_quantifier(&quan, reg + work.span + 1) + 1;
    while (*(work.tmp) && is_delimiter(st, (char*)work.tmp, ')'))
    {
        if (is_delimiter(st, (char*)work.tmp, '|'))
            work.tmp++;
        if (is_delimiter(st, (char*)work.tmp, '\\'))
            work.tmp++;
        ft_printf("%c\n", *work.tmp);
        if ((*s1 == *(work.tmp)) &&
                    verif_quantifier(&quan, ++(work.occur)))
        {
            work.tmp = (char*)reg;
            if (regex_parse(st, ++s1, reg + work.span))
                return (TRUE);
        }
        work.tmp += ft_spanchar_reg(st, work.tmp, "|)");
    }
    return (FALSE);
}