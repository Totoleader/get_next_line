/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:33:31 by macote            #+#    #+#             */
/*   Updated: 2023/03/10 10:44:18 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//vérifie si il y a un '\n' dans le current buffer (utilisé dans line_to_list)
int	list_has_no_nl(t_list *head)
{
	int	i;

	if (!head || !head->content)
		return (1);
	while (head->next)
		head = head->next;
	i = 0;
	while (head->content && head->content[i])
	{
		if (head->content[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

// free() toutes les nodes (sauf la dernière si on est pas a la fin)
void	free_all(t_list **head, int read_check)
{
	t_list	*next;

	if (!(*head))
		return ;
	while (((*head)->next))
	{
		next = (*head)->next;
		free((*head)->content);
		(*head)->content = NULL;
		free(*head);
		*head = next;
	}
	if (read_check <= 0)
	{		
		free((*head)->content);
		(*head)->content = NULL;
		free(*head);
		*head = NULL;
	}
}

// rempli le contenu de la line avec le contenu des nodes
void	fill_line(t_list *head, char **line)
{
	int	i;
	int	j;

	j = 0;
	while (head)
	{
		i = 0;
		while (head->content[i] && head->content[i] != '\n')
			line[0][j++] = head->content[i++];
		if (head->content[i] == '\n')
			line[0][j++] = '\n';
		head = head->next;
	}
	line[0][j] = '\0';
}

void	fill_node_with_buffer(char **node_content, char *buffer)
{
	int	i;

	i = -1;
	while (buffer[++i])
		node_content[0][i] = buffer[i];
	node_content[0][i] = '\0';
	free (buffer);
}

void	fill_last_node(char **content, int remainder_size, int i)
{
	char	*temp;
	int		j;

	temp = malloc(sizeof(char) * (remainder_size + 1));
	if (!temp)
		return ;
	j = 0;
	while (content[0][i])
		temp[j++] = content[0][i++];
	temp[j] = '\0';
	free(*content);
	*content = temp;
}
