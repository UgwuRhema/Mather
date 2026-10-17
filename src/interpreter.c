#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

size_t
slen(const uint8_t *s)
{
	size_t len = 0;
	while (*s++)
		len++;
	return len;
}

uint8_t *read_file(FILE *file);

uint32_t
main(int argc, char *argv[])
{
	/* interpreter */
	if (argc < 2)
	{
		const uint8_t *error = (const uint8_t *)"Mather: Error, found no input files\n";
		int a = write(2, error, slen(error));
		if (a < 0)
			return -1; /* this would be another crash, this would return a value of 255 */
		return 1;
	}

	const uint8_t * restrict filename = argv[1];
	FILE *fd = fopen((const char * restrict)filename, "r");
	read_file(fd); /* read contents of the file */
	fclose(fd);
	return 0;
}

uint8_t *
read_file(FILE *file)
{

}
