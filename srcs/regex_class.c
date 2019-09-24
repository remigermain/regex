/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_class.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 20:32:03 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/24 21:08:22 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

static int		regex_class_parsing(t_regex *st, t_reg_class *class, char *s1, char *reg)
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

static t_bool	regex_class_match(t_regex *st, t_reg_class *class, char *s1, char *reg)
{
	if (verif_quantifier(&(class->quantifier), ++class->match) && regex_parse(st, s1, reg + class->i))
		return (TRUE);
	return (FALSE);
}

void			regex_class_line(t_reg_class *class)
{
	if (!class->is_not && class->ret)
		class->line_class = TRUE;
	else if (class->is_not && class->ret)
		class->line_class = FALSE;
}

t_bool			regex_class_parse(t_regex *st, t_reg_class *class, char *s1, char *reg)
{
	int i;
	int	j;

	while (*s1 != '\0' && (i = class->is_not) != -1)
	{
		class->line_class = (class->is_not ? TRUE : FALSE);
		while (*s1 && *(reg + i) && (!is_metachar(st, reg + i) || *(reg + i) != ']'))
		{
			if (is_metachar(st, reg + i) && *(reg + i) == '\\')
				i++;
			else if (is_metachar(st, reg + i) && *(reg + i) == ':')
			{
				class->ret =  regex_class_is_type(st, s1, reg + i);
				i += regex_span_class_type(st, reg + i);
			}
			else
			{
				i += regex_class_parsing(st, class, s1, reg + i);
				class->ret = (*s1 >= class->range_min && *s1 <= class->range_max ? TRUE : FALSE);
			}
			regex_class_line(class);
		}
		if (class->line_class == TRUE && (++s1) && regex_class_match(st, class, s1, reg))
			return (TRUE);
		else if (class->line_class == FALSE)
			return (FALSE);
	}
	return (FALSE);
}

t_bool			regex_class(t_regex *st, char *s1, char *reg)
{
	t_reg_class	class;

	ft_bzero(&class, sizeof(t_reg_class));
	if (is_metachar(st, reg + class.i) && *(reg + class.i) == '^')
		class.is_not |= CLASS_NOT;
	class.i = ft_spanchar_reg(st, (char *)reg, "]");
	if (is_metachar(st, reg + class.i) && *(reg + class.i) == ']')
		class.i++;
	if (is_quantifier(st, reg + class.i))
		class.i += get_quantifier(&(class.quantifier), reg + class.i);
	return (regex_class_parse(st, &class, s1, reg));
}
