/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 21:28:31 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 15:30:04 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "libft.h"
# include "keys.h"
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <OpenAL/al.h>
# include <OpenAL/alc.h>
# include "core_structs.h"
# include "multithread_utils.h"

# define COLOR_RED "\x1b[31m"
# define COLOR_GREEN "\x1b[32m"
# define COLOR_YELLOW "\x1b[33m"
# define COLOR_BLUE "\x1b[34m"
# define COLOR_MAGENTA "\x1b[35m"
# define COLOR_CYAN "\x1b[36m"
# define COLOR_RESET "\x1b[0m"
# define COLOR_DARKGRAY "\e[37;2m"

# define STYLE_BOLD "\033[1m"
# define STYLE_UNDERLINE "\033[4m"
# define STYLE_NORMAL "\033[0m"

typedef enum	e_keys
{
	K_MOVE_FORWARD = 1,
	K_MOVE_BACKWARD = 2,
	K_STRAFE_LEFT = 4,
	K_STRAFE_RIGHT = 8,
	K_JUMP = 16,
	K_CROUNCH = 32,
	K_MOVE_UP = 64,
	K_MOVE_DOWN = 128,
	K_LOOK_UP = 256,
	K_LOOK_DOWN = 512,
	K_TILT_LEFT = 1024,
	K_TILT_RIGHT = 2048,
	K_SHIFT = 4096,
	K_E = 8192
}				t_keys;

typedef enum	e_error
{
	E_SUCCESS,
	E_ERROR_READING_FILE,
	E_ERROR_MALLOC,
	E_ERROR_PARSING_TEXTURE,
	E_ERROR_MALLOC_IMAGE,
	E_SPLIT_ERROR,
	E_ERROR_PARSE_POINTS
}				t_error;

typedef enum	e_poly_options
{
	HAS_VN = 1,
	IS_TRIANGLE = 2,
	IS_BLENDER = 4,
	IS_SPRITE = 8,
	HAS_TEXTURE = 16,
	IS_CONVEX = 32,
	IS_TEX_EQUAL = 64,
	ALL_POSITIVE = 128,
	HAS_BEEN_TRIANGULATED = 256,
	SKIP_CONVERSION = 512,
	O_WALL = 1024,
	O_FLOOR = 2048,
	O_CEIL = 4096,
	O_WALLY = 8192,
	O_IGNORE = 16384,
	O_INVISIBLE = 32768,
	O_INITIALIZED = 65536,
	O_PROJECTILE = 131072

}				t_poly_options;

typedef enum	e_obj_state
{
	ACT_BOOMED = 1,
	DISABLE_CULLING = 2,
	ACT_IS_BOOMING = 4,
	OBJ_DISABLE = 8,
	OBJ_PROJECTILE = 16,
	IS_PEWPEW = 32
}				t_obj_state;

typedef enum	e_pstate
{
	RASTER = 1,
	WIREFRAME = 2,
	FLYING = 4,
	ISOLATE = 8,
	DELIMITER_OBJ = 16,
	M_PLAY = 32,
	M_PAUSE = 64,
	M_MENU = 128,
	M_QUIT = 256,
	PACK_FILE_OPENNED = 512,
	IS_JUMPING = 1024,
	IS_FALLING = 2048,
	IS_CROUNCH = 4096,
	P_SPRINT = 8192,
	P_DEAD = 16384,
	LIFT = 32768,
	P_ENDED = 65536,
	DAMAGES = 131072,
	FADEINOUT = 262144,
	TELEPORTING = 524288
}				t_pstate;

typedef enum	e_action_enum
{
	ACT_ACTIVE = 1,
	ACT_IDLE = 2,
	ACT_DISABLED = 4,
	ACT_ENDED = 8,
	ACT_REPEAT = 16,
	ACT_INFINITE_ROT = 32,
	ACT_INSTANT = 64,
	ACT_SOUND_PLAYING = 128,
	ACT_SOUND_STOPPED = 256
}				t_action_enum;

# define CIRCLE_DETECTION 70
# define FEETS 40
# define HUMAN_SIZE 180

int					ft_printf(const char *format, ...);
int					map_packager(int argc, char *argv[]);
void				get_file_at_root(char *file);
void				file_extract(const char *file, const char *dest);

/*
** INITIALISATION
*/

void				umlx_hooks(t_param *p);
short int			umlx_init(t_param *p);
void				init_engine_settings(t_param *p);
void				init_polygons(t_param *p);
void				init_polygon_only_array(t_param *p);
void				init_struct(t_param *p);
void				init_sound(t_param *p);
void				log_error(t_param *p);

/*
** PRE-CALCULATIONS
*/

short int			ray_precompute(t_param *p);

/*
** MLX UTILS FUNCTIONS
*/

short int			umlx_create_image(void *ptr, t_mlx_img2 *img, int w, int h);
short int			umlx_xpm_to_image(void *ptr, t_mlx_img2 *img, char *file);
void				umlx_putpixel(t_mlx_img2 img, int x, int y, uint32_t color);
uint32_t			umlx_getpixel(t_mlx_img2 img, int x, int y);
uint32_t			umlx_getpixel2(t_mlx_img2 img, int x, int y);
void				display_img(t_mlx_img2 win, t_mlx_img2 texture, t_real pos,
					t_real size);
uint32_t			*gif_to_image(char *path, int *width, int *height);

/*
** EVENTS FUNCTIONS
*/

int					mouse_movement(int x, int y, struct s_param *p);
void				process_keys(t_param *p);
int					ev_keyrelease(int key, struct s_param *p);
int					ev_keypress(int key, struct s_param *p);
int					ev_mousepress(int k, int x, int y, t_param *p);
void				rotate_actions(t_param *p,
		t_vec (*fct)(t_vec vec, float vsin, float vcos), 	\
		float vsin, float vcos);
void				rotate_projectiles(t_param *p,
		t_vec (*fct)(t_vec vec, float vsin, float vcos), 	\
		float vsin, float vcos);
void				add_projectile(t_param *p, t_buffer buffer);
/*
** RENDER FUNCTIONS
*/

long long int		init_fps(void);
int					show_fps(t_param *p, long long int mseconds);
int					perf_counter(long long int mseconds);
void				process_gravity(t_param *p);
int					ray_inter_plane(t_vec o, t_vec d, t_plane p, t_vec *result);
int					check_under(t_polygon *poly);
void				upscale(t_engine_settings *settings, t_mlx_img2 win,
					t_mlx_img2 texture);
void				multithread_zone(t_param *p);
void				multithread_render(t_param *p);
void				iterate_multithread_rooms(t_param *p, t_zone_mt zone);
void				start_multithread(t_param *p);
void				iterate_polygons(t_param *p, t_polygon *poly,
					unsigned nb_poly);
void				iterate_rooms(t_param *p);
int					loop(t_param *p);
void				doom_rotate(t_param *p,
	t_vec (*fct)(t_vec vec, float vsin, float vcos), float vsin, float vcos);
t_vec				vec_rotx(t_vec v, float vsin, float vcos);
t_vec				vec_roty(t_vec v, float vsin, float vcos);
t_vec				vec_rotz(t_vec v, float vsin, float vcos);

/*
** CORE FUNCTIONS
*/

void				move_lights(t_param *p, t_rooms *room);
void				tmp_move(t_param *p, t_polygon *poly);
void				doom_move(t_param *p, t_vec move);
void				translate_polygons(t_polygon *poly, t_vec move);
void				translate_objects(t_rooms *room, t_vec move);

void				print_error(t_param *p, char *msg, char *file, int line);
int					free_and_exit(t_param *p);
void				logerror(t_param *p, char *str);

/*
** NEW PARSING
*/
char				*get_path(uint32_t pstate, const char *file);
char				*get_pathm(uint32_t pstate, const char *file);

int					check_line(t_line l, int nb_points, t_vec *points,
								t_vec per);
t_line				find_line1(int nb_points, t_vec *points, t_vec *per);
t_line				find_line2(int nb_points, t_vec *points, t_line l,
								t_vec per);
t_line				find_line3(int nb_points, t_vec *points, t_line l);
short unsigned int	check_textures(char *line);
short unsigned int	check_room(char *line, int nb_textures);
short unsigned int	check_vertices(char *line, int nb_textures);
short unsigned int	check_lights(char *line);
short unsigned int	check_objects(uint32_t pstate, char *line);
void				ft_putstr_rgb(char *str, int r, int g, int b);
int					show_parseprogress(t_param *p);
void				progress_comments(t_param *p, t_list_line *lines);
int					get_obj_options(char **data, t_list_objects **object);
void				parse_sprites(t_param *p, t_list_line *lst,
					t_list_polygons **walls, t_room_index index);
int					map_parser(t_param *p, const char *file);
int					count_textures(t_list_line *lst);
int					texture_parse(t_param *p, t_list_line *lst);
short unsigned int	check_integrity(uint32_t pstate, t_list_line *lines);
int					parse_player(t_param *p, t_list_line *lst);
t_list_lights		*parse_lights(t_list_line *lst, t_room_index index);
t_list_objects		*parse_objects(t_param *p, t_list_line *lst,
					t_room_index index);
void				parse_actions(t_param *p, t_list_line *lines);
t_list_polygons		*parse_walls(t_param *p, t_list_line *lst,
					t_room_index index);
int					generate_walls(t_param *p, t_list_polygons **lst_walls,
					char *line);
int					generate_ceilandfloor(t_param *p,
					t_list_polygons **lst_walls, int tex_floor,
					int tex_ceiling);
void				get_wall_options(char *line, t_list_polygons *poly);
int					parse_obj(t_list_objects **lst_objects, const char *file,
					t_param *p);
void				get_teleport(char *str, t_list_objects **object);
void				get_lift(char *str, t_list_objects **object);
void				get_end(char *str, t_list_objects **object);
int					get_ext(char *line);

/*
** IN POLYGON
*/

int					in_triangle_tmp(t_vec pt, t_vec a, t_vec b, t_vec c);
int					inter_poly(t_polygon *poly, t_vec p, t_cplx *result);
t_real				triangulation_get_tex(t_vec pt, t_vec a, t_vec b, t_vec c);
int					inter_poly_fix(t_polygon *poly, t_vec p);

/*
** TRIANGULATION
*/

t_vec				triangle_getcenter(t_pt_tri_tmp *a, t_pt_tri_tmp *b,
										t_pt_tri_tmp *c);
int					t_in_polygon(t_vec pt, t_list_polygons *w, t_vec vec);
int					t_check_in_tri(t_list_polygons *poly, t_vec a, t_vec b,
					t_vec c);
int					t_intersects(t_pt_tri_tmp *copy, t_vec a, t_vec b, t_vec c);
int					seg_inter_seg(t_seg s1, t_seg s2, t_vec *result);
int					intersect_check(t_pt_tri_tmp *copy, t_seg a);
t_pt_tri_tmp		*find_next(t_pt_tri_tmp *copy, t_pt_tri_tmp *points);
int					points_left(t_pt_tri_tmp *list);
void				triangulate_map(t_param *p);
void				start_triangulation(t_list_polygons *poly,
					t_pt_tri_tmp *copy, t_list_tri **tri, int depth);
void				triangulate_polygon(t_list_polygons **head,
										t_list_polygons *poly);

/*
** LISTS
*/

int					room_push(t_list_room **room, t_list_room data);
int					lights_push(t_list_lights **list, t_list_lights data);
int					object_push(t_list_objects **object, t_list_polygons *poly);
int					polygon_push(t_list_polygons **list, t_list_polygons data);
int					points_pushback(t_list_points **points, t_vec vertex);
int					line_pushback(t_list_line **lst, char *str);
int					line_pushfront(t_list_line **lst, char *str);
void				reverse_t_list_line(t_list_line **line);
int					lst_push_numbers(t_list_numbers **lst, int n);
int					count_faces(t_list_line *lst);
int					count_vertices(t_list_points *points);
void				free_t_list_lines(t_list_line **lst);
void				free_mtl_parser(t_parse_mtl **lst);
void				list_to_array(t_param *p);
unsigned int		tlist_count_rooms(t_param *p);
unsigned int		tlist_count_walls(t_list_room *room);
unsigned int		tlist_count_objects(t_list_room *room);
unsigned int		tlist_count_polygon(t_list_polygons *poly);
unsigned int		tlist_count_points(t_list_points *pt_list);
unsigned int		tlist_count_lights(t_list_room *room);
void				free_tlist_point(t_list_points **lst);
void				free_tlst_numbers(t_list_numbers **lst);
void				free_t_list_polygons(t_list_polygons **lst);
void				free_t_list_room(t_list_room **lst);
void				free_t_list_objects(t_list_objects **lst);
void				free_t_list_textures(t_textures_obj **lst);
int					lst_tri_addpoints(t_pt_tri_tmp **points, t_vec point);
void				free_lst_tri_points(t_pt_tri_tmp **lst);
int					lst_tri_add(t_list_tri **tri, t_vec a, t_vec b, t_vec c);
void				free_lst_tri(t_list_tri **lst);
int					push_triangulated_polygon(t_list_polygons **list,
					t_list_polygons data);
unsigned int		t_list_line_count(t_list_line *head);

/*
** CONVERT TO ARRAY
*/

void				copy_polygons(t_list_polygons *lst_poly,
					unsigned int nb_poly, t_polygon *poly);
void				convert_lights(t_list_lights *lst_lights,
					unsigned int nb_lights, t_lights *lights);
void				convert_t_list_points(t_list_points *lst_points,
					t_vec *dest);
void				convert_vt_tmp(t_list_points *lst_points, t_vec *dest);
void				convert_object_copy_data(t_objects *tab,
	t_list_objects *lst);

/*
** UTILS
*/

void				handle_error(t_param *p, unsigned short int type);

/*
** AUDIO ENGINE
*/

int					al_load_wav(t_audio_sources *audio_source,
					const char *file);
void				al_set_data(t_audio_sources *audio_source,
					t_format_hdr fmt, long int esize);
int					al_gen_source_buffer(t_audio_sources *audio_source);
int					al_init(void);
void				play_sound(t_param *p, t_audio_sources audio, ALfloat pitch,
					ALfloat gain);
int					al_isplaying(t_audio_sources audio_source);
int					al_get_id(t_param *p);

/*
** ENGINE
*/

void				make_tex(t_list_polygons *poly);
void				make_tex_tri(t_list_polygons *poly);
int					count_vertices(t_list_points *points);
void				make_projectiles(t_param *p);

/*
** WAVEFRONT OBJ PARSER
*/

void				assign_random_color(t_list_polygons *poly);
void				init_reader(t_tmp_obj *tmp);
int					open_file(t_param *p, t_tmp_obj *buff, const char *file);
t_list_polygons		*generate_polygon_no_mats(t_param *p, t_tmp_obj *buffer,
					t_list_polygons **res);
t_parse_mtl			*find_material(t_tmp_obj *buff, char *str);
void				iterate_material(t_list_line *lst, t_tmp_obj *buff);
void				iterate_mtl_tmp(t_list_line *lst, t_tmp_obj *buff);
int					open_mtl(t_param *p, t_tmp_obj *buff);
void				load_obj_texture(t_param *p, t_parse_mtl *lst);
int					push_material(t_parse_mtl **lst, int i, char *name);
void				reverse_buffer(t_tmp_obj *tmp);
void				*push_obj_textures(t_param *p, t_textures_obj **lst,
					char *file);
float				ft_atof(const char *str);
void				generate_polygon(t_tmp_obj *buffer, t_list_polygons *data,
					char **face_vertices, int nb_vertices);
void				gen_material_polygon(t_param *p, t_tmp_obj *buff,
					t_list_polygons **poly_list);
void				init_polygon_structure(t_list_polygons *polygon);
t_parse_mtl			*get_material_data(t_tmp_obj *buff, char *name);
void				populate_buffer(t_tmp_obj *buff, char *line, int *e);
void				triangulate_object(t_list_polygons **lst);
int					init_array(t_tmp_obj *buff);
void				init_lights(t_param *p);

/*
** ACTIONS
*/
void				teleport_player(t_param *p, t_vec pos);
void				handle_lift(t_param *p);

void				handle_action(t_param *p, t_actions *actions_list,
									t_actions *action, t_objects *obj);
void				action_move_object(t_objects *obj, t_vec move);
void				action_rotate_object(t_objects *obj, t_vec rot);
void				handle_action_sound(t_param *p, t_actions *action);
int					is_sound(t_param *p, t_actions *action);
void				action_set_wait(t_actions *action);
int					action_check_wait(t_actions *action);
int					action_check_item(t_param *p, int item);
void				handle_action_rewind(t_actions *action, t_objects *obj);
void				handle_action_animated(t_actions *action, t_objects *obj);
void				handle_action_infinite_rotation(t_actions *action,
													t_objects *obj);
int					handle_action_instant(t_param *p, t_actions *action,
									t_actions *actions_list, t_objects *obj);
void				animation_boom(t_param *p, t_objects *obj);
void				apply_action(t_param *p);
void				evt_action_add_inventory(t_param *p, int polyid,
											t_objects *obj);
void				get_touch(t_param *p);
t_vec				translate_obj_axis(t_axis axis, t_vec pos);

/*
** MAKE
*/

void				make_data(t_param *p, t_polygon *poly, t_objects *obj);
void				make_delimitation(t_polygon *poly);
void				proj3d_to_2d_array(t_engine_settings *settings,
										t_polygon *w);
void				create_delimitation(t_engine_settings *settings,
										t_polygon *poly);
void				clamp_to_window(t_engine_settings *settings, t_polygon *p);
void				expand_and_clamp_delimitation(t_engine_settings *settings,
										t_polygon *poly);
void				make_boundingbox(t_param *p);
void				generate_box_poly(t_vec pt, t_oob *boudingbox);
void				generate_box_obj(t_oob poly, t_oob *obj);
t_rotation_axes		axes_rotation_init(t_axis axis, t_vec rot);
void				axes_apply_rot(t_vec *pt, t_rotation_axes rot);
void				axes_apply_rot_origin(t_vec center, t_vec *pt,
					t_rotation_axes rot);
void				turn_tmp_points(t_param *p, t_polygon *poly,
					unsigned int *neg);
void				turn_tmp_tex(t_param *p, t_polygon *poly);
void				make_fixed(t_polygon *poly);
void				make_maths(t_polygon *poly);
void				make_data_obj(t_polygon *poly);
void				make_data_std(t_polygon *poly);
void				make_sprite(t_polygon *poly);

/*
** HUD
*/

void				hud_show_inventory(t_param *p);
void				trace_line(t_mlx_img2 img, t_int v1, t_int v2, uint32_t c);
void				hud_show_life(t_param *p);
void				hud_show_crosshair(t_param *p);
int					hud_menu(t_param *p);
void				hud_menu_event_mouse(t_param *p, int k, int x, int y);
int					hud_player_dead(t_param *p);
void				hud_inflict_damages(t_param *p);
void				hud_fadein_fadeout(t_param *p);
void				hud_show_ammo(t_param *p);
/*
** DISPLAY
*/

void				show_wireframe(t_param *p, t_polygon *poly);
void				show_bounding_box(t_param *p, t_polygon *poly);
void				show_bounding_obj(t_param *p, t_objects *obj);
void				show_texture_delimiter(t_param *p, t_polygon *poly);
void				debug_str(t_param *p);
void				display_room(t_param *p, t_polygon *poly);
void				display_triangle(t_param *p, t_polygon *poly);
unsigned int		display(t_param *p, t_buffer buffer);

/*
** COLLISIONS
*/

int					collision(t_param *p, t_vec *vec);
int					collision_intersection(t_param *p, t_vec *vec,
	t_polygon *poly, int feets);
int					collision_conditions(t_param *p, t_polygon *poly,
	t_vec *vec);
t_vec				proj_point_poly(t_vec point, t_polygon *poly, float *dist);
int					inter_seg_poly(t_seg s, t_polygon *poly, t_vec *result);

/*
** BLEH
*/

unsigned short int	prepass_buffer(t_vec r, t_polygon *w, t_buffer *buffer);
void				handle_texture_objects(t_polygon *poly, t_cplx new,
					int *tex_pos, unsigned int *color);
void				handle_texture_walls(t_polygon *poly, t_cplx new,
					int *tex_pos);

void				reduce_array(t_polygon *p);
#endif
