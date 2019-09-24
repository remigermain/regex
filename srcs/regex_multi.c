/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/24 21:48:34 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

static t_bool	explode_metachar(const char *reg, const char *mem)
{
	int i;

	i = 0;
	while (reg - i - 1 >= mem && *(reg - i - 1) == '\\')
		i++;
	if (i % 2)
		return (FALSE);
	return (TRUE);
}

static int		regex_len_line(const char *reg)
{
	int len;

	len = 0;
	return (len);
}

static int	regex_explode_len(const char *reg)
{
	t_bool	meta;
	const char *mem;
	int		len;

	meta = 0;
	mem = reg;
	while (*reg)
	{
		if (!explode_metachar(reg, mem) || *reg != '\\')
			len++;
	}

	len = 0;
	return (len);
}

char	**regex_explode(const char *reg)
{
	char	**tab;
	int		line_len;
	int		len;
	int		i;

	len = regex_explode_len(reg);
	ft_printf("len = %d\n", len);
	return (NULL);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * len)))
		return (NULL);
	while (*reg)
	{
		line_len = regex_len_line(reg);
		if (!(tab = (char *)ft_memalloc(sizeof(char) * line_len)))
		{
			ft_tabdel(&tab);
			return (NULL);
		}
		ft_strncpy(tab[i++], reg, line_len);
		reg += line_len;
	}
	return (tab);
}