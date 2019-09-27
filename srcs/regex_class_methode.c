/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_class_methode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/27 21:16:12 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
# define SET 1
# define UNSET 0

void	regex_is_type_made(char alpha[128], t_bool (*func)(int), int mod)
{
    t_bool  ret;
	int     i;

	i = -1;
	while (++i <= 127)
	{
        ret = func(i);
		if ((ret && mod) || (!ret && !mod))
			alpha[i] = 1;
	}
}

int	regex_class_is_metatype(char alpha[128], char *reg)
{
    int i;

    if (*reg == 'w')
		regex_is_type_made(alpha, ft_isword, SET);
    else if (*reg == 'W')
		regex_is_type_made(alpha, ft_isword, UNSET);
    if (*reg == 'd')
		regex_is_type_made(alpha, ft_isdigit, SET);
    else if (*reg == 'D')
		regex_is_type_made(alpha, ft_isdigit, UNSET);
    else if (*reg == 's')
		regex_is_type_made(alpha, ft_isspace, SET);
    else if (*reg == 'S')
		regex_is_type_made(alpha, ft_isspace, UNSET);
    return (1);
}

int	regex_class_is_type(char alpha[128], char *reg)
{
	int i;

	i = 0;
	if (!ft_strncmp(reg, ":alnum:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isalnum, SET);
	else if (!ft_strncmp(reg, ":alpha:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isalpha, SET);
	else if (!ft_strncmp(reg, ":ascii:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isascii, SET);
	else if (!ft_strncmp(reg, ":blank:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isblank, SET);
	else if (!ft_strncmp(reg, ":cntrl:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_iscntrl, SET);
	else if (!ft_strncmp(reg, ":digit:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isdigit, SET);
	else if (!ft_strncmp(reg, ":graph:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isgraph, SET);
	else if (!ft_strncmp(reg, ":lower:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_islowercase, SET);
	else if (!ft_strncmp(reg, ":print:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isprint, SET);
	else if (!ft_strncmp(reg, ":space:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isspace, SET);
	else if (!ft_strncmp(reg, ":upper:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isuppercase, SET);
	else if (!ft_strncmp(reg, ":xdigit:", 8) && (i = 8))
		regex_is_type_made(alpha, ft_isxdigit, SET);
	return (i);
}