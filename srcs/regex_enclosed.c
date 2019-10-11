/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_enclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 17:34:48 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

void			ft_regex_free(t_regex *st)
{
	t_reg_capt *list;
	t_reg_capt *tmp;

	list = st->capt;
	while (list)
	{
		tmp = list;
		list = list->next;
		ft_memdel((void **)&(tmp->str));
		ft_memdel((void **)&tmp);
	}
}

static void		regex_put_arg(t_regex *st, const char *base, const char *match)
{
	static t_reg_capt	*mem = NULL;
	t_reg_capt			*list;
	int					len;

	len = ft_strlen(base);
	len -= ft_strlen(match);
	if (!(list = (t_reg_capt *)ft_memalloc(sizeof(t_reg_capt))) ||
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

t_bool			regex_enclose_parse(t_regex *st, t_reg_encl *encl,\
											const char *s1, const char *reg)
{
	encl->mem = s1;
	encl->mem_last = st->last_s1;
	while (*s1 && *(reg + encl->i) && !is_delimiter(st, reg + encl->i, ")"))
	{
		if (regex_parse(st, s1, reg + encl->i))
		{
			s1 = st->last_s1;

			if (verif_quantifier(&(encl->quan), ++encl->quan.match))
			{
				if ((encl->quan.isset & QUAN_LAZY) && regex_parse(st, s1, reg + encl->len))
					return (TRUE);
				else if (regex_enclose_parse(st, encl, s1, reg))
					return (TRUE);
				else if (!(encl->quan.isset & QUAN_LAZY) && regex_parse(st, s1, reg + encl->len))
					return (TRUE);
			}
			encl->quan.match--;
			s1 = encl->mem;
		}
		encl->i += regex_span_or(st, reg + encl->i);
	}
	s1 = encl->mem;
	st->last_s1 = encl->mem_last;
	return (verif_quantifier(&(encl->quan), encl->quan.match) &&
		regex_parse(st, s1, reg + encl->len));
}

t_bool			regex_enclosed(t_regex *st, const char *s1, const char *reg)
{
	t_reg_encl encl;

	ft_bzero(&encl, sizeof(t_reg_encl));
	if (*reg == '?')
	{
		reg++;
		encl.is_not = TRUE;
	}
	encl.len = regex_span_enclose(st, reg);
	if (is_delimiter(st, reg + encl.len, QUANTIFIER))
		encl.len += regex_get_quantifier(&(encl.quan), reg + encl.len);
	if (regex_enclose_parse(st, &encl, s1, reg))
	{
		if (encl.is_not == FALSE)
			regex_put_arg(st, s1, st->last_s1);
		return (TRUE);
	}
	return (FALSE);

}
