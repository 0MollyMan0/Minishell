/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 08:20:49 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/10 14:18:58 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exec_path(t_minish *minish, char **envp)
{
	char	*path;

	path = find_path(minish->cmds->argv[0], envp);
	if (!path)
		printf("%s: command not found\n", minish->cmds->argv[0]);
	else
	{
		execve(path, minish->cmds->argv, envp);
		perror("execve");	
	}
	exit(127);
}

static void	exec_direct(t_minish *minish, char **envp)
{
	execve(minish->cmds->argv[0], minish->cmds->argv, envp);
	perror("execve");
	exit(127);
}

static void	exec_out(t_minish *minish, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (is_slash_in(minish->cmds->argv[0]))
			exec_direct(minish, envp);
		else
			exec_path(minish, envp);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			minish->g_exit_status = WEXITSTATUS(status);
	}
}

void	exec(t_minish *minish, char **envp)
{
	if (!minish->cmds || !minish->cmds->argv || !minish->cmds->argv[0])
		return ;
	if (is_builtin(minish->cmds->argv[0]))
	{
		minish->g_exit_status = exec_builtin(minish);
		return ;
	}
	exec_out(minish, envp);
}
