/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:17:52 by abarahho          #+#    #+#             */
/*   Updated: 2025/01/17 17:16:51 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	error_handling(t_error_code code, char *cmd)
{
	if (code == ERR_FILE_NOT_FOUND)
		return (ft_dprintf(2, "pipex: %s: No such file or directory\n", cmd));
	else if (code == ERR_ARGS)
		return (ft_dprintf(2, "pipex: invalid number of arguments.\n"));
	else if (code == ERR_PERMISSION_DENIED)
		return (ft_dprintf(2, "pipex: %s: Permission denied\n", cmd));
	else if (code == ERR_CMD_NOT_FOUND)
		return (ft_dprintf(2, "pipex: %s: command not found\n", cmd));
	else if (code == ERR_PIPE_FAILURE)
		return (ft_dprintf(2, "pipex: pipe failure\n"));
	else if (code == ERR_FORK_FAILURE)
		return (ft_dprintf(2, "pipex: fork failure\n"));
	else
		return (ft_dprintf(2, "pipex: unknown error\n"));
	return (1);
}
