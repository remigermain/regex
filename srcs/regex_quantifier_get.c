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

/*
**-------------------------------------------------------
**		va set le mini quantifier
**		*	equivaut a {0,}
**		+	equivaut a {1,}
**		?	equivaut a {,1}
**-------------------------------------------------------
*/

static int	quantifier_mini(t_reg_quan *quan, const char *reg)
{
	if (*reg == '*')
	{
		quan->isset |= QUAN_MIN;
		quan->n = 0;
	}
	else if (*reg == '+')
	{
		quan->isset |= QUAN_MIN;
		quan->n = 1;
	}
	else
	{
		quan->isset |= QUAN_MAX;
		quan->m = 1;
	}
	return (1);
}

/*
**-------------------------------------------------------
**		va set quantifier classic {m, n}
**		on recupere le premiers nombre m et on set le QUAN_MIN
**		si apres ce nombre il y a la fin du  quantifier }
**		cela veut quil doit etre egale a ce nombre
**		ex :  bonjour{5} le r devra etre egale au nombre de 5
**		si ce n'est pas la fin, on recupere le second nombre
**		et on set le QUAN_MAX
**
**		ex :  bonjour{5,9}
**				quan->isset vaudra QUAN_MIN et QUAN_MAX
**				m = 5 et n = 9
**
**		si en entre le min et le max il n'y a pas de virgule
**		et qu'il y a un point vigule cela veut dire qu'il
**		doit etre soit m soit n
**		ex : bonjour{5;9}
**				quan->isset vaudra QUAN_EQ
**				m = 5 et n = 9
**-------------------------------------------------------
*/

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

/*
**-------------------------------------------------------
**		va determiner le quantifier
**		si il sont les mini quantifier *+?
**		on apelle le mini sinon {m,n}
**		on verifie si le quantifier est lazy ?
**		et on renvoie le nombre de charactere qui sont des quantifiers
**		ex:  bonjour+  return 1  pour le +
**			 bonjour+?  return 2  pour le +?
**			 bonjour{55,99}  return 7  pour le {55,99}
**				
**-------------------------------------------------------
*/

int			regex_get_quantifier(t_reg_quan *quan, const char *reg)
{
	int		i;

	i = 0;
	ft_bzero(quan, sizeof(*quan));
	if (ft_strchr("*+?", *reg))
		i += quantifier_mini(quan, reg);
	else if (*reg)
		i = quantifier_set(quan, reg, i + 1);
	if (*(reg + i) == '?' && (++i))
		quan->isset |= QUAN_LAZY;
	return (i);
}
