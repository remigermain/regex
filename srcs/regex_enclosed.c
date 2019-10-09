/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_enclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/09 18:29:32 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

void	ft_regex_free(t_regex *st)
{
	t_reg_capt	*list;
	t_reg_capt	*tmp;

	list = st->capt;
	while (list)
	{
		tmp = list;
		list = list->next;
		ft_memdel((void**)&(tmp->str));
		ft_memdel((void**)&tmp);
	}
}

static void        regex_put_arg(t_regex *st, char *base, char *match)
{
    static t_reg_capt   *mem = NULL;
    t_reg_capt          *list;
    int                 len;
    
    len = ft_strlen(base);
    len -= ft_strlen(match);
    if (!(list = (t_reg_capt*)ft_memalloc(sizeof(t_reg_capt))) ||
        (!(list->str = ft_strsub(base, 0, len))))
    {
	    st->error = ERROR_REGEX;
        return ;
    }
    list->pos = st->nb_capt++;
    list->start = ft_strlen(st->s1) - ft_strlen(base);
    list->end = ft_strlen(st->s1) - ft_strlen(match);
    if (st->capt == NULL)
    {
        st->capt = list;
        mem = list;
    }
    else
    {
        mem->next = list;
        mem = list;
    }
}

t_bool		regex_enclose_parse(t_regex *st, t_reg_encl *encl, char *s1, char *reg)
{
    char    *mem_last;
    char    *mem;
    int     i;

    i = 0;
    mem = s1;
    mem_last = st->last_s1;
	while (*s1 && *(reg + i) && !is_delimiter(st, reg + i, ")"))
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
    st->last_s1 = mem_last;
    if (verif_quantifier(&(encl->quan), encl->quan.match) &&
        regex_parse(st, s1, reg + encl->len))
        return (TRUE);
    return (FALSE);
}


t_bool  regex_enclosed(t_regex *st, char *s1, char *reg)
{
    t_reg_encl  encl;

    ft_bzero(&encl, sizeof(t_reg_encl));
    if (*reg == '?')
    {
        reg++;
        encl.is_not = TRUE;
    }
	encl.len = regex_span_enclose(st, reg);
	if (is_delimiter(st, reg + encl.len, QUANTIFIER))    
        encl.len += regex_get_quantifier(&(encl.quan), reg + encl.len);
    return (regex_enclose_parse(st, &encl, s1, reg));
}