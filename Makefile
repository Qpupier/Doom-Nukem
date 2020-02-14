# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/13 11:56:39 by qpupier      #+#   ##    ##    #+#        #
#    Updated: 2020/02/10 15:29:48 by slopez      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SRC_PATH = sources
SRC_NAME = main.c loop.c compute.c mlx_utils.c trace.c fps_counter.c

SRC_NAME += events/events.c 								\
			events/keys.c 									\
			events/rotations.c 								\
			events/mouse_movements.c 						\
			events/mouse_press.c 							\
			events/collisions.c 							\
			events/collisions_utils.c 						\
			events/gravity.c 								\
			events/gravity_utils.c 							\
			events/movements_rotate.c 						\
			events/movements_rotate_supl.c 					\
			events/movements_translate.c 					\
			events/projectiles.c

SRC_NAME += utils/error.c

SRC_NAME += engine/display/wireframe.c 						\
			engine/display/debug.c 							\
			engine/display/textured.c

SRC_NAME += parser/utils.c 									\
			parser/map/map_parser.c 						\
			parser/map/textures.c 							\
			parser/map/progress_bar.c 						\
			parser/map/integrity_check_func.c 				\
			parser/map/integrity_check.c 					\
			parser/map/parse_lights.c 						\
			parser/map/parse_objects.c 						\
			parser/map/parse_position.c 					\
			parser/map/parse_actions.c 						\
			parser/map/parse_sprites.c 						\
			parser/map/parse_walls.c 						\
			parser/map/gen_walls.c 							\
			parser/map/get_walls_options.c 					\
			parser/map/triangulation.c 						\
			parser/map/triangulation_check_ptpolygon.c 		\
			parser/map/triangulation_check_intersection.c 	\
			parser/map/triangulation_conditions.c 			\
			parser/map/triangulation_recursive.c 			\
			parser/map/triangulation_start.c 				\
			parser/map/parse_objects_options.c 				\
			parser/map/parse_objects_options_supl.c 		\
			parser/gif/render_frame_gif.c 					\
			parser/gif/check_data_gif.c 					\
			parser/gif/extension_gif.c 						\
			parser/gif/read_data_gif.c 						\
			parser/gif/sub_bloc_gif.c 						\
			parser/gif/usefull_function_gif.c

SRC_NAME += parser/wavefront/read_file.c 					\
			parser/wavefront/generate_polygons.c 			\
			parser/wavefront/parse_materials.c 				\
			parser/wavefront/new_parser.c 					\
			parser/wavefront/obj_parser.c 					\
			parser/wavefront/gen_material_utils.c 			\
			parser/wavefront/buffer_populate.c 				\
			parser/wavefront/buffer_init_array.c 			\
			parser/wavefront/triangulation.c 				\
			parser/wavefront/parse_textures.c

SRC_NAME += lists/doom.c 									\
			lists/lines.c 									\
			lists/count.c 									\
			lists/wavefront.c 								\
			lists/numbers.c 								\
			lists/polygon_push.c 							\
			lists/count_lists.c 							\
			lists/count_lists_supl.c 						\
			lists/convert_to_array.c 						\
			lists/convert_utils.c 							\
			lists/convert_polygons.c 						\
			lists/convert_objects.c 						\
			lists/free_lists.c 								\
			lists/free_lists_supl.c 						\
			lists/triangulation.c

SRC_NAME += initialisation/polygon.c 						\
			initialisation/polygon_supl.c 					\
			initialisation/mlx.c 							\
			initialisation/engine.c 						\
			initialisation/projectiles.c					\
			initialisation/init_default.c

SRC_NAME += engine/multithreading/initiate.c 				\
			engine/multithreading/iterate.c

SRC_NAME += engine/upscale.c 								\
			engine/tex_mapping.c 							\
			engine/zbuffer.c 								\
			engine/in_polygon.c 							\
			engine/axes_rotation.c

SRC_NAME += engine/make/polygons/projection.c 				\
			engine/make/polygons/make.c 					\
			engine/make/polygons/tmp_rotate.c 				\
			engine/make/polygons/delimiter.c 				\
			engine/make/polygons/delimiter_clamp.c 			\
			engine/make/polygons/boundingboxes_3d.c 		\
			engine/make/polygons/boundingboxes_3d_supl.c 	\
			engine/make/polygons/maths.c

SRC_NAME += engine/make/tex/tex.c 							\
			engine/make/tex/find_lines.c

SRC_NAME += engine/touch.c

SRC_NAME += audio_engine/openal.c 							\
			audio_engine/parse_wav.c 						\
			audio_engine/buffer_init.c 						\
			audio_engine/play_sound.c

SRC_NAME += actions_engine/handle.c 						\
			actions_engine/move_rotate.c 					\
			actions_engine/checks.c 						\
			actions_engine/act_instant.c 					\
			actions_engine/act_reset.c 						\
			actions_engine/animated.c 						\
			actions_engine/boom.c 							\
			actions_engine/teleport.c 						\
			actions_engine/lift.c

SRC_NAME += hud/inventory.c 								\
			hud/life.c 										\
			hud/crosshair.c 								\
			hud/menu.c 										\
			hud/menu_events.c 								\
			hud/death.c 									\
			hud/fadeinout.c

SRC_NAME += file_archive/archive.c					\
			file_archive/file_extract.c				\
			file_archive/utoa.c						\
			file_archive/map_packer.c


SRC_SUP = {engine,file_archive,engine/display,actions_engine,hud,audio_engine,engine/actions,initialisation,engine/make/polygons,engine/make/tex,engine/objects,engine/multithreading,utils,engine/make,parser,events,lists,parser/map,parser/wavefront,parser/gif}
OBJ_PATH = .objects
CPPFLAGS = -I includes -I libft/includes
LDFLAGS = -L libft
LDLIBS = libft/libft.a ft_printf/libftprintf.a
MINILIBX = -I minilibx_macos -L minilibx_macos -lmlx -framework OpenGL 	\
		-framework AppKit -framework OpenAL
NAME = doom-nukem
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -march=native -flto -ffast-math
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
ERASE = \033[2K\r
BLUE = \033[36m
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
END = \033[0m
.PHONY: all, clean, fclean, re


all: lib make_printf make_editor $(NAME)
	@printf "$(BLUE)> $(NAME) : $(YELLOW)Doom is dooming ready !$(END)\n"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(MINILIBX) $(LDLIBS) $^ -o $@
	@printf "\n$(BLUE)> $@ : $(GREEN)Success !$(END)\n\n"

make_editor:
	@make -C ./Editor

make_printf:
	@make -C ./ft_printf

lib:
	@make -C libft

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c includes/doom.h includes/mapfile.h includes/gif.h ft_printf/includes/ft_printf.h ft_printf/libftprintf.a includes/core_structs.h includes/keys.h includes/multithread_utils.h libft/libft.a
	@mkdir -p $(OBJ_PATH) $(OBJ_PATH)/$(SRC_SUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@printf "$(BLUE)|"

clean:
	@make -C ./Editor clean
	@make -C libft clean
	@make -C ./ft_printf clean
	@rm -rf $(OBJ_PATH)
	@printf "$(BLUE)> Deleted : $(RED)$(OBJ_PATH)$(END)\n"

fclean: clean
	@make -C ./Editor fclean
	@make -C libft fclean
	@make -C ./ft_printf fclean
	@rm -rf $(NAME)
	@printf "$(BLUE)> Deleted : $(RED)$(NAME)$(END)\n"

re: fclean all

norme:
	@norminette $(SRC) $(INC_PATH)
