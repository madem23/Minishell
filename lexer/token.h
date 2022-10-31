/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:08:55 by anloisea          #+#    #+#             */
/*   Updated: 2022/10/31 17:51:10 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../minishell.h"

typedef struct s_token
{
	enum
	{
		TK_STRING,
		TK_WORD,
		TK_EQUAL,
		TK_DQUOTE,
		TK_SQUOTE,
		TK_LOWER,
		TK_GREATER,
		TK_DLOWER,
		TK_DGREATER,
		TK_PIPE,
		TK_DOLLAR,
		TK_EOC // End of command (equivalent de EOF)
	}type;

	char	*value;
}			t_token;

t_token	*token_init(int type, char *value);

#endif