/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:52:11 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/27 16:03:48 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

void	print_match(t_regex	*reg, char	*s1)
{
	t_regex	*tmp;
	int		i;

	tmp = reg;
	i = 0;
	while (tmp)
	{
		ft_printf("%.*s", tmp->start - i, s1 + i);
		ft_printf(B_BLUE T_BLACK"%.*s" B_WHITE T_WHITE,\
				tmp->end - tmp->start, s1 + tmp->start);
		i = tmp->end;
		tmp = tmp->next;
	}
	if (i < ft_strlen(s1))
		ft_printf("%s", s1 + i);
	ft_printf("\n");
}

int		count_match(t_regex	*reg)
{
	t_regex	*tmp;
	int		i;

	tmp = reg;
	i = 0;
	while (tmp && (++i))
		tmp = tmp->next;
	return (i);
}

t_regex	*add_list(int start, int end)
{
	t_regex	*reg;

	if (!(reg = (t_regex*)ft_memalloc(sizeof(t_regex))))
	{
		ft_dprintf(2, "malloc_error\n");
		exit(0);
	}
	reg->start = start;
	reg->end = end;
	return (reg);
}

void	add_match(t_regex **reg, int start, int end)
{
	t_regex	*tmp;

	tmp = (*reg);
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		(*reg) = add_list(start, end);
	else
		tmp->next = add_list(start, end);
}
