/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 08:22:52 by juspende          #+#    #+#             */
/*   Updated: 2019/05/07 01:18:06 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"
#include <stdlib.h>
#include <stdbool.h>

static void			allocate(struct s_map *map, struct s_map *piece)
{
	int				x;
	int				y;
	int				ind;

	map->stored = malloc(sizeof(char) * (map->height * map->width + 1));
	piece->stored = malloc(sizeof(char) * (piece->height * piece->width + 1));
	y = -1;
	ind = -1;
	while (map->data[++y] && ((x = -1) == -1))
	{
		while (map->data[y][++x])
			map->stored[++ind] = map->data[y][x];
		free(map->data[y]);
	}
	map->stored[++ind] = '\0';
	y = -1;
	ind = -1;
	while (piece->data[++y] && ((x = -1) == -1))
	{
		while (piece->data[y][++x])
			piece->stored[++ind] = piece->data[y][x];
		free(piece->data[y]);
	}
	piece->stored[++ind] = '\0';
}

static struct s_map	*read_map(int fd, bool piece, int ret)
{
	struct s_map	*map;
	int				height;
	int				width;
	int				y;
	char			*cmpr;

	if ((ret = get_next_line(fd, &cmpr) <= 0) ||
			!(((piece == false && !ft_strncmp(cmpr, "Plateau ", 7)) ||
				(piece == true && !ft_strncmp(cmpr, "Piece ", 5))) &&
			(height = ft_atoi(&cmpr[(piece == true ? 6 : 8)])) > 0 &&
			(width = ft_atoi(&cmpr[(piece == true ? 6 : 8)
							+ ft_strlen(ft_itoa(height))])) > 0))
		return (NULL);
	if (((y = -1) == -1) && piece == false)
		ret = get_next_line(fd, &cmpr) <= 0;
	map = malloc(sizeof(*map) + width * height);
	*map = (struct s_map){ .width = width, .height = height };
	map->data = malloc(sizeof(char *) * (height + 1));
	while (++y < height)
		if (!map || ((ret = get_next_line(fd, &cmpr)) <= 0) ||
				((map->data[y] = ft_strdup(&cmpr[piece == true ? 0 : 4]))
				== NULL))
			break ;
	y < height ? free(map) : (map->data[y] = NULL);
	return (y < height ? NULL : map);
}

static int			read_player_number(int fd, uint32_t *player_number)
{
	char	*cmpr;
	int		ret;

	ret = 0;
	if ((ret = get_next_line(fd, &cmpr)) <= 0)
		return (0);
	if (!cmpr || ft_strncmp(cmpr, "$$$ exec p", 9))
		return (0);
	*player_number = cmpr[10] - 48;
	return (1);
}

int					main(void)
{
	uint32_t		player_number;
	struct s_map	*map;
	struct s_map	*piece;
	int				fd;

	fd = 0;
	if (!read_player_number(fd, &player_number) || player_number > 2)
		return (ft_printf("Can't launch the game\n"));
	while (42)
	{
		if (((map = read_map(fd, false, 0)) == NULL) ||
				((piece = read_map(fd, true, 0)) == NULL))
		{
			free(map);
			free(piece);
			ft_printf("Can't play the game :(\n");
			return (1);
		}
		allocate(map, piece);
		play(map, piece, "OX"[player_number - 1]);
		free(map);
	}
}
