/*-------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

/*-------------------------------------------------------------------------*/

static unsigned hash(const char *key)
{
	unsigned i;

	unsigned hash = 0;

	for(i = 0; i < strlen(key); i++)
	{
		hash +=     key[i]    ;
		hash += (hash << 0x0A);
		hash ^= (hash >> 0x06);
	}

	hash += (hash << 0x03);
	hash ^= (hash >> 0x0B);
	hash += (hash << 0x0F);

	return hash;
}

/*-------------------------------------------------------------------------*/

int main(void)
{
	char buffer[1024];

	scanf("%s", buffer);
	printf("0x%08X\n", hash(buffer));

	return 0;
}

/*-------------------------------------------------------------------------*/

