/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/28 08:55:44 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

// static t_bool	explode_metachar(const char *reg, const char *mem)
// {
// 	int i;

// 	i = 0;
// 	while (reg - i - 1 >= mem && *(reg - i - 1) == '\\')
// 		i++;
// 	if (i % 2)
// 		return (FALSE);
// 	return (TRUE);
// }

// static int span_explode_metachar(const char *reg, char *meta)
// {
// 	const char *mem;

// 	mem = reg;
// 	while (*reg)
// 	{
// 		if (explode_metachar(reg, mem) && ft_strchr(meta, *reg))
// 			break ;
// 		reg++;
// 	}
// 	return (reg - mem);
// }

// static int		regex_len_line(const char *reg)
// {
// 	const char *mem;
// 	int len;

// 	len = 0;
// 	mem = reg;
// 	while (*reg)
// 	{
// 		if (explode_metachar(reg, mem))
// 		{
// 			if (*reg == '(')
// 				reg += span_explode_metachar(reg, ")");
// 			else
// 			{
// 				if (*reg == '|')
// 					break ;
// 				reg++;
// 			}
// 		}
// 		else
// 			reg++;
// 	}
// 	return (reg - mem);
// }


// static int	regex_explode_len(const char *reg)
// {
// 	const char *mem;
// 	int		len;

// 	len = 1;
// 	mem = reg;
// 	while (*reg)
// 	{
// 		if (explode_metachar(reg, mem))
// 		{
// 			if (*reg == '(')
// 				reg += span_explode_metachar(reg, ")");
// 			else
// 			{
// 				if (*reg == '|')
// 					len++;
// 				reg++;
// 			}
// 		}
// 		else
// 			reg++;
// 	}
// 	return (len);
// }

// char	**regex_explode(const char *reg)
// {
// 	char	**tab;
// 	int		line_len;
// 	int		len;
// 	int		i;

// 	i = -1;
// 	len = regex_explode_len(reg);
// 	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
// 		return (NULL);
// 	while (*reg)
// 	{
// 		line_len = regex_len_line(reg);
// 		if (!(tab[++i] = (char *)ft_memalloc(sizeof(char) * (line_len + 1))))
// 		{
// 			ft_tabdel(&tab);
// 			return (NULL);
// 		}
// 		ft_memcpy(tab[i], reg, sizeof(char) * line_len);
// 		reg += line_len;
// 		if (*reg == '|')
// 			reg++;
// 	}
// 	return (tab);
// }