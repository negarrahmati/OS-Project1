#ifndef _CALL_H_
#define _CALL_H_ 
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/module.h>

int setProcessTickets(int pid,int tickets);
int getProcessTickets(int pid);
int setLotteryMode(int mode);
int getLotteryMode(void);



#endif
