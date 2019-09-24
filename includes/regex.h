/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:47:12 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/24 21:48:56 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef	REGEX_H
# define REGEX_H
# include "libft.h"
# define REGEX_BUFF 40
# define DELEMITOR "|[]^."
# define QUANTIFIER "{*+?"
# define ENCLOSE "[("

enum e_regex_quan
{
	QUAN_MIN = 0b1,
	QUAN_MAX = 0b10,
	QUAN_EX = 0b100,
};

enum e_regex_class
{
	CLASS_NOT = 0b1,
};

typedef struct s_regex_quan
{
	int number_1;
	int	number_2;
	int isset;
}				t_reg_quan;

typedef struct s_regex_class
{
	t_reg_quan	quantifier;
	t_bool		line_class;
	t_bool		ret;
	int 		range_min;
	int 		range_max;
	int			is_not;
	int			match;
	int			i;
}				t_reg_class;

typedef struct s_regex_work
{
	char	*tmp;
	int		span;
	int		occur;
}				t_reg_work;

typedef struct s_reg_get
{
	char	get[REGEX_BUFF];
	size_t	start;
}				t_reg_get;

typedef struct s_regex
{
	const char	*reg;
	const char	*s1;
	size_t		reg_sub;
	t_reg_get	tab[REGEX_BUFF];
}				t_regex;

/*
**-------------------------------------------------------
**          regex_class.c
**-------------------------------------------------------
*/
t_bool	ft_regex_cmp(t_regex *reg, char *s1, char *regex);
t_bool	regex_parse(t_regex *st, char *s1, char *reg);
t_bool   regex_class_is_type(t_regex *st, char *s1, char *reg);


/*
**-------------------------------------------------------
**          regex_class.c
**-------------------------------------------------------
*/
t_bool  regex_class(t_regex *st, char *s1, char *reg);

/*
**-------------------------------------------------------
**          regex_enclosed.c
**-------------------------------------------------------
*/
t_bool  regex_enclosed(t_regex *st, char *s1, char *reg);

/*
**-------------------------------------------------------
**          regex_quantifier_func.c
**-------------------------------------------------------
*/
t_bool	char_quantifier(t_regex *st, char *s1, char *reg);
t_bool	regex_plus(t_regex *st, char c, char *s1, char *reg);
t_bool	regex_inter(t_regex *st, char c, char *s1, char *reg);
t_bool	regex_star(t_regex *st, char c, char *s1, char *reg);

/*
**-------------------------------------------------------
**          regex_quantifier.c
**-------------------------------------------------------
*/
t_bool  regex_quantifier(t_regex *st, char *s1, char *reg);

/*
**-------------------------------------------------------
**          regex_get_quantifier.c
**-------------------------------------------------------
*/
int         get_quantifier(t_reg_quan *st, char *reg);
t_bool  	verif_quantifier(t_reg_quan *st, int i);


/*
**-------------------------------------------------------
**          is_regex.c
**-------------------------------------------------------
*/
t_bool  is_metachar(t_regex *st, char *reg);
t_bool  is_start(t_regex *st, char *reg);
t_bool  is_end(t_regex *st, char *reg);
t_bool  is_or(t_regex *st, char *reg);
t_bool  is_quantifier(t_regex *st, char *reg);
t_bool  is_enclose(t_regex *st, char *reg);
int     convert_metachar(t_regex *st, char *reg);
int		convert_metachar_len(t_regex *st, char *reg);
int 	regex_span_class_type(t_regex *st, char *reg);

/*
**-------------------------------------------------------
**          regex_explode.c
**-------------------------------------------------------
*/
char	**regex_explode(const char *reg);

/*
**-------------------------------------------------------
**          regex_free.c
**-------------------------------------------------------
*/
	void ft_regex_free(t_regex *st);

/*
**-------------------------------------------------------
**          utils.c
**-------------------------------------------------------
*/
	t_bool
	is_delimiter(t_regex *st, char *reg, char delemiter);
void    	print_quan(t_reg_quan *st);
int 		ft_spanchar_reg(t_regex *st, char *reg, char *str);
#endif
