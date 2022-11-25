#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_branch(t_tree *branch)
{
	if (branch->exec_args)
		free_tab(branch->exec_args);
	if (branch->exec_path)
		free(branch->exec_path);
	free(branch->infiles);
	free(branch->outfiles);
	free(branch->outfiles_append);
	free(branch->diamonds);
	free(branch);
}

void	free_tree(t_tree *treetop)
{
	t_tree	*tmp;

	while (treetop)
	{
		free_branch(treetop->branch);
		tmp = treetop;
		treetop = treetop->subtree;
		free(tmp);
	}
}

void	free_parser(t_parser *parser)
{
	t_token	*tmp;
	
	while (parser->first_token)
	{
		tmp = parser->first_token;
		parser->first_token = parser->first_token->next_token;
		free(tmp->value);
		free(tmp);
	}
	free(parser->lexer);
	free_tab(parser->cmd_paths);
	free(parser);
}

void	free_exit_final(t_minishell *minishell)
{
	free_tree(minishell->tree);
	free_parser(minishell->parser);
	free(minishell);
	exit(EXIT_SUCCESS);
}
