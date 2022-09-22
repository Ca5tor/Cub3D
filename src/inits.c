/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 01:27:02 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/22 08:16:55 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

t_mlx	*init_mlx(void)
{
	t_mlx	*new_mlx;

	new_mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!new_mlx)
		return (NULL);

	new_mlx->p_mlx = mlx_init();
	new_mlx->p_win = mlx_new_window(new_mlx->p_mlx, WIDTH, HEIGHT, "cub3D");
	new_mlx->p_img = mlx_new_image(new_mlx->p_mlx, WIDTH, HEIGHT);
	new_mlx->p_addr = mlx_get_data_addr(new_mlx->p_img, &(new_mlx->bpp),
			&(new_mlx->len), &(new_mlx->endian));
	ft_bzero(new_mlx->p_addr, WIDTH * HEIGHT * (new_mlx->bpp / 8));
	return (new_mlx);
}

t_plr	*init_plr(t_map *map)
{
	t_plr	*new_plr;
	int		count;
	int		i;
	int		j;

	i = -1;
	new_plr = malloc(sizeof(t_plr));
	if (!new_plr)
		return (NULL);

	new_plr->pos.x = (int)((map->pl_x * BLOCK_SIZE) + (BLOCK_SIZE / 2));
	new_plr->pos.y = (int)((map->pl_y * BLOCK_SIZE) + (BLOCK_SIZE / 2));

	if (map->matrix[map->pl_y][map->pl_x] == MPN)
		new_plr->angl = POS_N;
	else if (map->matrix[map->pl_y][map->pl_x] == MPS)
		new_plr->angl = POS_S;
	else if (map->matrix[map->pl_y][map->pl_x] == MPW)
		new_plr->angl = POS_W;
	else
		new_plr->angl = POS_E;
	return (new_plr);
}

int	get_num_wall(t_map map)
{
	int		iters[2];
	int		count;

	iters[0] = -1;
	count = 0;
	while (++(iters[0]) < map.rows)
	{
		iters[1] = -1;
		while (++(iters[1]) < map.cols)
		{
			if (map.matrix[iters[0]][iters[1]] == 1)
				count++;
		}
	}
	return (count);
}

t_pos	*init_arr_pos(t_data *data)
{
	t_pos	*map_pos;
	int		iters[2];
	int		count;

	data->num_wall = get_num_wall(*data->map);
	map_pos = (t_pos *)malloc(sizeof(t_pos) * data->num_wall);
	count = 0;
	iters[0] = -1;
	while (++(iters[0]) < data->map->rows)
	{
		iters[1] = -1;
		while (++(iters[1]) < data->map->cols)
		{
			if (data->map->matrix[iters[0]][iters[1]] == 1)
			{
				map_pos[count].x = iters[1] * BLOCK_SIZE;
				map_pos[count].y = iters[0] * BLOCK_SIZE;
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
	if (!data)
		return (NULL);
	data->num_wall = 0;
	return (data);
}
