/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:08:55 by anloisea          #+#    #+#             */
/*   Updated: 2022/11/09 18:12:57 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>

typedef struct s_token
{
	enum
	{
		TK_STRING,
		TK_WORD,
		TK_EQUAL,
		TK_QUOTE,
		TK_LOWER,
		TK_GREATER,
		TK_DLOWER,
		TK_DGREATER,
		TK_PIPE,
		TK_DOLLAR,
		TK_EOC
	}	e_tk_type;
	bool			redir_token;
	char			*value;
	int				index;
	struct s_token	*next_token;
	bool			parsed;
}					t_token;
#endif