/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:48:43 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 20:35:56 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

t_bool	regex_parse(t_regex *st, const char *s1, const char *reg)
{
	if (is_delimiter(st, (char*)reg, '\\'))
		reg++;
	ft_printf("%c\n", *reg);
	if (*reg == '\0')
		return (TRUE);
	if (is_delimiter(st, (char*)reg, '['))
		return (regex_class(st, s1, ++reg));
	if (is_delimiter(st, (char*)reg, '('))
		return (regex_enclosed(st, s1, ++reg));

	if (ft_strchr("*+?{", *(reg + 1)) && is_delimiter(st, (char*)reg + 1, *(reg + 1)))
		return (char_quantifier(st, *reg, s1, reg + 1));


	if (is_delimiter(st, (char*)reg, '$') && *(reg + 1) == '\0')
		return (*s1 ? FALSE : TRUE);
	if (*s1 && (is_delimiter(st, (char*)reg, '.') || *reg == *s1))
		return (regex_parse(st, ++s1, ++reg));
	return (FALSE);
}

t_bool	regex_cmp(t_regex *st, const char *s1, const char *regex)
{
	ft_bzero(st, sizeof(*st));
	st->reg = regex;
	st->s1 = s1;
	if (is_delimiter(st, (char*)regex, '^'))
		return (regex_parse(st, s1, ++regex));
	while (*s1)
	{
		if (regex_parse(st, s1, regex))
			return (TRUE);
		s1++;
	}
	return (FALSE);
}
