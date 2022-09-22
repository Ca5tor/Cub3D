/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_prototypes.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:53:59 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/22 08:14:03 by ltacos           ###   ########.fr       */
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
t_plr	*init_plr(t_map *map);
t_pos	*init_arr_pos(t_data *data);
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
int		cheack_pos(t_pos a, t_pos *b, t_data *data);
int		chek_key(int key);
int		cheack_pos1(double ax, double ay, t_data *data);
int		bin_search_pos(t_data *data, double ax, double ay);


void	get_param(t_data *data);

/*	ray_cast_utils.c*/
void	*get_img(double depth, t_pos depth_hv, t_cs cs, t_data *data);
int		get_offset(t_param_rcst rcst);
int		get_proj_height(double depth, double cur_ang, t_data *data);
void	get_cur_cs(double cur_ang, t_cs *cs);
void	get_o_pos(t_data *data, t_param_rcst *rcst);

#endif