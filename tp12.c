#include <stdio.h>
#include <sys/time.h>

int main()
{
struct timeval curreent_time;
gettimeofday(&curreent_time,NULL);
printf("seconds:%ld\n micro seconde : %ld",curreent_time.tv_sec,curreent_time.tv_usec);

return 0;
}