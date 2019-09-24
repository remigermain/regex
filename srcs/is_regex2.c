/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_regex2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/24 20:02:16 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

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
		//	else
		//		len += ft_intlen_base(ft_atoi_base(reg, 8), 8);
		}
		//else if (ft_isdigit(*reg))
		//	len = ft_intlen(ft_atoi_base(reg, 10));
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
		//	else
		//		c = ft_atoi_base(reg + 1, 8);
		}
		//else if (ft_isdigit(*reg))
		//	c = ft_atoi_base(reg, 10);
	}
	return (c);
}