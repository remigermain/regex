/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   regex_class.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <rgermain@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 20:32:03 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 18:12:23 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

static t_bool	regex_class_do(t_regex *st, t_reg_class *class,
											const char *s1, const char *reg)
{
	t_bool	ret;
	int		i;

	i = -1;
	while (s1[++i])
	{
		ret = class->alpha[(int)s1[i]] ? TRUE : FALSE;
		if ((ret == TRUE && class->is_not == TRUE) ||
			(ret == FALSE && class->is_not == FALSE))
			break ;
		class->quantifier.match++;
	}
	return (regex_quantifier_do(st, &(class->quantifier), s1, reg));
}

static int		regex_class_parse(t_regex *st, t_reg_class *class,
															const char *reg)
{
	const char	*mem;
	int			i;

	mem = reg;
	while (*reg && !is_delimiter(st, reg, "]"))
	{
		if (is_delimiter(st, reg, "\\"))
			reg++;
		i = *reg;
		if (is_delimiter(st, reg, "[") && (i = -1))
			reg += regex_is_type(class->alpha, reg + 1) + 2;
		else if (!is_metachar(st, reg) && ft_strchr(REGEX_TYPE, i))
			reg += regex_is_metatype(class->alpha, reg);
		else
		{
			class->alpha[((int)*reg++)] = 1;
			if (*reg == REG_CLASS_TO)
			{
				reg++;
				while (i <= *reg)
					class->alpha[i++] = 1;
			}
		}
	}
	//i = 0;
	//while (i < 128)
	//	ft_printf("%d", class->alpha[i++]);
	//ft_printf("\n");
	//i = 0;
	//while (i < 128)
	//{
	//	ft_printf("%d", i >= 'a' && i <= 'z' ? 1 : 0);
	//	i++;
	//}
	//ft_printf("\n");
	return (regex_span_class(st, mem));
}

t_bool			regex_class(t_regex *st, const char *s1, const char *reg)
{
	t_reg_class	class;

	ft_bzero(&class, sizeof(t_reg_class));
	if (is_delimiter(st, reg, REG_CLASS_NOT))
		class.is_not = TRUE;
	reg += regex_class_parse(st, &class, reg);
	if (is_delimiter(st, reg, QUANTIFIER))
		reg += regex_get_quantifier(&(class.quantifier), reg);
	return (regex_class_do(st, &class, s1, reg));
}
