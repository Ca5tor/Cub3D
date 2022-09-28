NAME		=	cub3D
NAME_BONUS	=	cub3D_Bonus

CC		=	gcc
FLAGS	=	 -g -Wall -Werror -Wextra -O2

GNL		=	$(GNL_DIR)gnl.a
GNL_DIR	=	 ./lib/GNL/

LIBFT		=	$(LIBFT_DIR)libft.a
LIBFT_DIR	=	./lib/LIBFT/

MLX 		=	$(MLX_DIR)libmlx_Linux.a
MLX_DIR		=	./lib/mlx-linux/
MLX_FLAGS	=	-lm -lmlx -lX11 -lXext -lGL

HEADER	=	inc/cub3D.h \
			inc/consts.h \
			inc/setting.h\
			inc/fun_prototypes.h\
			inc/struct.h\
			lib/mlx-linux/mlx.h \
			lib/LIBFT/libft.h \
			lib/GNL/get_next_line.h

SOURCES_L	=	main.c utils.c \
				utils_move.c draw.c move.c \
				utils_draw.c utils_ray_casting.c \
				inits.c ray_casting.c utils_init.c \
				pars_0.c pars_1.c pars_2.c pars_3.c \
				pars_4.c pars_5.c pars_6.c

B_SOURCES_L	=	main_bonus.c utils.c \
				utils_move.c draw_bonus.c move.c \
				utils_draw.c utils_ray_casting.c \
				inits.c ray_casting.c utils_init.c \
				pars_0.c pars_1.c pars_2.c pars_3.c \
				pars_4.c pars_5.c pars_6.c

SOURCES_DIRECTORY	= ./src/

SOURCES			= $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_L))
OBJ_DIR			= objects/
OBJECTS_LIST	= $(patsubst %.c, %.o, $(SOURCES_L))
OBJECTS			= $(addprefix $(OBJ_DIR), $(OBJECTS_LIST))

B_SOURCES		= $(addprefix $(SOURCES_DIRECTORY), $(B_SOURCES_L))
B_OBJ_DIR		= objects_bonus/
B_OBJECTS_LIST	= $(patsubst %.c, %.o, $(B_SOURCES_L))
B_OBJECTS		= $(addprefix $(B_OBJ_DIR), $(B_OBJECTS_LIST))

.PHONY: all bonus clean clean_b fclean fclean_b re re_b

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER) 
	@make -C $(LIBFT_DIR)
	@make -C $(GNL_DIR)
	@make -C $(MLX_DIR)
	@$(CC) $(FLAGS) $(OBJECTS) $(GNL) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "\n$(NAME): $(CYAN)$(NAME) were created$(RESET)"

$(OBJ_DIR)%.o : $(SOURCES_DIRECTORY)%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@make -sC $(LIBFT_DIR) clean
	@make -sC $(GNL_DIR) clean
	@make -sC $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(MLX)
	@rm -f $(LIBFT)
	@rm -f $(GNL)
	@rm -f $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(B_OBJECTS) $(HEADER) 
	@make -C $(LIBFT_DIR)
	@make -C $(GNL_DIR)
	@make -C $(MLX_DIR)
	@$(CC) $(FLAGS) $(B_OBJECTS) $(GNL) $(LIBFT) $(MLX_FLAGS) -o $(NAME_BONUS)
	@echo "\n$(NAME_BONUS): $(CYAN)$(NAME_BONUS) were created$(RESET)"

$(B_OBJ_DIR)%.o : $(SOURCES_DIRECTORY)%.c $(HEADER)
	@mkdir -p $(B_OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

clean_b:
	@make -sC $(LIBFT_DIR) clean
	@make -sC $(GNL_DIR) clean
	@make -sC $(MLX_DIR) clean
	@rm -rf $(B_OBJ_DIR)

fclean_b: clean_b
	@rm -f $(MLX)
	@rm -f $(LIBFT)
	@rm -f $(GNL)
	@rm -f $(NAME_BONUS)

re:	fclean all

re_b: fclean_b bonus
