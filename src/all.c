/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:45:55 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/04 19:03:32 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#define DELTA 0.12f
#define BLOCK_SIZE 42
#define FOV (3.1415926535f / 3)
#define HALF_FOV (FOV / 2)
#define MAX_DEPTH (WIDTH / BLOCK_SIZE * BLOCK_SIZE)
#define NUM_RAYS	400
#define DELTA_RAY (FOV / (NUM_RAYS - 1))
#define DIST (NUM_RAYS / (3 * tan(HALF_FOV)))
#define PROJ_COEFF (3 * DIST * BLOCK_SIZE)
#define SCALE (WIDTH / NUM_RAYS) 

// жёлтый
#define CLR_N 0xFFFF00

// синий
#define CLR_S 0x0000FF

// фиолетовый
#define CLR_E 0xFF00FF

// серый
#define CLR_W 0x808080

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
	float	x;
	float	y;
}	t_pos;

typedef struct s_cs
{
	float	cos;
	float	sin;
}	t_cs;

typedef struct s_pos_int
{
	int	x;
	int	y;
}	t_pos_int;

typedef struct s_plr
{
	t_pos	pos;
	float	angl;
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
	{'1', '1', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', 'P', '0', '0', '0', '1'},
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
				new_plr->angl = 4.7;
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

float	find_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	find_min(float x, float y)
{
	if (x < y)
		return (x);
	return (y);
}

float	mod(float a)
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
	float	step;

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

void	draw_rect21(t_pos start, t_pos param, t_mlx *mlx, int color)
{
	t_pos	tmp;
	int		i;

	tmp.x = (start.x + param.x / BLOCK_SIZE);
	tmp.y = start.y;
	i = -1;
	while (++i < param.y)
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

void	background(int clr_sky, int clr_floor, t_mlx *mlx)
{
	t_pos	pos_floor[2];
	t_pos	pos_sky[2];

	pos_sky[0].x = 0;
	pos_sky[0].y = 0;
	pos_sky[1].x = WIDTH * BLOCK_SIZE;
	pos_sky[1].y = HEIGHT / 2;

	pos_floor[0].x = 0;
	pos_floor[0].y = HALF_HEIGHT;
	pos_floor[1].x = WIDTH * BLOCK_SIZE;
	pos_floor[1].y = HEIGHT / 2;

	draw_rect21(pos_sky[0], pos_sky[1], mlx, clr_sky); 
	draw_rect21(pos_floor[0], pos_floor[1], mlx, clr_floor);
}

void	draw_all(t_data *data)
{
	background(0x4682B4, 0x008000, data->mlx);
	ray_cast2(data);
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->p_win, data->mlx->p_img, 0, 0);
}

void	move_0(int key, t_data *data)
{
	float	speed = 1.5;

	if (key == TURN_L)
	{
		data->plr->angl -= 0.5 * DELTA * speed;
		return draw_all(data);
	}
	if (key == TURN_R)
	{
		data->plr->angl += 0.5 * DELTA * speed;
		return draw_all(data);
	}
}

void	move_1(int key, t_data *data)
{
	t_cs cs_a;
	int speed;

	speed = 50;
	cs_a.cos = cos(data->plr->angl);
	cs_a.sin = sin(data->plr->angl);
	if (key == M_DIRECTLY){
		data->plr->pos.x += cs_a.cos * DELTA * speed;
		data->plr->pos.y += cs_a.sin * DELTA * speed;
		return draw_all(data);
	}
	if (key == M_BACK)
	{
		data->plr->pos.x -= cs_a.cos * DELTA * speed;
		data->plr->pos.y -= cs_a.sin * DELTA * speed;
		return draw_all(data);
	}
}

void	move_2(int key, t_data *data)
{
	t_cs cs_a;
	int speed;

	speed = 50;
	cs_a.cos = cos(data->plr->angl);
	cs_a.sin = sin(data->plr->angl);
	if (key == M_RIGHT)
	{
		data->plr->pos.y += cs_a.cos * DELTA * speed;
		data->plr->pos.x -= cs_a.sin * DELTA * speed;
		return draw_all(data);
	}
	if (key == M_LEFT)
	{
		data->plr->pos.y -= cs_a.cos * DELTA * speed;
		data->plr->pos.x += cs_a.sin * DELTA * speed;
		return draw_all(data);
	}
	if (key == EXIT_WINDW)
	{
		close_win(data);
		return draw_all(data);
	}
}

void	move(int key, t_data *data)
{
	if (key == TURN_L || key == TURN_R)
		return move_0(key, data);
	if (key == M_DIRECTLY || key == M_BACK)
		return move_1(key, data);
	if (key == M_RIGHT || key == M_LEFT || key == EXIT_WINDW)
		return move_2(key, data);
}

int	cheack_pos(t_pos a, t_pos *b)
{
	float ax, cx, bx, ay, cy, by;
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

float	get_dv(t_data *data, t_cs cs_a, t_pos_int plr, t_pos_int plr_m)
{
	float	depth_v;
	t_pos	tmp;
	t_pos	d_tmp;
	t_pos	pos_v;
	int		i;

	tmp.x = plr_m.x;
	d_tmp.x = -1;
	if (cs_a.cos >= 0)
	{
		tmp.x += BLOCK_SIZE;
		d_tmp.x = 1;
	}
	i = -1;
	while (++i < WIDTH / BLOCK_SIZE)
	{
		depth_v = (tmp.x - plr.x) / cs_a.cos;
		tmp.y = plr.y + depth_v * cs_a.sin;
		pos_v.x = tmp.x + d_tmp.x;
		pos_v.y = tmp.y;
		if (cheack_pos(pos_v, data->map_pos))
			break;
		tmp.x += d_tmp.x * BLOCK_SIZE;
	}
	return depth_v;
}

float	get_dh(t_data *data, t_cs cs_a, t_pos_int plr, t_pos_int plr_m)
{
	float	depth_h;
	t_pos	tmp;
	t_pos	d_tmp;
	t_pos	pos_h;
	int		i;

	tmp.y = plr_m.y;
	d_tmp.y = -1;
	if (cs_a.sin >= 0)
	{
		tmp.y += BLOCK_SIZE;
		d_tmp.y = 1;
	}
	i = -1;
	while (++i <  HEIGHT / BLOCK_SIZE)
	{
		depth_h = (tmp.y - plr.y) / cs_a.sin;
		tmp.x = plr.x + depth_h * cs_a.cos;
		pos_h.x = tmp.x;
		pos_h.y = tmp.y + d_tmp.y;
		if (cheack_pos(pos_h, data->map_pos))
			break;
		tmp.y += d_tmp.y * BLOCK_SIZE;
	}
		return depth_h;
}

float	get_depth(float dh, float dv, t_cs cs_a, int *clr)
{
	float depth;

	depth = find_min(dh, dv);
	if (depth == dh && cs_a.sin >= 0)
	{
		*clr = CLR_S;
		return depth;
	}
	else if (depth == dh && cs_a.sin < 0)
	{
		*clr = CLR_N;
		return depth;
	}
	else if (depth == dv && cs_a.cos >= 0)
	{
		*clr = CLR_E;
		return depth;
	}
	else
		*clr = CLR_W;
	return depth;
}

void	render_ray(t_mlx *mlx, int clr, float depth, int ray)
{
	float	proj_height;
	t_pos		pos[2];

	proj_height = find_min((int)(PROJ_COEFF / depth), 2 * HEIGHT);
	pos[0].x = ray * SCALE;
	pos[0].y = (HALF_HEIGHT - proj_height / 2);
	pos[1].x = SCALE * BLOCK_SIZE;
	pos[1].y = proj_height;
	draw_rect21(pos[0], pos[1], mlx, clr);
}

void	ray_cast2(t_data *data)
{
	t_pos_int	plr[2];
	t_cs		cs_a;
	float	cur_ang;
	float	depth;
	int		color;
	int		ray;

	plr[0].x = data->plr->pos.x;
	plr[0].y = data->plr->pos.y;
	plr[1].x = plr[0].x / BLOCK_SIZE * BLOCK_SIZE;
	plr[1].y = plr[0].y / BLOCK_SIZE * BLOCK_SIZE;
	cur_ang = data->plr->angl - HALF_FOV;
	ray = -1;
	while (++ray < NUM_RAYS)
	{
		cs_a.sin = sin(cur_ang);
		cs_a.cos = cos(cur_ang);
		depth = get_depth(get_dh(data, cs_a, plr[0], plr[1]), \
			get_dv(data, cs_a, plr[0], plr[1]), cs_a, &color) \
				* cos(data->plr->angl - cur_ang);
		render_ray(data->mlx, color, find_max(depth, 0.00001), ray);
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
