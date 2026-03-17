/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 02:38:53 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/15 04:51:22 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* redir for stdin */

void	apply_redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->filename);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

/* redir for stdout */

void	apply_redir_out(t_redir *redir)
{
	int	fd;
	int	flags;

	if (redir->type == TOKEN_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(redir->filename, flags, 0644);
	if (fd < 0)
	{
		perror(redir->filename);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

/* Redirections depending on token */

void	apply_redirs(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == TOKEN_REDIR_IN)
			apply_redir_in(redirs);
		else if (redirs->type == TOKEN_REDIR_OUT)
			apply_redir_out(redirs);
		else if (redirs->type == TOKEN_APPEND)
			apply_redir_out(redirs);
		else if (redirs->type == TOKEN_HEREDOC)
			apply_redir_in(redirs);
		redirs = redirs->next;
	}
}
