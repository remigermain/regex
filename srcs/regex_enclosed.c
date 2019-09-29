/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_enclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/28 16:53:58 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

t_bool		regex_enclose_do(t_regex *st, t_reg_quan *quantifier, char *s1, char *reg)
{
	int i;

	i = 0;
	while ((quantifier->isset & QUAN_LAZY) && i <= quantifier->match)
	{
		if (verif_quantifier(quantifier, i))
		{
			if (regex_parse(st, s1 + i, reg))
				return (TRUE);
		}
		i++;
	}
	while (!(quantifier->isset & QUAN_LAZY) && quantifier->match >= 0)
	{
		if (verif_quantifier(quantifier, quantifier->match))
		{
			if (regex_parse(st, s1 + quantifier->match, reg))
				return (TRUE);
		}
		quantifier->match--;
	}
	return (FALSE);
}

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
        if (regex_parse(st, s1, reg + i))
        {
            s1 = st->enclose_s1;
            if (verif_quantifier(quantifier, index + 1) && regex_parse(st, s1, reg + len))
                return (TRUE);
            if (regex_enclose_parse(st, quantifier, s1, reg, len, index + 1))
                return (TRUE);
            s1 = mem_s1;
        }
        i += regex_span_enclose(reg + i, "|)");
        if (*(reg + i) == '|')
            i++;
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
	len = regex_span_enclose(reg, ")") + 1;
	if (is_quantifier(st, reg + len))    
        len += get_quantifier(&quantifier, reg + len);
    return (regex_enclose_parse(st, &quantifier, s1, reg, len, 0));
    //return (regex_enclose_do(st, &quantifier, s1, reg + len));

}