/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_create_branch.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:03:16 by antoine           #+#    #+#             */
/*   Updated: 2022/12/08 18:17:31 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "../parser/parser.h"
#include "../minishell.h"
#include "../libft/libft.h"

/* Creates each branch according to its type : VAR, WORD, CLOSING/OPENING TK.
Check and send the info to the init functions. end == lst_end.
*/
void	create_exp_branches_bis(t_expander_tree *cur_nod, char *value,
	int i, int type)
{
	int	end;

	g_global.u->len = ft_strlen(value) - 1;
	end = -1;
	while (value[i])
	{
		while (value[i] && value[i] != '$'
			&& value[i] != '\'' && value[i] != '"')
			i++;
		if ((end == -1 && (i > 0 || (i == 0 && ft_strlen(value) == 1)))
			|| (i - end > 1 && end >= 0))
			end = init_prv_brch(end, &g_global.u->index, &i, &cur_nod);
		if (value[i] == '$' && type != SQUOTE)
			end = init_var_brch(DOLLAR, &g_global.u->index, &i, &cur_nod);
		else if (value[i] == '$' && type == SQUOTE)
			end = init_wd_brch(WORD, &g_global.u->index, &i, &cur_nod);
		else if ((value[i] == '\'' && type == SQUOTE && i == 0)
			|| (value[i] == '"' && type == DQUOTE && i == 0))
			end = init_wd_brch(OPENING_TK, &g_global.u->index, &i, &cur_nod);
		else if ((value[i] == '\'' && type == SQUOTE && i == g_global.u->len)
			|| (value[i] == '"' && type == DQUOTE && i == g_global.u->len))
			end = init_clostk_brch(end, &g_global.u->index, &i, &cur_nod);
		else if (value[i])
			i++;
	}
}

/* Creates the list of branches for the received subtree.
Value = subtree's string;
Type = subtree's type;
*/
void	create_exp_branches(t_expander_tree *subtree, char *value,
	int type)
{
	t_expander_tree	*current_node;

	g_global.u->index = 0;
	current_node = subtree;
	create_exp_branches_bis(current_node, value, 0, type);
}
