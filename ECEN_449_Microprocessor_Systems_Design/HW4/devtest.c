#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	unsigned int result, x, y;
	int fd;
	int i, j;

	char input = 0;

	//open device file for reading and writing
	//use open to open /dev/multiplier
	fd = open("/multiplier", O_RDWR);
	
	//handle error
	if(fd == -1)
	{
		printf("Failed to open the device file!\n");
		return -1;
	}
	
	unsigned int* inputValues = (unsigned int*)malloc(2*sizeof(int));	//allocate space for the multiplication values
	char* output = (char*)malloc(3*sizeof(int));//create space for the two inputs and output product, buffer
	int* convert;	//will convert the char to int for multiplication
	while(input != 'q')
	{
		for(i=0;i<=16;i++)
		{
			for(j=0;j<=16;j++)
			{
				inputValues[0] = i;
				inputValues[1] = j;
				char* buff = (char*)inputValues;
				write(fd, buff, 2*sizeof(int));
				read(fd,output, 3*sizeof(int));

				convert = (int*)output;
				x = convert[0];
				y = convert[1];
				result = convert[2];

				printf("%u * %u = %u\n", x, y, result);
				if(result == (i*j))
					printf("Result Correct!\n");
				else
					printf("Result Incorrect!\n");
				input = getchar();
			}
		}
	}
	close(fd);
	free(inputValues);
	free(output);
	return 0;
}



