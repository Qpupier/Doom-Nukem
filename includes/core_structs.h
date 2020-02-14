/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   core_structs.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/07 10:38:13 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 15:27:02 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CORE_STRUCTS_H
# define CORE_STRUCTS_H
# include "limits.h"
# define AMMO 50

typedef struct					s_mlx_img2
{
	void						*ptr;
	unsigned int				*img;
	int							width;
	int							height;
	int							bpp;
	int							s_l;
	int							endian;
}								t_mlx_img2;

typedef struct					s_list_numbers
{
	int							n;
	struct s_list_numbers		*next;
}								t_list_numbers;

typedef struct					s_room_index
{
	int							start;
	int							end;
}								t_room_index;

typedef struct					s_textures_obj
{
	int							id;
	char						file[NAME_MAX];
	struct s_mlx_img2			t;
	struct s_textures_obj		*next;
}								t_textures_obj;

typedef struct					s_tmp_obj
{
	struct s_list_line			*file;
	struct s_list_line			*vertices;
	struct s_list_line			*faces;
	struct s_list_line			*normals;
	struct s_list_line			*textures;
	struct s_list_line			*materials;
	struct s_list_numbers		*materials_indexes;
	struct s_parse_mtl			*materials_list;
	long long int				nb_faces;
	unsigned int				nb_v;
	unsigned int				nb_vn;
	unsigned int				nb_vt;
	t_vec						*tab_vertices;
	t_vec						*tab_normals;
	t_vec						*tab_textures;
	char						*mtl_file;
}								t_tmp_obj;

typedef struct					s_parse_mtl
{
	char						*name;
	int							index;
	void						*ptr_tex;
	char						*ka;
	char						*kd;
	char						*map_kd;
	struct s_mlx_img2			img;
	struct s_parse_mtl			*next;
}								t_parse_mtl;

typedef struct					s_obj_action
{
	unsigned int				type;
	float						touch_min_dis;
	float						on_dis;
	int							touch_id;
	int							click_id;
	int							dis_id;
	int							end_id;
	int							action_id;
	int							boom_id;
	int							teleport_type;
	int							teleport_type_option;
	t_vec						teleport_position;
	float						lift_value;
	int							lift_type;
	int							lift_data;
	int							lift_state;
	int							end_type;
	int							end_data;
	int							boom;
}								t_obj_action;

typedef struct					s_actions
{
	uint32_t					state;
	t_vec						pos_curr;
	t_vec						pos;
	t_vec						rot_curr;
	t_vec						rot;
	t_vec						pos_inc;
	int							sound;
	int							item_id;
	unsigned long int			time_to_wait;
	unsigned long int			time_on_start;
}								t_actions;

typedef struct					s_list_tri
{
	t_vec						tri[3];
	struct s_list_tri			*next;
}								t_list_tri;

typedef struct					s_pt_tri_tmp
{
	t_vec						point;
	unsigned int				deleted;
	struct s_pt_tri_tmp			*next;
}								t_pt_tri_tmp;

typedef struct					s_parsing
{
	int							fd;
	char						*line;
	int							nb_wall;
	char						**data;
	int							has_error;
	int							curr_line;
}								t_parsing;

typedef struct					s_rotation_axes
{
	t_vec						cos_x;
	t_vec						cos_y;
	t_vec						cos_z;
	t_vec						sin_x;
	t_vec						sin_y;
	t_vec						sin_z;
}								t_rotation_axes;

typedef struct					s_list_polygons
{
	t_mlx_img2					texture;
	t_mlx_img2					*texture2;
	t_vec						tex[4];
	t_vec						vn;
	t_vec						obj_tex[3];
	t_vec						tex_u;
	t_vec						tex_v;
	struct s_list_points		*points;
	int							nb_points;
	float						ratio;
	t_vec						pos;
	unsigned int				color;
	unsigned int				options;
	t_vec						ka;
	t_vec						kd;
	void						*ptr_tex;
	struct s_list_points		*vt;
	struct s_list_polygons		*next;
}								t_list_polygons;

typedef struct					s_list_points
{
	t_vec						point;
	struct s_list_points		*next;
}								t_list_points;

typedef struct					s_list_lights
{
	t_vec						pos;
	t_vec						pos_rot;
	float						intensity;
	unsigned int				color;
	struct s_list_lights		*next;
}								t_list_lights;

typedef struct					s_list_objects
{
	t_list_polygons				*poly;
	t_vec						rot;
	t_vec						position;
	t_obj_action				action;
	float						scale;
	int							item_id;
	int							type;
	struct s_list_objects		*next;
}								t_list_objects;

typedef struct					s_list_room
{
	t_list_objects				*objects;
	t_list_polygons				*walls;
	t_list_lights				*lights;
	struct s_list_room			*next;
}								t_list_room;

typedef struct					s_bressen
{
	int							dx;
	int							dy;
	int							sx;
	int							sy;
	int							err;
	int							e2;
}								t_bressen;

typedef struct					s_mlx
{
	void						*mlx_ptr;
	void						*win_ptr;
	t_mlx_img2					debug;
	t_mlx_img2					win2;
	t_mlx_img2					render;
}								t_mlx;

typedef struct					s_texture_mapping
{
	t_vec						u;
	t_vec						v;
}								t_texture_mapping;

typedef struct					s_list_line
{
	char						*line;
	struct s_list_line			*next;
}								t_list_line;

typedef struct					s_buffer
{
	float						dis;
	unsigned int				color;
	struct s_rooms				*ptr_room;
	struct s_polygon			*ptr_poly;
	t_vec						pt;
}								t_buffer;

typedef struct					s_player
{
	float						rotx_angle;
	float						rotx_vsin;
	float						rotx_vcos;
	float						roty_vcos;
	float						roty_vsin;
	float						roty_angle;
	float						rotx;
	t_vec						position;
	t_vec						current_position;
	int							life;
	unsigned int				state;
	int							inventory[4];
	int							current_room;
}								t_player;

typedef struct					s_engine_settings
{
	int							win_width;
	int							win_height;
	int							width;
	int							height;
	int							zbuffer_center;
	int							hmultw;
	int							half_width;
	int							half_height;
	int							deg_fov_h;
	int							deg_fov_v;
	float						rad_fov_h;
	float						rad_fov_v;
	float						ratio_fov_h;
	float						ratio_fov_v;
	float						quality;
}								t_engine_settings;

typedef struct					s_riff_hdr
{
	unsigned char				riff[4];
	unsigned char				wave[4];
	uint32_t					size;
}								t_riff_hdr;

typedef struct					s_format_hdr
{
	unsigned char				fmt_txt[4];
	uint32_t					size;
	uint16_t					audio_fmt;
	uint16_t					channel;
	uint32_t					sampling_f;
	uint32_t					byte_rate;
	uint16_t					block_align;
	uint16_t					bits_per_sample;
}								t_format_hdr;

typedef struct					s_data_hdr
{
	unsigned char				id[4];
	uint32_t					size;
	int							num_samples;
}								t_data_hdr;

typedef struct					s_audio_lst
{
	unsigned char				*buffer;
	uint32_t					size;
	uint32_t					frequency;
	ALenum						format;
}								t_audio_lst;

typedef struct					s_audio_sources
{
	ALuint						source;
	t_audio_lst					audio;
	ALuint						buffer;
}								t_audio_sources;

typedef struct					s_projection2d
{
	t_real						pt[12];
	t_real						pt_delim[12];
	t_real						pt_tmp[12];
	unsigned int				nb;
	unsigned int				nb_delim;
	unsigned int				nb_tmp;
}								t_projection2d;

typedef struct					s_oob
{
	t_vec						max;
	t_vec						min;
	t_vec						center;
	float						dis;
}								t_oob;

typedef struct					s_axis
{
	t_vec						x;
	t_vec						y;
	t_vec						z;
}								t_axis;

typedef struct					s_polygon
{
	t_mlx_img2					*texture;
	t_vec						n;
	t_vec						u;
	t_vec						v;
	t_vec						o;
	t_plane						plane;
	float						scale_u;
	float						scale_v;
	float						scale_uv;
	t_vec						fix_n;
	t_vec						fix_u;
	t_vec						fix_v;
	t_vec						fix_o;
	t_plane						fix_plane;
	float						fix_scale_u;
	float						fix_scale_v;
	float						fix_scale_uv;
	t_vec						vn;
	t_vec						vn_rot;
	t_vec						tex[4];
	t_vec						tmp_tex[4];
	t_vec						tex_u;
	t_vec						tex_v;
	t_vec						points[4];
	t_vec						tmp_points[4];
	t_projection2d				proj;
	t_vec						vt[3];
	float						ratio_raycaster;
	float						ratio;
	unsigned short int			nb_points;
	unsigned int				color;
	unsigned int				options;
	int							index;
	t_vec						obj_tex[3];
	t_vec						ka;
	t_vec						kd;
	int							xmin;
	int							ymin;
	int							xmax;
	int							ymax;
	unsigned int				is_visible;
	struct s_rooms				*room_ptr;
	struct s_objects			*obj_ptr;
	float						dist_y;
	t_oob						boudingbox;
	t_axis						axis;
	float						sprite_angle;
	int							colle;
}								t_polygon;

typedef struct					s_lights
{
	t_vec						pos;
	t_vec						pos_tmp;
	float						intensity;
	unsigned int				color;
	int							roomid;
}								t_lights;

typedef struct					s_zone_mt
{
	int							xmin;
	int							xmax;
	int							ymin;
	int							ymax;
}								t_zone_mt;

typedef struct					s_objects
{
	struct s_polygon			*poly;
	unsigned int				nb_polygons;
	float						scale;
	t_vec						position;
	t_vec						rotation;
	t_oob						boundingbox;
	t_axis						axis;
	unsigned int				id_action;
	t_obj_action				action;
	unsigned int				id;
	float						distance;
	unsigned int				state;
	float						boom_curr;
	int							item_id;
}								t_objects;

typedef struct					s_rooms
{
	t_objects					*objects;
	struct s_polygon			*walls;
	t_lights					*lights;
	unsigned int				index;
	unsigned int				nb_lights;
	unsigned int				nb_walls;
	unsigned int				nb_objects;
}								t_rooms;

typedef struct					s_param
{
	uint32_t					keys;
	t_mlx						*mlx;
	t_vec						**rays;
	float						angle;
	unsigned long				frame_curr;
	unsigned long				frame_prev;
	uint32_t					pstate;
	t_buffer					*buffer;
	struct s_actions			*actions;
	int							nb_actions;
	int							poly_count;
	int							poly_culled;
	t_list_room					*room_list;
	int							nb_rooms;
	t_textures_obj				*tex_objs;
	t_mlx_img2					*textures;
	unsigned int				settings;
	t_engine_settings			*engine_settings;
	t_player					player;
	struct s_rooms				*rooms;
	t_audio_sources				*audio;
	ALuint						*audio_source;
	int							nb_audio;
	long int					total_polygons;
	struct s_polygon			**lst_polygons;
	int							fps;
	int							nb_object;
	int							parse_loading_bar;
	int							parse_total_line;
	int							parse_progress;
	int							nb_textures;
	int							fd_log;
	t_polygon					projectiles[AMMO];
	int							nb_projectiles;
}								t_param;

#endif
