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

t_bool  regex_enclosed(const char *s1, const char *reg)
{
    t_reg_quan  st;
    t_reg_work  work;

    work.occur = 0;
    work.tmp = (char*)reg;
    work.span = ft_spanchar(work.tmp, ")") + 1;
    if (*(reg + work.span) == '{')
        work.span += get_quantifier(&st, reg + work.span + 1) + 1;
    while (*(work.tmp) && *(work.tmp) != ')')
    {
        if (*(work.tmp) == '|')
            work.tmp++;
        if ((*s1 == *(work.tmp) || *(work.tmp) == ')') &&
                    verif_quantifier(&st, ++(work.occur)))
        {
            work.tmp = (char*)reg;
            if (regex_cmp(++s1, reg + work.span))
                return (TRUE);
        }
        work.tmp += ft_spanchar(work.tmp, "|)");
    }
    return (FALSE);
}