/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 00:27:00 by juspende          #+#    #+#             */
/*   Updated: 2019/05/07 02:33:30 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"
#include <stdbool.h>

static uint32_t	get_distance(struct s_map *map, int32_t xo,
		int32_t yo, char player)
{
	int32_t		x;
	int32_t		y;
	uint32_t	score;
	uint32_t	dist[2];

	score = UINT32_MAX;
	y = -1;
	while (++y < map->height && (x = -1) == -1)
	{
		while (++x < map->width)
		{
			if (map->stored[y * map->width + x] != '.' && (map->stored[y *
						map->width + x] | 0x20) != (player | 0x20))
			{
				dist[0] = (x > xo ? x - xo : xo - x);
				dist[1] = (y > yo ? y - yo : yo - y);
				if (dist[0] * dist[0] + dist[1] * dist[1] < score)
					score = dist[0] * dist[0] + dist[1] * dist[1];
			}
		}
	}
	return (score);
}

static uint32_t	get_score(struct s_map *map, struct s_map *piece,
		int32_t pos[2], char player_char)
{
	int32_t		x;
	int32_t		y;
	uint32_t	score;
	uint32_t	score2;

	score = UINT32_MAX;
	y = -1;
	while (++y < piece->height && (x = -1) == -1)
		while (++x < piece->width)
			if (piece->stored[y * piece->width + x] == '*')
				if ((score2 = get_distance(map, pos[0] + x,
								pos[1] + y, player_char)) < score)
					score = score2;
	return (score);
}

static bool		is_valid(struct s_map *map, struct s_map *piece, int32_t pos[2],
		char player_char)
{
	bool		overlap;
	int32_t		x;
	int32_t		y;
	char		c;

	overlap = false;
	y = -1;
	while ((x = -1) && ++y < piece->height)
		while (++x < piece->width)
			if (piece->stored[y * piece->width + x] != '*')
				continue ;
			else if (!(pos[1] + y >= 0 && pos[0] + x >= 0
			&& pos[1] + y < map->height && pos[0] + x < map->width))
				return (false);
			else if ((c = map->stored[(pos[1] + y) *
						map->width + (pos[0] + x)]) != '.')
			{
				if (!overlap && (c | 0x20) == (player_char | 0x20))
					overlap = true;
				else
					return (false);
			}
	return (overlap);
}

void			play(struct s_map *map, struct s_map *piece, char player_char)
{
	int32_t			x;
	int32_t			y;
	uint32_t		score;
	struct s_move	best;

	best.score = UINT32_MAX;
	y = -piece->height;
	while (y < map->height)
	{
		x = -piece->width;
		while (x < map->width)
		{
			if (is_valid(map, piece, (int32_t[2]){ x, y }, player_char))
				if ((score = get_score(map, piece, (int32_t[2]){ x, y },
								player_char)) < best.score)
					best = (struct s_move) { x, y, score };
			++x;
		}
		++y;
	}
	if (best.score == UINT32_MAX)
		ft_printf("Can't play\n");
	else
		ft_printf("%d %d\n", best.y, best.x);
}
