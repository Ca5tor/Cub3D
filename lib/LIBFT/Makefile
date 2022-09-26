NAME	=	libft.a
HEDR	=	libft.h

CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
COMPILE	=	$(CC) $(FLAGS)

LIB		=	ar rc $(NAME)
RLIB	=	ranlib

RM		=	rm -f

SRC_L	=	ft_atoi.c \
			ft_isdigit.c \
			ft_split.c \
			ft_strcmp.c \
			ft_strlen.c \
			ft_strnstr.c \
			ft_strtrim.c \
			ft_bzero.c \
			ft_putstr_fd.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strncmp.c \
			ft_strstr.c \
			ft_substr.c
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
	@echo "$(NAME): $(CYAN)object files were created$(RESET)"
	@echo "$(NAME): $(CYAN)libft were created$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all