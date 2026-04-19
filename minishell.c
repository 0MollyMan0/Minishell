/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:17:32 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/19 12:35:20 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_minish	init_minish(int ac, char **av, char **envp)
{
	t_minish	minish;

	(void)ac;
	(void)av;
	minish.exit_status = 0;
	minish.envp = dup_tab(envp);
	minish.input = NULL;
	minish.tokens = NULL;
	minish.cmds = NULL;
	return (minish);
}

int	main(int ac, char **av, char **envp)
{
	t_minish	minish;

	minish = init_minish(ac, av, envp);
	while (1)
	{
		setup_signals();
		minish.input = read_input();
		if (!minish.input)
			break ;
		add_history(minish.input);
		minish.tokens = tokenize(minish.input);
		if (g_signal != 0)
			minish.exit_status = g_signal;
		minish.cmds = expansion(minish, parser(&minish, minish.tokens));
		signal(SIGINT, SIG_IGN);
		if (!minish.cmds)
			minish.exit_status = 0;
		if (minish.cmds)
			execute(&minish);
		free_all(&minish);
	}
	free_tab(minish.envp);
	exit_minish();
	return (0);
}
