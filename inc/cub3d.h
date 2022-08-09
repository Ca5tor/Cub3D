/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:16:59 by ltacos            #+#    #+#             */
/*   Updated: 2022/07/21 00:31:45 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>

# include "../utils/LIBFT/libft.h"
# include "../utils/GNL/get_next_line.h"
# include "../mlx-linux/mlx.h"

/*	size window	*/
# define WIDTH 1600
# define HEIGHT 900

typedef struct s_cub
{
	char	**idntfrs[6];
	char	**map;
}	t_cub;

typedef struct s_mlx
{
	void	*p_mlx;
	void	*p_win;
	void	*p_img;
	char	*p_addr;
	int		bpp;
	int		len;
	int		endian;
}	t_mlx;


typedef struct s_data
{
	char	**file_lines;
	t_cub	*cub;
}	t_data;

void	exit_err(char *msg);

char	**reader_file(char *file);

t_data	*init_data(void);
t_cub	*init_cub(void);

t_mlx	*t_mlx_init(void);

#endif