#include <string.h>
void* memmove(void* dest, const void* src, size_t size)
{
	unsigned char* d = dest;
	const unsigned char* s = src;

	if (src > dest)
	{
		for (size_t i = 0; i < size; i++)
		{
			d[i] = s[i];
		}
	}
	else
	{
		for (size_t i = size; i > 0; i--)
		{
			d[i-1] = s[i-1];
		}
	}
	return dest;
}
