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

t_bool	regex_cmp(const char *s1, const char *reg)
{
	if (*reg == '\0')
		return (TRUE);
	if (*reg == '[')
		return (regex_class(s1, ++reg));
	if (*reg == '(')
		return (regex_enclosed(s1, ++reg));
	if (*(reg + 1) == '{')
		return (regex_quantifier(*reg , s1, (reg + 2)));
	if (*(reg + 1) == '*')
		return (regex_star(*reg, s1, reg + 2));
	if (*(reg + 1) == '?')
		return (regex_inter(*reg, s1, reg + 2));
	if (*(reg + 1) == '+')
		return (regex_plus(*reg, s1, reg + 2));
	if (*reg == '$' && *(reg + 1) == '\0')
		return (*s1 ? FALSE : TRUE);
	if (*s1 && (*reg == '.' || *reg == *s1))
		return (regex_cmp(++s1, ++reg));
	return (FALSE);
}

t_bool	match(const char *s1, const char *regex)
{
	if (*regex == '^')
		return (regex_cmp(s1, ++regex));
	while (*s1)
	{
		if (regex_cmp(s1, regex))
			return (TRUE);
		s1++;
	}
	return (FALSE);
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("./prog < string > < regex string >\n");
		exit(0);
	}
	ft_printf("match = %s\n", (match(argv[1], argv[2]) ?  "\033[38;5;326mTRUE" : "\033[1;31mFALSE"));
	return (0);
}
