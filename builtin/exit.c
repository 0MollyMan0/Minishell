/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:22:43 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/23 14:48:18 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exit_too_many_arg(void)
{
	write(2, "exit: too many arguments\n", 25);
	return (2);
}

// static int	exit_no_arg(t_minish *minish)
// {
// 	int	exit_code;

// 	exit_code = minish->g_exit_status;
// 	printf("exit\n");
// 	free_all(minish);
// 	free_tab(minish->envp);
// 	exit(exit_code);
// 	return (0);
// }

static int	exit_numeric_error(t_minish *minish, char *arg)
{
	write(2, "exit: ", 6);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
	free_all(minish);
	free_tab(minish->envp);
	exit(2);
}

static int	is_code_exit(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_minish *minish, char **argv)
{
	long arg;

	write(1, "exit\n", 5);
	if (!argv[1])
	{
		free_all(minish);
		free_tab(minish->envp);
		exit(minish->g_exit_status);
	}
	if (!is_code_exit(argv[1]) || !verif_max_long(argv[1]))
		exit_numeric_error(minish, argv[1]);
	if (argv[2])
		return (exit_too_many_arg());
	arg = ft_atol(argv[1]);
	free_all(minish);
	free_tab(minish->envp);
	exit((unsigned char)arg);
}
