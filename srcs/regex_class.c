/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_class.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 20:32:03 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/27 20:11:11 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

t_bool			regex_class_do(t_regex *st, t_reg_class *class, char *s1, char *reg)
{
	t_bool	ret;
	int		i;

	i = -1;
	while (s1[++i])
	{
		ret = class->alpha[s1[i]] ? TRUE : FALSE;
		if ((ret && class->is_not == CLASS_NOT) || 
			(!ret && class->is_not != CLASS_NOT))
			break ;
		class->match++;
	}
	while (class->match >= 0)
	{
		if (verif_quantifier(&(class->quantifier), class->match))
		{
			if (regex_parse(st, s1 + class->match, reg + class->i))
				return (TRUE);
		}
		class->match--;
	}
	return (FALSE);
}

char		*regex_class_parse(t_regex *st, t_reg_class *class, char *s1, char *reg)
{
	int		i;

	while (*reg && (!is_metachar(st, reg) || *reg != ']'))
	{
		i = convert_metachar(st, reg);
		if (is_metachar(st, reg) && i == '[' && (i = -1))
			reg += regex_class_is_type(class->alpha, reg + 1) + 2;
		else
		{
			reg += convert_metachar_len(st, reg);
			class->alpha[i] = 1;
			if (*reg == '-')
			{
				while (i <= convert_metachar(st, reg + 1))
					class->alpha[++i] = 1;
				reg += convert_metachar_len(st, reg + 1) + 1;
			}
		}
	}
	if (*reg != ']')
		regex_error_line(st, reg, ']');
	return (reg + 1);
}

t_bool			regex_class(t_regex *st, char *s1, char *reg)
{
	t_reg_class	class;

	ft_bzero(&class, sizeof(t_reg_class));
	if (is_metachar(st, reg) && *reg == '^')
		class.is_not |= CLASS_NOT;
	reg = regex_class_parse(st, &class, s1, reg);
	if (is_quantifier(st, reg))
		class.i += get_quantifier(&(class.quantifier), reg);
	return (regex_class_do(st, &class, s1, reg));
}
