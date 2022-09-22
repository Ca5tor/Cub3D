/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 01:19:38 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/22 10:30:23 by ltacos           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	pars_arg_check(argc, argv);

	t_cub cub;
	cub.params.so.img = NULL;
	cub.params.no.img = NULL;
	cub.params.we.img = NULL;
	cub.params.ea.img = NULL;
	cub.params.ce_rgb = NULL;
	cub.params.fl_rgb = NULL;
	cub.map.matrix = NULL;
	cub.mlx = mlx_init();
	
	int ret = pars_read_cfg(argv[1], &cub);

	if (ret != 0)
	{
		printf("Fail. %s\n", argv[1]);
		pars_free_all(&cub);
		pars_exit_with_error(ret);
	}

	t_data	*data;
	t_mlx	*mlx;
	t_plr	*plr;
	t_pos	*map_pos;

	data = init_data();
	// if (!data)
	// 	return (0);
	data->map = malloc(sizeof(t_map));
	data->params = malloc(sizeof(t_params));
	// if (!data->params)
	// 	return 0;
	mlx = init_mlx();
	data->mlx = mlx;
	// data->mlx->p_mlx = cub.mlx;
	// data->mlx->p_win = cub.win;
	
	//get_param(data);

	data->map->cols = cub.map.cols;
	data->map->rows = cub.map.rows;
	data->map->matrix = cub.map.matrix;
	data->map->pl_x = cub.map.pl_x;
	data->map->pl_y = cub.map.pl_y;

	data->params->ce_rgb = cub.params.ce_rgb;
	data->params->fl_rgb = cub.params.fl_rgb;
	data->params->no = cub.params.no;
	data->params->so = cub.params.so;
	data->params->we = cub.params.we;
	data->params->ea = cub.params.ea;


	// if (!plr)
	// 	return (0);
	
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
