/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 19:40:39 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

t_bool	is_metachar(t_regex *st, const char *reg)
{
	int i;

	i = 0;
	while (reg - i - 1 >= st->reg && *(reg - i - 1) == '\\')
		i++;
	if (i % 2)
		return (FALSE);
	return (TRUE);
}

t_bool	is_delimiter(t_regex *st, const char *reg, char *delimiter)
{
	if (*reg && ft_strchr(delimiter, *reg) && is_metachar(st, reg))
		return (TRUE);
	return (FALSE);
}
