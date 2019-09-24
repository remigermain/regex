/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_class.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 20:32:03 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/24 18:38:19 by rgermain         ###   ########.fr       */
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

t_bool	regex_class_line(int isset, t_bool ret, t_bool line_class)
{
	if (!isset && ret)
		line_class = TRUE;
	else if (isset && ret)
		line_class = FALSE;
	return (line_class);
}

t_bool	regex_class_parse(t_regex *st, t_reg_class *class, const char *s1, const char *reg)
{
	t_bool	line_class;
	t_bool	ret;
	int i;
	int	j;

	while (*s1 != '\0')
	{
		line_class = FALSE;
		i = class->isset;
		while (*s1 && *(reg + i) && (!is_metachar(st, reg + i) || *(reg + i) != ']'))
		{
			if (is_metachar(st, reg + i) && *(reg + i) == '\\')
				i++;
			else if (is_metachar(st, reg + i) && *(reg + i) == ':')
			{
				ft_printf("[ REG ] %s\n", reg + i);
				ret = regex_class_type(st, s1, reg + i);
				line_class = regex_class_line(class->isset, ret, line_class);
				i += regex_span_class_type(st, reg + i);
			}
			else
			{
				ft_printf("[ REG CHAR ] %c\n", *(reg + i));
				i += regex_class_parsing(st, class, s1, reg + i);
				ret = (*s1 >= class->range_min && *s1 <= class->range_max ? TRUE : FALSE);
				line_class = regex_class_line(class->isset, ret, line_class);
			}
		}
		if (line_class == TRUE && (++s1) && regex_class_match(st, class, s1, reg))
			return (TRUE);
		else if (line_class == FALSE)
			return (FALSE);
	}
	//if (verif_quantifier(&(class->quantifier), class->match))
	//	return (regex_parse(st, s1, reg + class->i));
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
