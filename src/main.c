/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:17:45 by abarahho          #+#    #+#             */
/*   Updated: 2025/01/17 17:18:07 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	wait_for_children(void)
{
	int	status;
	int	exit_status;

	exit_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	return (exit_status);
}

int	main(int ac, char **av, char **env)
{
	t_ppx	ppx;

	if (ac != 5)
		return (error_handling(ERR_ARGS, NULL), 1);
	initialize_pipex(&ppx, env);
	if (pipe(ppx.pipe_fd) == -1)
		return (error_handling(ERR_PIPE_FAILURE, NULL), free_pipex(&ppx), 1);
	if (!exec_command(&ppx, av[1], av[2], 1)
		|| !exec_command(&ppx, av[4], av[3], 0))
		return (free_pipex(&ppx), 1);
	free_pipex(&ppx);
	return (wait_for_children());
}
