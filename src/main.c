/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 01:19:38 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/22 08:11:51 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

t_pos	*sort_pos(t_data *data)
{
	t_pos	*a;
	t_pos	tmp;
	int		i;
	int		j;

	a = data->map_pos;
	i = data->num_wall;
	while (--i > 0)
	{
		j = -1;
		while (++j < i)
		{
			if (a[j].x > a[j + 1].x)
			{
				tmp.x = a[j].x;
				tmp.y = a[j].y;
				a[j].x = a[j + 1].x;
				a[j].y = a[j + 1].y;
				a[j + 1].x = tmp.x;
				a[j + 1].y = tmp.y;
			}
		}
	}
	return (a);
}

int	main(void)
{
	t_data	*data;
	t_mlx	*mlx;
	t_plr	*plr;
	t_pos	*map_pos;

	data = init_data();
	if (!data)
		return (0);
	data->map = malloc(sizeof(t_map));
	data->params = malloc(sizeof(t_params));
	if (!data->params)
		return 0;
	mlx = init_mlx();
	data->mlx = mlx;
	//printf("1clr=%d %d %d \n", data->params->ce_rgb[0], data->params->ce_rgb[1], data->params->ce_rgb[2]);
	get_param(data);
	//printf("1clr=%d %d %d \n", data->params->ce_rgb[0], data->params->ce_rgb[1], data->params->ce_rgb[2]);
	//plr = init_plr(data->map);
	if (!plr)
		return (0);
	//printf("2clr=%d %d %d \n", data->params->ce_rgb[0], data->params->ce_rgb[1], data->params->ce_rgb[2]);
	data->plr = init_plr(data->map);
	//map_pos = init_arr_pos(data);
	data->map_pos =  init_arr_pos(data);
	data->map_pos = sort_pos(data);


	draw_all(data);

	mlx_hook(mlx->p_win, 2, (1L << 0), move, data);
	mlx_hook(mlx->p_win, 17, 0, close_win, data);
	mlx_loop(mlx->p_mlx);

	free(mlx);
	free(plr);
	free(map_pos);
	free(data->map);
	free(data->params);
	free(data);
	return (0);
}
