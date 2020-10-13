
#include "cub3d.h"
#include "./libft/libft.h"




int ft_isnumber(char *s)
{
    int i;
    i = 0;
    while(s[i])
    {
        if (!ft_isdigit(s[i]))
            return (0);
        i++;
    }
    return(1);
}

int main()
{
 
if (ft_isnumber("48m7"))
{
    printf("immmm \n");
}

    return(0);
}