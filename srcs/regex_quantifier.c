/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_quantifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/27 20:45:19 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

t_bool		regex_quantifier_do(t_regex *st, t_reg_quan *quantifier, char *s1, char *reg)
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

t_bool		regex_quantifier(t_regex *st, char *s1, char *reg)
{
	t_reg_quan	quantifier;
	t_bool		is_meta;
	int			c;

	c = *reg;
	is_meta = is_metachar(st, reg++);
	reg += get_quantifier(&quantifier, reg);
	while (*(s1 + quantifier.match) &&
		(c == *(s1 + quantifier.match) || (is_meta && c == '.')))
		quantifier.match++;
	return (regex_quantifier_do(st, &quantifier, s1, reg));
}
