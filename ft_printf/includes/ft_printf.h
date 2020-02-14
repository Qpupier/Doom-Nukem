/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 15:30:17 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 10:48:15 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <inttypes.h>
# include <stdlib.h>

# define FLAGS "cspdDioOuUxXfF"
# define MODIFIER "Llhjz"
# define OPTIONS ". +-#0"
# define O_MINUS 1
# define O_PLUS 2
# define O_HASH 4
# define O_ZERO 8
# define O_SPACE 16
# define L_LL 32
# define L_L 64
# define L_H 128
# define L_HH 256
# define L_J 512
# define L_Z 1024
# define L_LMAJ 2048

typedef struct	s_calcs
{
	int			pdiff;
	int			wdiff;
	int			count;
}				t_calcs;

typedef struct	s_parser
{
	int			found;
	int			pmodif;
	int			palpha;
	int			space;
}				t_parser;

typedef struct	s_env
{
	va_list		arg;
	char		*format;
	int			flags;
	long int	nb;
	short int	base;
	int			width;
	int			precision;
	char		spacing;
	char		type;
	t_calcs		calcs;
}				t_env;

/*
** BASE
*/
int				convert_base(t_env *e, uintmax_t nb, short int base, int i);
/*
** FLOATS
*/
void			handle_floats(t_env *e);
char			*pf_ft_ftoa(t_env *e, long double d, int p);
/*
** ---
*/
void			print_error(t_env *e, char *s);
/*
** UTILITIES
*/
size_t			pf_strlen(const char *c);
int				pf_isdigit(int c);
int				isoption(char c);
int				ft_isalpha(int c);
int				endofparse(char c);
int				ismodifier(char c);
void			printnchar(t_env *e, char c, int n);
void			field_right(t_env *e, short int nb);
void			field_left(t_env *e);
/*
** PARSING
*/
void			init_parser_struct(t_parser *p);
void			pf_init_structs(t_env *env);
int				ft_parse(t_env *e, char *str, int start);
int				pf_parse_type(t_env *e, char *str, int start, int end);
void			pf_extract_precision(t_env *e, int start, int end,
												char *string);
void			pf_extract_width(t_env *e, int start, int end, char *string);
void			pf_init_structs(t_env *env);
int				percent_nextocc(char *str, int start);
uintmax_t		handle_length_unsigned(t_env *e);
intmax_t		handle_length(t_env *e);
/*
** HANDLERS
*/
void			handle_d(t_env *e);
void			handle_s(t_env *e);
void			handle_c(t_env *e);
void			handle_xou(t_env *e);
void			handle_p(t_env *e);
void			handle_f(t_env *e);
#endif
