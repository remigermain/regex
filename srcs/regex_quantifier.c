/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_quantifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 19:40:48 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

t_bool		verif_quantifier_max(t_reg_quan *quan, int i)
{
	t_bool n;
	t_bool m;

	n = (quan->n >= i ? TRUE : FALSE);
	m = (quan->m >= i ? TRUE : FALSE);
	if (quan->isset & QUAN_EX && n == TRUE)
		return (FALSE);
	else if (quan->isset & QUAN_MAX && m == TRUE)
		return (FALSE);
	else if (quan->isset & QUAN_OR && n == TRUE && m == TRUE)
		return (FALSE);
	else if (quan->isset == 0 && i >= 1)
		return (FALSE);
	return (TRUE);
}

t_bool		verif_quantifier(t_reg_quan *quan, int i)
{
	if (quan->isset & QUAN_EX && quan->n != i)
		return (FALSE);
	else if (quan->isset & QUAN_MIN && quan->n > i)
		return (FALSE);
	else if (quan->isset & QUAN_MAX && quan->m < i)
		return (FALSE);
	else if (quan->isset & QUAN_OR && quan->n != i && quan->m != i)
		return (FALSE);
	else if (quan->isset == 0 && i != 1)
		return (FALSE);
	return (TRUE);
}

t_bool		regex_quantifier_do(t_regex *st, t_reg_quan *quan,
											const char *s1, const char *reg)
{
	int i;

	i = 0;
	while ((quan->isset & QUAN_LAZY) && i <= quan->match)
	{
		if (verif_quantifier(quan, i))
		{
			if (regex_parse(st, s1 + i, reg))
				return (TRUE);
		}
		i++;
	}
	while (!(quan->isset & QUAN_LAZY) && quan->match >= 0)
	{
		if (verif_quantifier(quan, quan->match))
		{
			if (regex_parse(st, s1 + quan->match, reg))
				return (TRUE);
		}
		quan->match--;
	}
	return (FALSE);
}

t_bool		regex_quantifier(t_regex *st, const char *s1, const char *reg)
{
	t_reg_quan	quan;
	char		alpha[128];

	ft_bzero(alpha, sizeof(char) * 128);
	if (!is_metachar(st, reg))
		regex_is_metatype(alpha, reg);
	else
		alpha[(int)(*reg)] = 1;
	reg += regex_get_quantifier(&quan, reg + 1) + 1;
	while (*(s1 + quan.match) && (is_delimiter(st, reg, ".") ||
				alpha[(int)(*(s1 + quan.match))] == 1) && *s1 != '\n')
		quan.match++;
	return (regex_quantifier_do(st, &quan, s1, reg));
}
