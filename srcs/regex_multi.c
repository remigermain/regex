/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/25 17:57:12 by rgermain         ###   ########.fr       */
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

static int span_explode_metachar(const char *reg, char *meta)
{
	const char *mem;

	mem = reg;
	while (*reg)
	{
		if (explode_metachar(reg, mem) && ft_strchr(meta, *reg))
			break ;
		reg++;
	}
	return (reg - mem);
}

static int		regex_len_line(const char *reg)
{
	const char *mem;
	int len;

	len = 0;
	mem = reg;
	while (*reg)
	{
		ft_printf("[ %s ]\n", reg);
		usleep(10000);
		if (explode_metachar(reg, mem))
		{
			if (*reg == '(')
				reg += span_explode_metachar(reg, ")");
			else
			{
				if (*reg == '|')
					break ;
				reg++;
			}
		}
		else
			reg++;
	}
	ft_printf("FINN [ %s   %lld   ]\n", reg, reg - mem);
	return (reg - mem);
}


static int	regex_explode_len(const char *reg)
{
	const char *mem;
	int		len;

	len = 1;
	mem = reg;
	while (*reg)
	{
		if (explode_metachar(reg, mem))
		{
			if (*reg == '(')
				reg += span_explode_metachar(reg, ")");
			else
			{
				if (*reg == '|')
					len++;
				reg++;
			}
		}
		else
			reg++;
	}
	return (len);
}

char	**regex_explode(const char *reg)
{
	char	**tab;
	int		line_len;
	int		len;
	int		i;

	i = -1;
	len = regex_explode_len(reg);
	ft_printf("len = %d\n", len);
	//return (NULL);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		return (NULL);
	while (*reg)
	{
		line_len = regex_len_line(reg);
		ft_printf("[ len = %d ]\n", line_len);
		if (!(tab[++i] = (char *)ft_memalloc(sizeof(char) * (line_len + 1))))
		{
			ft_tabdel(&tab);
			return (NULL);
		}
		ft_memcpy(tab[i], reg, sizeof(char) * line_len);
		//ft_printf("len = %d\n", line_len);
		reg += line_len;
		if (*reg == '|')
			reg++;
	}
	//ft_print_memory(tab[0], ft_strlen(tab[0]), MEM_ASCII | MEM_SP);
	ft_printf("\n\n[ TAB ]\n");
	ft_printtab(tab);
	ft_printf("len first = %d\n", ft_strlen(tab[0]));
	return (tab);
}