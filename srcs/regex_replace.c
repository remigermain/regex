/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   regex_replace.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <rgermain@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 18:11:55 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 18:11:57 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

static t_bool	regex_replace_check(t_reg_list *list, int len,\
													enum e_regex_replace mod)
{
	if ((len == 0 && (mod & REG_FIRST)) ||
		(list->next == NULL && (mod & REG_LAST)) ||
		(mod & REG_ALL))
		return (TRUE);
	return (FALSE);
}

int				regex_replace_len(t_regex *st, const char *s1, char *src,
													enum e_regex_replace mod)
{
	t_reg_list	*list;
	int			len;
	int			rem;

	len = 0;
	rem = 0;
	list = st->capt;
	while (list)
	{
		if (regex_replace_check(list, len, mod) && (++len))
			rem += ft_strlen(list->str);
		list = list->next;
	}
	return ((ft_strlen(s1) - rem) + (ft_strlen(src) * len));
	return (0);
}

static void regex_replace_str(t_regex *st, char *ptr, const char *rep,
							  						enum e_regex_replace mod)
{
	t_reg_list *list;
	int			len;
	int			i;

	list = st->capt;
	len = -1;
	i = 0;
	while (list && (++len))
	{
		ft_strncat(ptr, st->s1 + i, list->start - i);
		if (regex_replace_check(list, len, mod))
			ft_strcat(ptr, rep);
		else
			ft_strncat(ptr, st->s1 + list->start, list->end - list->start);
		i = list->end;
		list = list->next;
	}
	ft_strcat(ptr, st->s1 + i);
}

char			*ft_regex_replace(const char *s1, const char *reg,
									const char *rep, enum e_regex_replace mod)
{
	t_regex		st;
	char		*ptr;
	int			len;

	ptr = NULL;
	if (ft_regex_exec(&st, s1, reg))
	{
		len = regex_replace_len(&st, s1, rep, mod);
		if (!(ptr = (char*)ft_memalloc(sizeof(char) * (len + 1))))
			return (NULL);
		regex_replace_str(&st, ptr, rep, mod);
	}
	ft_regex_free(&st);
	return (ptr);
}
