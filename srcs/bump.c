/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:14:19 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/28 17:49:34 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bump_init(t_data *data)
{
	data->mlx.img_bump.img = mlx_xpm_file_to_image(data->mlx.mlx, \
	"./image/bump.xpm",
			&data->mlx.img_bump.width, &data->mlx.img_bump.height);
	if (!data->mlx.img_bump.img)
		ft_error(data, E_MLX);
	data->mlx.img_bump.addr = mlx_get_data_addr(data->mlx.img_bump.img,
			&data->mlx.img_bump.bits_per_pixel, &data->mlx.img_bump.line_length,
			&data->mlx.img_bump.endian);
	if (!data->mlx.img_bump.addr)
		ft_error(data, E_MLX);
}

void	earth_init(t_data *data)
{
	data->mlx.img_earth.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./image/earth.xpm",
			&data->mlx.img_earth.width, &data->mlx.img_earth.height);
	if (!data->mlx.img_earth.img)
		ft_error(data, E_MLX);
	data->mlx.img_earth.addr = mlx_get_data_addr(data->mlx.img_earth.img,
			&data->mlx.img_earth.bits_per_pixel,
			&data->mlx.img_earth.line_length,
			&data->mlx.img_earth.endian);
	if (!data->mlx.img_earth.addr)
		ft_error(data, E_MLX);
}

t_color	bump_color(t_data *data, int x, int y)
{
	char	*dst;
	t_color	color;

	dst = data->mlx.img_bump.addr + (y * data->mlx.img_bump.line_length
			+ x * (data->mlx.img_bump.bits_per_pixel / 8));
	color.r = (*(unsigned int *)dst >> 16) & COLOR_MAX;
	color.g = (*(unsigned int *)dst >> 8) & COLOR_MAX;
	color.b = *(unsigned int *)dst & COLOR_MAX;
	return (color);
}

t_color	earth_color(t_data *data, int x, int y)
{
	char	*dst;
	t_color	color;

	dst = data->mlx.img_earth.addr + (y * data->mlx.img_earth.line_length
			+ x * (data->mlx.img_earth.bits_per_pixel / 8));
	color.r = (*(unsigned int *)dst >> 16) & COLOR_MAX;
	color.g = (*(unsigned int *)dst >> 8) & COLOR_MAX;
	color.b = *(unsigned int *)dst & COLOR_MAX;
	return (color);
}

void	earth_bump_nv(t_data *data, t_color color, t_ray *ray)
{
	t_point	vector_x;
	t_point	vector_y;
	t_point	bump;
	t_point	new_nv;

	vector_x = vcross(ray->hit.nv, vminus(ray->inter, data->cam.point));
	if (vlength(vector_x) == 0)
		vector_x = vcross(ray->hit.nv, tie_vector(0, 0, 1));
	vector_x = vunit(vector_x);
	vector_y = vunit(vcross(ray->hit.nv, vector_x));
	bump.x = (color.r / COLOR_MAX) * 2 - 1;
	bump.y = (color.g / COLOR_MAX) * 2 - 1;
	bump.z = (color.b / COLOR_MAX) * 2 - 1;
	new_nv = vsum(vsum(vmul(vector_x, bump.x), vmul(vector_y, bump.y)),
			vmul(ray->hit.nv, bump.z));
	ray->hit.nv = vunit(new_nv);
	if (vdot(ray->dir, ray->hit.nv) > 0)
		ray->hit.nv = vmul(ray->hit.nv, -1);
}
