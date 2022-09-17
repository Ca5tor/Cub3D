/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_prototypes.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:53:59 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/17 03:50:29 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUN_PROTOTYPES_H
# define FUN_PROTOTYPES_H

# include "cub3D.h"

/*	draw_utils.c	*/

int		my_mlx_pixel_get(t_img *data, int x, int y);
void	_dda_line(t_pos a, t_pos b, int color, t_mlx *mlx);
void	draw_rect(t_pos start, t_pos end, t_mlx *mlx, int color);
void	draw_all(t_data *data);

/*	inits.c	*/

t_mlx	*init_mlx(void);
t_plr	*init_plr(void);
t_pos	*init_arr_pos(void);
t_data	*init_data(void);

/*	ray_cast.c	*/

void	ray_cast2(t_data *data);

/*	move.c	*/
int		close_win(t_data *data);
void	move(int key, t_data *data);

/*	utils.c	*/

double	find_max(double a, double b);
double	find_min(double x, double y);
double	mod(double a);
int		cheack_pos(t_pos a, t_pos *b);
int		chek_key(int key);


#endif