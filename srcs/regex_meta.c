/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/27 21:15:03 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

t_bool is_metachar(t_regex *st, char *reg)
{
	int i;

	i = 0;
	while (reg - i - 1 >= st->reg && *(reg - i - 1) == '\\')
		i++;
	if (i % 2)
		return (FALSE);
	return (TRUE);
}

int convert_metachar_len(t_regex *st, char *reg)
{
	int len;

	len = 1;
	if (*reg == '\\' && is_metachar(st, reg))
		len++;
	if (*reg && !is_metachar(st, reg))
	{
		if (*reg == '0')
		{
			if (ft_tolower(*(reg + 1)) == 'x')
				len += 1 + ft_intlen_base(ft_atoi_base(reg + 2, 16), 16);
			else if (ft_tolower(*(reg + 1)) == 'b')
				len += 1 + ft_intlen_base(ft_atoi_base(reg + 2, 2), 2);
		}
	}
	return (len);
}

int convert_metachar(t_regex *st, char *reg)
{
	int c;

	if (*reg == '\\' && is_metachar(st, reg))
		reg++;
	c = *reg;
	if (*reg && !is_metachar(st, reg))
	{
		if (*reg == 'n')
			c = '\n';
		else if (*reg == 't')
			c = '\t';
		else if (*reg == 'v')
			c = '\v';
		else if (*reg == '0')
		{
			if (ft_tolower(*(reg + 1)) == 'x')
				c = ft_atoi_base(reg + 2, 16);
			else if (ft_tolower(*(reg + 1)) == 'b')
				c = ft_atoi_base(reg + 2, 2);
		}
	}
	return (c);
}