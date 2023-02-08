/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:00:18 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/02/03 16:20:36 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	timer(long sleep)
{
	int				time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (time - sleep);
}

void	ph_wait(t_ph *ph, long sleep)
{
	long	time;
	long	start;

	start = timer(0);
	time = start;
	while (!died(ph) && sleep + start > time)
	{
		usleep(100);
		time = timer(0);
	}
}
