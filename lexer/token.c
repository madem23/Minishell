/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:33:54 by anloisea          #+#    #+#             */
/*   Updated: 2022/12/01 14:52:09 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_a_variable_declaration(char *value)
{
	int	i;

	i = 0;
	if (value[0] && !ft_isalpha(value[0]) && value[0] != '_')
		return (0);
	while (ft_isaccepted_var_name(value[i]) && value[i] != '=')
		i++;
	if (i == 0)
		return (0);
	if (value[i] == '=' && (!value[++i] || ft_isaccepted(value[i])))
		return (1);
	else
		return (0);
}

t_token	*token_init(int type, char *value, t_lexer *lexer)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		error(1, "failed to allocate token\n");
	if (type == TK_WORD && is_a_variable_declaration(value))
		type = TK_EQUAL;
	token->e_tk_type = type;
	token->value = value;
	if (type == TK_LOWER || type == TK_GREATER || type == TK_DLOWER
		|| type == TK_DGREATER)
		token->redir_token = true;
	else
		token->redir_token = false;
	token->parsed = false;
	token->next_token = NULL;
	token->index = lexer->token_index;
	lexer->token_index++;
	return (token);
}
