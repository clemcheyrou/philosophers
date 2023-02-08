/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:00:09 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/02/03 17:31:08 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	exit_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 6 || ac == 5)
	{
		data = malloc(sizeof(t_data) * 1);
		memset(data, 0, (sizeof(t_data)));
		if (!check_and_init_arg(ac, av, data))
			return (0);
		if (!init_thread(data))
			return (0);
	}
	else
		ft_putstr_fd("Wrong number of arguments\n", 2);
	return (0);
}
