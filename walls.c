
#include "cub3d.h"



int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};



void	draw_wall_cx(t_cub3d *cub3d)
{		
	cub3d->cx = (2 * cub3d->x / screenWidth) - 1; // all the values are limited between [-1,1]
	cub3d->raydirx = cub3d->dirx + cub3d->planx * cub3d->cx;
	cub3d->raydiry = cub3d->diry + cub3d->plany * cub3d->cx;

}

void	draw_wall_delta( t_cub3d *cub3d)
{
	cub3d->deltadistx = (cub3d->raydiry == 0)? 0 : ((cub3d->raydirx == 0)? 1 : fabs(1/cub3d->raydirx));
	cub3d->deltadisty = (cub3d->raydirx == 0) ? 0 : ((cub3d->raydiry == 0) ? 1 : fabs(1 / cub3d->raydiry));;
	cub3d->mapx = (int)cub3d->posx;
	cub3d->mapy= (int)cub3d->posy;
}

void	draw_wall_side(t_cub3d *cub3d)
{
	if (cub3d->raydirx < 0)
	{
		cub3d->stepx = -1;
		cub3d->sidedistx = (cub3d->posx - cub3d->mapx) * cub3d->deltadistx;
	}
	else
	{
		cub3d->stepx = 1;
		cub3d->sidedistx = (cub3d->mapx + 1.0 - cub3d->posx) * cub3d->deltadistx;
	}
	if (cub3d->raydiry < 0)
	{
		cub3d->stepy = -1;
		cub3d->sidedisty = (cub3d->posy - cub3d->mapy) * cub3d->deltadisty;
	}
	else
	{
		cub3d->stepy = 1;
		cub3d->sidedisty = (cub3d->mapy+ 1.0 - cub3d->posy) * cub3d->deltadisty;
	}
}

 void	draw_wall_dda(t_cub3d *cub3d)
 {
	while (cub3d->hit == 0)
	{
		if (cub3d->sidedistx < cub3d->sidedisty)
		{
			cub3d->sidedistx += cub3d->deltadistx;
			cub3d->mapx += cub3d->stepx;
			cub3d->side = 0;
		}
		else
		{
			cub3d->sidedisty += cub3d->deltadisty;
			cub3d->mapy+= cub3d->stepy;
			cub3d->side = 1;
		}//++
		if(cub3d->side == 0 && cub3d->raydirx < 0)
		{
			cub3d->side = 2;
		}
		else if(cub3d->side == 1 && cub3d->raydiry < 0)
		{
			cub3d->side = 3;
		}//++
		if (worldMap[cub3d->mapx][cub3d->mapy] == 1) 
			cub3d->hit = 1;
	} 
 }

void	draw_wall_perp(t_cub3d *cub3d)
{
	if (cub3d->side == 0 || cub3d->side == 2)//++
		cub3d->perpwalldist = (double)(cub3d->mapx - cub3d->posx + (1 - cub3d->stepx) / 2) / cub3d->raydirx;
	else          
		cub3d->perpwalldist = (double)(cub3d->mapy- cub3d->posy + (1 - cub3d->stepy) / 2) / cub3d->raydiry;
}


void	draw_wall_h_w(t_cub3d *cub3d)
{
	cub3d->lineHeight = (int)(screenHeight / cub3d->perpwalldist);
	cub3d->drawStart = -cub3d->lineHeight / 2 + screenHeight / 2;
	if(cub3d->drawStart < 0)
		cub3d->drawStart = 0;
	cub3d->drawEnd = cub3d->lineHeight / 2 + screenHeight / 2;
	if(cub3d->drawEnd >= screenHeight)
		cub3d->drawEnd = screenHeight - 1;
		//++
	if(cub3d->side == 0)
		cub3d->color = 0xFF2500;
	else if(cub3d->side ==1)
		cub3d->color = 0x0044ed4;
	else if(cub3d->side ==2)
		cub3d->color = 0x4EBDAD;
	else if(cub3d->side ==3)
		cub3d->color = 0xF3CE00;
		//++
	if (cub3d->change == 1)
	{
		cub3d->drawStart +=  cub3d->plus;
		cub3d->drawEnd +=  cub3d->plus;
	}	
	else if (cub3d->change == -1)
	{
		cub3d->drawStart += cub3d->plus;
		cub3d->drawEnd += cub3d->plus;
	}
	if (cub3d->jump == 1)
	{
		//printf("j");
		cub3d->drawStart += 100;
		cub3d->drawEnd += 100;
		
	}
	else if (cub3d->jumpback == -1)
	{
	//	printf("b");
		cub3d->drawStart -= 100;
		cub3d->drawEnd -= 100;
		// printf("jumpback drawstart : %d\n", cub3d->drawStart);
	}
	
}

void    drawline(int x, int start, int end, t_cub3d *cub3d)
{
	int i = 0;

	while (i <  screenHeight)
	{
		if(i <= start)
			cub3d->data[i * screenWidth + x] = 0x81DBF2;
		else
		{
			if (i <= end)
				cub3d->data[i * screenWidth + x] = cub3d->color;
			else
				cub3d->data[i * screenWidth + x] = 0xEFA719;	
		}
		i++;
	}
}

void    draw_wall(t_cub3d *cub3d)
{
	cub3d->x = 0;
	while (cub3d->x < screenWidth) 
	{
		draw_wall_cx(cub3d);
		draw_wall_delta(cub3d);
		draw_wall_side(cub3d);
		cub3d->hit = 0;
		draw_wall_dda(cub3d);
		draw_wall_perp(cub3d);
		draw_wall_h_w(cub3d);
		drawline(cub3d->x, cub3d->drawStart, cub3d->drawEnd, cub3d);
		cub3d->x++;
	}
	//printf("****%d\n",cub3d->drawStart);
}




int ft_key_press(int keycode, t_cub3d *cub3d)
{
//	printf("%d",keycode);
	if (cub3d->movespeed > 1)
		cub3d->movespeed *= 0.1;
	if (keycode == 49)
	{
		//printf("im here *\n");
		cub3d->jump = 1;
		//cub3d->jumpback = -1;
	}
	//printf("posx:%d    dirx*movespeed:%d     totale:%d \n",
	//(int) (cub3d->posx),(int)(cub3d->dirx * cub3d->movespeed),(int)(cub3d->posx + cub3d->dirx * cub3d->movespeed));
	if (keycode == 126)
	{
		cub3d->change = 1;
		if (cub3d->drawStart <= screenHeight - 20)
			cub3d->plus += 10;
	}
	if (keycode == 125)
	{
		cub3d->change = -1;
		if (cub3d->drawEnd >= 10)
			cub3d->plus -= 10;
	}
	if (keycode == 13)
	{
		if(worldMap[(int)(cub3d->posx + cub3d->dirx * cub3d->movespeed)][(int)(cub3d->posy)] == 0) 
			cub3d->posx += cub3d->dirx * cub3d->movespeed;
		if(worldMap[(int)(cub3d->posx)][(int)(cub3d->posy + cub3d->diry * cub3d->movespeed)] == 0)
		cub3d->posy += cub3d->diry * cub3d->movespeed;
	}
	if (keycode == 1)
	{
		if(worldMap[(int)(cub3d->posx - cub3d->dirx * cub3d->movespeed)][(int)(cub3d->posy)] == 0)
			cub3d->posx -= cub3d->dirx * cub3d->movespeed;
		if(worldMap[(int)(cub3d->posx)][(int)(cub3d->posy - cub3d->diry * cub3d->movespeed)] == 0)
			cub3d->posy -= cub3d->diry * cub3d->movespeed;
		
	}
	// move_left_side
	// if (keycode == 0)
	// {
	// 	if(worldMap[(int)(cub3d->posx + cub3d->dirx * cub3d->movespeed)][(int)(cub3d->posy)] == 0) 
	// 		cub3d->posx += cub3d->dirx * cub3d->movespeed;
	// 	if(worldMap[(int)(cub3d->posx)][(int)(cub3d->posy + cub3d->diry * cub3d->movespeed)] == 0)
	// 	cub3d->posy += cub3d->diry * cub3d->movespeed;
	// }
	// move_right_side
	// if (keycode == 2)
	// {
	// 	if(worldMap[(int)(cub3d->posx - cub3d->dirx * cub3d->movespeed)][(int)(cub3d->posy)] == 0)
	// 		cub3d->posx -= cub3d->dirx * cub3d->movespeed;
	// 	if(worldMap[(int)(cub3d->posx)][(int)(cub3d->posy - cub3d->diry * cub3d->movespeed)] == 0)
	// 		cub3d->posy -= cub3d->diry * cub3d->movespeed;
		
	// }
	if (keycode == moveright)
	{

		cub3d->olddirx = cub3d->dirx;
		cub3d->dirx = cub3d->dirx * cos(-cub3d->rotspeed) - cub3d->diry * sin(-cub3d->rotspeed);
		cub3d->diry = cub3d->olddirx * sin(-cub3d->rotspeed) + cub3d->diry * cos(-cub3d->rotspeed);
		cub3d->oldplanx = cub3d->planx;
		cub3d->planx = cub3d->planx * cos(-cub3d->rotspeed) - cub3d->plany * sin(-cub3d->rotspeed);
		cub3d->plany = cub3d->oldplanx * sin(-cub3d->rotspeed) + cub3d->plany * cos(cub3d->rotspeed);

	}
	if (keycode == moveleft)
	{
		cub3d->olddirx =  cub3d->dirx;
		cub3d->dirx =  cub3d->dirx * cos( cub3d->rotspeed) -  cub3d->diry * sin( cub3d->rotspeed);
		cub3d->diry =  cub3d->olddirx * sin(cub3d->rotspeed) +  cub3d->diry * cos( cub3d->rotspeed);
		cub3d->oldplanx =  cub3d->planx;
		cub3d->planx =  cub3d->planx * cos(cub3d->rotspeed) -  cub3d->plany * sin( cub3d->rotspeed);
		cub3d->plany =  cub3d->oldplanx * sin(cub3d->rotspeed) + cub3d->plany * cos(cub3d->rotspeed);
   
	}
	if (keycode == 53)
		exit(1);
	mlx_clear_window(cub3d->connection, cub3d->window);
	mlx_destroy_image(cub3d->connection, cub3d->image_ptr);
	cub3d->image_ptr = mlx_new_image(cub3d->connection, screenWidth, screenHeight);
	cub3d->data = (int*)mlx_get_data_addr(cub3d->image_ptr, &(cub3d->bpp), &(cub3d->size), &(cub3d->endian));
	draw_wall(cub3d);
	if (cub3d->jump == 1)
	{
		cub3d->jump = 0;
		cub3d->jumpback = -1;
		mlx_clear_window(cub3d->connection, cub3d->window);
		mlx_destroy_image(cub3d->connection, cub3d->image_ptr);
		cub3d->image_ptr = mlx_new_image(cub3d->connection, screenWidth, screenHeight);
		draw_wall(cub3d);
		cub3d->jumpback = 0;
	 }
	mlx_put_image_to_window(cub3d->connection, cub3d->window, cub3d->image_ptr, 0, 0);
	return (0);
}


