/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:17:41 by abarahho          #+#    #+#             */
/*   Updated: 2025/01/17 17:29:04 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	initialize_pipex(t_ppx *ppx, char **env)
{
	ppx->env = env;
	ppx->paths = find_paths(env);
	ppx->pipe_fd[0] = -1;
	ppx->pipe_fd[1] = -1;
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free (strs);
}

void	free_pipex(t_ppx *ppx)
{
	ft_free_strs(ppx->paths);
	close_pipe(ppx);
}

char	**find_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}
