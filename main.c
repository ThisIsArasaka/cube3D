/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:36:46 by olardeux          #+#    #+#             */
/*   Updated: 2025/02/17 12:01:50 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cube3D.h"
#include "inc/parsing.h"

int	move_hook(int keycode, t_game *data)
{
	if (keycode == XK_Escape)
		mlx_destroy_textures(data);
	if (keycode == XK_e)
		open_door(data);
	if (keycode == XK_w || keycode == XK_s)
	{
		data->textures.dino.state = 1;
		move_forward(data, keycode);
	}
	if (keycode == XK_a || keycode == XK_d)
	{
		data->textures.dino.state = 1;
		move_sideways(data, keycode);
	}
	if (keycode == XK_Left)
		data->player->dir -= ROT_SPEED;
	if (keycode == XK_Right)
		data->player->dir += ROT_SPEED;
	return (0);
}

int	mouse_hook(int x, int y, t_game *data)
{
	int	delta_x;

	(void)y;
	delta_x = x - WIDTH / 2;
	data->player->dir += delta_x * SENSITIVITY;
	mlx_mouse_move(data->mlx->mlx, data->mlx->windows, WIDTH / 2, HEIGHT / 2);
	return (0);
}

int	key_release(int keycode, t_game *data)
{
	if (keycode == XK_Tab)
		data->map->minimap = !data->map->minimap;
	data->textures.dino.state = 0;
	return (0);
}

void	init_hook(t_game *game)
{
	mlx_hook(game->mlx->windows, 17, (1L << 17), mlx_destroy_textures, game);
	mlx_hook(game->mlx->windows, 2, (1L << 0), move_hook, game);
	mlx_hook(game->mlx->windows, 6, (1L << 6), mouse_hook, game);
	mlx_hook(game->mlx->windows, 3, (1L << 1), key_release, game);
	mlx_loop_hook(game->mlx->mlx, draw, game);
	mlx_loop(game->mlx->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (!valid_args(ac, av))
		return (0);
	if (valid_content(av[1], &game) && valid_textures(&game))
		get_player_pos(&game, game.map->map);
	else
		return (free_game(&game.textures, &game), 0);
	game.mlx->mlx = mlx_init();
	if (!game.mlx->mlx)
		return (free_game(&game.textures, &game), 0);
	init_dir(&game);
	init_var(&game);
	game.mlx->windows = mlx_new_window(game.mlx->mlx, WIDTH, HEIGHT, "cube3D");
	if (!game.mlx->windows)
		return (free(game.mlx->mlx), free_game(&game.textures, &game), 0);
	game.mlx->img.img = mlx_new_image(game.mlx->mlx, WIDTH, HEIGHT);
	game.mlx->img.addr = mlx_get_data_addr(game.mlx->img.img,
			&game.mlx->img.bpp, &game.mlx->img.line_len, &game.mlx->img.endian);
	if (!init_texture(&game))
		return (mlx_destroy_textures(&game), 0);
	init_hook(&game);
	return (0);
}

// mlx_mouse_hide(game.mlx->mlx, game.mlx->windows);