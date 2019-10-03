/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/03 19:22:03 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

int main(int argc, char **argv)
{
	t_regex st;
	if (argc != 3)
	{
		ft_printf("./prog < string > < regex string >\n");
		exit(0);
	}
	int ret = ft_regex_cmp(&st, argv[1], argv[2]);
	if (ret > 0)
		ft_printf("\033[38;5;326mTRUE  %d\n"T_WHITE, ret);
	else if (ret == 0)
		ft_printf("\033[1;31mFALSE  %d\n"T_WHITE, ret);
	else
		ft_printf("\033[1;31mERROR MALLOC %d\n"T_WHITE, ret);	


	if (ret == 0)
	{
		error_line_pos("error parsing", 76, st.pos);
		error_line_e(st.s1, st.pos);
	}
	
	t_reg_capt *list = st.capt;
	while (list != NULL)
	{
		ft_printf("[ >>%s<<  ][%d][%d][%d]\n", list->str, list->pos, list->start, list->end);
		list = list->next;
	}
	ft_regex_free(&st);
	return (0);
}
