/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_v1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:45:55 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/15 11:28:56 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#define DELTA 0.12f
#define BLOCK_SIZE 64
#define FOV (3.1415926535f / 3)
#define HALF_FOV (FOV / 2)
#define MAX_DEPTH (WIDTH / BLOCK_SIZE * BLOCK_SIZE)
#define NUM_RAYS	200
#define DELTA_RAY (FOV / (NUM_RAYS - 1))
#define DIST (NUM_RAYS / (tan(HALF_FOV)))
#define PROJ_COEFF (SCALE / 2 * DIST * BLOCK_SIZE)
#define SCALE (WIDTH / (NUM_RAYS - 1)) 
 

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
void	ray_cast2(t_data *data);
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

//texture settings 64x64
#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64
#define TEXTURE_SCALE (TEXTURE_WIDTH / BLOCK_SIZE)


typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		llen;
	int		endian;
	char	*relative_path;
	int		img_width;
	int		img_height;
}				t_img;

int	my_mlx_pixel_get(t_img *data, int x, int y)
{

	char	*dst;

	dst = data->addr + (y * data->llen + x * (data->bpp / 8));
	return *(unsigned int*)dst;
}

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->p_addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	ray_cast2(t_data *data){
	int ox, oy;
	double cur_ang, cos_a, sin_a;
	int xm, ym;

	ox = data->plr->pos.x;
	oy = data->plr->pos.y;
	xm = ox / BLOCK_SIZE * BLOCK_SIZE;
	ym = oy / BLOCK_SIZE * BLOCK_SIZE;
	cur_ang = data->plr->angl - HALF_FOV;

	t_img	timg;
	t_img	img_mas[4];
	img_mas[0].img = mlx_xpm_file_to_image(data->mlx->p_mlx, "./textures/bricks.xpm", &timg.img_width, &timg.img_height);
	img_mas[1].img = mlx_xpm_file_to_image(data->mlx->p_mlx, "./textures/grass.xpm", &timg.img_width, &timg.img_height);
	img_mas[2].img = mlx_xpm_file_to_image(data->mlx->p_mlx, "./textures/stone.xpm", &timg.img_width, &timg.img_height);
	img_mas[3].img = mlx_xpm_file_to_image(data->mlx->p_mlx, "./textures/redbrick.xpm", &timg.img_width, &timg.img_height);
	//timg.addr = mlx_get_data_addr(timg.img, &timg.bpp, &timg.llen, &timg.endian);

	for (int ray = 0; ray < NUM_RAYS; ray++)
	{
		sin_a = sin(cur_ang);
		cos_a = cos(cur_ang);
		double x, y;
		int xh, yv;
		double dx, dy;
		double depth_v, depth_h;
		//Verticale
		if (cos_a >= 0)
		{
			xh = xm + BLOCK_SIZE;
			dx = 1;
		}
		else{
			xh = xm;
			dx = -1;
		}
		for (int i = 0; i < WIDTH; i+= BLOCK_SIZE)
		{
			depth_v = (xh - ox) / cos_a;
			y = oy + depth_v * sin_a;
			t_pos pos_v;
			pos_v.x = xh + dx;
			pos_v.y = y;
			if (cheack_pos(pos_v, data->map_pos))
				break;
			xh += dx * BLOCK_SIZE;
		}

		//Horizontal
		if (sin_a >= 0)
		{
			yv = ym + BLOCK_SIZE;
			dy = 1;
		}
		else {
			yv = ym;
			dy = -1;
		}
		for (int i = 0; i < HEIGHT; i+= BLOCK_SIZE)
		{
			depth_h = (yv - oy) / sin_a;
			x = ox + depth_h * cos_a;
			t_pos pos_h;
			pos_h.x = x;
			pos_h.y = yv + dy;
			if (cheack_pos(pos_h, data->map_pos))
				break;
			yv += dy * BLOCK_SIZE;
		}
		
		//projection
		double depth = find_min(depth_h, depth_v);
		
		int offset;
		if (depth == depth_h)
			offset = x;
		else
			offset = y;
		
		
		offset = abs((int)offset % BLOCK_SIZE);
		//offset = abs((int)offset % BLOCK_SIZE);
		if (depth == depth_h && sin_a >= 0)
			timg.img = img_mas[0].img;
		else if (depth == depth_h && sin_a < 0)
			timg.img = img_mas[1].img;
		else if (depth == depth_v && cos_a >= 0)
			timg.img = img_mas[2].img;
		else
			timg.img = img_mas[3].img;
		timg.addr = mlx_get_data_addr(timg.img, &timg.bpp, &timg.llen, &timg.endian);
		
		
		// int clr;
		// if (depth == depth_h && sin_a >= 0)
		// 	clr = CLR_S;
		// else if (depth == depth_h && sin_a < 0)
		// 	clr = CLR_N;
		// else if (depth == depth_v && cos_a >= 0)
		// 	clr = CLR_E;
		// else
		// 	clr = CLR_W;

		depth *= cos(data->plr->angl - cur_ang);
		depth = find_max(depth, 0.00001);

		int proj_height = abs(find_min((int)(PROJ_COEFF / depth), 2 * HEIGHT));
		
		t_pos p1, p2;
		p1.x = ray * SCALE;
		p1.y = (HALF_HEIGHT - proj_height / 2);
		// p2.x = SCALE;
		// p2.y = proj_height ;
		// draw_rect21(p1, SCALE * BLOCK_SIZE, proj_height, data->mlx, clr);
		
		//offset = (BLOCK_SIZE - 1) % (int)offset;

		//offset = proj_height % (int)offset;
		//int	x1 = ray * SCALE;
		int	x1 = ray * SCALE;
		int	y1 = (HALF_HEIGHT - proj_height / 2);
		int	x2 = x1 + SCALE;
		int	y2 = y1 + proj_height;
		//_dda_line(p1, p2, PLAYER_B, data->mlx);
		
	//printf("OFFSET=%d\n", offset);
		//draw_rect21(p1, SCALE * BLOCK_SIZE, proj_height, data->mlx, my_mlx_pixel_get(&timg, (int)offset % BLOCK_SIZE, 0));
		
	t_pos	tmp;
	t_pos	start;
	start.x = x1;
	start.y = y1;
	tmp.x = x2;
	tmp.y = y1;
	
	int kk =abs( (proj_height) / (timg.img_height - 1)) ;
	int m = 0;
	int j = -1;
	
		int i = -1;
		while (++i < proj_height)
		{
			_dda_line(start, tmp, my_mlx_pixel_get(&timg, offset, (int)(i * timg.img_height / proj_height)), data->mlx);
			start.y++;
			tmp.y++;
		}
		
	//	int kk =( (proj_height) / (timg.img_height - 1)) ;
		
		// int zz = 0;//printf("size=%d\n", kk);
		// for (int i = y1; i < y2; i++)
		// {
		// 	int jj = 0;
		// 	for (int j = x1; j < x2 ; j++)
		// 	{
				
		// 		my_mlx_pixel_put(data->mlx, j, i, \
		// 		my_mlx_pixel_get(&timg, offset, jj * 64 / proj_height));
		// 		jj++;
		// 	}
			
		// }
		//my_mlx_pixel_get(&timg, (i % BLOCK_SIZE), j % BLOCK_SIZE)
		
		
		
		
		cur_ang += DELTA_RAY;
	}
	//mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->p_win, data->mlx->p_img, 0, 0);
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