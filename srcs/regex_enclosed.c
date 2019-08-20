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
    t_bool is_match;

    if (!ft_strncmp(reg, "...)", 4)) // TODO
        return (regex_cmp(s1, reg + 4));
    is_match = (*reg == ')' ? TRUE : FALSE);
    while (*reg && *reg != ')')
    {
        if (*reg == '|')
            reg++;
        if (*s1 == *reg || *reg == ')')
            is_match = TRUE;
        reg += ft_spanchar((char*)reg, "|)");
    }
    if (*reg == ')')
        reg++;
    if (is_match)
        return (regex_cmp(++s1, reg));
    return (FALSE);
}