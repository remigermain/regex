/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_quantifier_get.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/09 18:17:15 by rgermain         ###   ########.fr       */
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

static int	mini_quantifier(t_reg_quan *quantifier, char *reg)
{
	if (ft_strchr("*+", *reg))
	{
		quantifier->isset |= QUAN_MIN;
		quantifier->number_1 = (*reg == '*' ? 0 : 1);
	}
	else
	{
		quantifier->isset |= QUAN_MAX;
		quantifier->number_2 = 1;
	}
	return (1);
}

int			regex_get_quantifier(t_reg_quan *quantifier, char *reg)
{
	t_bool mod;
	int i;

	i = 0;
	mod = FALSE;
	ft_bzero(quantifier, sizeof(*quantifier));
	if (ft_strchr("*?+", *reg))
		i += mini_quantifier(quantifier, reg);
	else if (*reg)
	{
		i += get_quantifier_number(&quantifier->number_1, &quantifier->isset, QUAN_MIN,  reg + i + 1) + 1;
		if (*(reg + i) == '}')
			quantifier->isset = QUAN_EX;
		else
		{
			mod = ((*reg + i) == ';' ? TRUE : FALSE);
			i += get_quantifier_number(&quantifier->number_2, &quantifier->isset, QUAN_MAX, reg + i + 1) + 1;
		}
		i++;
	}
	if (mod == TRUE)
		quantifier->isset = QUAN_OR;
	if (*(reg + i) == '?')
	{
		quantifier->isset |= QUAN_LAZY;
		i++;
	}
	return (i);
}
