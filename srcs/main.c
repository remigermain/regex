/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/09 18:48:48 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

void	t(char **argv)
{
	int ret = 0;
	t_regex st;
	ft_printf("[ MATCH ]\n");
	ft_printf("[ S1  >>%s<< ]\n", argv[1]);
	ft_printf("[ REG  >>%s<< ]\n", argv[2]);

	ret = ft_regex_cmp(&st, argv[1], argv[2]);
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

}

void	r(char **argv)
{
	ft_printf("[ REPLACE ]\n");
	char *ptr = ft_regex_replace(argv[1], argv[2], argv[3], 1 << ft_atoi(argv[4]));
	ft_printf("[BF %s ]\n", argv[1]);
	ft_printf("[AF %s ]\n", ptr);
}

int main(int argc, char **argv)
{
	t(argv);
	//r(argv);
	return (0);
}
