/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_init_branch.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:32:31 by antoine           #+#    #+#             */
/*   Updated: 2022/12/08 18:02:26 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "../parser/parser.h"
#include "../minishell.h"
#include "../libft/libft.h"

/* Initializes (malloc) expander branches.
Branches will then be converted and then joined again to
form expanded tokens. */
t_expander_tree	*init_branch(t_expander_tree *subtree, int type,
	int index, char *value)
{
	t_expander_tree	*branch;

	printf("Creation branch = %s, of type : %d\n", value, type);
	branch = malloc(sizeof(t_expander_tree));
	if (!branch)
		error(1, "Failed to allocate branch\n");
	branch->treetop = subtree->treetop;
	branch->index = index;
	branch->next_subtree = NULL;
	branch->subtree = subtree;
	branch->next_branch = NULL;
	branch->e_brch_type = type;
	branch->value = value;
	branch->is_subtree = false;
	branch->is_branch = true;
	return (branch);
}

/* Send the string to the correct function for extraction to create
a branch of type VAR, and moves to the next branch. */
int	init_var_brch(int type, int *index, int *i, t_expander_tree **current_node)
{
	(*current_node)->next_branch = init_branch(g_global.cur_exp_subtree, type,
			(*index)++, get_var(i, g_global.cur_exp_subtree->value));
	*current_node = (*current_node)->next_branch;
	return ((*i) - 1);
}

/* Send the string to the correct function for extraction to create
a branch of type WORD or OPENING TK, and moves to the next branch. */
int	init_wd_brch(int type, int *index, int *i, t_expander_tree **current_node)
{
	(*current_node)->next_branch = init_branch(g_global.cur_exp_subtree, type,
			(*index)++, get_word(i, g_global.cur_exp_subtree->value));
	*current_node = (*current_node)->next_branch;
	return ((*i) - 1);
}

/* Send the string to the correct function for extraction to create a branch
of type Prev Word, and moves to the next branch. */
int	init_prv_brch(int last_end, int *index, int *i,
	t_expander_tree **current_node)
{
	if (g_global.cur_exp_subtree->e_brch_type == WORD
		&& (*i) == ft_strlen(g_global.cur_exp_subtree->value) - 1)
		(*i)++;
	(*current_node)->next_branch = init_branch(g_global.cur_exp_subtree, WORD,
			(*index)++,
			get_prev_word(last_end, i, g_global.cur_exp_subtree->value));
	*current_node = (*current_node)->next_branch;
	return ((*i) - 1);
}

/* Send the string to the correct function for extraction to create a branch
of type CLOSING TK, and moves to the next branch. */
int	init_clostk_brch(int last_end, int *index, int *i,
	t_expander_tree **current_node)
{
	(*current_node)->next_branch = init_branch(g_global.cur_exp_subtree,
			CLOSING_TK, (*index)++,
			get_prev_word(last_end, i, g_global.cur_exp_subtree->value));
	*current_node = (*current_node)->next_branch;
	(*i)++;
	return ((*i) - 2);
}
