#include "call.h"



int
main(int argc, char **argv)
{
	//char *endptr;
	//int syscall_num;
	//struct module_stat stat;
	
	printf("for each of the desired operations enter the number of the operation as declared below: \n *1 -> set process tickets \n *2 -> get process tickets \n *3 -> set lottery mode \n *4 -> get lottery mode \n"); 
	int input,procId,tickets,lotMode,output;
	scanf("%d" ,&input);
	//printf("%d",input);
	if(input==1)
	{
	printf("enter process id please: ");
	scanf("%d" ,&procId);
	printf("enter tickets please: ");
	scanf("%d" ,&tickets);

	setProcessTickets(procId,tickets);
	
	}	
	else if(input==2)
	{
		printf("enter process id please: \n");
	    scanf("%d" ,&procId);
		getProcessTickets(procId);
	
	}
	else if(input==3)
	{
	printf("enter lottery mode please: \n");
	scanf("%d",&lotMode);
	
	setLotteryMode(lotMode);
	return 0;

	}
	else if(input==4)
	{
		getLotteryMode();
	}
	else printf("you haven't entered the correct operation number \n");

	return 0;
}
