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
	int i,msg;
	u8 buffer[100];
	while(1){
		/* open the file for writing*/
		fp = fopen ("bus.txt","r");
		/* write 10 lines of text into the file stream*/
		fgets(buffer, 255, (FILE*)fp);
	  	printf("%s\n", buffer );
		   /* close the file*/  
		fclose (fp);
		msg = atoi(buffer);
		if(msg == 2){
			fp = fopen ("bus.txt","w");
			fprintf (fp, "%x",0x55);
			fclose (fp);
			msg = 0;
		}
	}

   	return 0;
}
