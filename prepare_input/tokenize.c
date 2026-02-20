/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:14:29 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/20 14:29:30 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token *new_token(t_token_type type, char *value, int is_strndup)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value != NULL)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->next = NULL;
	if (is_strndup)
		free(value);
	return (token);
}

static void add_token(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!lst || !new)
		return ;	
	if (!*lst)
	{
		*lst = new;
		return;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static int	tokenize_arrow(const char *input, size_t i, t_token **tokens)
{
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			add_token(&(*tokens), new_token(TOKEN_APPEND, ">>", 0));
			i++;
		}
		else
			add_token(&(*tokens), new_token(TOKEN_REDIR_OUT, ">", 0));
	}
	else
	{
		if (input[i + 1] == '<')
		{
			add_token(&(*tokens), new_token(TOKEN_HEREDOC, "<<", 0));
			i++;
		}
		else
			add_token(&(*tokens), new_token(TOKEN_REDIR_IN, "<", 0));
	}
	i++;
	return (i);
}

static int	tokenize_word(const char *input, size_t i, t_token **tokens)
{
	size_t	start;
	char	quote;

	start = i;
	quote = 0;
	while (input[i])
	{
		if (!quote && (isspace(input[i]) || input[i] == '|'
			|| input[i] == '<' || input[i] == '>'))
			break;

		if (input[i] == '\'' || input[i] == '"')
		{
			if (!quote)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		i++;
	}
	add_token(&(*tokens),
		new_token(TOKEN_WORD, ft_strndup(input, start, i - 1), 1));
	return (i);
}

t_token *tokenize(const char *input)
{
	t_token	*tokens;
	size_t	i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '|')
		{
			add_token(&tokens, new_token(TOKEN_PIPE, "|", 0));
			i++;
		}
		else if (input[i] == '>' || input[i] == '<')
			i = tokenize_arrow(input, i, &tokens);
		else
			i = tokenize_word(input, i, &tokens);
	}
	return (tokens);
}
