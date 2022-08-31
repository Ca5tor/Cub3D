/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:45:55 by ltacos            #+#    #+#             */
/*   Updated: 2022/08/31 11:28:05 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#define DELTA 0.12f
#define BLOCK_SIZE 42
#define FOV (3.1415926535 / 3)
#define HALF_FOV (FOV / 2)
#define MAX_DEPTH (WIDTH / BLOCK_SIZE * BLOCK_SIZE)
#define NUM_RAYS	400
#define DELTA_RAY (FOV / (NUM_RAYS - 1))
#define DIST (NUM_RAYS / (2 * tan(HALF_FOV)))
#define PROJ_COEFF (3 * DIST * BLOCK_SIZE) 
#define SCALE (WIDTH / NUM_RAYS) 

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

	int count = 0;
	int i = -1;
	new_plr = malloc(sizeof(t_plr));
	while (++i < 8)
	{
		int j = -1;
		while (++j < 8)
		{
			if (map[i][j] == 'P')
			{
				new_plr->pos.x = j * BLOCK_SIZE ;//+ (BLOCK_SIZE / 2);
				new_plr->pos.y = i * BLOCK_SIZE ;//+ (BLOCK_SIZE / 2);
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

void	draw_rect21(t_pos start, int w, int h, t_mlx *mlx, int color)
{
	t_pos	tmp;

	tmp.x = (start.x + w / BLOCK_SIZE);
	tmp.y = start.y;
	int i = -1;
	
	while (++i < h)
	{
		_dda_line(start, tmp, color, mlx);
		start.y++;
		tmp.y++;
	}
}

int	close_win(t_data *data)
{
	free(data->mlx);
	free(data->plr);
	free(data->map_pos);
	free(data);
	exit(0);
	return (0);
}

void	draw_all(t_data *data)
{
	//_set_background(data->mlx);
	t_pos pos_floor, pos_sky;
	pos_sky.x = 0;
	pos_sky.y = 0;

	pos_floor.x = 0;
	pos_floor.y = HALF_HEIGHT;
	//рисуем пол и небо
	draw_rect21(pos_sky, WIDTH * BLOCK_SIZE, HEIGHT / 2, data->mlx, 0x4682B4);
	draw_rect21(pos_floor, WIDTH * BLOCK_SIZE, HEIGHT / 2, data->mlx, 0x008000);
	
	//print_map2d(data);
	ray_cast2(data);
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->p_win, data->mlx->p_img, 0, 0);
}

void	move(int key, t_data *data)
{
	int	speed = 1.5;

	if (key == TURN_L)
	{
		data->plr->angl -= 0.5 * DELTA * speed;
		draw_all(data);
		return ;
	}
	if (key == TURN_R)
	{
		data->plr->angl += 0.5 * DELTA * speed;
		draw_all(data);
		return ;
	}
		

	double cos_a;
	double sin_a;

	speed = 50;
	cos_a = cos(data->plr->angl);
	sin_a = sin(data->plr->angl);

	if (key == M_DIRECTLY){
		data->plr->pos.x += cos_a * DELTA * speed;
		data->plr->pos.y += sin_a * DELTA * speed;
		draw_all(data);
		return ;
	}
	if (key == M_BACK)
	{
		data->plr->pos.x -= cos_a * DELTA * speed;
		data->plr->pos.y -= sin_a * DELTA * speed;
		draw_all(data);
		return ;
	}
	if (key == M_RIGHT)
	{
		data->plr->pos.x -= sin_a * DELTA * speed;
		data->plr->pos.y += cos_a * DELTA * speed;
		draw_all(data);
		return ;
	}
	if (key == M_LEFT)
	{
		data->plr->pos.x += sin_a * DELTA * speed;
		data->plr->pos.y -= cos_a * DELTA * speed;
		draw_all(data);
		return ;
	}
	if (key == EXIT_WINDW)
		close_win(data);
	draw_all(data);
}

int	cheack_pos(t_pos a, t_pos *b)
{
	double ax, cx, bx, ay, cy, by;
	for (int i = 0; i < 31; i++)
	{
		ax = b[i].x, ay = b[i].y;
		cx = b[i].x + BLOCK_SIZE, cy = b[i].y + BLOCK_SIZE;
		bx = a.x, by = a.y;
		if (bx > ax && by > ay && bx < cx && by < cy)
			return 1;
	}
	return 0;
}

#define BLOCK3D (BLOCK_SIZE * BLOCK_SIZE)

void	ray_cast2(t_data *data){
	int ox, oy;
	double cur_ang, cos_a, sin_a;
	int xm, ym;

	ox = data->plr->pos.x;
	oy = data->plr->pos.y;
	xm = ox / BLOCK_SIZE * BLOCK_SIZE;
	ym = oy / BLOCK_SIZE * BLOCK_SIZE;
	cur_ang = data->plr->angl - HALF_FOV;

	for (int ray = 0; ray < NUM_RAYS; ray++)
	{
		sin_a = sin(cur_ang);
		cos_a = cos(cur_ang);
		double x, y;
		double dx, dy;
		double depth_v, depth_h;
		//Verticale
		if (cos_a >= 0)
		{
			x = xm + BLOCK_SIZE;
			dx = 1;
		}
		else{
			x = xm;
			dx = -1;
		}
		for (int i = 0; i < WIDTH; i+= BLOCK_SIZE)
		{
			depth_v = (x - ox) / cos_a;
			y = oy + depth_v * sin_a;
			t_pos pos_v;
			pos_v.x = x + dx;
			pos_v.y = y;
			if (cheack_pos(pos_v, data->map_pos))
				break;
			x += dx * BLOCK_SIZE;
		}

		//Horizontal
		if (sin_a >= 0)
		{
			y = ym + BLOCK_SIZE;
			dy = 1;
		}
		else {
			y = ym;
			dy = -1;
		}
		for (int i = 0; i < HEIGHT; i+= BLOCK_SIZE)
		{
			depth_h = (y - oy) / sin_a;
			x = ox + depth_h * cos_a;
			t_pos pos_h;
			pos_h.x = x;
			pos_h.y = y + dy;
			if (cheack_pos(pos_h, data->map_pos))
				break;
			y += dy * BLOCK_SIZE;
		}
		
		//projection
		double depth = find_min(depth_h, depth_v);
		depth *= cos(data->plr->angl - cur_ang);
		depth = find_max(depth, 0.00001);
		int color = 255 / (1 + depth * depth * 0.0002);
		int clr = (color, color, color);
		double proj_height = find_min((int)(PROJ_COEFF / depth), 2 * HEIGHT);
		t_pos p1, p2;
		p1.x = ray * SCALE;
		p1.y = (HALF_HEIGHT - proj_height / 2);
		p2.x = SCALE;
		p2.y = proj_height;
		draw_rect21(p1, SCALE * BLOCK_SIZE, proj_height, data->mlx, clr);
		// печать 2д лучей от камеры
		//_dda_line(data->plr->pos, pos_end, PLAYER_B, data->mlx);
		cur_ang += DELTA_RAY;
	}
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

	draw_all(data);

	mlx_hook(mlx->p_win, 2, (1L << 0), move, data);
	mlx_hook(mlx->p_win, 17, 0, close_win, data);
	mlx_loop(mlx->p_mlx);

	free(mlx);
	free(plr);
	free(map_pos);
	free(data);
	return (0);
}
