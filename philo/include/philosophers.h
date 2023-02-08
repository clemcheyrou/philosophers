/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:40:32 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/02/03 18:56:04 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_ph
{
	int					id;
	int					nb_eat;
	long long			finish_eat;
	int					fork_left;
	int					fork_right;
	pthread_t			ph_thread;
	struct s_data		*data;
}	t_ph;

typedef struct s_data
{
	int					nb_philo;
	int					die;
	long long			start;
	int					t_die;
	int					t_eat;
	long long			t_sleep;
	int					eat_max;
	pthread_mutex_t		*forks;
	pthread_mutex_t		display;
	pthread_mutex_t		eating;
	pthread_mutex_t		dead;
	pthread_mutex_t		time;
	pthread_mutex_t		protect;
	struct s_ph			**ph;
}	t_data;

int			init_thread(t_data *data);
long		timer(long sleep);
void		exit_thread(t_data *data, t_ph *ph);
void		ph_wait(t_ph *ph, long sleep);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
void		free_array(t_data *data);
int			check_and_init_arg(int ac, char **av, t_data *data);
int			died(t_ph *ph);
int			exced_meal(t_ph *ph);
void		*p_death(void *philo);
void		exit_mutex(t_data *data);
long long	ft_atoi(char *nptr);
void		*philo_eats_odd(t_data *data, t_ph *ph);
void		*philo_eats_even(t_data *data, t_ph *ph);
void		display(t_data *data, t_ph *ph, int id, char *str);

#endif