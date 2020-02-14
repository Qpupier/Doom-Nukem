
NAME	= libftprintf.a
SRCS 	= ft_printf.c utils.c length_conversion.c
DESC	= ft_printf
SRCS	+= handlers/ouxp.c
SRCS	+= handlers/cs.c
SRCS	+= handlers/diu.c handlers/digitbase_tools.c
SRCS	+= handlers/floats.c handlers/floats_tools.c
SRCS	+= parser/field.c parser/type.c parser/utilities.c parser/general.c

OBJ_DIR = ./.objs
SRC_DIR = ./srcs
INC_DIR = ./includes

INC_H	= includes/ft_printf.h

CFLAGS	:= -Wall -Wextra -Werror
OBJS	:= $(patsubst %.c,$(OBJ_DIR)/%.o, $(SRCS))

ERASE	= \033[2K\r
BLUE	= \033[36m
WHITE	= \033[37m
END		= \033[0m
GREEN	= \033[0;32m
RED		= \033[0;31m
YELLOW	= \033[0;33m

all: print_name $(NAME)

$(NAME): $(OBJS)
		@ar -rc $(NAME) $(OBJS)
		@ranlib $(NAME)
		@printf "\n-> $(GREEN)$(DESC)$(WHITE): success.$(END)\n"

print_name:
	@printf "Compiling $(GREEN)$(DESC)$(WHITE)\n"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_H)
		@mkdir -p .objs
		@mkdir -p .objs/handlers
		@mkdir -p .objs/parser
		@gcc $(CFLAGS) -I$(INC_DIR) -o $@ -c $<
		@printf "$(YELLOW)|"

clean:
		@rm -rf $(OBJS)
		@printf "$(ERASE)> $(YELLOW)$(DESC)$(WHITE): objects deleted.$(END)\n"

fclean : clean
		@rm -f $(NAME)
		@rm -rf $(OBJ_DIR)
		@printf "$(ERASE)> $(YELLOW)$(DESC)$(WHITE): library deleted.$(END)\n"

re:		fclean all
