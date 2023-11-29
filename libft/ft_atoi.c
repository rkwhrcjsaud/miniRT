/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:22:45 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/14 14:32:47 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_num(const char *str)
{
	int	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	int	sign;

	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	return (ft_num(str) * sign);
}
