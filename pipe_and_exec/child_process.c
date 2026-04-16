/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 04:11:02 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/15 04:58:38 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipes_child(int i, int nb_cmds, int **pipes)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < nb_cmds - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
}

static void	perm_or_dir(int i, char **path)
{
	if (i == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(*path);
		exit(126);
	}
	if (i == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(*path);
		exit(126);
	}
}

void	exec_external(t_cmd *cmd, char **envp)
{
	char		*path;
	struct stat	st;

	path = resolve_cmd(cmd->argv[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		perm_or_dir(0, &path);
	if (access(path, X_OK) != 0)
		perm_or_dir(1, &path);
	execve(path, cmd->argv, envp);
	perror("execve");
	free(path);
	exit(1);
}

void	child_process(t_minish *minish, t_cmd *cmd, int i, t_exec *exec)
{
	int	ret;

	setup_pipes_child(i, exec->nb_cmds, exec->pipes);
	if (cmd->redirs)
	{
		if (apply_redirs(cmd->redirs))
			exit(1);
	}
	close_all_pipes(exec->pipes, exec->nb_cmds - 1);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
	{
		ret = exec_builtin(cmd, minish, 1);
		exit(ret);
	}
	exec_external(cmd, minish->envp);
}
