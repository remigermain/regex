/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_is_methode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/27 18:59:26 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

t_bool	is_enclose(t_regex *st, char *reg)
{
	if (*reg && ft_strchr(ENCLOSE, *reg) && is_metachar(st, reg))
		return (TRUE);
	return (FALSE);    
}

t_bool	is_quantifier(t_regex *st, char *reg)
{
	if (*reg && ft_strchr(QUANTIFIER, *reg) && is_metachar(st, reg))
		return (TRUE);
	return (FALSE);
}

t_bool	is_delimiter(t_regex *st, char *reg, char delimiter)
{
	if (*reg && delimiter == *reg && is_metachar(st, reg))
		return (TRUE);
	return (FALSE);
}

void	regex_is_type_made(char alpha[128], t_bool (*func)(int))
{
	int i;

	i = -1;
	while (++i <= 127)
	{
		if (func(i))
			alpha[i] = 1;
	}
}

int	regex_class_is_type(char alpha[128], char *reg)
{
	int i;

	i = 0;
	if (!ft_strncmp(reg, ":alnum:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isalnum);
	else if (!ft_strncmp(reg, ":alpha:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isalpha);
	else if (!ft_strncmp(reg, ":ascii:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isascii);
	else if (!ft_strncmp(reg, ":blank:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isblank);
	else if (!ft_strncmp(reg, ":cntrl:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_iscntrl);
	else if (!ft_strncmp(reg, ":digit:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isdigit);
	else if (!ft_strncmp(reg, ":graph:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isgraph);
	else if (!ft_strncmp(reg, ":lower:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_islowercase);
	else if (!ft_strncmp(reg, ":print:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isprint);
	else if (!ft_strncmp(reg, ":space:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isspace);
	else if (!ft_strncmp(reg, ":upper:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isuppercase);
	else if (!ft_strncmp(reg, ":xdigit:", 8) && (i = 8))
		regex_is_type_made(alpha, ft_isxdigit);
	return (i);
	//    else if (!ft_strncmp(reg, ":punct:", 9))
	//        regex_is_type_made(alpha, ft_ispunct);
}