/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:05:23 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/27 18:55:23 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	chek_key(int key)
{
	return (key == TURN_L || key == TURN_R \
		|| key == MOVE_W || key == MOVE_A \
		|| key == MOVE_S || key == MOVE_D \
		|| key == KEY_ESC || key == KEY_SPACE);
}
