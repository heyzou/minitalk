/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakai <hnakai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:56:59 by hnakai            #+#    #+#             */
/*   Updated: 2023/07/30 18:30:40 by hnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t bit = 0;

void signal_handler(int signum)
{
	static int count;
	char c;

	c = 0xff;
	bit = bit << 1;
	if (signum == SIGUSR1)
		bit |= 1;
	c = c & bit;
	count++;
	if (count == 8)
	{
		write(STDOUT_FILENO, &c, 1);
		count = 0;
	}
	usleep(100);
}

int main(void)
{
	pid_t my_pid;
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	my_pid = getpid();
	printf("%d\n", my_pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
