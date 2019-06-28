/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   class.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 20:32:03 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 19:39:35 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

t_bool	ft_strchr_range(t_regex *reg, t_reg_class *class, char *s1)
{
	int	i;

	i = -1;
	while (s1[++i] && s1[i] != class->stop)
	{
		if ((class->flags >> RR_NOT) & 0x1)
		{
			if (!(s1[i] >= class->range1 && s1[i] <= class->range2))
				add_match(&(reg->match), i, i + 1);
		}
		else if (!(s1[i] < class->range1 || s1[i] > class->range2))
			add_match(&(reg->match), i, i + 1);
	}
	return (TRUE);
}

t_bool	ft_strchr_norange(t_regex *reg, t_reg_class *class, char *s1)
{
	int	i;
	int	j;
	int	diff;

	j = -1;
	while (s1[++j] && s1[j] != class->stop)
	{
		diff = 0;
		i = (((class->flags >> RR_NOT) & 0x1) ? 1 : 0);
		while (reg->regex[++i] && reg->regex[i] != ']')
		{
			if (s1[j] == reg->regex[i])
				diff |= 1 << 0;
			else if (s1[j] != reg->regex[i])
				diff |= 1 << 1;
		}
		if ((class->flags >> RR_NOT) & 0x1)
		{
			if (diff == 2)
				add_match(&(reg->match), j, j + 1);
		}
		else if (diff & 0x1)
			add_match(&(reg->match), j, j + 1);
	}
}

void		parse_class(t_regex *reg, t_reg_class *cl)
{
	int	i;

	i = 1;
	cl->range1 = -1;
	cl->range2 = -1;
	while (reg->regex[i] && reg->regex[i] != ']')
	{
		if (reg->regex[i] == R_NOT)
			cl->flags |= (1 << RR_NOT);
		else if (reg->regex[i] == R_OR)
			cl->flags |= (1 << RR_OR);
		else if (reg->regex[i] == R_RANGE)
			cl->flags |= (1 << RR_RANGE);
		else if (cl->range1 == -1)
			cl->range1 = reg->regex[i];
		else if (cl->range2 == -1)
			cl->range2 = reg->regex[i];
		i++;
	}
	if (reg->regex[i] == ']')
		i++;
	reg->end = i;
	cl->stop = reg->regex[i];
}

int			find_class(t_regex *reg, char *s1, int start)
{
	t_reg_class	cl;
	int	i;

	ft_bzero(&cl, sizeof(t_reg_class));
	i = start;
	parse_class(reg, &cl);
	if ((cl.flags >> RR_RANGE) & 0x1)
		return (ft_strchr_range(reg, &cl, s1));
	else
		return (ft_strchr_norange(reg, &cl, s1));
}
