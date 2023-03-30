/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:32:44 by macote            #+#    #+#             */
/*   Updated: 2023/03/29 17:16:50 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//sépare la node qui contient '\n' en deux nodes: avant '\n' et apres '\n'
void	cleanup_last_node(t_list **head, int read_check)
{
	t_list	*current;
	int		remainder_size;
	int		i;

	if (read_check <= 0)
		return ;
	current = *head;
	while (current->next)
		current = current->next;
	i = 0;
	while (current->content[i] && current->content[i] != '\n')
		i++;
	if (current->content[i] == '\n')
		i++;
	remainder_size = read_check - i;
	fill_last_node(&(current->content), remainder_size, i);
}

//Ajoute une nouvelle t_list a la fin de la linked list
void	add_node(t_list **head, char *buffer, int read_check)
{
	t_list	*current;
	t_list	*new_node;
	char	*node_content;

	node_content = malloc(sizeof(char) * (read_check + 1));
	if (!node_content)
		return ;
	fill_node_with_buffer(&node_content, buffer);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = node_content;
	new_node->next = NULL;
	if (!(*head))
		(*head) = new_node;
	else
	{
		current = (*head);
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

//créer des nodes avec content de taille BUFFER_SIZE jusqu'a un '\n'
void	line_to_nodes(t_list **head, int fd, int *read_check)
{
	char	*buffer;

	while (list_has_no_nl(*head))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		*read_check = read(fd, buffer, BUFFER_SIZE);
		if (*read_check <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[*read_check] = '\0';
		add_node(head, buffer, *read_check);
	}
}

//concat le content des node pour créer le string de retour du programme
char	*return_line(t_list *head)
{
	char	*line;
	t_list	*current;
	int		i;
	int		j;

	if (!head)
		return (NULL);
	current = head;
	j = 0;
	while (current)
	{
		i = 0;
		while (current->content[i] && current->content[i] != '\n' && ++j)
			i++;
		j += current->content[i] == '\n';
		current = current ->next;
	}	
	line = malloc(sizeof(char) * (j + 1));
	if (!line)
		return (NULL);
	fill_line(head, &line);
	return (line);
}

//  1 - Ajoute des nodes a la linked list.
//  2 - Créer la string de retour à partir de la linked list.
//  3 - Cleanup la dernière node pour garder seulement le restant du buffer.
//  4 - Libère la mémoire de la linked list.
char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	int				read_check;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	read_check = 0;
	if (head && head->content)
	{
		read_check = 0;
		while (head->content[read_check])
			read_check++;
	}
	line_to_nodes(&head, fd, &read_check);
	line = return_line(head);
	cleanup_last_node(&head, read_check);
	free_all(&head, read_check);
	if ((line && !line[0]) || read_check < 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int main(void)
{
	int fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));

	free(get_next_line(fd));
	return (0);
}
