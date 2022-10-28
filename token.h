/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:08:55 by anloisea          #+#    #+#             */
/*   Updated: 2022/10/28 16:24:17 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

typedef struct s_token
{
	enum
	{
		TK_ID,
		TK_STR,
		TK_WORD,
		TK_DQUOTE,
		TK_SQUOTE,
		TK_LOWER,
		TK_GREATER,
		TK_DLOWER,
		TK_DGREATER,
		TK_PIPE,
		TK_DOLLAR
	}type;

	char	*value;
}			t_token;

t_token	*token_init(int type, char *value);

#endif