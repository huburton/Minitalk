/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:40:09 by huburton          #+#    #+#             */
/*   Updated: 2025/04/04 15:52:30 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

volatile sig_atomic_t	g_bit_received = 1;

void	handle_signal(int signum)
{
	(void)signum;
	g_bit_received = 0;
}

void	send_char(pid_t pid, unsigned char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_bit_received = 1;
		if (c & (1 << (7 - i)))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (g_bit_received)
			usleep(100);
		i++;
	}
}

static int	init_client(int argc, char **argv, pid_t *pid)
{
	struct sigaction	sa;

	if (argc != 3)
	{
		write(2, "Usage: ./client <server_pid> <message>\n", 39);
		return (1);
	}
	*pid = ft_atoi(argv[1]);
	if (*pid <= 0)
	{
		write(2, "Error: Invalid PID\n", 19);
		return (1);
	}
	sa.sa_handler = &handle_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	return (0);
}

static void	send_message(pid_t pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (init_client(argc, argv, &pid))
		return (1);
	send_message(pid, argv[2]);
	return (0);
}
