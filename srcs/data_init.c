/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:52:55 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/28 17:49:15 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	esc_key(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
		exit(0);
	}
	return (1);
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	exit(0);
	return (1);
}

void	event_hooks(t_data *data)
{
	mlx_hook(data->mlx.mlx_win, 2, 0, &esc_key, &data->mlx);
	mlx_hook(data->mlx.mlx_win, 17, 0, &close_window, &data->mlx);
}

void	let_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		ft_error(data, E_MLX);
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx,
			data->win.x, data->win.y, "miniRT");
	if (!data->mlx.mlx_win)
		ft_error(data, E_MLX);
	data->mlx.img.img = mlx_new_image(data->mlx.mlx, data->win.x, data->win.y);
	if (!data->mlx.img.img)
		ft_error(data, E_MLX);
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img,
			&data->mlx.img.bits_per_pixel,
			&data->mlx.img.line_length, &data->mlx.img.endian);
	if (!data->mlx.img.addr)
		ft_error(data, E_MLX);
	bump_init(data);
	earth_init(data);
	ray_tracing(data);
	if (!mlx_put_image_to_window(data->mlx.mlx,
			data->mlx.mlx_win, data->mlx.img.img, 0, 0))
		ft_error(data, E_MLX);
	event_hooks(data);
	mlx_loop(data->mlx.mlx);
}

void	data_init(t_data *data)
{
	data->win.x = INIT_WINX;
	data->win.y = INIT_WINY;
	data->win.z = 0;
	ft_bzero(&data->amb, sizeof(data->amb));
	ft_bzero(&data->cam, sizeof(data->cam));
	data->light = NULL;
	data->cylinder = NULL;
	data->plane = NULL;
	data->sphere = NULL;
	data->cone = NULL;
}
