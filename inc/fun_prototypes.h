/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_prototypes.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 02:44:30 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 20:10:49 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUN_PROTOTYPES_H
# define FUN_PROTOTYPES_H

# include "cub3D.h"

void		init_cub(t_cub *cub);
t_plr		*init_plr(const t_map map);
t_mlx		*init_mlx(const t_cub cub);
t_pos_int	*init_arr_pos(t_data *data, const t_map map);
t_data		*init_data(const t_cub cub);

int			get_num_wall(const t_map map);
t_pos_int	*sort_pos(t_pos_int *a, const int num_wall);

int			close_win(t_data *data);
int			move(int key, t_data *data);

int			chek_key(int key);

int			my_mlx_pixel_get(t_texture *img, int x, int y);
int			create_rgb(int r, int g, int b);

void		_dda_line(t_pos_double a, t_pos_double b, int color, t_mlx *mlx);
void		draw_rect(t_pos_double start, t_pos_double end, \
				t_mlx *mlx, int color);
void		draw_all(t_data *data);

void		ray_cast2(t_data *data);

void		*get_img(double depth, t_pos_double depth_hv, \
				t_pos_double cs, t_data *data);
int			get_offset(t_param_rcst rcst);
int			get_proj_height(double depth, double cur_ang, \
				double proj_coeff, t_data *data);
void		get_cur_cs(double cur_ang, t_pos_double *cs);
void		get_o_pos(t_data *data, t_param_rcst *rcst);

double		find_max(double a, double b);
double		find_min(double x, double y);
double		mod(double a);
int			bin_search_pos(t_data *data, double ax, double ay);

int			pars_is_char_number(char *str);
int			*pars_get_rgb(char *str);
char		*last_strstr(char *haystack, char *needle);
char		**add_str(char **arr, char *str);
char		**ft_split2(char *str, char token);

int			pars_ends_with(char *str, char *end);
int			pars_starts_with(char *str, char *pre);
int			pars_char_arr_length(char **arr);
void		pars_free_char_arr(char **arr);
void		pars_arg_check(int argc, char **argv);

bool		map_is_direction(char c);
bool		map_is_allowed_char(char c);
bool		map_is_num_direction(int c);
int			**map_get_empty_matrix(int rows, int cols);
int			**map_copy_matrix(int **matrix, int rows, int cols);

void		map_free_matrix(int	**matrix, int rows);
bool		map_is_floor(int c);
bool		map_is_safe(int x, int y, int **mtx, t_map *map);
void		map_dfs(int x, int y, int **mtx, t_map *map);
void		map_exclude_border(int **mtx, t_map *map);

int			map_count_all_zeros(t_map *map);
bool		parse_map(char **str_arr, t_map *map);
bool		map_pre_parse(char **str_arr, t_map *map);
void		pars_exit_with_error(int code);
void		pars_free_all(t_cub *cub);

int			pars_textures3(char *key, char *value, int *flags, t_cub *cub);
int			pars_textures2(char *key, char *value, int *flags, t_cub *cub);
int			pars_textures(char *key, char *value, int *flags, t_cub *cub);
int			pars_rgb_value(char *key, char *value, int *flags, t_cub *cub);
int			pars_handle_str(char **key_value, int *flags, t_cub *cub);

int			pars_handle_cfg(char **str_arr, t_cub *cub);
int			pars_read_cfg(char *file, t_cub *cub);
#endif