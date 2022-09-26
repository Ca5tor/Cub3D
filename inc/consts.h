/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 02:06:07 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 18:17:19 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTS_H
# define CONSTS_H

/*	Defining a name variable for
	an array (int [2] and double [2])	*/
# define X 0
# define Y 1
# define COS 0
# define SIN 1
# define DEPTH_H 0
# define DEPTH_V 1
# define CLR_SKY 0
# define CLR_FLOOR 1
# define IMG_NO 0
# define IMG_SO 1
# define IMG_WE 2
# define IMG_EA 3
# define VAR_LOW 0
# define VAR_MID 1
# define  VAR_HEIGHT 2

/*	For the player’s start Spawning Orientation(SO),
	(SO_+ direction)	*/
# define SO_N 30
# define SO_S 35
# define SO_E 21
# define SO_W 39

/*	For map	*/
# define POS_WALL 1

/*	Orientation Start Angle,
	(OSA_ + direction)	*/
# define OSA_N 4.7f
# define OSA_S 1.55f
# define OSA_E 0
# define OSA_W 3.17f

/*	For function ray_casting	*/
# define NUM_RAYS 200
# define TILE 64
# define PI 3.1415926535f

/*	For move and turn player*/
# define DELTA 0.12f
# define SPEED_SIGHT 1
# define SPEED_MOVE 50

# define FLAGS_NO 1
# define FLAGS_SO 2
# define FLAGS_WE 4
# define FLAGS_EA 8
# define FLAGS_F  16
# define FLAGS_C  32
# define ALL_FLAG 63

#endif