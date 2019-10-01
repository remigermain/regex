/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_enclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/01 18:51:12 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

t_bool		regex_enclose_parse(t_regex *st, t_reg_quan *quantifier, char *s1, char *reg, int len, int index)
{
    char    *mem_s1;
    char    *mem_reg;
    size_t  match;
    int     i;

	match = 0;
    i = 0;
    mem_s1 = s1;
    mem_reg = reg;
	while (*s1 && *(reg + i) && !is_delimiter(st, reg + i, ')'))
    {
        //ft_printf("[ BF :   %s  %s  %d]\n", s1, reg + i, index);
        if (regex_parse(st, s1, reg + i))
        {
            s1 = st->enclose_s1;
            ft_printf("%.*s\n",ft_strlen(mem_s1) - ft_strlen(st->enclose_s1), mem_s1);
            if (verif_quantifier(quantifier, index + 1) && regex_parse(st, s1, reg + len))
                return (TRUE);
            if (regex_enclose_parse(st, quantifier, s1, reg, len, index + 1))
                return (TRUE);
            s1 = mem_s1;
        }
        i += regex_span_or(st, reg + i);
    }
    s1 = mem_s1;
    if (verif_quantifier(quantifier, index) && regex_parse(st, s1, reg + len))
        return (TRUE);
    return (FALSE);
}


t_bool  regex_enclosed(t_regex *st, char *s1, char *reg)
{
    t_reg_quan  quantifier;
    int         len;

    ft_bzero(&quantifier, sizeof(t_reg_quan));
	len = regex_span_enclose(st, reg);
	if (is_quantifier(st, reg + len))    
        len += regex_get_quantifier(&quantifier, reg + len);
    return (regex_enclose_parse(st, &quantifier, s1, reg, len, 0));
}