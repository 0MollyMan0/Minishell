/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:35:28 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/24 10:43:35 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	int				has_pipe;
	int				type;
	struct s_cmd	*next;
}	t_cmd;



// --- Utils Libft --- //
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, int start, int end);
int		ft_isspace(const char c);
char	*add_char(char *str, char c);

// --- Utils Token --- //
void	add_token(t_token **lst, t_token *new);
t_token	*new_token(t_token_type type, char *value, int is_strndup);

// --- Utils Cmd --- //
t_cmd	*new_cmd(void);
void	add_cmd(t_cmd **lst, t_cmd *new);
void	add_arg(t_cmd *cmd, char *value);
void	add_redir(t_cmd *cmd, t_token_type type, char *filename);

// --- Utils Expansion --- //
int		is_expandable(char c);
int		is_char_var(char c);
char	*get_var(char *str, int *i);

// --- Signals --- //
void	handle_sigint(int sig);
void	setup_signals(void);

// --- Prepare Input --- //
char	*read_input(void);
t_token	*tokenize(const char *input);
t_cmd	*parser(t_token *tokens);
t_cmd	*expansion(t_cmd *cmds);
void	var_case(char *str, char **new_str, int	*i);

// --- Free --- //
void	free_all(char *input, t_token *tokens, t_cmd *cmds);
void	free_cmds(t_cmd *cmds);

void	exit_minish(void);

#endif