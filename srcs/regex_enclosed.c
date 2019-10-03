/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_enclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/03 18:44:11 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

t_bool		regex_enclose_parse(t_regex *st, t_reg_encl *encl, char *s1, char *reg)
{
    char    *mem;
    int     i;

    i = 0;
    mem = s1;
	while (*s1 && *(reg + i) && !is_delimiter(st, reg + i, ')'))
    {
        if (regex_parse(st, s1, reg + i))
        {
            s1 = st->last_s1;
            if (encl->is_not == FALSE)
                regex_put_arg(st, mem, st->last_s1);
            if ((verif_quantifier(&(encl->quan), ++encl->quan.match) &&
                regex_parse(st, s1, reg + encl->len)) || 
                regex_enclose_parse(st, encl, s1, reg))
                return (TRUE);
            encl->quan.match--;            
            s1 = mem;
        }
        i += regex_span_or(st, reg + i);
    }
    s1 = mem;
    if (verif_quantifier(&(encl->quan), encl->quan.match) &&
        regex_parse(st, s1, reg + encl->len))
        return (TRUE);
    return (FALSE);
}


t_bool  regex_enclosed(t_regex *st, char *s1, char *reg)
{
    t_reg_encl  encl;

    ft_bzero(&encl, sizeof(t_reg_encl));
    ft_printf("[REG  %s ]\n", reg);
    if (*reg == '?')
    {
        ft_printf("HERRE\n");
        reg++;
        encl.is_not = TRUE;
    }
	encl.len = regex_span_enclose(st, reg);
	if (is_quantifier(st, reg + encl.len))    
        encl.len += regex_get_quantifier(&(encl.quan), reg + encl.len);
    return (regex_enclose_parse(st, &encl, s1, reg));
}