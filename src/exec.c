/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:17:50 by abarahho          #+#    #+#             */
/*   Updated: 2025/01/17 13:07:36 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	exec_command(t_ppx *ppx, char *file, char *cmd, int is_first)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close_pipe(ppx);
		return (error_handling(ERR_FORK_FAILURE, cmd), 0);
	}
	if (pid == 0)
	{
		if (!setup_io(ppx, file, is_first))
			exit(1);
		exec_process(ppx, cmd);
	}
	return (1);
}

void	exec_process(t_ppx *ppx, char *cmd)
{
	ppx->cmds = ft_split_quotes(cmd, ' ');
	if (!ppx->cmds || !ppx->cmds[0])
	{
		error_handling(ERR_CMD_NOT_FOUND, cmd);
		exit(127);
	}
	ppx->path = find_path(ppx->paths, ppx->cmds[0]);
	if (!ppx->path)
	{
		error_handling(ERR_CMD_NOT_FOUND, cmd);
		ft_free_strs(ppx->cmds);
		exit(127);
	}
	execve(ppx->path, ppx->cmds, ppx->env);
	perror("execve");
	ft_free_strs(ppx->cmds);
	free(ppx->path);
	exit(127);
}

char	*construct_path(const char *dir, const char *cmd)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(dir, "/");
	path = NULL;
	if (temp)
	{
		path = ft_strjoin(temp, cmd);
		free(temp);
	}
	return (path);
}

char	*find_path(char **paths, char *cmd)
{
	int		i;
	char	*road;

	if (!paths || !cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		road = construct_path(paths[i], cmd);
		if (road && access(road, F_OK) == 0)
			return (road);
		free(road);
		i++;
	}
	return (NULL);
}
