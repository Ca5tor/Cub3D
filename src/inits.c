/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 01:27:02 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/17 03:58:51 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

t_mlx	*init_mlx(void)
{
	t_mlx	*new_mlx;

	new_mlx = (t_mlx *)malloc(sizeof(t_mlx));
	new_mlx->p_mlx = mlx_init();
	new_mlx->p_win = mlx_new_window(new_mlx->p_mlx, WIDTH, HEIGHT, "cub3D");
	new_mlx->p_img = mlx_new_image(new_mlx->p_mlx, WIDTH, HEIGHT);
	new_mlx->p_addr = mlx_get_data_addr(new_mlx->p_img, &(new_mlx->bpp),
			&(new_mlx->len), &(new_mlx->endian));
	ft_bzero(new_mlx->p_addr, WIDTH * HEIGHT * (new_mlx->bpp / 8));
	return (new_mlx);
}

		char	map[8][8] = {
	{'1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', 'P', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1'}
	};

t_plr	*init_plr(void)
{
	t_plr	*new_plr;
	int		count;
	int		i;
	int		j;

	count = 0;
	i = -1;
	new_plr = malloc(sizeof(t_plr));
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
		{
			if (map[i][j] == 'P')
			{
				new_plr->pos.x = j * BLOCK_SIZE;
				new_plr->pos.y = i * BLOCK_SIZE;
				new_plr->angl = 0;
				count++;
			}
		}
	}
	return (new_plr);
}

t_pos	*init_arr_pos(void)
{
	t_pos	*map_pos;

	map_pos = (t_pos *)malloc(sizeof(t_pos) * 31);
	int count = 0;
	int i = -1;
	while (++i < 8)
	{
		int j = -1;
		while (++j < 8)
		{
			if (map[i][j] == '1')
			{
				map_pos[count].x = j * BLOCK_SIZE;
				map_pos[count].y = i * BLOCK_SIZE;
				count++;
			}
		}
	}
	return (map_pos);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	return (data);
}