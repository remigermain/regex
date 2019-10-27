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

/*
**-------------------------------------------------------
**		met 1 si la function retourne le meme resulta que mode
**		mod set = TRUE
**		mod unset = FALSE
**		cela sert pour les meta \d ou \D
**		\d doit etre que des digits 0-9
**		\D doit etre tout sauf des digits 0-9
**		si ft_isdigit nous retourne TRUE et que le mod et SET
**		alors on met 1
**		si ft_isdigit nous retourne FALSE et que le mod et UNSET
**		alors on met 1
**-------------------------------------------------------
*/

static void	regex_is_type_made(char alpha[128], t_bool (*func)(int), int mod)
{
	int		i;

	i = -1;
	while (++i <= 127)
	{
		if (mod == func(i))
			alpha[i] = 1;
	}
}

/*
**-------------------------------------------------------
**		perl type regex , qui pass en parametre de regex_is_type
**		la fonction en rapoort avec la string
**		ou set la possition ascci dans alpha
**-------------------------------------------------------
*/

int			regex_is_metatype(t_regex *st, char alpha[128], const char *reg)
{
	t_bool	is_meta;

	is_meta = is_metachar(st, reg) ? FALSE : TRUE;
	if (is_meta && (*reg == 'w' || *reg == 'W'))
		regex_is_type_made(alpha, ft_isword, UPPER(*reg) ? UNSET : SET);
	else if (is_meta && (*reg == 'd' || *reg == 'D'))
		regex_is_type_made(alpha, ft_isdigit, UPPER(*reg) ? UNSET : SET);
	else if (is_meta && (*reg == 's' || *reg == 'S'))
		regex_is_type_made(alpha, ft_isspace, UPPER(*reg) ? UNSET : SET);
	else if (is_meta && (*reg == 'p' || *reg == 'P'))
		regex_is_type_made(alpha, ft_isalnum, UPPER(*reg) ? UNSET : SET);
	else if (is_meta && *reg == 'n')
		alpha[(int)('\n')] = SET;
	else if (is_meta && *reg == 'r')
		alpha[(int)('\r')] = SET;
	else if (is_meta && *reg == 'e')
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

/*
**-------------------------------------------------------
**		posix type regex , qui pass en parametre de regex_is_type
**		la fonction en rapoort avec la string
**-------------------------------------------------------
*/

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
