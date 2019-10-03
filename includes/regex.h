/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:47:12 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/03 19:31:08 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef	REGEX_H
# define REGEX_H
# include "libft.h"
# define REGEX_BUFF 40
# define DELEMITOR "|[]^."
# define QUANTIFIER "{*+?"
# define ENCLOSE "[("
# define ERROR_REGEX -1
# define REGEX_TYPE "wWbBdDsSAZ"

enum e_regex_quan
{
	QUAN_MIN = 0b1,
	QUAN_MAX = 0b10,
	QUAN_EX = 0b100,
	QUAN_LAZY = 0b1000,
};

enum e_regex_replace
{
    REG_FIRST,
    REG_END,
    REG_ALL,
};

typedef struct s_regex_quantifier
{
	int	number_1;
	int	number_2;
	int	match;
	int	isset;
}				t_reg_quan;

typedef struct s_regex_enclose_in
{
	char	*mem_s1;
    int		i;
}				t_regex_encl_in;

typedef struct s_regex_enclose
{
	t_reg_quan	quan;
	t_bool		is_not;
	int			len;
}				t_reg_encl;

typedef struct s_regex_class
{
	t_reg_quan	quantifier;
	t_bool		is_not;
	char		alpha[128];
}				t_reg_class;

typedef struct	s_regex_capt
{
	char	*str;
	int		pos;
	int		start;
	int		end;
	struct s_regex_capt *next;
}				t_reg_capt;

typedef struct s_regex
{
	t_reg_capt	*capt;
	t_bool		error;
	const char	*reg;
	const char	*s1;
	size_t		match;
	char		*last_s1;
	int			pos;
}				t_regex;

/*
**-------------------------------------------------------
**          regex_class.c
**-------------------------------------------------------
*/
int				ft_regex_cmp(t_regex *reg, char *s1, char *regex);
char			*ft_regex_replace(char *s1, char *reg, char *src, enum e_regex_replace mod);
t_bool			regex_parse(t_regex *st, char *s1, char *reg);

/*
**-------------------------------------------------------
**          regex_class.c
**-------------------------------------------------------
*/
t_bool  		regex_class(t_regex *st, char *s1, char *reg);

/*
**-------------------------------------------------------
**          regex_enclosed.c
**-------------------------------------------------------
*/
t_bool  		regex_enclosed(t_regex *st, char *s1, char *reg);

/*
**-------------------------------------------------------
**          regex_arg.c
**-------------------------------------------------------
*/
void        	regex_put_arg(t_regex *st, char *s1, char *s2);
void        	regex_cal(t_regex *st);

/*
**-------------------------------------------------------
**          regex_quantifier.c
**-------------------------------------------------------
*/
t_bool			verif_quantifier(t_reg_quan *st, int i);
t_bool			regex_quantifier_do(t_regex *st, t_reg_quan *quantifier, char *s1, char *reg);
t_bool			regex_quantifier(t_regex *st, char *s1, char *reg);

/*
**-------------------------------------------------------
**          regex_regex_get_quantifier.c
**-------------------------------------------------------
*/
int         	regex_get_quantifier(t_reg_quan *st, char *reg);

/*
**-------------------------------------------------------
**          regex_is_methode.c
**-------------------------------------------------------
*/
t_bool			is_enclose(t_regex *st, char *reg);
t_bool			is_quantifier(t_regex *st, char *reg);
t_bool			is_delimiter(t_regex *st, char *reg, char delimiter);

/*
**-------------------------------------------------------
**          regex_free.c
**-------------------------------------------------------
*/
void			ft_regex_free(t_regex *st);

/*
**-------------------------------------------------------
**          regex_span.c
**-------------------------------------------------------
*/
int     		regex_span_quantifier(t_regex *st, char *reg);
int     		regex_span_or(t_regex *st, char *reg);
int     		regex_span_enclose(t_regex *st, char *reg);
int     		regex_span_class(t_regex *st, char *reg);

/*
**-------------------------------------------------------
**          regex_class_methode.c
**-------------------------------------------------------
*/
void			regex_is_type_made(char alpha[128], t_bool (*func)(int), int mod);
int				regex_class_is_metatype(char alpha[128], char *reg);
int				regex_class_is_type(char alpha[128], char *reg);

/*
**-------------------------------------------------------
**          regex_meta.c
**-------------------------------------------------------
*/
t_bool			is_metachar(t_regex *st, char *reg);
int				convert_metachar_len(t_regex *st, char *reg);
int				convert_metachar(t_regex *st, char *reg);

/*
**-------------------------------------------------------
**          utils.c
**-------------------------------------------------------
*/
void			regex_error_line(t_regex *st, char *reg, char c);
t_bool			regex_return(t_regex *st, t_bool ret);
void			regex_error(t_regex *st);

#endif
