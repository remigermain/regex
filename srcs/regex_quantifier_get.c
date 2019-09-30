/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_quantifier_get.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/30 17:32:52 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

static int  get_quantifier_number(int *number, int *isset , int set, char *reg)
{
	if (*reg)
	{
		*number = ft_atoi(reg);
		*isset |= set;
		return (ft_spantype(reg, ft_isdigit));
	}
	return (0);
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

int			regex_get_quantifier(t_reg_quan *st, char *reg)
{
	int i;

	i = 0;
	ft_bzero(st, sizeof(*st));
	if (ft_strchr("*?+", *reg))
		i += mini_quantifier(st, reg);
	else if (*reg)
	{
		i += get_quantifier_number(&st->number_1, &st->isset, QUAN_MIN,  reg + i + 1) + 1;
		if (*(reg + i) != ',')
			st->isset = QUAN_EX;
		else
			i += get_quantifier_number(&st->number_2, &st->isset, QUAN_MAX, reg + i + 1) + 1;
		if (*(reg + i) != '}')
			regex_error_line(NULL, reg + i, '}');
		i++;
	}
	if (*(reg + i) == '?')
	{
		st->isset |= QUAN_LAZY;
		i++;
	}
	return (i);
}
