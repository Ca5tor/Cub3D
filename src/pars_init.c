/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:54:24 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/22 08:14:48 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static	int	map[9][8] = {
	{0, 1, 1, 1, 1, 1, 1, 0},
	{1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 1, 1},
	{1, 0, 35, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 0, 1, 1},
	{0, 1, 0, 1, 0, 1, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 0}
	};

void	get_param(t_data *data)
{
	data->map->matrix = (int**)malloc(9 * sizeof(int*));
	if (!data->map->matrix)
		return ;
	for (int i = 0; i <9; i++)
	{
		data->map->matrix[i] = (int*)malloc(8 * sizeof(int));
		for (int j = 0; j < 8; j++)
		{
			data->map->matrix[i][j] = map[i][j];
		}
	}

	data->map->cols = 8;
	data->map->rows = 9;
	data->map->pl_x = 2;
	data->map->pl_y = 5;

	data->params->no.img = mlx_xpm_file_to_image(data->mlx->p_mlx, \
		"./textures/eagle.xpm", &data->params->no.width, &data->params->no.height);
	data->params->so.img = mlx_xpm_file_to_image(data->mlx->p_mlx, \
		"./textures/grass.xpm", &data->params->no.width, &data->params->no.height);
	data->params->ea.img = mlx_xpm_file_to_image(data->mlx->p_mlx, \
		"./textures/stone.xpm", &data->params->no.width, &data->params->no.height);
	data->params->we.img = mlx_xpm_file_to_image(data->mlx->p_mlx, \
		"./textures/redbrick.xpm", &data->params->no.width, &data->params->no.height);

	data->params->fl_rgb = malloc(sizeof(int) * 3);
	data->params->fl_rgb[0] = 3;
	data->params->fl_rgb[1] = 92;
	data->params->fl_rgb[2] = 13;
	data->params->ce_rgb = malloc(sizeof(int) * 3);
	data->params->ce_rgb[0] = 0;
	data->params->ce_rgb[1] = 114;
	data->params->ce_rgb[2] = 163;

}
