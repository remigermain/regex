/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_regex_cmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/24 20:23:19 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

t_bool	regex_parse(t_regex *st, char *s1, char *reg)
{
	st->last_s1 = s1;
	if (*reg == '\\' && is_metachar(st, reg))
		reg++;
	if (*reg == '\0')
		return (regex_return(st, TRUE));
	if (is_delimiter(st, reg, '|'))
		return (TRUE);
	if (is_delimiter(st, reg, ')'))
		return (TRUE);
	if (is_delimiter(st, reg, '['))
		return (regex_class(st, s1, ++reg));
	if (is_delimiter(st, reg, '('))
		return (regex_enclosed(st, s1, ++reg));
	if (is_quantifier(st, reg + 1))
		return (regex_quantifier(st, s1, reg));
	if (is_delimiter(st, reg, '$') && *(reg + 1) == '\0')
		return (regex_return(st, (*s1 ? FALSE : TRUE)));
	// need fix for special type
	if (*s1 && ((is_delimiter(st, reg, '.') && *s1 != '\n') || convert_metachar(st, reg) == *s1))
		return (regex_parse(st, ++s1, (reg + convert_metachar_len(st, reg))));
	return (regex_return(st, FALSE));
}

int	ft_regex_cmp(t_regex *st, char *s1, char *reg)
{
	int i;

	ft_bzero(st, sizeof(*st));
	st->s1 = s1;
	st->reg = reg;
	while (*reg)
	{
		if (is_delimiter(st, reg, '^'))
			regex_parse(st, s1, reg + 1);
		else
		{
			i = -1;
			while (*(s1 + ++i))
				regex_parse(st, s1 + i, reg);
		}
		reg += regex_span_or(st, reg);
	}
	regex_cal(st);
	return (st->error || st->match);
}

char	*ft_regex_replace(char *s1, char *reg, char *src, enum e_regex_replace mod)
{
	t_regex st;
	t_bool	ret;
	char	*ptr;

	ret = ft_regex_cmp(&st, s1, reg);
	if (ret == 0)
		return (s1);
	if (ret < 0)
		return (NULL);
	
	return (ptr);
}