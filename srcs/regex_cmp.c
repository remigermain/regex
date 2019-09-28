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
	if (*reg == '\\' && is_metachar(st, reg))
		reg++;
	//ft_printf("[ REGEX_PARSE ]\n|%s| |%s|   %d %d\n\n", s1, reg, *s1, *reg);
	if (*reg == '\0')
		return (regex_return(st, TRUE));
	if (is_delimiter(st, reg, ')') || is_delimiter(st, reg, '|'))
		return (TRUE);
	if (is_delimiter(st, reg, '['))
		return (regex_class(st, s1, ++reg));
	if (is_delimiter(st, reg, '('))
		return (regex_enclosed(st, s1, ++reg));
	if (is_quantifier(st, reg + 1))
		return (regex_quantifier(st, s1, reg));
	if (is_delimiter(st, reg, '$') && *(reg + 1) == '\0')
		return (regex_return(st, (*s1 ? FALSE : TRUE)));
	if (*s1 && ((is_delimiter(st, reg, '.') && *s1 != '\n') || convert_metachar(st, reg) == *s1))
		return (regex_parse(st, ++s1, (reg + convert_metachar_len(st, reg))));
	return (regex_return(st, FALSE));
}

int	ft_regex_cmp(t_regex *st, char *s1, char *regex)
{
	int i;

	st->s1 = s1;
	ft_bzero(st, sizeof(*st));
	while (*regex)
	{
		st->reg = regex;
		if (is_delimiter(st, regex, '^'))
			regex_parse(st, s1, regex + 1);
		else
		{
			i = -1;
			while (*(s1 + ++i))
				regex_parse(st, s1 + i, regex);
		}
		regex += regex_span_enclose(regex, ")");
		if (*regex == '|')
			regex++;
	}
	return (st->match);
}
