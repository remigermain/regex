/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:52:11 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 20:37:34 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

t_bool	is_noregex(char	c)
{
	int		i;

	i = 0;
	if (c == END_STRING || c == START_STRING || c == R_CLASS_O ||
		c == R_CLASS_C || c == R_QUAN_O || c == R_QUAN_C || c == R_COMMA ||
		c == R_STAR ||c == R_RANGE ||c == R_OR)
		return (FALSE);
	return (TRUE);
}

void	print_match(t_match	*reg, char	*s1)
{
	t_match	*tmp;
	static	int	nb = 0;
	char	*match;
	int		len;
	int		i;

	len = ft_strlen(s1);
	tmp = reg;
	i = 0;
	ft_printf("match = %d\n", nb++);
	if (!(match = (char*)ft_memalloc(ft_strlen(s1))))
		error_regex();
	while (tmp)
	{
		i = tmp->start;
		while (i < tmp->end)
			match[i++] = 1;
		tmp = tmp->next;
	}
	i = 0;
	while (s1[i])
	{
		if (match[i])
			ft_printf(B_BLUE T_BLACK);
		ft_printf("%c", s1[i]);
		if (match[i])
			ft_printf(T_WHITE);
		i++;
	}
	ft_printf("\n");
}

int		count_match(t_match	*reg)
{
	t_match	*tmp;
	int		i;

	tmp = reg;
	i = 0;
	while (tmp && (++i))
		tmp = tmp->next;
	return (i);
}

t_match	*add_list(int start, int end)
{
	t_match	*reg;

	if (!(reg = (t_match*)ft_memalloc(sizeof(t_match))))
	{
		ft_dprintf(2, "malloc_error\n");
		exit(0);
	}
	reg->start = start;
	reg->end = end;
	return (reg);
}

void	add_match(t_match **reg, int start, int end)
{
	t_match	*tmp;

	tmp = (*reg);
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		(*reg) = add_list(start, end);
	else
		tmp->next = add_list(start, end);
}
