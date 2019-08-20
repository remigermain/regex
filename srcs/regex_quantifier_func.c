/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:48:43 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 20:35:56 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

t_bool	regex_star(char c, const char *s1, const char *reg)
{
	while (*s1 && (*s1 == c || c == '.'))
	{
		if (regex_cmp(++s1, reg))
			return (TRUE);
	}
}

t_bool	regex_inter(char c, const char *s1, const char *reg)
{
	if (*s1 == c)
	{
		s1++;
		if (*s1 == c)
			return (FALSE);
	}
	return (regex_cmp(s1, reg));
}

t_bool	regex_plus(char c, const char *s1, const char *reg)
{
	if (*s1 != c)
		return (FALSE);
	while (*s1 && (*s1 == c || c == '.'))
	{
		if (regex_cmp(++s1, reg))
			return (TRUE);
	}
}