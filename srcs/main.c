/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/01 19:17:52 by rgermain         ###   ########.fr       */
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
	//ft_printf("[ STRING ] %s\n", argv[1]);
	//ft_printf("[ REGEX  ] %s\n", argv[2]);
	int ret = ft_regex_cmp(&reg, argv[1], argv[2]);
	ft_printf("match = %s  [ % d ] \n"T_WHITE, (ret ? "\033[38;5;326mTRUE" : "\033[1;31mFALSE"), ret);

	t_reg_capt *list = reg.capt;
	while (list != NULL)
	{
		ft_printf("[ >>%s<<  ][%d][%d][%d]\n", list->str, list->pos, list->start, list->end);
		list = list->next;
	}
	ft_regex_free(&reg);

//
	//ft_regex_free(&reg);

	return (0);
}
