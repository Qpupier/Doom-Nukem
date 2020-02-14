# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/13 11:56:39 by qpupier      #+#   ##    ##    #+#        #
#    Updated: 2020/02/05 23:43:31 by qpupier     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SRC_PATH = sources
SRC_NAME = 	display/ft_putchar_fd.c 							\
			display/ft_putchar.c 								\
			display/ft_putendl_fd.c 							\
			display/ft_putendl.c 								\
			display/ft_putnbr_fd.c 								\
			display/ft_putnbr.c 								\
			display/ft_putstr_fd.c 								\
			display/ft_putstr.c 								\
			math/cplx/cplx_add.c 								\
			math/cplx/cplx_average.c 							\
			math/cplx/cplx_cos.c 								\
			math/cplx/cplx_cosh.c 								\
			math/cplx/cplx_discriminant.c 						\
			math/cplx/cplx_div.c 								\
			math/cplx/cplx_equ.c 								\
			math/cplx/cplx_exp.c 								\
			math/cplx/cplx_ln.c 								\
			math/cplx/cplx_modul.c 								\
			math/cplx/cplx_modul_2.c 							\
			math/cplx/cplx_mult.c 								\
			math/cplx/cplx_pow.c 								\
			math/cplx/cplx_remove.c 							\
			math/cplx/cplx_sin.c 								\
			math/cplx/cplx_sinh.c 								\
			math/cplx/cplx_swap.c 								\
			math/cplx/cplx_to_real.c 							\
			math/cplx/cplx_turn.c 								\
			math/cplx/cplx_make.c 								\
			math/cplx/ft_make_real.c 							\
			math/cplx/ft_real_to_cplx.c 						\
			math/geometry/create_2d_line_point_vec.c 			\
			math/geometry/create_2d_line_points.c 				\
			math/geometry/create_2d_ray.c 						\
			math/geometry/inter_2d_line_line.c 					\
			math/geometry/inter_2d_line_seg.c 					\
			math/geometry/inter_2d_ray_seg.c 					\
			math/geometry/point_2d_line_in_seg.c 				\
			math/geometry/point_line_in_seg.c 					\
			math/geometry/proj_point.c 							\
			math/line/line_check.c 								\
			math/line/line_create.c 							\
			math/line/line_equal.c 								\
			math/line/line_half_inter_seg.c 					\
			math/line/line_init.c 								\
			math/line/line_inter_line.c 						\
			math/line/line_inter_seg.c 							\
			math/line/line_parallel_line_point.c 				\
			math/line/line_perpendicular_line_point_plane.c 	\
			math/line/line_point.c 								\
			math/line/line_vec_dir.c 							\
			math/line/inter_line_plane.c 						\
			math/line/inter_seg_plane.c 						\
			math/matrix/matrix_mult_matrix.c 					\
			math/matrix/matrix_mult_vec.c 						\
			math/matrix/matrix_rotation.c 						\
			math/real/op_real.c 								\
			math/real/real_norm.c 								\
			math/real/real_normalize.c 							\
			math/real/real_oriented_angle.c 					\
			math/real/real_scale_product.c 						\
			math/real/real_turn.c 								\
			math/real/real_arraycpy.c 							\
			math/sys/sys_solve_1equ_1var_deg1.c 				\
			math/sys/sys_solve_2equ_2var_deg1.c 				\
			math/vec/vec_add.c 									\
			math/vec/vec_array_cpy.c 							\
			math/vec/vec_check.c 								\
			math/vec/vec_null.c 								\
			math/vec/vec_normalize.c 							\
			math/vec/vec_collinears.c 							\
			math/vec/vec_create.c 								\
			math/vec/vec_equal.c 								\
			math/vec/vec_mult.c 								\
			math/vec/vec_move.c 								\
			math/vec/vec_norm.c 								\
			math/vec/vec_product.c 								\
			math/vec/vec_sub.c 									\
			math/vec/vec_extract.c 								\
			math/vec/vec_rot.c 									\
			math/ft_abs.c 										\
			math/ft_average.c 									\
			math/ft_deg_to_rad.c 								\
			math/clamp.c 										\
			math/ft_digit_abs.c 								\
			math/ft_digit_hex_to_int.c 							\
			math/ft_max.c 										\
			math/ft_min.c 										\
			math/ft_mod.c 										\
			math/ft_pow.c 										\
			math/ft_sq.c 										\
			math/ft_sqrt.c 										\
			math/float_cmp.c 									\
			memory/ft_memalloc.c 								\
			memory/ft_memccpy.c 								\
			memory/ft_memchr.c 									\
			memory/ft_memcmp.c 									\
			memory/ft_memcpy.c 									\
			memory/ft_memdel.c 									\
			memory/ft_memmove.c 								\
			memory/ft_memset.c 									\
			mlx/colors/ft_color_average.c 						\
			mlx/colors/ft_color_hex_to_rgb.c 					\
			mlx/colors/ft_color_int_to_rgb.c 					\
			mlx/colors/ft_color_convert.c 						\
			mlx/colors/ft_color_rgb_random.c 					\
			mlx/colors/ft_color_rgb_to_hex.c 					\
			mlx/colors/ft_color_rgb_to_int.c 					\
			mlx/colors/ft_hex_color_complete.c 					\
			mlx/line/ft_line.c 									\
			mlx/line/ft_line_horiz.c 							\
			mlx/line/ft_line_straight.c 						\
			mlx/line/ft_line_straight_horiz.c 					\
			mlx/line/ft_line_straight_vert.c 					\
			mlx/line/ft_line_vert.c 							\
			mlx/ft_create_img.c 								\
			mlx/ft_img_dark.c 									\
			mlx/ft_pixel_put.c 									\
			mlx/ft_get_pixel.c 									\
			mlx/xpm_to_img.c 									\
			str/ft_stractrim.c 									\
			str/ft_strcat.c 									\
			str/ft_strchr.c 									\
			str/ft_strclr.c 									\
			str/ft_strcmp.c 									\
			str/ft_strcpy.c 									\
			str/ft_strcspn.c 									\
			str/ft_strctrim.c 									\
			str/ft_strdel.c 									\
			str/ft_strdup.c 									\
			str/ft_strequ.c 									\
			str/ft_striter.c 									\
			str/ft_str_getaocc.c 								\
			str/ft_count_dstr.c 								\
			str/ft_striteri.c 									\
			str/ft_strjoin.c 									\
			str/ft_strlcat.c 									\
			str/ft_strlen.c 									\
			str/ft_strlen_words.c 								\
			str/ft_strmap.c 									\
			str/ft_strmap_display.c 							\
			str/ft_strmapi.c 									\
			str/ft_strncat.c 									\
			str/ft_strncdelete.c 								\
			str/ft_strncmp.c 									\
			str/ft_strncpy.c 									\
			str/ft_strnequ.c 									\
			str/ft_strnew.c 									\
			str/ft_strnstr.c 									\
			str/ft_strrchr.c 									\
			str/ft_strsplit.c 									\
			str/ft_strstr.c 									\
			str/ft_str_isnumber.c 								\
			str/ft_strsub.c 									\
			str/ft_strtrim.c 									\
			str/ft_strtrimsplit.c 								\
			ft_atoi.c 											\
			ft_atof.c 											\
			ft_atoi_hexa.c 										\
			ft_bzero.c 											\
			ft_count_words.c 									\
			ft_error.c 											\
			ft_exit.c 											\
			ft_find.c 											\
			ft_ftoa.c 											\
			ft_intlen.c 										\
			ft_isalnum.c 										\
			ft_isalpha.c 										\
			ft_isascii.c 										\
			ft_isdigit.c 										\
			ft_isnumber.c 										\
			ft_isprint.c 										\
			ft_itoa.c 											\
			ft_occur.c 											\
			ft_splitdel.c 										\
			ft_swap.c 											\
			ft_fileexists.c 									\
			ft_tolower.c 										\
			ft_toupper.c 										\
			ft_realloc.c 										\
			ft_calloc.c 										\
			get_next_line.c
SRC_SUP = {display,math,math/line,math/cplx,math/geometry,math/matrix,math/real,math/vec,math/sys,memory,mlx,mlx/colors,mlx/line,str}
OBJ_PATH = .objects
INC_PATH = includes
CPPFLAGS = -I $(INC_PATH)
NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -march=native -flto -ffast-math
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

ERASE = \033[2K\r
BLUE = \033[36m
WHITE = \033[37m
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
END = \033[0m

.PHONY: all, clean, fclean, re

all: mlx $(NAME)

$(NAME): $(OBJ)
	@ar -rc $@ $^
	@ranlib $@
	@printf "$(ERASE)$(BLUE)> libft : $(GREEN)Success !$(END)\n"

mlx:
	@make -C ../minilibx_macos

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c ../minilibx_macos/libmlx.a includes/libft.h includes/get_next_line.h
	@mkdir -p $(OBJ_PATH) $(OBJ_PATH)/$(SRC_SUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@printf "$(ERASE)$(BLUE)> Compilation :$(END) $<"

clean:
	@rm -rf $(OBJ_PATH)
	@printf "$(BLUE)> Deleted : $(RED)libft/$(OBJ_PATH)$(END)\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(BLUE)> Deleted : $(RED)$(NAME)$(END)\n"
	@make -C ../minilibx_macos clean

re: fclean all

norme:
	@norminette $(SRC) $(INC_PATH)
