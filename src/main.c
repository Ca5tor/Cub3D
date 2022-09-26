/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 02:45:40 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 20:44:25 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	pars_err(int ret, t_cub *cub, char **argv)
{
	if (ret != 0)
	{
		printf("Fail. %s\n", argv[1]);
		pars_free_all(cub);
		pars_exit_with_error(ret);
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	t_data	*data;

	(void)argc;
	init_cub(&cub);
	pars_err(pars_read_cfg(argv[1], &cub), &cub, argv);
	data = init_data(cub);
	if (!data && printf("Error allocate memory\n"))
		return (0);
	draw_all(data);
	mlx_hook(data->mlx->p_win, 2, (1L << 0), move, data);
	mlx_hook(data->mlx->p_win, 17, 0, close_win, data);
	mlx_loop(data->mlx->p_mlx);
	return (0);
}
