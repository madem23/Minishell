#include "parser.h"
#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"

void	converting_dollar_tk(t_minishell *minishell, t_word_parser_tree *branch)
{
	char	*tmp_s;
	int		i_occur;

	tmp_s = NULL;
	i_occur = ft_strchrset(branch->value + 1, "\"\'!@#^%&*$()- +=[]{}:;.,");
	if (branch->value[1] == '{')
		tmp_s = managing_curly_brakets(branch->value, 0, minishell);
	else if (i_occur == 0)
		return ;
	else if (i_occur == -1)
		tmp_s = convert_dollar_token(branch->value + 1, minishell);
	free(branch->value);
	branch->value = tmp_s;
}


void	removing_op_clos_quotes(t_word_parser_tree *branch, int type)
{
	char	*new_value;

	new_value = NULL;
	if (type == OPENING_TK)
		new_value = ft_strdup(branch->value + 1);
	else if (type == CLOSING_TK)
		new_value = ft_strtrim(branch->value, branch->value + (ft_strlen(branch->value) - 1));
	free(branch->value);
	branch->value = new_value;
}

void	converting_all_branches(t_word_parser_tree *tree, t_minishell *minishell)
{
	t_word_parser_tree *current_node;
	t_word_parser_tree *tmp;
	
	tmp = tree->next_subtree;
	current_node = tmp->next_branch;
	while (tmp)
	{
		while (current_node)
		{
			if (current_node->type == OPENING_TK || current_node->type == CLOSING_TK)
				removing_op_clos_quotes(current_node, current_node->type);
			else if (current_node->type == DOLLAR)
				converting_dollar_tk(minishell, current_node);
			current_node = current_node->next_branch;
		}
		tmp = tmp->next_subtree;
		if (tmp)
			current_node = tmp->next_branch;
	}
}

char	*parsing_quotes_dollar(char *value, t_minishell *minishell, t_word_parser_tree *tree)
{
	char				*new_value;
	char				*buf;
	t_word_parser_tree *tmp;

	new_value = NULL;
	converting_all_branches(tree, minishell);
	tmp = tree->next_subtree;
	free(tree);
	tree = tmp;
	while (tree)
	{
		while (tree->next_branch)
		{
			if (!new_value)
				new_value = tree->next_branch->value;
			else
			{
				buf = ft_strjoin(new_value, tree->next_branch->value);
				free(new_value);
				new_value = buf;
				buf = new_value;
			}
			tmp = tree->next_branch->next_branch;
			free(tree->next_branch);
			tree->next_branch = tmp;
		}
		tmp = tree->next_subtree;
		free(tree);
		tree = tmp;
	}
	free(value);
	//free_parsing_tree(begin);
	return (new_value);
}

void	lexing_quotes_and_dollar(t_parser *parser, t_minishell *minishell)
{
	t_token	*tmp;

	tmp = parser->first_token;
	while (tmp)
	{
		if (tmp->type == TK_WORD || tmp->type == TK_QUOTE || tmp->type == TK_DOLLAR)
			tmp->value = parsing_quotes_dollar(tmp->value, minishell, creating_word_parsing_tree(tmp->value, minishell));
		tmp = tmp->next_token;
	}
}
