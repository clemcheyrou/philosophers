/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:27:13 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/02/03 18:54:05 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_data(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->eat_max = -1;
	data->die = 0;
	if (ac == 6)
		data->eat_max = ft_atoi(av[5]);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (0);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], 0) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->display, NULL))
		return (0);
	if (pthread_mutex_init(&data->eating, NULL))
		return (0);
	if (pthread_mutex_init(&data->dead, NULL))
		return (0);
	if (pthread_mutex_init(&data->time, NULL))
		return (0);
	if (pthread_mutex_init(&data->protect, NULL))
		return (0);
	return (1);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->ph = malloc(sizeof(t_ph *) * (data->nb_philo + 1));
	if (!data->ph)
		return (0);
	while (i < data->nb_philo)
	{
		data->ph[i] = malloc(sizeof(t_ph));
		if (!data->ph[i])
			return (free_array(data), 0);
		data->ph[i]->data = data;
		data->ph[i]->id = i;
		data->ph[i]->finish_eat = timer(0);
		data->ph[i]->nb_eat = 0;
		data->ph[i]->fork_left = i;
		data->ph[i]->fork_right = (i + 1) % data->nb_philo;
		i++;
	}
	data->ph[i] = NULL;
	return (1);
}

int	check_and_init_arg(int ac, char **av, t_data *data)
{
	if (ft_atoi(av[1]) < 1)
		return (ft_putstr_fd("Wrong input of philosophers\n", 2), 0);
	if (ft_atoi(av[2]) <= 0)
		return (ft_putstr_fd("Wrong input of time to die\n", 2), 0);
	if (ft_atoi(av[3]) <= 0)
		return (ft_putstr_fd("Wrong input of time to eat\n", 2), 0);
	if (ft_atoi(av[4]) <= 0)
		return (ft_putstr_fd("Wrong input of time to sleep\n", 2), 0);
	if (ac == 6)
		if (ft_atoi(av[5]) <= 0)
			return (ft_putstr_fd("Wrong input of number max to eat\n", 2), 0);
	init_data(ac, av, data);
	if (!init_philo(data))
		return (0);
	if (!init_mutex(data))
		return (0);
	return (1);
}
