/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:01:57 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/28 12:06:09 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	gaze_direction(int key, t_data *data)
{
	double	num;

	num = 0.5 * DELTA * SPEED_SIGHT;
	if (key == TURN_L)
	{
		data->plr->angl -= num;
		return (draw_all(data));
	}
	data->plr->angl += num;
	draw_all(data);
}

static void	direction_move(int key, t_data *data)
{
	double	num_x;
	double	num_y;

	num_x = cos(data->plr->angl) * DELTA * SPEED_MOVE;
	num_y = sin(data->plr->angl) * DELTA * SPEED_MOVE;
	if (key == MOVE_W)
	{
		data->plr->pos.pos[X] += num_x;
		data->plr->pos.pos[Y] += num_y;
		return (draw_all(data));
	}
	data->plr->pos.pos[X] -= num_x;
	data->plr->pos.pos[Y] -= num_y;
	draw_all(data);
}

static void	sideways_move(int key, t_data *data)
{
	double	num_x;
	double	num_y;

	num_x = sin(data->plr->angl) * DELTA * SPEED_MOVE;
	num_y = cos(data->plr->angl) * DELTA * SPEED_MOVE;
	if (key == MOVE_D)
	{
		data->plr->pos.pos[X] -= num_x;
		data->plr->pos.pos[Y] += num_y;
		return (draw_all(data));
	}
	data->plr->pos.pos[X] += num_x;
	data->plr->pos.pos[Y] -= num_y;
	draw_all(data);
}

int	close_win(t_data *data)
{
	mlx_destroy_image(data->mlx->p_mlx, data->mlx->p_img);
	free(data->mlx);
	free(data->plr);
	free(data->map_pos);
	free(data);
	exit(0);
	return (0);
}

int	move(int key, t_data *data)
{
	if (!chek_key(key))
		return (0);
	if (key == TURN_L || key == TURN_R)
		return (gaze_direction(key, data), 0);
	if (key == MOVE_W || key == MOVE_S)
		return (direction_move(key, data), 0);
	if (key == MOVE_A || key == MOVE_D)
		return (sideways_move(key, data), 0);
	if (key == KEY_ESC)
		close_win(data);
	return (draw_all(data), 0);
}
