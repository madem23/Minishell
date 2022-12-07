#include "minishell.h"

/* Frees tabs. */
void	free_tab(void **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{	
		free(tab[i]);
		i++;
	}
	free(tab);
}

/* Frees all mallocs of a parsing branch.*/
void	free_branch(t_tree *branch)
{
	if (branch->exec_args)
		free_tab((void **)branch->exec_args);
	if (branch->exec_path)
		free(branch->exec_path);
	if (branch->exec_name)
		free(branch->exec_name);
	free(branch->infiles);
	free(branch->outfiles);
	free(branch->outfiles_append);
	free(branch);
}

/* Frees all mallocs of a parsing tree/subtree. */
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
