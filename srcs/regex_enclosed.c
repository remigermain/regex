/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_enclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 19:40:31 by rgermain         ###   ########.fr       */
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
		if (tmp->name)
			ft_memdel((void **)&(tmp->name));
		ft_memdel((void **)&tmp);
	}
}

static void		regex_put_capt(t_regex *st, t_reg_capt *new)
{
	t_reg_capt	*lst;
	t_reg_capt	*mem;

	lst = st->capt;
	mem = NULL;
	while (lst && lst->start < new->start)
	{
		mem = lst;
		lst = lst->next;
	}
	new->next = lst;
	if (mem)
		mem->next = new;
	else
		st->capt = new;
}

t_bool			exist_capt(t_regex *st, int start, int end)
{
	t_reg_capt	*lst;

	lst = st->capt;
	while (lst)
	{
		if (lst->start == start && lst->end == end)
			return (TRUE);
		lst = lst->next;
	}
	return (FALSE);
}

static void		regex_put_arg(t_regex *st, const char *base, const char *match, char *name)
{
	t_reg_capt			*list;
	int					len;

	ft_printf("base = %s\n", base);
	ft_printf("match = %s\n", match);
	len = ft_strlen(base);
	len -= ft_strlen(match);
	if (len <= 0 || exist_capt(st, ft_strlen(st->s1) - ft_strlen(base),
							   ft_strlen(st->s1) - ft_strlen(match)))
		return ;
	if (!(list = (t_reg_capt *)ft_memalloc(sizeof(t_reg_capt))) ||
		(!(list->str = ft_strsub(base, 0, len))))
	{
		st->error = ERROR_REGEX;
		return ;
	}
	if (name && !(list->name = ft_strdup(name)))
		st->error = ERROR_REGEX;
	list->start = ft_strlen(st->s1) - ft_strlen(base);
	list->end = ft_strlen(st->s1) - ft_strlen(match);
	regex_put_capt(st, list);
}
t_bool		verif_quantifier_max(t_reg_quan *quan, int i)
{
	if (quan->isset & QUAN_EX && quan->number_1 >= i)
		return (FALSE);
	else if (quan->isset & QUAN_MAX && quan->number_2 >= i)
		return (FALSE);
	else if (quan->isset & QUAN_OR && quan->number_1 >= i && quan->number_2 >= i)
		return (FALSE);
	else if (quan->isset == 0)
		return (i >= 1 ? FALSE : TRUE);
	return (TRUE);
}

t_bool			regex_enclose_do(t_regex *st, t_reg_encl *encl,\
											const char *s1, const char *reg)
{
	st->befor_do = s1;
	encl->quan.match++;
	if (verif_quantifier(&(encl->quan), encl->quan.match) &&
			(encl->quan.isset & QUAN_LAZY) && regex_parse(st, s1, reg + encl->len))
		return (TRUE);
	else if (s1 != encl->mem && verif_quantifier_max(&(encl->quan), encl->quan.match) && regex_enclose_parse(st, encl, s1, reg))
		return (TRUE);
	else if (verif_quantifier(&(encl->quan), encl->quan.match) &&
			!(encl->quan.isset & QUAN_LAZY) && regex_parse(st, s1, reg + encl->len))
		return (TRUE);
	encl->quan.match--;
	return (FALSE);
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
			if (regex_enclose_do(st, encl, s1, reg))
				return (TRUE);
			s1 = encl->mem;
		}
		encl->i += regex_span_or(st, reg + encl->i);
	}
	s1 = encl->mem;
	st->last_s1 = encl->mem_last;
	if (st->befor_do == NULL)
		st->befor_do = st->s1;
	return (verif_quantifier(&(encl->quan), encl->quan.match) &&
		regex_parse(st, s1, reg + encl->len));
}

int				regex_enclose_get_name(t_regex *st, t_reg_encl *encl, const char *reg)
{
	int i;

	i = -1;
	while (*(reg + i) && *(reg + i) != '>')
		i++;
	if (i > 0)
	{
		if (!(encl->name = ft_strsub(reg, 0, i)))
			st->error = ERROR_REGEX;
	}
	if (*(reg + i) == '>')
		i++;
	return (i);
}

t_bool			regex_enclosed(t_regex *st, const char *s1, const char *reg)
{
	t_reg_encl	encl;
	const char	*mem;

	mem = st->befor_do;
	ft_bzero(&encl, sizeof(t_reg_encl));
	if (*reg == '?')
	{
		reg++;
		encl.is_not = TRUE;
	}
	if (*reg == '<')
		reg += regex_enclose_get_name(st, &encl, reg + 1) + 1;
	encl.len += regex_span_enclose(st, reg);
	if (is_delimiter(st, reg + encl.len, QUANTIFIER))
		encl.len += regex_get_quantifier(&(encl.quan), reg + encl.len);
	if (regex_enclose_parse(st, &encl, s1, reg))
	{
		if (encl.is_not == FALSE)
			regex_put_arg(st, s1, st->befor_do, encl.name);
		st->befor_do = mem;
		ft_strdel(&(encl.name));
		return (TRUE);
	}
	ft_strdel(&(encl.name));
	st->befor_do = mem;
	return (FALSE);
}
