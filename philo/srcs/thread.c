/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:10:11 by clementinec       #+#    #+#             */
/*   Updated: 2023/02/08 15:24:41 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	display(t_data *data, t_ph *ph, int id, char *str)
{
	pthread_mutex_lock(&data->display);
	if (!died(ph))
	{
		printf("%ld ", timer(data->start));
		printf("%d ", id + 1);
		printf("%s", str);
	}
	pthread_mutex_unlock(&data->display);
	return ;
}

void	*one_p_thread(t_data *data, t_ph *ph)
{
	pthread_mutex_lock(&data->forks[ph->fork_left]);
	display(data, ph, ph->id, "has taken a fork\n");
	ph_wait(ph, data->t_die);
	display(data, ph, ph->id, "died\n");
	pthread_mutex_unlock(&data->forks[ph->fork_left]);
	return (NULL);
}

void	*philo_eats(t_data *data, t_ph *ph, int flag)
{
	if (flag == 1)
		philo_eats_odd(data, ph);
	else
		philo_eats_even(data, ph);
	return (NULL);
}

void	*p_thread(void *void_ph)
{
	t_ph	*ph;

	ph = (t_ph *)void_ph;
	if (ph->data->nb_philo == 1)
		return (one_p_thread(ph->data, ph), NULL);
	if (ph->id % 2 == 0)
		usleep(300);
	pthread_mutex_lock(&ph->data->time);
	ph->finish_eat = timer(0);
	pthread_mutex_unlock(&ph->data->time);
	while (!died(ph) && !exced_meal(ph))
	{
		if (ph->id % 2 == 0
			|| (ph->id == ph->data->nb_philo && (ph->data->nb_philo % 2) != 0))
			philo_eats(ph->data, ph, 0);
		else
			philo_eats(ph->data, ph, 1);
		display(ph->data, ph, ph->id, "is sleeping\n");
		ph_wait(ph, ph->data->t_sleep);
		display(ph->data, ph, ph->id, "is thinking\n");
	}
	return (NULL);
}

int	init_thread(t_data *data)
{
	int			i;
	pthread_t	dead;

	i = -1;
	data->start = timer(0);
	pthread_mutex_lock(&data->protect);
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->ph[i]->ph_thread,
				NULL, p_thread, data->ph[i]))
			return (exit_mutex(data), free_array(data), 0);
		pthread_create(&dead, NULL, p_death, data->ph[i]);
		pthread_detach(dead);
	}
	pthread_mutex_unlock(&data->protect);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->ph[i]->ph_thread, NULL))
			return (exit_mutex(data), free_array(data), 0);
	}
	free_array(data);
	exit_mutex(data);
	return (1);
}
