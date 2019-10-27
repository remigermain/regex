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

/*
**-------------------------------------------------------
**          calcule le nombre de character qui match
**			si le encl->capture est a TRUE
**			alors on le met de coter dans regex_put_arg
**			et on return TRUE
**-------------------------------------------------------
*/

static t_bool	regex_enclose_capt(t_regex *st, t_reg_encl *encl,
																const char *s1)
{
	int	len;

	if (encl->capture)
	{
		len = ft_strlen(s1) - ft_strlen(encl->mem);
		if (len)
			regex_put_arg(st, s1, len, encl->name);
		else if (encl->name)
			ft_strdel(&(encl->name));
	}
	return (TRUE);
}

/*
**-------------------------------------------------------
**         	parse l'enclose   en beta
**-------------------------------------------------------
*/

t_bool		regex_enclose_parse(t_regex *st, t_reg_encl *encl,\
											const char *s1, const char *reg)
{
	while (*(reg + encl->i) && !is_delimiter(st, reg + encl->i, ")"))
	{
		if (encl->is_not != regex_parse(st, s1, reg + encl->i))
		{
			encl->mem = st->last_s1;
			encl->quan.match++;
			encl->ret = verif_quantifier(&(encl->quan), encl->quan.match);
			encl->ret_max = verif_quantifier_max(&(encl->quan), encl->quan.match);
			if (LAZY_QUAN(encl) && encl->ret &&
				regex_parse(st, st->last_s1, reg + encl->len))
				return (regex_enclose_capt(st, encl, s1));
			if (s1 != st->last_s1 && encl->ret_max &&
				regex_enclose_parse(st, encl, st->last_s1, reg))
				return (regex_enclose_capt(st, encl, s1));
			if (!LAZY_QUAN(encl) && encl->ret &&
				regex_parse(st, st->last_s1, reg + encl->len))
				return (regex_enclose_capt(st, encl, s1));
			encl->quan.match--;
		}
		encl->i += regex_span_or(st, reg + encl->i);
	}
	encl->ret = verif_quantifier(&(encl->quan), encl->quan.match);
	if (encl->ret && regex_parse(st, s1, reg + encl->len))
		return (regex_enclose_capt(st, encl, s1));
	return (FALSE);
}

/*
**-------------------------------------------------------
**          parse les flags de l'enclose
**			le ?  signifie le garde en memoire
**			le !  signifie que le paterrne de doit pas matcher
**			le <name> pour capture avec un nomage
**				le ? doit etre set pour que ca fonctionne
**-------------------------------------------------------
*/

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

/*
**-------------------------------------------------------
**          parse les flags de enclose,
**			puis on regarde si il y a un quantifier
**			si on le capture on incremente le level
**			cela va servire pour determiner le niveau
**			de capturation de la regex
**			on parse l'enclose
**			si il na pas puis capture quelque chose
**			et qu'il y avait un nomage <name>
**			on le free
**-------------------------------------------------------
*/

t_bool		regex_enclosed(t_regex *st, const char *s1, const char *reg)
{
	t_reg_encl 	encl;
	t_bool		ret;

	if (REGEX_DEBUG)
		ft_dprintf(2, "[regex_enclosed]\n[s1][%s]\n[reg][%s]\n", s1, reg);
	ft_bzero(&encl, sizeof(t_reg_encl));
	reg += regex_enclosed_flags(st, &encl, reg);
	encl.len += regex_span_enclose(st, reg);
	if (is_delimiter(st, reg + encl.len, QUANTIFIER))
		encl.len += regex_get_quantifier(&(encl.quan), reg + encl.len);
	if (encl.capture)
		st->level++;
	ret = regex_enclose_parse(st, &encl, s1, reg);
	if (ret == FALSE && encl.name)
		ft_strdel(&(encl.name));
	if (encl.capture)
		st->level--;
	return (ret);
}
