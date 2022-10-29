/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:33:54 by anloisea          #+#    #+#             */
/*   Updated: 2022/10/29 11:12:23 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_init(int type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		error(1, "failed to allocate token\n");
	token->type = type;
	token->value = value;
	return (token);
}