/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:47:12 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 19:07:03 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REGEX_H
# define REGEX_H
# include "libft.h"
# define QUANTIFIER "{*+?"
# define ERROR_REGEX -1
# define REGEX_TYPE "wWbBdDsSAZ"
# define REG_LAZY '?'
# define REG_QUAN_MINI "*+?"
# define REG_CLASS_NOT "^"
# define REG_CLASS_TO '-'
# define REG_START "^"
# define REG_END "$"

enum	e_regex_quan
{
	QUAN_MIN = 0b1,
	QUAN_MAX = 0b10,
	QUAN_EX = 0b100,
	QUAN_OR = 0b1000,
	QUAN_LAZY = 0b10000,
};

enum	e_regex_replace
{
	REG_ALL = 0b1,
	REG_FIRST = 0b10,
	REG_LAST = 0b100,
};

typedef struct	s_regex_quantifier
{
	int	n;
	int	m;
	int	match;
	int	isset;
}				t_reg_quan;

typedef struct	s_regex_class
{
	t_reg_quan	quantifier;
	t_bool		is_not;
	char		alpha[128];
}				t_reg_class;

typedef struct	s_regex_enclose
{
	t_reg_quan	quan;
	t_bool		is_not;
	t_bool		capture;
	const char	*mem_last;
	const char	*mem;
	char		*name;
	int			len;
	int			i;
}				t_reg_encl;

typedef struct	s_regex_print
{
	size_t	str;
	size_t	name;
	size_t	pos;
	size_t	start;
	size_t	end;
}				t_regex_pr;

typedef struct	s_regex_capt
{
	char				*str;
	char				*name;
	int					pos;
	int					start;
	int					end;
	struct s_regex_capt	*next;
}				t_reg_capt;

typedef struct	s_regex
{
	t_reg_capt	*capt;
	t_bool		error;
	const char	*reg;
	const char	*s1;
	size_t		match;
	const char	*last_s1;
	const char	*befor_do;
	int			error_pos;
	int			nb_capt;
}				t_regex;

/*
**-------------------------------------------------------
**          regex_class.c
**-------------------------------------------------------
*/
int				ft_regex_exec(t_regex *reg, const char *s1, const char *regex);
char			*ft_regex_replace(const char *s1, const char *reg, char *src,
													enum e_regex_replace mod);
t_bool			regex_parse(t_regex *st, const char *s1, const char *reg);

/*
**-------------------------------------------------------
**          regex_class.c
**-------------------------------------------------------
*/
t_bool			regex_class(t_regex *st, const char *s1, const char *reg);

/*
**-------------------------------------------------------
**          regex_enclosed.c
**-------------------------------------------------------
*/
t_bool			regex_enclosed(t_regex *st, const char *s1, const char *reg);
t_bool 			regex_enclose_parse(t_regex *st, t_reg_encl *encl,
							   const char *s1, const char *reg);
/*
**-------------------------------------------------------
**          regex_enclosed_capt.c
**-------------------------------------------------------
*/
void			regex_put_arg(t_regex *st, const char *base, const char *match,
																	char *name);
void			ft_regex_free(t_regex *st);

/*
**-------------------------------------------------------
**          regex_quantifier.c
**-------------------------------------------------------
*/
t_bool			verif_quantifier(t_reg_quan *st, int i);
t_bool			verif_quantifier_max(t_reg_quan *quan, int i);
int				regex_get_quantifier(t_reg_quan *st, const char *reg);
t_bool			regex_quantifier_do(t_regex *st, t_reg_quan *quantifier,
							   const char *s1, const char *reg);
t_bool			regex_quantifier(t_regex *st, const char *s1, const char *reg);

/*
**-------------------------------------------------------
**          regex_span.c
**-------------------------------------------------------
*/
int				regex_span_quantifier(t_regex *st, const char *reg);
int				regex_span_or(t_regex *st, const char *reg);
int				regex_span_enclose(t_regex *st, const char *reg);
int				regex_span_class(t_regex *st, const char *reg);

/*
**-------------------------------------------------------
**          regex_class_methode.c
**-------------------------------------------------------
*/
int				regex_is_metatype(char alpha[128], const char *reg);
int				regex_is_type(char alpha[128], const char *reg);

/*
**-------------------------------------------------------
**          regex_meta.c
**-------------------------------------------------------
*/
t_bool			is_metachar(t_regex *st, const char *reg);
t_bool			is_delimiter(t_regex *st, const char *reg, char *delimiter);
int				convert_metachar_len(t_regex *st, const char *reg);
int				convert_metachar(t_regex *st, const char *reg);

/*
**-------------------------------------------------------
**          utils.c
**-------------------------------------------------------
*/
void			ft_regex_print(t_regex *st);

#endif
