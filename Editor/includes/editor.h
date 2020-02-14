/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   editor.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/07 12:22:06 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 12:22:21 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include "libft.h"
# include "keys.h"
# include <fcntl.h>
# include <pthread.h>
# include <math.h>
# define WIDTH 1600
# define HEIGHT 900

typedef struct			s_kevent
{
	short int			q;
	short int			e;
	short int			w;
	short int			a;
	short int			s;
	short int			d;
	short int			i;
	short int			r;
	short int			f;
	short int			add;
	short int			sub;
	short int			del;
	short int			nb_1;
	short int			space;
	short int			ar_left;
	short int			ar_right;
	short int			ar_up;
	short int			ar_down;
	short int			mouse_1;
	short int			mouse_2;
	short int			mouse_3;
	short int			mouse_4;
	short int			mouse_5;
	short int			mouse_x;
	short int			mouse_y;
	short int			mouse_last_x;
	short int			mouse_last_y;
}						t_kevent;

typedef struct			s_mlx_img2
{
	void				*ptr;
	unsigned int		*img;
	int					width;
	int					height;
	int					bpp;
	int					s_l;
	int					endian;
}						t_mlx_img2;

typedef struct			s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_mlx_img			win;
	t_mlx_img2			win2;
	t_mlx_img2			render;
}						t_mlx;

typedef struct			s_circle
{
	int					xoff;
	int					yoff;
	int					balance;
	int					p0;
	int					p1;
	int					w0;
	int					w1;
}						t_c;

typedef struct			s_point
{
	int					i;
	int					x;
	int					y;
	int					z;
	int					state;
	int					lay;
	struct s_point		*next;
}						t_point;

typedef struct			s_v
{
	int					x;
	int					y;
}						t_v;

typedef struct			s_fvec2d
{
	double				x;
	double				y;
}						t_fvec2d;

typedef struct			s_vec3d
{
	int					x;
	int					y;
	int					z;
}						t_vec3d;

typedef struct			s_obj
{
	int					obj;
	struct s_vec3d		pos;
	int					state;
	int					lay;
	int					type;
	int					action;
	int					room;
	struct s_obj		*next;
}						t_obj;

typedef struct			s_wall
{
	int					i;
	int					state;
	struct s_point		p_one;
	struct s_point		p_two;
	struct s_point		p_three;
	struct s_point		p_four;
	short int			tex;
	int					lay;
	int					co;
	struct s_wall		*next;
}						t_wall;

typedef struct			s_windex
{
	int					i;
	struct s_windex		*next;
}						t_windex;

typedef struct			s_room
{
	int					i;
	int					state;
	int					lay;
	struct s_wall		*wall;
	struct s_room		*next;
}						t_room;

typedef struct			s_bressen
{
	int					dx;
	int					dy;
	int					sx;
	int					sy;
	int					err;
	int					e2;
}						t_bressen;

typedef struct			s_walltool
{
	struct s_wall		w;
	short int			nb;
}						t_walltool;

typedef struct			s_hightool
{
	t_point				p1;
	t_point				p2;
	t_point				p3;
	t_point				p4;
}						t_hightool;

typedef struct			s_param
{
	t_mlx				*mlx;
	struct s_room		*room;
	struct s_point		*p;
	struct s_wall		*w;
	struct s_room		*r;
	struct s_bressen	b;
	struct s_mlx_img2	*tex;
	struct s_point		character;
	struct s_obj		*o;
	int					lay;
	int					current_frame;
	int					i_point;
	int					i_wall;
	int					i_room;
	int					touch;
	int					tool;
	int					nb_tex;
	int					switch_dis;
	int					pick_tool;
	struct s_walltool	walltool;
	struct s_hightool	hightool;
	t_kevent			kevent;
}						t_param;

int						ev_keypress(int key, struct s_param *p);
int						ev_keyrelease(int key, struct s_param *p);
void					umlx_create_image(void *ptr,
t_mlx_img2 *img, int w, int h);
int						ev_mousepress(int key, int x, int y, struct s_param *p);
int						ev_mouserelease(int key, int x,
int y, struct s_param *p);
int						ev_mousemove(int x, int y, struct s_param *p);
void					trace(t_mlx_img2 img, t_v v1, t_v v2, uint32_t c);
void					umlx_putpixel(t_mlx_img2 img,
int x, int y, uint32_t color);
void					pushback(t_point **list, t_param *p);
void					fillcircle(t_param *p, t_v v, int radius, uint32_t col);
void					editor_ui(t_param *p);
void					wall_pushback(t_wall **list, t_wall w, t_param *p);
void					editor_background(t_param *p);
void					editor_nb(t_param *p);
int						inside(t_param *p);
void					square(t_param *p);
void					selector_wall(t_param *p);
void					point_delete_all(t_param *p, t_point **point);
void					point_delete(t_param *p, t_point **point);
void					wall_delete_all(t_param *p, t_wall **wall);
void					wall_delete(t_param *p, t_wall **wall);
void					reset_state(t_param *p, t_point *point,
						t_wall *wall, t_obj *obj);
void					create_file(t_param *p);
int						count_list(t_wall *w);
void					modif_tex(t_param *p, int tex);
void					trace_points(t_param *p);
void					trace_walls(t_param *p, t_wall *w);
void					trace_rooms(t_param *p);
int						walls_selected(t_param *p);
int						points_selected(t_param *p);
void					tweak_tool_display(t_param *p);
void					tweak_select_point(t_param *p,
t_point *points, int size);
int						touch_point(t_param *p, t_point *point, int size);
void					change_layer(t_param *p);
void					room_delete_all(t_param *p, t_room **r);
void					pushback(t_point **list, t_param *p);
void					wall_pushback(t_wall **list, t_wall w, t_param *p);
void					room_pushback(t_room **list, t_wall *w, t_param *p);
void					windex_pushback(t_windex **list, t_wall *w);
void					place_character(t_param *p);
void					display_tools(t_param *p);
void					selec_tool(t_param *p);
int						touch_pixel(t_param *p, t_v v, int sizex, int sizey);
void					selec_mouse(t_param *p);
void					wall_set_connect(t_param *p);
void					trace_rooms_nb(t_param *p);
void					pick_img(t_param *p);
void					display_enemies(t_param *p);
void					pick_mouse(t_param *p);
void					display_tex(t_param *p);
void					square_ui(t_param *p, t_v p1, t_v p2);
void					obj_pushback(t_obj **list, t_obj *obj);
void					display_obj(t_param *p);
void					place_obj(t_param *p);
void					select_obj(t_param *p, t_obj **obj, int s);
void					obj_delete_all(t_obj **obj);
void					obj_delete(t_obj **obj);
t_point					*which_mouse_point(t_param *p, int size);
int						touch_wall(t_param *p, t_wall w, int size);
int						all_touch_wall(t_param *p, int size);
void					selected_points(t_param *p);
void					select_walls(t_param *p, t_wall **wall, int size);
void					select_points(t_param *p, t_point **points, int size);
t_point					get_last(t_param *p);
int						wall_check_exist(t_param *p, t_point one, t_point two);
int						room_check_exist(t_param *p, t_wall *w);
void					point_create(t_param *p);
void					check_connection(t_param *p, t_wall *w);
void					point_wall(t_param *p);
void					load_textures(t_param *p);
int						show_fps(t_param *p, long long int mseconds);
long long int			init_fps(void);
void					init_input(t_param *p);
void					init_tools(t_param *p);
void					tool_one(t_param *p);
void					tool_two(t_param *p);
void					change_tool(t_param *p);
void					change_display(t_param *p);
void					display_img(t_mlx_img2 win,
t_mlx_img2 texture, t_fvec2d pos,
									t_fvec2d size);
void					tweak_high_obj(t_param *p);
void					display_obj_info(t_param *p);
void					wall_fill(t_param *p, t_wall *w, t_wall *wall);
void					select_character(t_param *p, int s);
void					display_chara_info(t_param *p);
void					create_room(t_param *p);
void					delete_events(t_param *p);
void					wall_connect(t_param *p, t_wall w);
int						all_t_p(t_param *p, t_point **point, int size);
int						in_ui(t_param *p);
void					add_action(t_param *p);
void					display_point_info(t_param *p);
void					sort_wall(t_wall *wall);
short int				umlx_xpm_to_image(void *ptr,
t_mlx_img2 *img, char *file);
void					header_map(t_param *p, int f);
void					put_player(t_param *p, int f);

#endif
