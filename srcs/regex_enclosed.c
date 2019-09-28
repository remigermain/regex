/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_enclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/28 11:35:05 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

t_bool		regex_enclose_do(t_regex *st, char *s1, char *reg, int len)
{
    size_t  match;
    int     i;

	match = 0;
    i = 0;
	while (*(s1 + match) && *(reg + i) && !is_delimiter(st, reg + i, ')'))
    {
        if (regex_parse(st, s1 + match, reg + i))
            match++;
        else
            i += regex_span_enclose(reg + i, "|)");
    }
    if (ret)
        return (regex_parse(st, s1, reg + len));
    return (ret);
}


t_bool  regex_enclosed(t_regex *st, char *s1, char *reg)
{
    t_reg_quan  quantifier;
    int         len;

    ft_bzero(&quantifier, sizeof(t_reg_quan));
	len = regex_span_enclose(reg, ")");
	if (is_quantifier(st, reg + len))    
        len += get_quantifier(&quantifier, reg + len);
    return (regex_enclose_do(st, s1, reg, len));
}