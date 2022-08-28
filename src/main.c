/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 01:31:27 by ltacos            #+#    #+#             */
/*   Updated: 2022/08/26 20:06:33 by ltacos           ###   ########.fr       */
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

// t_map	*init_map(void){
// 	t_map	*new_map;
// 	int	map[8][8] = {
// 		{1, 1, 1, 1, 1, 1, 1, 1},
// 		{1, 0, 0, 1, 0, 0, 0, 1},
// 		{1, 0, 1, 1, 0, 0, 0, 1},
// 		{1, 0, 0, 0, 1, 0, 0, 1},
// 		{1, 0, 0, 0, 0, 1, 0, 1},
// 		{1, 0, 0, 7, 0, 1, 0, 1},
// 		{1, 0, 0, 0, 0, 0, N, 1},
// 		{1, 1, 1, 1, 1, 1, 1, 1}
// 	};

// 	new_map = (t_map *)malloc(sizeof(t_map));
// 	new_map->pp_map = &map;
// 	new_map->m_height = 8;
// 	new_map->m_width = 8;
// 	new_map->m_size = 64;
// 	return (new_map);
// }



void	init_data(t_data *data)
{
	char	map[8][8] = {\
		{'1', '1', '1', '1', '1', '1', '1', '1'}, \
		{'1', '0', '0', '1', '0', '0', '0', '1'}, \
		{'1', '0', '1', '1', '0', '0', '0', '1'}, \
		{'1', '0', '0', '0', '1', '0', '0', '1'}, \
		{'1', '0', '0', '0', '0', '1', '0', '1'}, \
		{'1', '0', '0', 'N', '0', '1', '0', '1'}, \
		{'1', '0', '0', '0', '0', '0', '0', '1'}, \
		{'1', '1', '1', '1', '1', '1', '1', '1'}
	};
	char		**maps;

	maps = malloc(sizeof(char *) * 8);
	for (int i = 0; i < 8; i++)
	{
		maps[i] = &map[i][0];
	}

	data->mlx = init_mlx();
	data->map_obj = init_2d_map(maps);

	t_player	*plyr;
	//plyr->obj = malloc(sizeof(t_obj));
	plyr = malloc(sizeof(plyr));
	if (!plyr)
		return ;
	int i = -1;
	while (++i < 8)
	{
		int j = -1;
		while (++j < 8)
		{
			if(map[i][j] == 'N')
			{
				plyr->obj.x = j;
				plyr->obj.y = i;
				break ;
			}
		}
		
		// if (data->map_obj->obj[i].type == PR_N || \
		// 	data->map_obj->obj[i].type == PR_S || \
		// 	data->map_obj->obj[i].type == PR_E || \
		// 	data->map_obj->obj[i].type == PR_W)
		// {
		// 	plyr->obj = data->map_obj->obj[i];
		// 	break ;
		// }
	}
	plyr->angle = 0;
	data->plyr = plyr;
}

int	find_key(int key)
{
	if (key == M_DIRECTLY || key == M_BACK || key == M_LEFT || key == M_RIGHT)
		return (1);
	else if (key == TURN_L || key == TURN_R)
		return (2);
	else if (key == EXIT_WINDW)
		return (3);
	return (0);
}

int	close_win(void)
{
	//free_struct(param);
	exit(0);
	return (0);
}

void	movement(int key, t_data *data, t_player *plyr)
{
	double cos_a;
	double sin_a;
	double delta = 0.1;
	int speed = 3;

	cos_a = cos(data->plyr->angle);
	sin_a = sin(data->plyr->angle);
	
	if (key == M_DIRECTLY){
		plyr->obj.x += cos_a * delta * speed;
		plyr->obj.y += sin_a * delta * speed;
	}
	else if (key == M_BACK)
	{
		plyr->obj.x -= cos_a * delta * speed;
		plyr->obj.y -= sin_a * delta * speed;
	}
	//	plyr->obj.y += 0.1;
	else if (key == M_RIGHT)
	{
		plyr->obj.x -= sin_a * delta * speed;
		plyr->obj.y += cos_a * delta * speed;
	}
	//	plyr->obj.x -= 0.1;
	else if (key == M_LEFT)
	{
		plyr->obj.x += sin_a * delta * speed;
		plyr->obj.y -= cos_a * delta * speed;
	}
	//	plyr->obj.x += 0.1;
	draw_player(data);
}

void	turn_cam(int key, t_data *data)
{
	
	if (key == TURN_L)
		data->plyr->angle -= 0.05;
	if (key == TURN_R)
		data->plyr->angle += 0.05;
	draw_player(data);
}

int	deal_key(int key, t_data *data)
{
	int	deal;
	(void) data;
	deal = find_key(key);
	if (deal == 0)
		return (0);
	if (deal == 1)
		movement(key, data, data->plyr);
	if (deal == 2)
		turn_cam(key, data);
	if (deal == 3)
		close_win();
	//draw(data);
	return (0);
}



int	main(void)
{
	t_data	data;

	init_data(&data);
	draw(&data);
	printf("DONE123\n");
	draw_player(&data);
	
	mlx_hook(data.mlx->p_win, 2, (1L << 0), deal_key, &data);
	mlx_hook(data.mlx->p_win, 17, 0, close_win, &data);
	mlx_loop(data.mlx->p_mlx);
	return (0);
}
