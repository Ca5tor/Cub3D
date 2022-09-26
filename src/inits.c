/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:38:23 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 20:37:49 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	init_cub(t_cub *cub)
{
	cub->params.so.img = NULL;
	cub->params.no.img = NULL;
	cub->params.we.img = NULL;
	cub->params.ea.img = NULL;
	cub->params.ce_rgb = NULL;
	cub->params.fl_rgb = NULL;
	cub->map.matrix = NULL;
	cub->mlx = mlx_init();
}

t_plr	*init_plr(const t_map map)
{
	t_plr	*new_plr;

	new_plr = malloc(sizeof(t_plr));
	if (!new_plr)
		return (NULL);
	new_plr->pos.pos[X] = (int)((map.pl_x * TILE) + (TILE / 2));
	new_plr->pos.pos[Y] = (int)((map.pl_y * TILE) + (TILE / 2));
	if (map.matrix[map.pl_y][map.pl_x] == SO_N)
	{
		new_plr->angl = OSA_N;
		return (new_plr);
	}
	else if (map.matrix[map.pl_y][map.pl_x] == SO_S)
	{
		new_plr->angl = OSA_S;
		return (new_plr);
	}
	else if (map.matrix[map.pl_y][map.pl_x] == SO_W)
	{
		new_plr->angl = OSA_W;
		return (new_plr);
	}
	new_plr->angl = OSA_E;
	return (new_plr);
}

t_mlx	*init_mlx(const t_cub cub)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->p_mlx = cub.mlx;
	mlx->p_win = mlx_new_window(mlx->p_mlx, WIDTH, HEIGHT, "cub3D");
	mlx->p_img = mlx_new_image(mlx->p_mlx, WIDTH, HEIGHT);
	mlx->p_addr = mlx_get_data_addr(mlx->p_img, &(mlx->bpp), \
		&(mlx->len), &(mlx->endian));
	ft_bzero(mlx->p_addr, WIDTH * HEIGHT * (mlx->bpp / 8));
	return (mlx);
}

t_pos_int	*init_arr_pos(t_data *data, const t_map map)
{
	t_pos_int	*map_pos;
	int			iters[2];
	int			count;

	data->num_wall = get_num_wall(map);
	map_pos = malloc(sizeof(t_pos_int) * data->num_wall);
	if (!map_pos)
		return (NULL);
	count = 0;
	iters[0] = -1;
	while (++(iters[0]) < map.rows)
	{
		iters[1] = -1;
		while (++(iters[1]) < map.cols)
		{
			if (map.matrix[iters[0]][iters[1]] == POS_WALL)
			{
				map_pos[count].pos[X] = iters[1] * TILE;
				map_pos[count].pos[Y] = iters[0] * TILE;
				count++;
			}
		}
	}
	return (sort_pos(map_pos, data->num_wall));
}

t_data	*init_data(const t_cub cub)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->mlx = init_mlx(cub);
	if (!data->mlx)
		return (free(data), NULL);
	data->num_wall = 0;
	data->clr_fons[CLR_SKY] = create_rgb(cub.params.ce_rgb[0], \
		cub.params.ce_rgb[1], cub.params.ce_rgb[2]);
	data->clr_fons[CLR_FLOOR] = create_rgb(cub.params.fl_rgb[0], \
		cub.params.fl_rgb[1], cub.params.fl_rgb[2]);
	data->texture[IMG_NO] = cub.params.no;
	data->texture[IMG_SO] = cub.params.so;
	data->texture[IMG_WE] = cub.params.we;
	data->texture[IMG_EA] = cub.params.ea;
	data->plr = init_plr(cub.map);
	if (!data->plr)
		return (free(data->mlx), free(data), NULL);
	data->map_pos = init_arr_pos(data, cub.map);
	if (!data->map_pos)
		return (free(data->mlx), free(data->map_pos), free(data), NULL);
	return (data);
}
