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

int main(int argc, char **argv)
{
	t_regex reg;
	if (argc != 3)
	{
		ft_printf("./prog < string > < regex string >\n");
		exit(0);
	}
	ft_printf("[ STRING ] %s\n", argv[1]);
	ft_printf("[ REGEX  ] %s\n", argv[2]);
	ft_printf("match = %s\n", (regex_cmp(&reg, argv[1], argv[2]) ?  "\033[38;5;326mTRUE" : "\033[1;31mFALSE"));
	return (0);
}
