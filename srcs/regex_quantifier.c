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

t_bool		verif_quantifier(t_reg_quan *quan, int i)
{
	if (quan->isset & QUAN_EX && quan->number_1 != i)
		return (FALSE);
	else if (quan->isset & QUAN_MIN && quan->number_1 > i)
		return (FALSE);
	else if (quan->isset & QUAN_MAX && quan->number_2 < i)
		return (FALSE);
	else if (quan->isset & QUAN_OR && quan->number_1 != i
			&& quan->number_2 != i)
		return (FALSE);
	else if (quan->isset ==  0)
		return (i == 1 ? TRUE : FALSE);
	return (TRUE);
}

t_bool		regex_quantifier_do(t_regex *st, t_reg_quan *quantifier,
											const char *s1, const char *reg)
{
	int i;

	i = 0;
	while ((quantifier->isset & QUAN_LAZY) && i <= quantifier->match)
	{
		if (verif_quantifier(quantifier, i))
		{
			if (regex_parse(st, s1 + i, reg))
				return (TRUE);
		}
		i++;
	}
	while (!(quantifier->isset & QUAN_LAZY) && quantifier->match >= 0)
	{
		if (verif_quantifier(quantifier, quantifier->match))
		{
			if (regex_parse(st, s1 + quantifier->match, reg))
				return (TRUE);
		}
		quantifier->match--;
	}
	return (FALSE);
}

t_bool		regex_quantifier(t_regex *st, const char *s1, const char *reg)
{
	t_reg_quan	quantifier;
	char		alpha[128];

	ft_bzero(alpha, sizeof(char) * 128);
	if (!is_metachar(st, reg))
		regex_is_metatype(alpha, reg);
	else
		alpha[(int)(*reg)] = 1;
	reg += regex_get_quantifier(&quantifier, reg + 1) + 1;
	while (*(s1 + quantifier.match) && (is_delimiter(st, reg, ".") ||
				alpha[(int)(*(s1 + quantifier.match))] == 1) && *s1 != '\n')
		quantifier.match++;
	return (regex_quantifier_do(st, &quantifier, s1, reg));
}
