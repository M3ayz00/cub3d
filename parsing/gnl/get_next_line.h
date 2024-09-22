/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:16:50 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/22 20:29:42 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include "../../cub3d.h"

# define BUFFER_SIZE 1

int		ft_strlen(char *str);
char	*ft_strchr(char *str, int c);
void	*ft_memcpy(void *dest, void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t num_elements, size_t element_size);
char	*get_next_line(int fd, char **rescue);
char	*ft_strjoin2(char *s1, char *s2);
char	*read_file(int fd, char *container);
char	*gget_line(char *container);
char	*update_container(char *container);

#endif
