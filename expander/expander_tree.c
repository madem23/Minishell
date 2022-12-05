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
	branch->type = type;
	branch->value = value;
	branch->is_subtree = false;
	branch->is_branch = true;
	return (branch);
}

int	init_var_branch_and_move(t_expander_tree *subtree, int *index, int *i, t_expander_tree **current_node)
{
	//printf("----------ENTREE loop VAR i = %d et last_end = %d\n", i, last_end);
	(*current_node)->next_branch = init_branch(subtree, DOLLAR, (*index)++, get_var(i, subtree->value));
	*current_node = (*current_node)->next_branch;
	printf("SORTIE loop VAR, i = %d et last_end = %d\n", *i, (*i) - 1);
	return ((*i) - 1);
}

int	init_word_branch_and_move(t_expander_tree *subtree, int *index, int *i, t_expander_tree **current_node)
{
	//	printf("----------ENTREE loop VAR SQUOTE i = %d et last_end = %d\n", i, last_end);
	(*current_node)->next_branch = init_branch(subtree, WORD, (*index)++, get_word(i, subtree->value));
	*current_node = (*current_node)->next_branch;
	printf("SORTIE loop VAR, i = %d et last_end = %d\n", *i, (*i) - 1);
	return ((*i) - 1);
}

int	init_op_tk_branch_and_move(t_expander_tree *subtree, int *index, int *i, t_expander_tree **current_node)
{
	//	printf("----------ENTREE loop VAR SQUOTE i = %d et last_end = %d\n", i, last_end);
	(*current_node)->next_branch = init_branch(subtree, OPENING_TK, (*index)++, get_word(i, subtree->value));
	*current_node = (*current_node)->next_branch;
	printf("SORTIE loop VAR, i = %d et last_end = %d\n", *i, (*i) - 1);
	return ((*i) - 1);
}

void	create_parsing_branches(t_expander_tree *subtree, char *value_subtree,
	int type_subtree)
{
	t_expander_tree	*current_node;
	int				index;
	int				i;
	int				last_end;

	index = 0;
	i = 0;
	last_end = -1;
	current_node = subtree;
	while (value_subtree[i])
	{
		while (value_subtree[i] && value_subtree[i] != '$' && value_subtree[i] != '\''
			&& value_subtree[i] != '"')
			i++;
		if ((last_end == -1 && (i > 0 || (i == 0 && ft_strlen(value_subtree) == 1)))
			|| (i - last_end > 1 && last_end >= 0))
		{ 
			if (type_subtree == WORD && i == ft_strlen(value_subtree) - 1)
				i++;
		//	printf("----------ENTREE loop WORD i = %d et last_end = %d\n", i, last_end);
			current_node->next_branch = init_branch(subtree, WORD, index++, get_prev_word(last_end, &i, value_subtree));
			current_node = current_node->next_branch;
			last_end = i - 1;
		//	printf("SORTIE loop WORD, i = %d et last_end = %d\n", i, last_end);
		}
		if (value_subtree[i] == '$' && type_subtree != SQUOTE)
			last_end = init_var_branch_and_move(subtree, &index, &i, &current_node);
		else if (value_subtree[i] == '$' && type_subtree == SQUOTE)
			last_end = init_word_branch_and_move(subtree, &index, &i, &current_node);
		else if ((value_subtree[i] == '\'' && type_subtree == SQUOTE && i == 0)
				|| (value_subtree[i] == '"' && type_subtree == DQUOTE && i == 0))
			last_end = init_op_tk_branch_and_move(subtree, &index, &i, &current_node);
		else if ((value_subtree[i] == '\'' && type_subtree == SQUOTE && i == ft_strlen(value_subtree) - 1)
				|| (value_subtree[i] == '"' && type_subtree == DQUOTE && i == ft_strlen(value_subtree) - 1))
		{
		//	printf("----------ENTREE loop CLOSING TOKEN, i = %d et last_end = %d\n", i, last_end);
			current_node->next_branch = init_branch(subtree, CLOSING_TK, index++, get_prev_word(last_end, &i, value_subtree));
			current_node = current_node->next_branch;
		//	printf("Sortiee fct , i = %d et last_end = %d\n", i, last_end);
			last_end = i - 1;
			i++;
		//	printf("SORTIE loop CLOSING TOKEN, i = %d et last_end = %d\n", i, last_end);
		}
		else if (value_subtree[i])
			i++;
	}
}

t_expander_tree	*create_parsing_subtree(int type, t_expander_tree *treetop, char *value)
{
	t_expander_tree	*subtree;
	
	printf("Creation subtree = %s, of type : %d\n", value, type);
	subtree = malloc(sizeof(t_expander_tree));
	if (!subtree)
		error(1, "Failed to allocate parsing subtree\n");
	subtree->treetop = treetop;
	subtree->next_subtree = NULL;
	create_parsing_branches(subtree, value, type);
	subtree->type = type;
	subtree->value = value;
	subtree->is_subtree = true;
	subtree->is_branch = false;
	return (subtree);
}

t_expander_tree	*creating_expander_tree(char *value, t_minishell *minishell)
{
	t_expander_tree	*tree;
	t_expander_tree	*current_node;
	int		i;
	int		i_end;
	char	*s_tmp;

	i = 0;
	i_end = - 1;
	(void)minishell;
	tree = malloc(sizeof(t_expander_tree));
	if (!tree)
		error(1, "Failed to allocate parsing tree\n");
	tree->value = value;
	tree->treetop = tree;
	current_node = tree->treetop;
	while (value[i])
	{
		if (value[i] =='\'' && locate_char(value + i + 1, '\'') >= 0)
		{
			if (i - i_end >= 2)
			{
				if (i_end == -1)
					i_end = 0;
				current_node->next_subtree = create_parsing_subtree(WORD, tree->treetop, ft_substr(value, i_end, i - i_end));
				current_node = current_node->next_subtree;
			}
			if (locate_char(value + i + 1, '\'') >=0)
			{
				i_end = locate_char(value + i + 1, '\'');
				current_node->next_subtree = create_parsing_subtree(SQUOTE, tree->treetop, ft_substr(value, i, i_end + 2));
				current_node = current_node->next_subtree;
				i += ++i_end;
				i_end = i + 1;
			}
		}
		if (value[i] =='"' && locate_char(value + i + 1, '"') >= 0)
		{
			if (i - i_end >= 2)
			{
				if (i_end == -1)
					i_end = 0;
				current_node->next_subtree = create_parsing_subtree(WORD, tree->treetop, ft_substr(value, i_end, i - i_end));
				current_node = current_node->next_subtree;
			}
			if (locate_char(value + i + 1, '"') >=0)
			{
				i_end = locate_char(value + i + 1, '"');
				current_node->next_subtree = create_parsing_subtree(DQUOTE, tree->treetop, ft_substr(value, i, i_end + 2));
				current_node = current_node->next_subtree;
				i += ++i_end;
				i_end = i + 1;
			}
		}
		i++;
	}
	if (i - i_end >= 1)
	{
		if (i_end == -1)
			i_end = 0;
		s_tmp = ft_substr(value, i_end, i - i_end);
		current_node->next_subtree = create_parsing_subtree(WORD, tree->treetop, s_tmp);
		free(s_tmp);
		current_node = current_node->next_subtree;
	}
	return (tree);
}
