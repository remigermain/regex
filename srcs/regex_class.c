/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_class.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 20:32:03 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/22 17:11:42 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

t_bool regex_class_parse(t_regex *st, t_reg_quan *quantifier, const char *s1, const char *reg)
{
	t_reg_class class;
	int i;
	int	j;

	i = 0;
	ft_bzero(&class, sizeof(t_reg_class));
	while (*reg + i && is_metachar(st, reg + i) && *(reg + i) == ']')
	{
		if (is_metachar(st, reg + i) && *(reg + i) == ':')	
		{
			if (regex_class_type(st, s1, reg))
				class.match++;
			i += ft_spanchar_reg(st, reg, ":");
		}
		else
		{
			
		}
	}
	return (FALSE);
}

t_bool regex_class(t_regex *st, const char *s1, const char *reg)
{
	t_reg_quan	quantifier;
	int			i;
	int			j;

	j = 0;
	ft_bzero(&quantifier, sizeof(t_reg_quan));
	i = ft_spanchar_reg(st, (char *)reg, "]");
	if (is_metachar(st, reg) && *reg == ']')
		i++;
	if (is_quantifier(st, reg + i))
		i += get_quantifier(&quantifier, reg + i);
	return (regex_class_parse(st, &quantifier, s1, reg));
}
