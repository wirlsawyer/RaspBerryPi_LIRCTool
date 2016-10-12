#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <time.h>


#define GPIO_PIN_IN	1
#define BASEHZ		560
//gcc -o main *.c -lwiringPi 




int main()
{
    	if (wiringPiSetup() == -1)
    	{
       		printf("fault:wiringPiSetup\n");
      		return 0;
    	}
   	pinMode(GPIO_PIN_IN, INPUT);

    
  	clock_t start, stop;
   	start = clock();
    	stop = clock(); 
    	int i, j;
   	int count = 0;
    	int fBuf[64];
    	memset(fBuf, 0, sizeof(fBuf));

    	while (1)
   	{
        	start = clock();
         	float durDown = ((float)(start-stop)/CLOCKS_PER_SEC);
         	while (digitalRead(GPIO_PIN_IN) == 0)
         	{
               		start = clock();              
        	}
         	float durPulse = ((float)(start-stop)/CLOCKS_PER_SEC); 
         	while (digitalRead(GPIO_PIN_IN) == 1)
         	{
               		stop = clock();
        	 }
         	float durSpace = ((float)(stop-start)/CLOCKS_PER_SEC); 
	 
	 
         
        	int diPulse = durPulse*1000000 > 1000 ? 1 : 0;
        	int diSpace = (durSpace*1000000 + BASEHZ/2)/ BASEHZ;

       		printf("%2d Pulse:%f (%d) \tSpace:%f (%d)\n", count, durPulse*1000000, diPulse, durSpace*1000000, diSpace);
         	
   	}// end while

   	printf("End!\n");
    	return 0;
}

