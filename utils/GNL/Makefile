NAME	=	gnl.a
HEDR	=	get_next_line.h

CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
COMPILE	=	$(CC) $(FLAGS)

LIB		=	ar rc $(NAME)
RLIB	=	ranlib

RM		=	rm -f

SRC_L	=	get_next_line.c \
			get_next_line_utils.c
SRC_DIR	= ./
SRC		= $(addprefix $(SRC_DIR), $(SRC_L))

OBJ_DIR	= obj/
OBJ_L	= $(patsubst %.c, %.o, $(SRC_L))
OBJ		= $(addprefix $(OBJ_DIR), $(OBJ_L))

CYAN	= \033[0;36m
RED		= \033[0;31m
RESET	= \033[0m

.PHONY: all clean fclean re

all:	$(SRC) $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEDR)
	@mkdir -p $(OBJ_DIR)
	@$(COMPILE) -c $< -o $@
	@echo "$(OBJ_DIR): $(CYAN) was created$(RESET)"

$(NAME): $(OBJ)
	@$(LIB) $(OBJ)
	@$(RLIB) $(NAME)
	@echo "$(OBJ_DIR): $(CYAN) object files were created$(RESET)"
	@echo "$(NAME): $(CYAN)libft were created$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all