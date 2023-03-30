/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:33:05 by macote            #+#    #+#             */
/*   Updated: 2023/03/09 13:37:57 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

int					list_has_no_nl(t_list *head);
void				cleanup_last_node(t_list **head, int read_check);
void				add_node(t_list **head, char *buffer, int read_check);
void				line_to_nodes(t_list **head, int fd, int *read_check);
char				*return_line(t_list *head);
char				*get_next_line(int fd);
void				free_all(t_list **head, int read_check);

void				fill_line(t_list *head, char **line);
void				fill_node_with_buffer(char **node_content, char *buffer);
void				fill_last_node(char **content, int remainder_size, int i);

#endif