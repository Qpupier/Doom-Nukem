# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/13 11:56:39 by qpupier      #+#   ##    ##    #+#        #
#    Updated: 2020/02/10 10:24:45 by slopez      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SRC_PATH = sources
SRC_NAME = main.c mlx_utils.c events.c circle.c ui.c selector.c utility_lst.c
SRC_NAME += delete.c createmap.c texture.c display.c tweak_wall.c layer.c
SRC_NAME += selected_obj.c list_pushback.c character.c tools.c ui_mouse.c
SRC_NAME += picktool.c delete_bis.c mouse_events.c touch.c reset.c check.c
SRC_NAME += load_textures.c touch_wall.c select_algo.c create_pw.c
SRC_NAME += create_room.c init.c tools_event.c display_icons.c tweak_obj.c
SRC_NAME += action_obj.c tweak_wall_bis.c
SRC_SUP =
OBJ_PATH = .objects
INC_PATH = includes
CPPFLAGS = -I $(INC_PATH) -I../libft/includes
LDFLAGS = -L ../libft
LDLIBS = ../libft/libft.a
MINILIBX = -I ../minilibx_macos -L ../minilibx_macos -lmlx -framework OpenGL -framework AppKit
NAME = DoomMapEditor
CC = gcc
CFLAGS = -Wall -Wextra -O3 -march=native
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

all: lib $(NAME)
	@printf "$(BLUE)> $(NAME) : $(YELLOW)Editor ready !$(END)\n"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(MINILIBX) $(LDLIBS) $^ -o $@
	@printf "$(ERASE)$(BLUE)> $@ : $(GREEN)Success !$(END)\n\n"
	@mv $(NAME) ../$(NAME)

lib:
	@make -C ../libft

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c ../libft/libft.a ../minilibx_macos/libmlx.a includes/editor.h includes/keys.h
	@mkdir -p $(OBJ_PATH) $(OBJ_PATH)/$(SRC_SUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@printf "$(ERASE)$(BLUE)> Compilation :$(END) $<"

clean:
	@make -C ../libft clean
	@rm -rf $(OBJ_PATH)
	@printf "$(BLUE)> Deleted : $(RED)$(OBJ_PATH)$(END)\n"

fclean: clean
	@make -C ../libft fclean
	@rm -rf $(NAME)
	@rm -rf ../$(NAME)
	@printf "$(BLUE)> Deleted : $(RED)$(NAME)$(END)\n"

re: fclean all

norme:
	@norminette $(SRC) $(INC_PATH)
