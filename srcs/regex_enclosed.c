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

t_bool		regex_enclose_do(t_regex *st, t_reg_encl *encl,\
											const char *s1, const char *reg)
{
	t_bool ret_max;
	t_bool ret;

	st->befor_do = s1;
	encl->quan.match++;
	ret = verif_quantifier(&(encl->quan), encl->quan.match);
	ret_max = verif_quantifier_max(&(encl->quan), encl->quan.match);
	if (ret && (encl->quan.isset & QUAN_LAZY) &&
			regex_parse(st, s1, reg + encl->len))
		return (TRUE);
	if (s1 != encl->mem && ret_max &&
			regex_enclose_parse(st, encl, s1, reg))
		return (TRUE);
	if (ret && !(encl->quan.isset & QUAN_LAZY) &&
			regex_parse(st, s1, reg + encl->len))
		return (TRUE);
	encl->quan.match--;
	return (FALSE);
}

t_bool		regex_enclose_parse(t_regex *st, t_reg_encl *encl,\
											const char *s1, const char *reg)
{
	t_bool	ret;

	encl->mem = s1;
	encl->mem_last = st->last_s1;
	while (*s1 && *(reg + encl->i) && !is_delimiter(st, reg + encl->i, ")"))
	{
		ret = regex_parse(st, s1, reg + encl->i);
		if ((encl->is_not == TRUE && ret == FALSE) ||
			(encl->is_not == FALSE && ret == TRUE))
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

static int	regex_enclosed_flags(t_regex *st, t_reg_encl *encl, const char *reg)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (*reg == '?' && (++i))
		encl->capture = TRUE;
	if (*(reg + i) == '!' && (++i))
		encl->is_not = TRUE;
	if (*(reg + i) == '<' && (++i))
	{
		while (*(reg + i + j) && *(reg + i + j) != '>')
			j++;
		if (j > 0 && !(encl->name = ft_strsub(reg + i, 0, j)))
			st->error = ERROR_REGEX;
		if (*(reg + i + j) == '>')
			i++;
	}
	return (i + j);
}

t_bool		regex_enclosed(t_regex *st, const char *s1, const char *reg)
{
	t_reg_encl	encl;
	const char	*mem;
	t_bool		ret;

	mem = st->befor_do;
	encl.is_encl = st->is_encl;
	st->is_encl = TRUE;
	ft_bzero(&encl, sizeof(t_reg_encl));
	reg += regex_enclosed_flags(st, &encl, reg);
	encl.len += regex_span_enclose(st, reg);
	if (is_delimiter(st, reg + encl.len, QUANTIFIER))
		encl.len += regex_get_quantifier(&(encl.quan), reg + encl.len);
	ret = regex_enclose_parse(st, &encl, s1, reg);
	if (ret == TRUE && encl.capture == TRUE)
		regex_put_arg(st, s1, encl.quan.match, encl.name);
	else
		ft_strdel(&(encl.name));
	st->befor_do = mem;
	st->is_encl = encl.is_encl;
	return (ret);
}
