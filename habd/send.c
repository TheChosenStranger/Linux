#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

typedef unsigned char u8;
typedef short int u16;
typedef long int u32;

  
void delay(int milli_seconds) 
{ 
    // Converting time into milli_seconds 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 
}
int main(int argc, char const *argv[])
{
	FILE * fp;
	int i=0;
	while(1){
		
		/* open the file for writing*/
		delay(1000);
		fp = fopen ("bus.txt","w");
		
		/* write 10 lines of text into the file stream*/
		
		fprintf (fp, "%x",i++);
		printf("data sent\n");
		   /* close the file*/ 
		if(i == 3)
			i=0; 
		fclose (fp);
	}
   	return 0;
}
