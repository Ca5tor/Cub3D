/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 01:27:11 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/22 08:14:36 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

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

/*
int	levl[0] -  low
int	levl[1] - mid
int	levl[2] - height
*/
int	bin_search_pos(t_data *data, double ax, double ay)
{
	int		levl[3];
	t_pos	guess;

	if (ax < 0 || ay < 0)
		return (0);
	levl[0] = 0;
	levl[2] = data->num_wall - 1;
	while (levl[0] <= levl[2])
	{
		levl[1] = (levl[0] + levl[2]) / 2;
		guess = data->map_pos[levl[1]];
		if (ax > guess.x && ay > guess.y && \
			ax < (guess.x + BLOCK_SIZE) && ay < (guess.y + BLOCK_SIZE))
			return (1);
		if (((ax < guess.x || ay < guess.y) && \
			(ax < (guess.x + BLOCK_SIZE) && ay < (guess.y + BLOCK_SIZE))) || \
				(ax < guess.x && ay > guess.y))
			levl[2] = levl[1] - 1;
		else
			levl[0] = levl[1] + 1;
	}
	return (0);
}

int	chek_key(int key)
{
	return (key == TURN_L || key == TURN_R \
		|| key == M_DIRECTLY || key == M_BACK \
		|| key == M_RIGHT || key == M_LEFT \
		|| key == EXIT_WINDW);
}
