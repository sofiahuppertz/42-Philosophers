#include "../philosophers.h"

void	*my_calloc(size_t elements, size_t size)
{
	void	*ptr;

	ptr = malloc(elements * size);
	if (!ptr)
		return (NULL);
    if (elements && size > SIZE_MAX / elements) {
        return NULL;
    }
	memset(ptr, 0, elements * size);
	return ((void *)ptr);
}

int valid_number(char *str) {
    int i;

    i = 0;
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
        {
            perror("Invalid argument");
            return (0);
        }
        i += 1;
    }
    return (1);
}

int str_to_int(char *str) {
    int i;
    int res;

    i = 0;
    res = 0;
    while (str[i]) {
        res = res * 10 + str[i] - '0';
        i += 1;
    }
    return (res);
}