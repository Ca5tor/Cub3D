/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:49:01 by ltacos            #+#    #+#             */
/*   Updated: 2022/08/28 08:22:20 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#define DELTA 0.1f
#define BLOCK_SIZE 60
#define FOV (3.14 / 4)
#define HALF_FOV (FOV / 4)
#define MAX_DEPTH (WIDTH / BLOCK_SIZE)
#define NUM_RAYS	13
#define DELTA_RAY (FOV / (NUM_RAYS - 1))

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

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_plr
{
	t_pos	pos;
	double	angl;
}	t_plr;

typedef struct s_data
{
	t_plr	*plr;
	t_mlx	*mlx;
	t_pos	*map_pos;
}	t_data;


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

t_plr	*init_plr(void)
{
	t_plr	*new_plr;

	new_plr = malloc(sizeof(t_plr));
	new_plr->pos.x = HALF_WIDTH;
	new_plr->pos.y = HALF_HEIGHT;
	new_plr->angl = 0;
	return (new_plr);
}

t_pos	*init_arr_pos(void)
{
	t_pos	*map_pos;
		char	map[8][8] = {
	{'1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1'}
	};

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

double	find_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	find_min(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}

double	mod(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	_set_background(t_mlx *mlx)
{
	int	*img;
	int	i;

	i = 0;
	img = (int *)(mlx->p_addr);
	while (i < HEIGHT * WIDTH)
		img[i++] = BACKGROUND >> 2;
}

int	_put_pixel(t_pos *a, int color, t_mlx *mlx)
{
	char	*dst;

	if ((a->x < WIDTH && a->y < HEIGHT) && (a->x >= 0 && a->y >= 0))
	{
		dst = mlx->p_addr + (((int)a->y * mlx->len)
				+ ((int)a->x * (mlx->bpp / 8)));
		*(unsigned int *)dst = color;
	}
	return (1);
}

void	_dda_line(t_pos a, t_pos b, int color, t_mlx *mlx)
{
	t_pos	delta;
	t_pos	cur;
	double	step;

	delta.x = (b.x - a.x);
	delta.y = (b.y - a.y);
	step = find_max(mod(delta.x), mod(delta.y));
	delta.x /= step;
	delta.y /= step;
	cur = a;
	while ((int)step-- && _put_pixel(&cur, color, mlx))
	{
		cur.x += delta.x;
		cur.y += delta.y;
	}
}

void	draw_rect(t_pos start, int len, t_mlx *mlx)
{
	t_pos	tmp;

	tmp.x = start.x + len - 1;
	tmp.y = start.y - 1;
	int i = -1;
	while (++i < len - 1)
	{
		_dda_line(start, tmp, WALL_B, mlx);
		start.y += 1;
		tmp.y += 1;
	}
	//mlx_put_image_to_window(mlx->p_mlx, mlx->p_win, mlx->p_img, 0, 0);
}

void	print_map2d(t_data *data)
{
	int count = 31;
	int c = 0;
	while (c < count)
		draw_rect(data->map_pos[c++], BLOCK_SIZE, data->mlx);
}

void	move(int key, t_data *data)
{
	_set_background(data->mlx);
	print_map2d(data);
	
	//ray_cast(data);

	int	speed = 1.5;

	if (key == TURN_L)
		data->plr->angl -= 0.5 * DELTA * speed;
	if (key == TURN_R)
		data->plr->angl += 0.5 * DELTA * speed;

	double cos_a;
	double sin_a;

	speed = 50;
	cos_a = cos(data->plr->angl);
	sin_a = sin(data->plr->angl);

	if (key == M_DIRECTLY){
		data->plr->pos.x += cos_a * DELTA * speed;
		data->plr->pos.y += sin_a * DELTA * speed;
	}
	else if (key == M_BACK)
	{
		data->plr->pos.x -= cos_a * DELTA * speed;
		data->plr->pos.y -= sin_a * DELTA * speed;
	}
	else if (key == M_RIGHT)
	{
		data->plr->pos.x -= sin_a * DELTA * speed;
		data->plr->pos.y += cos_a * DELTA * speed;
	}
	else if (key == M_LEFT)
	{
		data->plr->pos.x += sin_a * DELTA * speed;
		data->plr->pos.y -= cos_a * DELTA * speed;
	}
	ray_cast(data);
	mlx_pixel_put(data->mlx->p_mlx, data->mlx->p_win, data-> plr->pos.x, data->plr->pos.y, PLAYER_B);
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->p_win, data->mlx->p_img, 0, 0);
}

int	cheack_pos(t_pos a, t_pos *b, t_pos *line)
{
	double ax, cx, bx, ay, cy, by;
	for (size_t i = 0; i < 31; i++)
	{
		ax = b[i].x - 2, ay = b[i].y - 2;
		cx = b[i].x + BLOCK_SIZE + 1, cy = b[i].y + BLOCK_SIZE + 1;
		bx = a.x, by = a.y;
		if (bx > ax && by > ay && bx < cx && by < cy)
		{
			*line = b[i];
			return 1;
		}
	}
	return 0;
}

int	cheack_pos_local(t_pos a, t_pos b, int num)
{
	double ax, cx, bx, ay, cy, by;

	ax = b.x, ay = b.y;
	cx = b.x + BLOCK_SIZE, cy = b.y + BLOCK_SIZE;
	bx = (int)a.x, by = (int)a.y;
	// if (num == 2)
	// {
	// 	printf("ax=%f ay=%f\n", ax, ay);
	// 	printf("cx=%f cy=%f\n", cx, cy);
	// 	printf("bx=%f by=%f\n", bx, by);
	// 	printf("HYI\n");
		if (bx > ax && by > ay && bx < cx && by < cy)
			return 1;
	// }
	// if (num == 1)
	// {
	// 	printf("ax=%f ay=%f\n", ax, ay);
	// 	printf("cx=%f cy=%f\n", cx, cy);
	// 	printf("bx=%f by=%f\n", bx, by);
	// 	if (bx > ax && by > ay && bx < cx && by < cy)
	// 		return 1;
	// }

	return 0;
}

double resize_line(double hvd, t_data *data, int j, t_pos f, int num)
{
	double cur_ang =  data->plr->angl - HALF_FOV + 0.1 * j;
	double cos_a = cos(cur_ang);
	double sin_a = sin(cur_ang);
	double x = hvd * cos_a +  data->plr->pos.x;
	double y = hvd * sin_a +  data->plr->pos.y;
	double fix_x = x / BLOCK_SIZE * BLOCK_SIZE;
	double fix_y = y / BLOCK_SIZE * BLOCK_SIZE;
			//printf("verticale\n");
	t_pos tmp;
	
	tmp.x = fix_x;
	tmp.y = fix_y;

	while (cheack_pos_local(tmp, f, num))
	{
		hvd -= 1;
		x = hvd * cos_a + data->plr->pos.x;
		y = hvd * sin_a + data->plr->pos.y;
		fix_x = x / BLOCK_SIZE * BLOCK_SIZE;
		fix_y = y / BLOCK_SIZE * BLOCK_SIZE;
		tmp.x = fix_x;
		tmp.y = fix_y;
	}
	return hvd;
}

void	ray_cast(t_data *data)
{
	// int left = data->plr->pos.x - data->plr->pos.x / BLOCK_SIZE * BLOCK_SIZE;
	// int top = data->plr->pos.y - data->plr->pos.y / BLOCK_SIZE * BLOCK_SIZE;
	// int right =  BLOCK_SIZE - (left);
	// int botton = BLOCK_SIZE - (top);

	for (int i = 0; i < NUM_RAYS; i++)
	{
		double cur_ang = data->plr->angl - HALF_FOV + 0.1 * i;
		double cos_a = cos(cur_ang);
		double sin_a = sin(cur_ang);
		double vd = 0, hd = 0;

		//verticale
		for (double j = 0; j < MAX_DEPTH; j += 0.1)
		{
			if (cos_a > 0)
				vd = cos_a + BLOCK_SIZE / cos_a * j + 1;
			else if (cos_a <= 0)
				vd = (-cos_a) + BLOCK_SIZE / (-cos_a) * j + 1;

			double x = vd * cos_a + data->plr->pos.x;
			double y = vd * sin_a + data->plr->pos.y;
			double fix_x = x / BLOCK_SIZE * BLOCK_SIZE;
			double fix_y = y / BLOCK_SIZE * BLOCK_SIZE;
			t_pos tmp;

			tmp.x = fix_x;
			tmp.y = fix_y;
			t_pos f;
			int num = 1;
				if (cheack_pos(tmp, data->map_pos, &f))
				{
					//vd = resize_line(vd, data, i, f, num);
					break ;
				}
		}
		//gorizontal
		for (double k = 0; k < MAX_DEPTH; k += 0.1)
		{
			if (sin_a > 0)
				hd = sin_a + BLOCK_SIZE / sin_a * k + 1;
			else if (sin_a <= 0)
				hd = (-sin_a) + BLOCK_SIZE / (-sin_a) * k + 1;
			double x = hd * cos_a + data->plr->pos.x;
			double y = hd * sin_a + data->plr->pos.y;
			double fix_x = x / BLOCK_SIZE * BLOCK_SIZE;
			double fix_y = y / BLOCK_SIZE * BLOCK_SIZE;
			t_pos tmp;

			tmp.x = fix_x;
			tmp.y = fix_y;
			t_pos f;
			int num = 2;

			if (cheack_pos(tmp, data->map_pos, &f))
			{
				//hd = resize_line(hd, data, i, f, num);
				break ;
			}
		}

		t_pos	toPos;
		double ray_size = find_min(hd, vd);
		printf("ray_size=%f\n", ray_size);
		printf("hd=%f vd=%f\n", hd, vd);
		toPos.x = ray_size * cos(cur_ang) + data->plr->pos.x;
		toPos.y = ray_size * sin(cur_ang) + data->plr->pos.y;
		_dda_line(data->plr->pos, toPos, FLOOR_B, data->mlx);
	}
}

void	print_pos_map(t_pos *a)
{
	for (int i = 0; i < 31; i++)
	{
		printf("i=%d aX=%f aY=%f\n", i, a[i].x, a[i].y);
	}
	// printf("i=%d aX=%f aY=%f\n", 0, a[0].x, a[0].y);
	// printf("i=%d aX=%f aY=%f\n", 1, a[0].x + BLOCK_SIZE, a[0].y + BLOCK_SIZE);
	
}

int	main(void)
{
	t_data	*data;
	t_mlx	*mlx;
	t_plr	*plr;
	t_pos	*map_pos;

	map_pos = init_arr_pos();
	mlx = init_mlx();
	plr = init_plr();
	data = init_data();

	data->plr = plr;
	data->mlx = mlx;
	data->map_pos = map_pos;

	_set_background(mlx);

	//отрисовка карты
	print_map2d(data);

	//отрисовка точки игрока
	mlx_pixel_put(mlx->p_mlx, mlx->p_win, plr->pos.x, plr->pos.y, PLAYER_B);
	
	//отрисовка угла обзора
	ray_cast(data);
	//print_pos_map(map_pos);
	mlx_put_image_to_window(mlx->p_mlx, mlx->p_win, mlx->p_img, 0, 0);

	mlx_hook(mlx->p_win, 2, (1L << 0), move, data);
	mlx_loop(mlx->p_mlx);
	free(mlx);
	free(plr);
	free(map_pos);
	free(data);
	return (0);
}
