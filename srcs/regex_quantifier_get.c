/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_quantifier_get.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 17:33:40 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

static int	get_quantifier_number(int *nb, int *is, int set, const char *reg)
{
	if (*reg)
	{
		*nb = ft_atoi(reg);
		*is |= set;
		return (ft_spantype(reg, ft_isdigit));
	}
	return (0);
}

static int	mini_quantifier(t_reg_quan *quantifier, const char *reg)
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

static int	regex_get_quantifier_set(t_reg_quan *quantifier, const char *reg,
														int i, t_bool *mod)
{
	i += get_quantifier_number(&quantifier->number_1, &quantifier->isset,
													QUAN_MIN, reg + i + 1) + 1;
	if (*(reg + i) == '}')
		quantifier->isset = QUAN_EX;
	else
	{
		*mod = (*(reg + i) == ';' ? TRUE : FALSE);
		i += get_quantifier_number(&quantifier->number_2, &quantifier->isset,
													QUAN_MAX, reg + i + 1) + 1;
	}
	return (i + 1);
}

int			regex_get_quantifier(t_reg_quan *quantifier, const char *reg)
{
	t_bool	mod;
	int		i;

	i = 0;
	mod = FALSE;
	ft_bzero(quantifier, sizeof(*quantifier));
	if (ft_strchr("*?+", *reg))
		i += mini_quantifier(quantifier, reg);
	else if (*reg)
		i = regex_get_quantifier_set(quantifier, reg, i, &mod);
	if (mod == TRUE)
		quantifier->isset = QUAN_OR;
	if (*(reg + i) == '?')
	{
		quantifier->isset |= QUAN_LAZY;
		i++;
	}
	return (i);
}
