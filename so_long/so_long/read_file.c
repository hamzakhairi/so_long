#include "so_long.h"

int number_map(char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd == -1)
        return -1;

    int i = 0;
    char *str = get_next_line(fd);
    while (str)
    {
        free(str);
        str = get_next_line(fd);
        i++;
    }
    free(str);
    close(fd);
    return i;
}

static int ft_len_str(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

char *ft_strdup_str(char *src)
{
    int i = 0;
    int len = ft_len_str(src);
    char *dup = (char *)malloc(sizeof(char) * (len + 1));
    if (!dup)
        return NULL;
    while (src[i])
    {
        if (src[i] != '\n')
            dup[i] = src[i];
        else
            break;
        i++;
    }
    dup[i] = '\0';
    return dup;
}

char **read_map(char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd == -1) 
    {
        perror("Error opening file");
        exit(1);
    }

    int number = number_map(file);
    if (number <= 0)
    {
        close(fd);
        return NULL;
    }

    char **map = malloc(sizeof(char *) * (number + 1));
    if (!map)
    {
        close(fd);
        return NULL;
    }

    int i = 0;
    char *str = get_next_line(fd);
    while (str)
    {
        map[i] = ft_strdup_str(str);
        if (!map[i] || map[i][0] == '\0')
        {
            printf("Invalid map\n");
            free(str);
            free_map(map);
            close(fd);
            exit(1);
        }
        free(str);
        str = get_next_line(fd);
        i++;
    }
    map[i] = NULL;

    if (i > 0 && map[i - 1][0] == '\0')
    {
        printf("Invalid map (last line is empty)\n");
        free_map(map);
        close(fd);
        exit(1);
    }

    close(fd);
    return map;
}