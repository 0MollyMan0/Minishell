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

void	exec_external(t_cmd *cmd, char **envp)
{
	char	*path;

	path = resolve_cmd(cmd->argv[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	perror(path);
	free(path);
	exit(1);
}

/* ---- Child process ---- */

void	child_process(t_minish *minish, t_cmd *cmd, int i, t_exec *exec)
{
	int	ret;

	setup_pipes_child(i, exec->nb_cmds, exec->pipes);
	if (cmd->redirs)
		apply_redirs(cmd->redirs);
	close_all_pipes(exec->pipes, exec->nb_cmds - 1);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
	{
		ret = exec_builtin(cmd, minish);
		exit(ret);
	}
	exec_external(cmd, minish->envp);
}
