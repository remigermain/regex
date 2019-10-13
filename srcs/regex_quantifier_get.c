/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_quantifier_get.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 18:21:07 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

static int	quantifier_number(int *nb, int *is, int set, const char *reg)
{
	if (*reg)
	{
		*nb = ft_atoi(reg);
		*is |= set;
		return (ft_spantype(reg, ft_isdigit));
	}
	return (0);
}

static int	quantifier_mini(t_reg_quan *quan, const char *reg)
{
	if (ft_strchr("*+", *reg))
	{
		quan->isset |= QUAN_MIN;
		quan->n = (*reg == '*' ? 0 : 1);
	}
	else
	{
		quan->isset |= QUAN_MAX;
		quan->m = 1;
	}
	return (1);
}

static int	quantifier_set(t_reg_quan *quan, const char *reg, int i)
{
	t_bool	mod;

	mod = FALSE;
	i += quantifier_number(&quan->n, &quan->isset, QUAN_MIN, reg + i);
	if (*(reg + i) == '}')
		quan->isset = QUAN_EX;
	else
	{
		mod = (*(reg + i++) == ';' ? TRUE : FALSE);
		i += quantifier_number(&quan->m, &quan->isset, QUAN_MAX, reg + i);
		if (mod == TRUE)
			quan->isset = QUAN_OR;
	}
	return (i + 1);
}

int			regex_get_quantifier(t_reg_quan *quan, const char *reg)
{
	int		i;

	i = 0;
	ft_bzero(quan, sizeof(*quan));
	if (ft_strchr("*?+", *reg))
		i += quantifier_mini(quan, reg);
	else if (*reg)
		i = quantifier_set(quan, reg, i + 1);
	if (*(reg + i) == '?' && (++i))
		quan->isset |= QUAN_LAZY;
	return (i);
}
