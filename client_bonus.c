/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanukool <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 07:19:18 by tanukool          #+#    #+#             */
/*   Updated: 2022/08/29 18:03:24 by tanukool         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

int	simple_atoi(const char *str)
{
	int	to_return;

	to_return = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			ft_putstr_fd("pid must must be non-negative number.\n", 2);
			exit(EXIT_FAILURE);
		}
		to_return *= 10;
		to_return += *str - '0';
		str++;
	}
	return (to_return);
}

void	send_byte(pid_t pid, char c)
{
	char	bit_count;
	int		sig;

	bit_count = 7;
	while (bit_count >= 0)
	{
		if ((c >> bit_count) & 1)
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		if (kill(pid, sig) == -1)
		{
			ft_putstr_fd("Error when trying to send the message.\n", 2);
			exit(EXIT_FAILURE);
		}
		bit_count--;
		pause();
		usleep(50);
	}
}

void	send_msg(pid_t pid, char *msg)
{
	while (*msg)
	{
		send_byte(pid, *msg);
		msg++;
	}
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static char				bit_count;
	static unsigned char	c;

	(void) info;
	(void) context;
	c = c << 1;
	if (sig == SIGUSR1)
		c |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &c, 1);
		bit_count = 0;
		c = 0;
	}
}

int	main(int ac, char *av[])
{
	pid_t				pid;
	struct sigaction	sa;

	if (ac == 3)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
		sigemptyset(&sa.sa_mask);
		sigaddset(&sa.sa_mask, SIGUSR1);
		sigaddset(&sa.sa_mask, SIGUSR2);
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pid = simple_atoi(av[1]);
		send_msg(pid, av[2]);
	}
	else
	{
		ft_putstr_fd("./client [pid] [message]\n", 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
