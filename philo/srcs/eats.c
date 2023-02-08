/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eats.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:43:45 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/02/03 19:14:22 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_eats_even(t_data *data, t_ph *ph)
{
	pthread_mutex_lock(&data->forks[ph->fork_right]);
	display(data, ph, ph->id, "has taken a fork\n");
	pthread_mutex_lock(&data->forks[ph->fork_left]);
	display(data, ph, ph->id, "has taken a fork\n");
	if (!died(ph))
	{
		display(data, ph, ph->id, "is eating\n");
		pthread_mutex_lock(&data->eating);
		if (ph->data->eat_max != -1)
			ph->nb_eat++;
		pthread_mutex_unlock(&data->eating);
		pthread_mutex_lock(&ph->data->time);
		ph->finish_eat = timer(0);
		pthread_mutex_unlock(&ph->data->time);
		ph_wait(ph, data->t_eat);
	}
	pthread_mutex_unlock(&data->forks[ph->fork_left]);
	pthread_mutex_unlock(&data->forks[ph->fork_right]);
	return (NULL);
}

void	*philo_eats_odd(t_data *data, t_ph *ph)
{
	pthread_mutex_lock(&data->forks[ph->fork_left]);
	display(data, ph, ph->id, "has taken a fork\n");
	pthread_mutex_lock(&data->forks[ph->fork_right]);
	display(data, ph, ph->id, "has taken a fork\n");
	if (!died(ph))
	{
		display(data, ph, ph->id, "is eating\n");
		pthread_mutex_lock(&data->eating);
		if (ph->data->eat_max != -1)
			ph->nb_eat++;
		pthread_mutex_unlock(&data->eating);
		pthread_mutex_lock(&ph->data->time);
		ph->finish_eat = timer(0);
		pthread_mutex_unlock(&ph->data->time);
		ph_wait(ph, data->t_eat);
	}
	pthread_mutex_unlock(&data->forks[ph->fork_right]);
	pthread_mutex_unlock(&data->forks[ph->fork_left]);
	return (NULL);
}
