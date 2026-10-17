#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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
	const uint8_t * restrict contents = read_file(fd); /* read contents of the file */
	int w = write(1, contents, slen(contents));
	if (w < 0)
		return -1;
	fclose(fd);
	return 0;
}


/* this is just a test, bison automatically reads input from file using yyin */
/* we don't have to implement this, i am just testing */
uint8_t *
read_file(FILE *file)
{
	fseek(file, 0, SEEK_END);
	long len = ftell(file);
	fseek(file, 0, SEEK_SET);
	uint8_t *buffer = (uint8_t *)malloc(len * sizeof(*buffer));
	fread(buffer, sizeof(buffer), len, file);
	return buffer;
}
