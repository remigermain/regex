/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   regex.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:47:12 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/27 20:43:54 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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

typedef struct s_regex_class
{
	int range_min;
	int range_max;
	int	isset;
	int	match;
}				t_reg_class;

typedef struct s_regex_quan
{
	int number_1;
	int	number_2;
	int isset;
}				t_reg_quan;

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
t_bool	regex_cmp(t_regex *reg, const char *s1, const char *regex);
t_bool	regex_parse(t_regex *st, const char *s1, const char *reg);
t_bool  regex_class_type(t_regex *st, const char *s1, const char *reg);


/*
**-------------------------------------------------------
**          regex_class.c
**-------------------------------------------------------
*/
t_bool  regex_class(t_regex *st, const char *s1, const char *reg);

/*
**-------------------------------------------------------
**          regex_enclosed.c
**-------------------------------------------------------
*/
t_bool  regex_enclosed(t_regex *st, const char *s1, const char *reg);

/*
**-------------------------------------------------------
**          regex_quantifier_func.c
**-------------------------------------------------------
*/
t_bool	char_quantifier(t_regex *st, char c, const char *s1, const char *reg);
t_bool	regex_plus(t_regex *st, char c, const char *s1, const char *reg);
t_bool	regex_inter(t_regex *st, char c, const char *s1, const char *reg);
t_bool	regex_star(t_regex *st, char c, const char *s1, const char *reg);

/*
**-------------------------------------------------------
**          regex_quantifier.c
**-------------------------------------------------------
*/
t_bool  regex_quantifier(t_regex *st, char c, const char *s1, const char *reg);

/*
**-------------------------------------------------------
**          regex_get_quantifier.c
**-------------------------------------------------------
*/
int         get_quantifier(t_reg_quan *st, const char *reg);
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


/*
**-------------------------------------------------------
**          utils.c
**-------------------------------------------------------
*/
t_bool      is_delimiter(t_regex *st, char *reg, char delemiter);
void    	print_quan(t_reg_quan *st);
int			ft_spanchar_reg(char *flag, char *str);
#endif
