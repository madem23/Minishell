/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:03:01 by mdemma            #+#    #+#             */
/*   Updated: 2022/11/30 13:03:06 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "../parser/parser.h"
#include "../minishell.h"
#include "../libft/libft.h"

/* Initializes the subtree's structure. Branches are created from here. */
t_expander_tree	*init_exp_subtree(int type, t_expander_tree *treetop,
	char *value)
{
	t_expander_tree	*subtree;

	printf("Creation subtree = %s, of type : %d\n", value, type);
	subtree = malloc(sizeof(t_expander_tree));
	if (!subtree)
		error(1, "Failed to allocate parsing subtree\n");
	subtree->treetop = treetop;
	subtree->next_subtree = NULL;
	subtree->value = value;
	subtree->e_brch_type = type;
	subtree->is_subtree = true;
	subtree->is_branch = false;
	global.cur_exp_subtree = subtree;
	create_exp_branches(subtree, value, type);
	return (subtree);
}

/* Creates a subtree (SQUOTE, DQUOTE) when closed quotes are met.
Creates a WORD subtree if words not enclosed in quotes.*/
void	create_exp_subtree(int *i, int *i_end,
	t_expander_tree **cur_nod, char quote)
{
	int	type;

	if (quote == '\'')
		type = SQUOTE;
	else
		type = DQUOTE;
	if ((*i) - (*i_end) >= 2)
	{
		if (*i_end == -1)
			*i_end = 0;
		(*cur_nod)->next_subtree = init_exp_subtree(WORD,
				global.cur_exp_treetop, ft_substr(global.cur_exp_treetop->value,
					*i_end, (*i) - (*i_end)));
		(*cur_nod) = (*cur_nod)->next_subtree;
	}
	if (locate_char(global.cur_exp_treetop->value + (*i) + 1, quote) >= 0)
	{
		*i_end = locate_char(global.cur_exp_treetop->value + (*i) + 1, quote);
		(*cur_nod)->next_subtree = init_exp_subtree(type,
				global.cur_exp_treetop, ft_substr(global.cur_exp_treetop->value,
					*i, (*i_end) + 2));
		(*cur_nod) = (*cur_nod)->next_subtree;
		*i += ++(*i_end);
		*i_end = (*i) + 1;
	}
}

/* Creates the final subtree if final word not into quotes. */
void	create_exp_final_subtree(int i, int i_end, char *value,
	t_expander_tree **cur_node)
{
	char	*s_tmp;

	if (i_end == -1)
			i_end = 0;
	s_tmp = ft_substr(value, i_end, i - i_end);
	(*cur_node)->next_subtree = init_exp_subtree(WORD,
			global.cur_exp_treetop, s_tmp);
	free(s_tmp);
	(*cur_node) = (*cur_node)->next_subtree;
}

/* Main function of the expander tree creation.
Initializes the expander tree and cuts sent token in subtrees
if closed quotes are met.*/
t_expander_tree	*creating_expander_tree(char *value)
{
	t_expander_tree	*tree;
	t_expander_tree	*cur_node;
	int				i;
	int				i_end;

	i = 0;
	i_end = -1;
	tree = malloc(sizeof(t_expander_tree));
	if (!tree)
		error(1, "Failed to allocate parsing tree\n");
	tree->value = value;
	tree->treetop = tree;
	global.cur_exp_treetop = tree;
	cur_node = tree->treetop;
	while (value[i])
	{
		if (value[i] == '\'' && locate_char(value + i + 1, '\'') >= 0)
			create_exp_subtree(&i, &i_end, &cur_node, '\'');
		if (value[i] == '"' && locate_char(value + i + 1, '"') >= 0)
			create_exp_subtree(&i, &i_end, &cur_node, '"');
		i++;
	}
	if (i - i_end >= 1)
		create_exp_final_subtree(i, i_end, value, &cur_node);
	return (tree);
}
