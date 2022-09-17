/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 01:27:08 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/17 03:39:34 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

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
	img_mas[0].img = mlx_xpm_file_to_image(data->mlx->p_mlx, "./textures/eagle.xpm", &timg.img_width, &timg.img_height);
	img_mas[1].img = mlx_xpm_file_to_image(data->mlx->p_mlx, "./textures/grass.xpm", &timg.img_width, &timg.img_height);
	img_mas[2].img = mlx_xpm_file_to_image(data->mlx->p_mlx, "./textures/stone.xpm", &timg.img_width, &timg.img_height);
	img_mas[3].img = mlx_xpm_file_to_image(data->mlx->p_mlx, "./textures/redbrick.xpm", &timg.img_width, &timg.img_height);

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

		offset = mod((int)offset % BLOCK_SIZE);

		if (depth == depth_h && sin_a >= 0)
			timg.img = img_mas[0].img;
		else if (depth == depth_h && sin_a < 0)
			timg.img = img_mas[1].img;
		else if (depth == depth_v && cos_a >= 0)
			timg.img = img_mas[2].img;
		else
			timg.img = img_mas[3].img;
		timg.addr = mlx_get_data_addr(timg.img, &timg.bpp, &timg.llen, &timg.endian);

		depth *= cos(data->plr->angl - cur_ang);
		depth = find_max(depth, 0.00001);

		int proj_height = mod(find_min((int)(PROJ_COEFF / depth), 2 * HEIGHT));
		
		t_pos	tmp;
		t_pos	start;
		start.x = ray * SCALE;
		start.y = (HALF_HEIGHT - proj_height / 2);
		tmp.x = ray * SCALE + SCALE;
		tmp.y = (HALF_HEIGHT - proj_height / 2);

		int i = -1;
		while (++i < proj_height)
		{
			int clr = my_mlx_pixel_get(&timg, offset, (int)(i * timg.img_height / proj_height));
			_dda_line(start, tmp, clr, data->mlx);
			start.y++;
			tmp.y++;
		}
		cur_ang += DELTA_RAY;
	}
}