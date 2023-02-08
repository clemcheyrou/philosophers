/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:28:06 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/02/03 14:56:24 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_notdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

long long	ft_atoi(char *nptr)
{
	int			i;
	long long	res;
	int			neg;

	neg = 1;
	res = 0;
	i = 0;
	if (ft_notdigit(nptr))
		return (-2);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	if ((res * neg) <= 2147483647 && (res * neg) >= -2147483648)
		return (res * neg);
	else
		return (-2);
}

void	free_array(t_data *data)
{
	int	i;

	i = 0;
	if (data->ph)
	{
		while (i < data->nb_philo)
		{
			free(data->ph[i]);
			i++;
		}
		free(data->ph);
	}
}
