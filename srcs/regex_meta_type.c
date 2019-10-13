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
#define REG_SET 1
#define REG_UNSET 0

static void	regex_is_type_made(char alpha[128], t_bool (*func)(int), int mod)
{
	t_bool	ret;
	int		i;

	i = -1;
	while (++i <= 127)
	{
		ret = func(i);
		if ((ret == TRUE && mod == REG_SET) ||
			(ret == FALSE && mod == REG_UNSET))
			alpha[i] = 1;
	}
}

int			regex_is_metatype(char alpha[128], const char *reg)
{
	if (*reg == 'w')
		regex_is_type_made(alpha, ft_isword, REG_SET);
	else if (*reg == 'W')
		regex_is_type_made(alpha, ft_isword, REG_UNSET);
	else if (*reg == 'd')
		regex_is_type_made(alpha, ft_isdigit, REG_SET);
	else if (*reg == 'D')
		regex_is_type_made(alpha, ft_isdigit, REG_UNSET);
	else if (*reg == 's')
		regex_is_type_made(alpha, ft_isspace, REG_SET);
	else if (*reg == 'S')
		regex_is_type_made(alpha, ft_isspace, REG_UNSET);
	else if (*reg == 'n')
		alpha[(int)('\n')] = REG_SET;
	else if (*reg == 'r')
		alpha[(int)('\r')] = REG_SET;
	else if (*reg == 'e')
		alpha[(int)('\e')] = REG_SET;
	else
		alpha[(int)(*reg)] = REG_SET;
	return (1);
}

static int	regex_is_type2(char alpha[128], const char *reg, int i)
{
	if (!ft_strncmp(reg, ":print:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isprint, REG_SET);
	else if (!ft_strncmp(reg, ":space:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isspace, REG_SET);
	else if (!ft_strncmp(reg, ":upper:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isuppercase, REG_SET);
	else if (!ft_strncmp(reg, ":xdigit:", 8) && (i = 8))
		regex_is_type_made(alpha, ft_isxdigit, REG_SET);
	else if (!ft_strncmp(reg, ":isword:", 8) && (i = 8))
		regex_is_type_made(alpha, ft_isword, REG_SET);
	return (i);
}

int			regex_is_type(char alpha[128], const char *reg)
{
	int i;

	i = 0;
	if (!ft_strncmp(reg, ":alnum:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isalnum, REG_SET);
	else if (!ft_strncmp(reg, ":alpha:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isalpha, REG_SET);
	else if (!ft_strncmp(reg, ":ascii:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isascii, REG_SET);
	else if (!ft_strncmp(reg, ":blank:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isblank, REG_SET);
	else if (!ft_strncmp(reg, ":cntrl:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_iscntrl, REG_SET);
	else if (!ft_strncmp(reg, ":digit:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isdigit, REG_SET);
	else if (!ft_strncmp(reg, ":graph:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_isgraph, REG_SET);
	else if (!ft_strncmp(reg, ":lower:", 7) && (i = 7))
		regex_is_type_made(alpha, ft_islowercase, REG_SET);
	else
		return (regex_is_type2(alpha, reg, i));
	return (i);
}
