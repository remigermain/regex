/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   regex_span.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <rgermain@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:48:43 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 18:12:15 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

int		regex_span_quantifier(t_regex *st, const char *reg)
{
	int i;

	i = 0;
	if (is_delimiter(st, reg, QUANTIFIER))
	{
		if (ft_strchr("*?+", *reg))
			i++;
		else
		{
			i += ft_spantype(reg + i + 1, ft_isdigit) + 1;
			if (ft_strchr(",;", *(reg + i)))
				i += ft_spantype(reg + i, ft_isdigit) + 1;
			i++;
		}
		if (*(reg + i) == '?')
			i++;
	}
	return (i);
}

int		regex_span_enclose(t_regex *st, const char *reg)
{
	int i;

	i = 0;
	while (*(reg + i) && !is_delimiter(st, reg + i, ")"))
	{
		if (is_delimiter(st, reg + i, "("))
			i += regex_span_enclose(st, reg + i + 1) + 1;
		else
			i++;
	}
	if (*(reg + i) == ')')
		i++;
	return (i);
}

int		regex_span_or(t_regex *st, const char *reg)
{
	int i;

	i = 0;
	while (*(reg + i) && !is_delimiter(st, reg + i, "|"))
	{
		if (is_delimiter(st, reg + i, "("))
			i += regex_span_enclose(st, reg + i + 1) + 1;
		else
			i++;
	}
	if (*(reg + i) == '|')
		i++;
	return (i);
}

int		regex_span_class(t_regex *st, const char *reg)
{
	int i;

	i = 0;
	while (*(reg + i) && !is_delimiter(st, reg + i, "]"))
		i++;
	if (*(reg + i) == ']')
		i++;
	return (i);
}
