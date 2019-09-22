/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_class.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 20:32:03 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/22 19:24:28 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

int regex_class_parsing(t_regex *st, t_reg_class *class, const char *s1, const char *reg)
{
	int len;

	class->range_min = convert_metachar(st, reg);
	len = convert_metachar_len(st, reg);
	if (is_metachar(st, reg + len) &&  *(reg + len) == '-')
	{
		class->range_max = convert_metachar(st, reg + len + 1);
		len += convert_metachar_len(st, reg + len + 1) + 1;
	}
	else
		class->range_max = class->range_min;
	return (len);
}

t_bool	regex_class_match(t_regex *st, t_reg_class *class, const char *s1, const char *reg)
{
	if (verif_quantifier(&(class->quantifier), ++class->match) && regex_parse(st, s1, reg + class->i))
		return (TRUE);
	return (FALSE);
}

t_bool	regex_class_parse(t_regex *st, t_reg_class *class, const char *s1, const char *reg)
{
	t_bool	ret;
	int i;
	int	j;

	i = class->isset;
	while (*s1 && *reg + i && is_metachar(st, reg + i) && *(reg + i) != ']')
	{
		if (is_metachar(st, reg + i) && *(reg + i) == ':')
		{
			ret = regex_class_type(st, s1, reg + i);
			if (((ret && !class->isset) || (!ret && class->isset & CLASS_NOT)) && (++s1))
			{
				if (regex_class_match(st, class, s1, reg))
					return (TRUE);
				i = class->isset;
			}
			else
				i += regex_span_class_type(st, reg + i);
		}
		else
		{
			ft_printf("lalalalala    %c %c\n", class->range_min, class->range_max);
			i += regex_class_parsing(st, class, s1, reg + i);
			ret = (*s1 >= class->range_min && *s1 <= class->range_max ? TRUE : FALSE);
			if (((ret && !class->isset) || (!ret && class->isset & CLASS_NOT)) && (++s1))
			{
				if (regex_class_match(st, class, s1, reg))
					return (TRUE);
				i = class->isset;
			}
		}
	}
	if (verif_quantifier(&(class->quantifier), class->match))
		return (regex_parse(st, s1, reg + class->i));
	return (FALSE);
}

t_bool regex_class(t_regex *st, const char *s1, const char *reg)
{
	t_reg_class	class;

	ft_bzero(&class, sizeof(t_reg_class));
	if (is_metachar(st, reg + class.i) && *(reg + class.i) == '^')
		class.isset |= CLASS_NOT;
	class.i = ft_spanchar_reg(st, (char *)reg, "]");
	if (is_metachar(st, reg + class.i) && *(reg + class.i) == ']')
		class.i++;
	if (is_quantifier(st, reg + class.i))
		class.i += get_quantifier(&(class.quantifier), reg + class.i);
	ft_printf("class |||||   |%s|\n", reg + class.i);
	return (regex_class_parse(st, &class, s1, reg));
}
