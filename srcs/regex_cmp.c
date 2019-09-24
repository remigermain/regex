/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_cmp.c                                        :+:      :+:    :+:   */
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

	ft_printf("[ REGEX_PARSE ]\n|%s| |%s|   %d %d\n\n", s1, reg, *s1, *reg);
	if (*reg == '\0')
		return (TRUE);

	if (is_delimiter(st, reg, '['))							// class FUNCTION
		return (regex_class(st, s1, ++reg));

	if (is_delimiter(st, reg, '('))							// enclosesur FUNCTION
		return (regex_enclosed(st, s1, ++reg));
	
	if (is_quantifier(st, reg + 1))								// quantifier
		return (regex_quantifier(st, s1, reg));

	if (is_delimiter(st, reg, '$') && *(reg + 1) == '\0') 		// end string
		return (*s1 ? FALSE : TRUE);

	if (*s1 && (is_delimiter(st, reg, '.') || convert_metachar(st, reg) == *s1))
		return (regex_parse(st, ++s1, (reg + convert_metachar_len(st, reg))));   // same character
	return (FALSE);
}

t_bool	regex_cmp(t_regex *st, char *s1, char *regex)
{
	ft_bzero(st, sizeof(*st));
	st->reg = regex;
	st->s1 = s1;
	if (is_delimiter(st, (char *)regex, '^'))
		return (regex_parse(st, s1, ++regex));
	while (*s1)
	{
		if (regex_parse(st, s1, regex))
			return (TRUE);
		s1++;
	}
	return (FALSE);
}
