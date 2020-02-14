/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 16:49:53 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 16:31:04 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <math.h>
# include "get_next_line.h"
# include "../../minilibx_macos/mlx.h"

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define WHITE 0xFFFFFF
# define GREY 0xAAAAAA
# define BLACK 0x000000

typedef struct		s_rgb
{
	int	r;
	int	g;
	int	b;
	int	a;
}					t_rgb;

typedef struct		s_cplx
{
	float	rl;
	float	im;
}					t_cplx;

typedef struct		s_real
{
	float			x;
	float			y;
}					t_real;

typedef struct		s_int
{
	intmax_t		x;
	intmax_t		y;
}					t_int;

typedef struct		s_vec
{
	float	x;
	float	y;
	float	z;
}					t_vec;

typedef struct		s_seg
{
	t_vec	a;
	t_vec	b;
}					t_seg;

typedef struct		s_half_line
{
	t_vec	p;
	t_vec	d;
}					t_half_line;

typedef struct		s_line_parameter
{
	float	o;
	float	u;
}					t_line_parameter;

typedef struct		s_line
{
	t_line_parameter	x;
	t_line_parameter	y;
	t_line_parameter	z;
}					t_line;

typedef struct		s_plane
{
	float	a;
	float	b;
	float	c;
	float	d;
}					t_plane;

typedef struct		s_sys_sol_1var_deg1
{
	float	x;
}					t_sys_sol_1var_deg1;

typedef struct		s_equ_2var_deg1
{
	float	a_x;
	float	a_y;
	float	b;
}					t_equ_2var_deg1;

typedef struct		s_sys_sol_2var_deg1
{
	float	x;
	float	y;
}					t_sys_sol_2var_deg1;

typedef struct		s_mlx_img
{
	void	*ptr;
	char	*img;
	int		width;
	int		height;
	int		bpp;
	int		s_l;
	int		endian;
}					t_mlx_img;

typedef struct		s_inter_2d_ray_seg
{
	t_real	result;
	int		r;
	int		s1;
	int		s2;
}					t_inter_2d_ray_seg;

typedef struct		s_2d_ray
{
	t_real	p;
	t_real	d;
	float	a;
	float	b;
	float	c;
}					t_2d_ray;

typedef struct		s_2d_seg
{
	t_real	a;
	t_real	b;
}					t_2d_seg;

typedef struct		s_2d_line
{
	float	a;
	float	b;
	float	c;
}					t_2d_line;

typedef struct		s_inter_seg_plane
{
	t_vec	result;
	int		s1;
	int		s2;
}					t_inter_seg_plane;

typedef float		t_matrix_3_3[3][3];

t_cplx				cplx_add(t_cplx a, t_cplx b);
t_cplx				cplx_average(t_cplx a, t_cplx z, float b);
t_cplx				cplx_cos(t_cplx z);
t_cplx				cplx_cosh(t_cplx z);
int					cplx_discriminant(t_cplx z);
t_cplx				cplx_div(t_cplx a, t_cplx b);
int					cplx_equ(t_cplx a, t_cplx b);
t_cplx				cplx_exp(t_cplx z);
t_cplx				cplx_ln(t_cplx z);
t_cplx				cplx_make(float rl, float im);
float				cplx_modul(t_cplx z);
float				cplx_modul_2(t_cplx z);
t_cplx				cplx_mult(t_cplx a, t_cplx b);
t_cplx				cplx_pow(t_cplx z, int n);
t_cplx				cplx_remove(t_cplx a, t_cplx b);
t_cplx				cplx_sin(t_cplx z);
t_cplx				cplx_sinh(t_cplx z);
void				cplx_swap(t_cplx *a, t_cplx *b);
t_real				cplx_to_real(t_cplx z);
t_cplx				cplx_turn(t_cplx a, t_cplx o, float angle);

t_2d_line			create_2d_line_point_vec(t_real p1, t_real p2);
t_2d_line			create_2d_line_points(t_real p1, t_real p2);
t_2d_ray			create_2d_ray(t_real a, t_real b);
int					inter_2d_line_line(t_2d_line l1, t_2d_line l2, 			\
		t_real *result);
int					inter_2d_line_seg(t_2d_line l, t_2d_seg s, t_real *result);
int					inter_2d_ray_seg(t_2d_ray r, t_2d_seg s, 				\
		t_inter_2d_ray_seg *sol);
int					point_2d_line_in_seg(t_real p, t_2d_seg s);

int					point_line_in_seg(t_vec p, t_seg s);
t_vec				proj_point_plane(t_vec point, t_plane plane, float *dist);
int					inter_seg_plane(t_seg s, t_plane p,
		t_inter_seg_plane *result);
int					inter_line_plane(t_line l, t_plane p, t_vec *result);
t_vec				proj_point_plane(t_vec point, t_plane plane, float *dist);
t_vec				proj_point_seg(t_vec p, t_seg s, float *dist);
t_vec				proj_point_line(t_vec p, t_line l, float *dist);

void				matrix_mult_matrix(t_matrix_3_3 m1, t_matrix_3_3 m2, 	\
		t_matrix_3_3 r);
t_vec				matrix_mult_vec(t_matrix_3_3 mat, t_vec v);
void				matrix_rotation_x(float angle, t_matrix_3_3 matrix);
void				matrix_rotation_y(float angle, t_matrix_3_3 matrix);
void				matrix_rotation_z(float angle, t_matrix_3_3 matrix);
void				matrix_rotation(float theta_x, float theta_y, 			\
		float theta_z, t_matrix_3_3 rot);

t_real				op_real(t_real a, char op, t_real b);
float				real_norm(t_real p);
t_real				real_normalize(t_real v);
float				real_oriented_angle(t_real u, t_real v);
float				real_scale_product(t_real p1, t_real p2);
t_real				real_turn(t_real point, float degree);
void				treal_arraycpy(t_real *src, t_real *dest, unsigned int nb);

t_vec				vec_add(t_vec u, t_vec v);
void				tvec_array_cpy(t_vec *in, t_vec *out, unsigned int nb);
int					vec_null(t_vec u);
t_vec				vec_normalize(t_vec u);
t_vec				vec_check(t_vec src);
int					vec_collinears(t_vec u, t_vec v);
t_vec				vec_create(float x, float y, float z);
t_vec				vec_cross_product(t_vec u, t_vec v);
int					vec_equal(t_vec u, t_vec v);
t_vec				vec_move_x(t_vec v, float mov);
t_vec				vec_move_y(t_vec v, float mov);
t_vec				vec_move_z(t_vec v, float mov);
float				vec_norm(t_vec u);
t_vec				vec_mult_float(t_vec vec, float f);
t_vec				vec_sub(t_vec u, t_vec v);
t_vec				vec_rot_x(t_vec v, float rad);
t_vec				vec_rot_y(t_vec v, float rad);
t_vec				vec_rot_z(t_vec v, float rad);
float				vec_scale_product(t_vec u, t_vec v);
int					vec_equal_precision(t_vec u, t_vec v, float p);
int					check_tvec_from_str(char *str);
t_vec				str_to_vec3(const char *str);
int					count_dstr(char **d);
int					extract_tvec_from_str(char *str, t_vec *result);

int					line_check(t_line l, int nb_points, t_vec *points, 		\
					t_vec per);
t_line				line_create_points(t_vec p1, t_vec p2);
t_line				line_create_point_vec(t_vec o, t_vec u);
int					line_equal(t_line l1, t_line l2);
int					line_half_inter_seg(t_half_line l, t_seg s, t_vec *result);
t_line				line_init(void);
int					line_inter_line(t_line l1, t_line l2, t_vec *result);
int					line_inter_seg(t_line l, t_seg s, t_vec *result);
t_line				line_parallel_line_point(t_line l, t_vec p);
t_line				line_perpendicular_line_point_plane(t_line l, t_vec p, 	\
					t_vec n);
t_vec				line_point(t_line l);
t_vec				line_vec_dir(t_line l);

int					sys_solve_1equ_1var_deg1(float a, float b, 				\
					t_sys_sol_1var_deg1 *s);
int					sys_solve_2equ_2var_deg1(t_equ_2var_deg1 e1, 			\
					t_equ_2var_deg1 e2, t_sys_sol_2var_deg1 *s);

void				xpm_to_img(void *ptr, t_mlx_img *img, char *file);

int					floatcmp(float f1, float f2, float p);
float				ft_abs(float nb);
void				fclamp(float *curr, float min, float max);
void				iclamp(intmax_t *curr, int min, int max);

int					ft_atoi(const char *str);
unsigned long long	ft_atoull(const char *str);
float				ft_atof(const char *str);
int					ft_atoi_hexa(const char *str);
float				ft_average(int nb1, int nb2, float p);
void				ft_bzero(void *s, size_t n);
t_rgb				ft_color_average(t_rgb c1, t_rgb c2, float p);
t_rgb				ft_color_hex_to_rgb(char *color);
t_rgb				ft_color_int_to_rgb(int nb);
t_rgb				ft_color_rgb_random(void);
char				*ft_color_rgb_to_hex(t_rgb rgb);
int					ft_color_rgb_to_int(t_rgb rgb);
int					color_avg_calc(int start, int end, double percentage);
int					color_avg(unsigned int s_col, unsigned int end_col,
							double p);
int					ft_count_words(char *s, char c);
void				ft_create_img(void *ptr, t_mlx_img *img, int w, int h);
float				ft_deg_to_rad(float nb);
int					ft_digit_abs(int d);
int					ft_digit_hex_to_int(char c);
t_rgb				hex_to_rgb(unsigned int color);
unsigned int		rgb_to_hex(t_rgb c);
void				ft_error(char *str);
int					ft_exit(void);
int					ft_find(char *str, char c);
char				*ft_ftoa(float nb, int p);
t_rgb				ft_get_pixel(t_mlx_img img, int x, int y);
char				*ft_hex_color_complete(char *c);
void				ft_img_dark(t_mlx_img img);
int					ft_intlen(long int nb);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isnumber(int c);
int					ft_isprint(int c);
char				*ft_itoa(long int n);
void				ft_line(t_mlx_img img, t_cplx a, t_cplx z, t_rgb color);
void				ft_line_horiz(t_mlx_img img, t_cplx a, t_cplx z, 		\
					t_rgb color);
int					ft_line_straight(t_mlx_img img, t_cplx a, t_cplx z, 	\
					t_rgb color);
int					ft_line_straight_horiz(t_mlx_img img, t_cplx a, 		\
					t_cplx z, t_rgb color);
int					ft_line_straight_vert(t_mlx_img img, t_cplx a, 			\
					t_cplx z, t_rgb color);
void				ft_line_vert(t_mlx_img img, t_cplx a, t_cplx z, 		\
					t_rgb color);
t_real				ft_make_real(int x, int y);
float				ft_max(float a, float b);
void				*ft_realloc(void *array, size_t new_size);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
float				ft_min(float a, float b);
int					ft_mod(int a, int b);
int					ft_occur(const char *str, const char c);
void				ft_pixel_put(t_mlx_img img, int x, int y, uint32_t color);
void				ft_pixel_put_rgb(t_mlx_img img, int x, int y, t_rgb color);
int					ft_pow(float nb, int pow);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(const char *str);
void				ft_putstr_fd(char const *s, int fd);
t_cplx				ft_real_to_cplx(t_real xy);
int					ft_splitdel(char ***split);
float				ft_sq(float nb);
int					ft_sqrt(int nb);
char				*ft_stractrim(const char *str, const char c);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
size_t				ft_strcspn(const char *s, const char *reject);
char				*ft_strctrim(char const *s, char c);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void(*f)(char*));
void				ft_striteri(char *s, void(*f)(unsigned int, char*));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
int					ft_strlen_words(const char *s, char c);
char				*ft_strmap(char const *s, char (*f)(char));
void				ft_strmap_display(char *str, int l, int h);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
void				ft_strncdelete(char *str, char letter, char replace, 	\
					int count);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *haystack, const char *needle, 	\
					size_t len);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
char				**ft_strtrimsplit(char **str, char *n, char c);
void				ft_swap(int *a, int *b);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					get_next_line(const int fd, char **line);
int					str_isnumber(char *str);
int					str_isnumbern(char *str, int n);
char				*str_getaocc(char *str, char c);
int					fileexists(char *file);

#endif
