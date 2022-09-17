NAME	=	cub3D

CC		=	gcc
FLAGS	=	 -g

GNL			=	$(GNL_DIR)gnl.a
GNL_DIR 	=	 ./utils/GNL/

LIBFT 		=	$(LIBFT_DIR)libft.a
LIBFT_DIR 	=	./utils/LIBFT/

MLX 			=	$(MLX_DIR)libmlx_Linux.a
MLX_DIR	=	./mlx-linux/
MLX_FLAGS 			=	-lm -lmlx -lX11 -lXext -lGL

HEADER		=	inc/cub3D.h \
				inc/configure.h\
				inc/fun_prototypes.h\
				inc/structs.h\
				mlx-linux/mlx.h \
				utils/LIBFT/libft.h \
				utils/GNL/get_next_line.h

SOURCES_L	=	draw_utils.c inits.c main.c ray_cast.c move.c utils.c
	
SOURCES_DIRECTORY	= ./src/
SOURCES 			= $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_L))
OBJ_DIR 			= objects/
OBJECTS_LIST 		= $(patsubst %.c, %.o, $(SOURCES_L))
OBJECTS				= $(addprefix $(OBJ_DIR), $(OBJECTS_LIST))

.PHONY: all clean fclean re test norm

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

re:	fclean all