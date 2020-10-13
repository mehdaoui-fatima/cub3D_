
#include "cub3d.h"

void initializedata(t_data *cubdata)
{
	cubdata->rx = -1;
	cubdata->ry = -1;
	cubdata->cr = -1;
	cubdata->cg = -1;
	cubdata->cb = -1;
	cubdata->fr = -1;
	cubdata->fg = -1;
	cubdata->fb = -1; 
	cubdata->res = 0;// no idea
	cubdata->map = ft_strdup("");;
}

int ok(char **newline)
{
	int i = 0;
	while(newline[i])
		i++;
	return(i);
}

int ft_isnumber(char *s)
{
    int i;
    i = 0;
	if (s[i] == '-')
		i++;
    while(s[i])
    {
        if (!ft_isdigit(s[i]))
            return (0);//is not number
        i++;
    }
    return(1);//is number
}


int ft_arr_isnumber(char **new)
{
	int i;

	i = 0;
	while(new[i])
	{
		if(!ft_isnumber(new[i]))
			return(0);//an element not a number
		i++;
	}
	return(1);// array of numbers
}

/* 
void	clear(t_data *cubdata)
{
	int i;

	i = 0;
	while(cubdata->newline[i])
	{
		free(cubdata->newline[i]);
		i++;
	}
}

 */

int 	resolution(t_data *cubdata, int *i)
{
	if(cubdata->res != 3)
		ft_putstr_fd("error: incorrect line", 1);
	else if(cubdata->rx != -1)
		ft_putstr_fd("error: duplicate line", 1);
	else if ( !(ft_isnumber(cubdata->newline[*i + 1]) 
				&& ft_isnumber(cubdata->newline[*i + 2])) )
		ft_putstr_fd("error: line containe strings instead of integers", 1);
	else 
	{
		cubdata->rx = ft_atoi(cubdata->newline[*i + 1]);
		cubdata->ry = ft_atoi(cubdata->newline[*i + 2]);
		if (cubdata->rx < 0 || cubdata->ry < 0)
			ft_putstr_fd("error: screen height and weidth shoud be positive", 1);
		//!!! if number zere so small or too large
		/* else if( cubdata->rx > 1024)
			cubdata->rx = max_width;
		else if (cubdata->ry > 768)
			cubdata->ry = max_height; */
		return (0);
	}
	return (1);
}


void	ft_errors(char *str)
{
	ft_putendl_fd("Error", 1);
	ft_putstr_fd(str, 1);
}




int	ft_ceil_floor(t_data *cubdata)
{
	//duplicate line
	int n;
	int res;
	
	res = 0;
	cubdata->new = ft_split(cubdata->newline[1], ',');
	n = ok(cubdata->new);
	if( cubdata->res != 2 || n != 3 )// make sure of num of arguments
		ft_errors("incorrect line");
	else if(ft_arr_isnumber(cubdata->new))
	{
		if(ft_strcmp(cubdata->newline[0], "C") == 0)
		{
			cubdata->cr = ft_atoi(cubdata->new[0]);
			cubdata->cg = ft_atoi(cubdata->new[1]);
			cubdata->cb = ft_atoi(cubdata->new[2]);
		}
		else
		{
			cubdata->fr = ft_atoi(cubdata->new[0]);
			cubdata->fg = ft_atoi(cubdata->new[1]);
			cubdata->fb = ft_atoi(cubdata->new[2]);	
		}
		res = 1;
	}
	else 
		ft_errors("error: line containe strings instead of integers");
	//shoud not pass 255
	// free new
	return(res);
}

int	texture(t_data *cubdata)
{

	//duplicate line
	int res;

	res = 0;
	if (cubdata->res != 2)
		ft_errors("incorrect line");
	else
	{
		if(ft_strcmp(cubdata->newline[0], "NO") == 0)
			cubdata->no = ft_strdup(cubdata->newline[1]);
		else if(ft_strcmp(cubdata->newline[0], "SO") == 0)
			cubdata->so = ft_strdup(cubdata->newline[1]);
		else if( ft_strcmp(cubdata->newline[0], "WE") == 0)
			cubdata->we = ft_strdup(cubdata->newline[1]);
		else if(ft_strcmp(cubdata->newline[0], "EA") == 0)
			cubdata->ea = ft_strdup(cubdata->newline[1]);
		else if(ft_strcmp(cubdata->newline[0], "S") == 0)
			cubdata->s = ft_strdup(cubdata->newline[1]);
		res = 1;
	//make sure of path 


	//free
	}
	return(res);
}



int skips(t_data *cubdata)
{
	int i;

	i = 0;
	while(cubdata->line[i] && cubdata->line[i] == ' ')
		i++;
	return(i);
}

int skipe(t_data *cubdata)
{
	int i;
	int len;

	i = ft_strlen(cubdata->line) - 1;
	len = i;
	while(i >= 0 && cubdata->line[i] == ' ')
		i--;
	//printf("%d",i);
	return(i);
}



void	ft_getstr(t_data *cubdata)
{
		int start;
		int len;

		start = skips(cubdata);
		len = skipe(cubdata);
		//printf("%d %d\n",start,len);

	//printf("%d %d  %c|%s|\n",i, j, cubdata->line[j], ft_substr(cubdata->line, i,j));
	//printf("|%d %ld|\n",start,len - start + 1);
		
		cubdata->map = ft_strjoin(cubdata->map, ft_substr(cubdata->line, start, len - start + 1));
		//printf("%s\n",cubdata->map);


	
	//printf("|%d %d|\n",i,j);



}







t_data *parssing(t_data *cubdata, char *argv)
{
	int i;
	char *mapt[40];
	int x;
	

	if ((cubdata->fd = open(argv, O_RDONLY)) < 0)
	{ 
		perror(strerror(errno));
		exit(0);
	}
	initializedata(cubdata);
	while((cubdata->r = get_next_line(cubdata->fd,&(cubdata->line))) > 0)
	{
		i = 0;
		x = 0;
		cubdata->newline = ft_split(cubdata->line, ' ');
		cubdata->res = ok(cubdata->newline);
		while(cubdata->newline[i])
		{
			//dont forgot ..if digit 
			/* if(ft_isdigit(cubdata->newline[i][0]))
			{
				ft_putstr_fd("unvalide .cub file\n", 1);
			} */
			// line containe tkharbi9a jbkbcbicq
			if( ft_strcmp(cubdata->newline[0], "R") == 0 )
			{	
				if(resolution(cubdata, &i))	
					exit(0);
			}	//there is a problem so we should exit	
			else if( ft_strcmp(cubdata->newline[0], "C") == 0 || 
						ft_strcmp(cubdata->newline[0], "F") == 0)
			{
					if(!ft_ceil_floor(cubdata))
						exit(0);
			}
			else if( ft_strcmp(cubdata->newline[0], "NO") == 0
					|| ft_strcmp(cubdata->newline[0], "SO") == 0
					|| ft_strcmp(cubdata->newline[0], "WE") == 0
					|| ft_strcmp(cubdata->newline[0], "EA") == 0
					|| ft_strcmp(cubdata->newline[0], "S") == 0 )
			{
				if(!texture(cubdata))
					exit(0);
			}
			else if(cubdata->line[0] == ' ' || cubdata->line[0] == '1')
			{
				 
						mapt[x] = cubdata->line;
						printf("|%s|\n",mapt[x]);
				/* else
				{
					ft_errors("map incorrect");
					exit(0);
				}	 */
				//cubdata->map = ft_strjoin(cubdata->map, cubdata->newline[0]);
				//cubdata->map = ft_strjoin(cubdata->map, cubdata->line);
			}
		 	/* else
			{
				errors(cubdata);
			}
	 */
			free(cubdata->newline[i]);
			i++;
			x++;
		}
		free(cubdata->line);
	}

	
	/* printf("rx:%d\n ry:%d\n cr:%d\n cg:%d\n rb:%d\n",cubdata->rx,
	cubdata->ry,cubdata->cr,cubdata->cg,cubdata->cb);
	printf("fr:%d\n fg:%d\n fb:%d\n",cubdata->fr,cubdata->fg,cubdata->fb);
	printf("NO:%s\nSO:%s\nWE:%s\nEA:%s\n S:%s\n",
	cubdata->no,cubdata->so,cubdata->we,cubdata->ea,cubdata->s); */
	return (cubdata);

}	