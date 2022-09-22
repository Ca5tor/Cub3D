/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 01:05:36 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/17 17:37:21 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "configure.h"
# include "structs.h"
# include "fun_prototypes.h"

# include "../utils/LIBFT/libft.h"
# include "../utils/GNL/get_next_line.h"
# include "../mlx-linux/mlx.h"

# include <stdlib.h>
# include <stdio.h>
# include <math.h>

/*	for move.c	*/

# define SPEED_SIGHT 1
# define SPEED_MOVE 50

# define DELTA 0.12f
# define BLOCK_SIZE 64
# define FOV (3.1415926535f / 3)
# define HALF_FOV (FOV / 2)
# define MAX_DEPTH (WIDTH / BLOCK_SIZE * BLOCK_SIZE)
# define NUM_RAYS	200
# define DELTA_RAY (FOV / (NUM_RAYS - 1))
# define DIST (NUM_RAYS / (tan(HALF_FOV)))
# define PROJ_COEFF (SCALE / 2 * DIST * BLOCK_SIZE)
# define SCALE (WIDTH / (NUM_RAYS - 1))

// for map
# define MPN 30
# define MPS 35
# define MPE 21
# define MPW 39
# define WALL 1

# define POS_N 4.7
# define POS_S 1.55
# define POS_E 0
# define POS_W 3.17

#endif