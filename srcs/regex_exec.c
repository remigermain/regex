/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:11:21 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 19:32:26 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

static t_bool	regex_same_char(t_regex *st, const char *s1, const char *reg)
{
	char	alpha[128];

	if (*s1)
	{
		ft_bzero(alpha, sizeof(char) * 128);
		if (!is_metachar(st, reg))
			regex_is_metatype(alpha, reg);
		else
			alpha[(int)(*reg)] = 1;
		if ((is_delimiter(st, reg, ".") || alpha[(int)(*s1)] == 1))
		{
			reg += convert_metachar_len(st, reg);
			return (regex_parse(st, ++s1, reg));
		}
	}
	return (FALSE);
}

t_bool			regex_parse(t_regex *st, const char *s1, const char *reg)
{
	st->last_s1 = s1;
	if (is_delimiter(st, reg, "\\"))
		reg++;
	if (*reg == '\0' && (++st->match))
		return (TRUE);
	if (is_delimiter(st, reg, "|"))
		return (TRUE);
	if (is_delimiter(st, reg, ")"))
		return (TRUE);
	if (is_delimiter(st, reg, "["))
		return (regex_class(st, s1, ++reg));
	if (is_delimiter(st, reg, "("))
		return (regex_enclosed(st, s1, ++reg));
	if (is_delimiter(st, reg + 1, QUANTIFIER))
		return (regex_quantifier(st, s1, reg));
	if (is_delimiter(st, reg, "$") && *(reg + 1) == '\0')
	{
		if (*s1 == '\0' && (++st->match))
			return (TRUE);
		return (FALSE);
	}
	return (regex_same_char(st, s1, reg));
}

int				ft_regex_exec(t_regex *st, const char *s1, const char *reg)
{
	int i;

	ft_bzero(st, sizeof(*st));
	st->s1 = s1;
	while (*reg)
	{
		st->reg = reg;
		if (is_delimiter(st, reg, "^"))
			regex_parse(st, s1, reg + 1);
		else
		{
			i = -1;
			while (*(s1 + i))
				regex_parse(st, s1 + ++i, reg);
		}
		reg += regex_span_or(st, reg);
	}
	st->pos = ft_strlen(st->s1) - ft_strlen(st->last_s1);
	return (st->error || st->match);
}
