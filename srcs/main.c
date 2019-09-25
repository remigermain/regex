/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/25 17:17:20 by rgermain         ###   ########.fr       */
/*                                                                            */
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
	ft_printf("match = %s\n"T_WHITE, (ft_regex_cmp(&reg, argv[1], argv[2]) ? "\033[38;5;326mTRUE" : "\033[1;31mFALSE"));

	ft_regex_free(&reg);

	regex_explode(argv[2]);
	return (0);
}
