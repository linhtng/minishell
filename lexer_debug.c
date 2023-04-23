/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:53:43 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/20 18:53:45 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/minishell.h"

void    print_tokens_list(t_list *list)
{
    t_list	*ptr;
	int		i;

	ptr = list;
	i = 1;
	while (ptr)
    {
		printf("token number %d has content: %s, type: %d\n", i, ((t_token *) ptr->content)->string, ((t_token *) ptr->content)->type);
        ptr = ptr->next;
		i++;
    }
}

//int	main(int arc, char **arv)
/* int main(void)
{
	int size;
    t_list	*tokens_lst;
    char *input;

	tokens_lst = NULL;
	 	if (arc == 2)
    {
        size = ft_strlen(arv[1]);
        tokens_lst = token_lst(arv[1], size);
        print_list(tokens_lst);
    }
    input = readline("minishell$  ");
    //input = "echo";
    size = ft_strlen(input);
    tokens_lst = token_lst(input, size);
    print_tokens_list(tokens_lst);
	return (0);
} */