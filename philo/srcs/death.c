/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:29:33 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/02/08 15:26:05 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	died(t_ph *ph)
{
	pthread_mutex_lock(&ph->data->dead);
	if (ph->data->die)
	{
		pthread_mutex_unlock(&ph->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->data->dead);
	return (0);
}

int	exced_meal(t_ph *ph)
{
	if (ph->data->eat_max > 0)
	{
		pthread_mutex_lock(&ph->data->eating);
		if (ph->nb_eat >= ph->data->eat_max)
		{
			pthread_mutex_unlock(&ph->data->eating);
			return (1);
		}
		pthread_mutex_unlock(&ph->data->eating);
	}
	return (0);
}

void	*p_death(void *philo)
{
	t_ph		*ph;
	long long	time;

	ph = (t_ph *)philo;
	while (!died(ph) && !exced_meal(ph) && ph->data->nb_philo != 1)
	{
		usleep(100);
		pthread_mutex_lock(&ph->data->time);
		pthread_mutex_lock(&ph->data->display);
		time = timer(ph->finish_eat);
		if (time > ph->data->t_die && !died(ph) && !exced_meal(ph))
		{
			pthread_mutex_lock(&ph->data->dead);
			ph->data->die = 1;
			pthread_mutex_unlock(&ph->data->dead);
			printf("%ld %d died\n", timer(ph->data->start), ph->id + 1);
		}
		pthread_mutex_unlock(&ph->data->display);
		pthread_mutex_unlock(&ph->data->time);
		usleep(100);
	}
	return (NULL);
}
