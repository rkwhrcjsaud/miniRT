/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_passing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:08:09 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/28 17:53:35 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_file_name(char *file)
{
	size_t	name_len;

	name_len = ft_strlen(file);
	if (name_len <= 3)
	{
		write(2, "Error\nNot allowed file!\n", 24);
		exit(1);
	}
	if (ft_strcmp(file + name_len - 3, ".rt"))
	{
		write(2, "Error\nFile extension is wrong!\n", 31);
		exit(1);
	}
}

static void	ft_open(t_data *data, char *file)
{
	check_file_name(file);
	data->fd = open(file, O_RDONLY, 0644);
	if (data->fd < 0)
		errno_error();
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		errno_error();
}

static int	check_line(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len == 1 && line[0] == '\n')
		free(line);
	else
	{
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		return (1);
	}
	return (0);
}

void	data_passing(t_data *data, char *file)
{
	char	*line;
	char	**word;
	int		flag;

	ft_open(data, file);
	while (1)
	{
		line = get_next_line(data->fd);
		if (!line)
			break ;
		if (!check_line(line))
			continue ;
		word = ft_split(line, ' ');
		if (!word)
			ft_error(data, ERRNO);
		free(line);
		line = NULL;
		flag = insert_data(data, word);
		free_double_arr(word);
	}
	if (flag != (1 << FLAG_AMBIENT) + (1 << FLAG_CAMERA))
		ft_error(data, E_ARGUMENT);
	ft_close(data->fd);
}
