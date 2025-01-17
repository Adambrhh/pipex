/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:18:10 by abarahho          #+#    #+#             */
/*   Updated: 2025/01/17 17:01:49 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"

typedef enum e_error_code
{
	ERR_FILE_NOT_FOUND,
	ERR_ARGS,
	ERR_PERMISSION_DENIED,
	ERR_CMD_NOT_FOUND,
	ERR_PIPE_FAILURE,
	ERR_FORK_FAILURE,
	ERR_UNKNOWN
}				t_error_code;

typedef struct s_ppx
{
	int		pipe_fd[2];
	char	**paths;
	char	**env;
	char	**cmds;
	char	*path;
	char	*file;
	int		is_first;
}			t_ppx;

void	initialize_pipex(t_ppx *ppx, char **envp);
void	free_pipex(t_ppx *ppx);
char	*find_path(char **paths, char *cmd);
void	close_pipe(t_ppx *ppx);
int		setup_io(t_ppx *ppx, char *file, int is_first);
int		file_to_pipe(char *file, t_ppx *ppx);
int		pipe_to_file(char *file, t_ppx *ppx);
int		exec_command(t_ppx *ppx, char *file, char *cmd, int is_first);
void	exec_process(t_ppx *ppx, char *cmd);
char	**find_paths(char **envp);
char	*construct_path(const char *dir, const char *cmd);
void	ft_free_strs(char **strs);
int		error_handling(t_error_code code, char *cmd);
int		wait_for_children(void);

#endif
