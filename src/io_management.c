/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:17:48 by abarahho          #+#    #+#             */
/*   Updated: 2025/01/17 17:28:59 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	setup_io(t_ppx *ppx, char *file, int is_first)
{
	if (is_first)
		return (file_to_pipe(file, ppx));
	else
		return (pipe_to_file(file, ppx));
}

int	file_to_pipe(char *file, t_ppx *ppx)
{
	int	file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
		return (error_handling(ERR_FILE_NOT_FOUND, file), 0);
	dup2(file_fd, STDIN_FILENO);
	dup2(ppx->pipe_fd[1], STDOUT_FILENO);
	close(file_fd);
	close_pipe(ppx);
	return (1);
}

int	pipe_to_file(char *file, t_ppx *ppx)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
		return (error_handling(ERR_FILE_NOT_FOUND, file), 0);
	dup2(ppx->pipe_fd[0], STDIN_FILENO);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	close_pipe(ppx);
	return (1);
}

void	close_pipe(t_ppx *ppx)
{
	if (ppx->pipe_fd[0] != -1)
		close(ppx->pipe_fd[0]);
	if (ppx->pipe_fd[1] != -1)
		close(ppx->pipe_fd[1]);
}
