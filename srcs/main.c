/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:48:43 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/27 15:52:36 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

t_bool	regex_start_string(char *s1, char *regex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
}

t_bool	match_regex(char *s1, char *regex)
{
	t_regex		*reg;

	reg = NULL;
	add_match(&reg, 1, 4);
	add_match(&reg, 6, 7);
	add_match(&reg, 11, 14);
	print_match(reg, s1);
	return (TRUE);
}


t_bool	match(char *s1, char *regex)
{
	int	i;

	i = -1;
	while (s1[++i])
	{
		if (match_regex(s1 + i, regex))
			return (TRUE);
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
