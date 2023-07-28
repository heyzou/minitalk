/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakai <hnakai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:56:59 by hnakai            #+#    #+#             */
/*   Updated: 2023/07/28 17:30:37 by hnakai           ###   ########.fr       */
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
	if (signum == SIGUSR1)
		bit |= 1;
	else if (signum == SIGUSR2)
		;
	c = c & bit;
	count++;
	if (count == 8)
	{
		write(STDOUT_FILENO, &c, 1);
		count = 0;
	}
}

int main(void)
{
	pid_t my_pid;
	my_pid = getpid();
	printf("%d", my_pid);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (0)
		pause();
}
