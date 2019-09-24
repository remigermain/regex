/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_get_quantifier.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/24 20:36:53 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

t_bool verif_quantifier(t_reg_quan *quan, int i)
{
	if (quan->isset & QUAN_EX && quan->number_1 != i)
		return (FALSE);
	else if (quan->isset & QUAN_MIN && quan->number_1 > i)
		return (FALSE);
	else if (quan->isset & QUAN_MAX && quan->number_2 < i)
		return (FALSE);
	else if (quan->isset == 0)
		return (i == 1 ? TRUE : FALSE);
	return (TRUE);
}

static int  get_quantifier_number(int *number, int *isset , int set, char *reg)
{
	int i;

	i = 0;
	if (*reg && *reg != ',' && *reg != '}')
	{
		*number = ft_atoi(reg);
		*isset |= set;
		i += ft_spantype(reg, ft_isdigit);
	}
	return (i);
}

static int	mini_quantifier(t_reg_quan *st, char *reg)
{
	if (ft_strchr("*+", *reg))
	{
		st->isset |= QUAN_MIN;
		st->number_1 = (*reg == '*' ? 0 : 1);
	}
	else
	{
		st->isset |= QUAN_MAX;
		st->number_2 = 1;
	}
	return (1);
}

int			get_quantifier(t_reg_quan *st, char *reg)
{
	int i;

	i = 1;
	ft_bzero(st, sizeof(*st));
	if (ft_strchr("*?+", *reg))
		return (mini_quantifier(st, reg));
	i += get_quantifier_number(&st->number_1, &st->isset, QUAN_MIN,  reg + i);
	i += ft_spantype(reg + i, ft_isspace);
	if (*(reg + i) != ',')
		st->isset = QUAN_EX;
	else
	{
		i += get_quantifier_number(&st->number_2, &st->isset, QUAN_MAX, reg + i + 1) + 1;
		i += ft_spantype(reg + i, ft_isspace);
	}
	return (i + 1);
}

t_bool		regex_quantifier(t_regex *st, char *s1, char *reg)
{
	t_reg_quan quantifier;
	t_bool is_meta;
	int match;
	int c;

	match = 0;
	c = *reg;
	is_meta = is_metachar(st, reg++);
	reg += get_quantifier(&quantifier, reg);
	while (*s1)
	{
		if ((c == *s1 || (is_meta && c == '.')) && (++s1))
		{
			if (verif_quantifier(&quantifier, ++match))
			{
				if (regex_parse(st, s1, reg))
					return (TRUE);
			}
		}
		else
			break;
	}
	return (FALSE);
}
