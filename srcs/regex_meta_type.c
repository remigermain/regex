/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   regex_meta_type.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <rgermain@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:48:43 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 18:11:02 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"
#define SET TRUE
#define UNSET FALSE

static void	regex_is_type_made(char alpha[128], t_bool (*func)(int), int mod)
{
	t_bool	ret;
	int		i;

	i = -1;
	while (++i <= 127)
	{
		ret = func(i);
		if (ret == mod)
			alpha[i] = 1;
	}
}

int			regex_is_metatype(char alpha[128], const char *reg)
{
	if (*reg == 'w' || *reg == 'W')
		regex_is_type_made(alpha, ft_isword, UPPER(*reg) ? UNSET : SET);
	else if (*reg == 'd' || *reg == 'D')
		regex_is_type_made(alpha, ft_isdigit, UPPER(*reg) ? UNSET : SET);
	else if (*reg == 's' || *reg == 'S')
		regex_is_type_made(alpha, ft_isspace, UPPER(*reg) ? UNSET : SET);
	else if (*reg == 'p' || *reg == 'P')
		regex_is_type_made(alpha, ft_isalnum, UPPER(*reg) ? UNSET : SET);
	else if (*reg == 'n')
		alpha[(int)('\n')] = SET;
	else if (*reg == 'r')
		alpha[(int)('\r')] = SET;
	else if (*reg == 'e')
		alpha[(int)('\e')] = SET;
	else
		alpha[(int)(*reg)] = SET;
	return (1);
}

static int	regex_is_type2(char alpha[128], const char *reg, int i)
{
	if (!ft_strncmp(reg, ":print:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isprint, SET);
	else if (!ft_strncmp(reg, ":space:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isspace, SET);
	else if (!ft_strncmp(reg, ":upper:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isuppercase, SET);
	else if (!ft_strncmp(reg, ":xdigit:", 8) && (i = 8))
		regex_is_type_made(alpha, ft_isxdigit, SET);
	else if (!ft_strncmp(reg, ":isword:", 8) && (i = 8))
		regex_is_type_made(alpha, ft_isword, SET);
	else
		ft_dprintf(2, "REGEX error regex type %s\n", reg);
	return (i);
}

int			regex_is_type(char alpha[128], const char *reg)
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
	else
		return (regex_is_type2(alpha, reg, i));
	return (i);
}
