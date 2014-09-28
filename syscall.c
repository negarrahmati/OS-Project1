/*-
 * Copyright (c) 1999 Assar Westerlund
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/share/examples/kld/syscall/module/syscall.c,v 1.6.2.1.2.1 2009/10/25 01:10:29 kensmith Exp $
 */

#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysproto.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/lock.h>
#include <sys/mutex.h>

/*
 * The function for implementing the syscall.
 */
static int
hello(struct thread *td, void *arg)
{

	printf("hello negar \n");
	return (0);
}

/*
 * The `sysent' for the new syscall
 */
static struct sysent hello_sysent = {
	0,			/* sy_narg */
	hello			/* sy_call */
};

/*
 * The offset in sysent where the syscall is allocated.
 */
static int offset = NO_SYSCALL;

/*
 * The function called at load/unload.
 */
static int
load(struct module *module, int cmd, void *arg)
{
	int error = 0;

	switch (cmd) {
	case MOD_LOAD :
		printf("syscall loaded at %d\n", offset);
		break;
	case MOD_UNLOAD :
		printf("syscall unloaded from %d\n", offset);
		break;
	default :
		error = EOPNOTSUPP;
		break;
	}
	return (error);
}

SYSCALL_MODULE(syscall, &offset, &hello_sysent, load, NULL);

//************************get lottery mode
extern int lottery_mode;
static int getLotteryMode(struct proc *p, void* param)
{
	
        curthread->td_retval[0] = lottery_mode;
		//printf("Lottery mode is: ", lottery_mode);
	return 0;
}

static struct sysent getLotteryMode_sysent = {0,(sy_call_t*)getLotteryMode};

static int offset1 = NO_SYSCALL;

static int load1 (struct module *module, int cmd, void *arg) {
int error = 0;

switch (cmd) {
case MOD_LOAD:
       //printf("syscall loaded at %d\n", offset1);
       break;
case MOD_UNLOAD:
       //printf("syscall unloaded from %d\n", offset1);
       break;
default:
       error = EINVAL;
       break;
}
return error;
}

SYSCALL_MODULE(getLotteryMode, &offset1, &getLotteryMode_sysent, load1, NULL);

//***********************************get process tickets*****************************************************

static int getProcessTickets(struct proc *p, void* arg)
{
        int processID = *((int*)arg);
	
	struct proc* process = pfind(processID);
	if(process == NULL) {
		curthread->td_retval[0] = -1;
		return 0;
	}
	PROC_UNLOCK(process); 

        curthread->td_retval[0] = process->tickets;
	//printf("get tickets \n");
	return 0;
}

static struct sysent getProcessTickets_sysent = {1, (sy_call_t*)getProcessTickets};

static int offset2 = NO_SYSCALL;

static int load2 (struct module *module, int cmd, void *arg) {
int error = 0;

switch (cmd) {
case MOD_LOAD:
       //printf("syscall loaded at %d\n", offset1);
       break;
case MOD_UNLOAD:
       //printf("syscall unloaded from %d\n", offset1);
       break;
default:
       error = EINVAL;
       break;
}
return error;
}

SYSCALL_MODULE(getProcessTickets, &offset2, &getProcessTickets_sysent, load2, NULL);


//************************************set lottery mode ***************************************************

static int setLotteryMode(struct proc *p, void* arg)
{
	 int lotteryMode = *((int*)arg);

	lottery_mode = lotteryMode;	
        curthread->td_retval[0] = 1;
	return 0;
}

static struct sysent setLotteryMode_sysent = {1,(sy_call_t*)setLotteryMode};

static int offset3 = NO_SYSCALL;

static int load3 (struct module *module, int cmd, void *arg) {
int error = 0;

switch (cmd) {
case MOD_LOAD:
       //printf("syscall loaded at %d\n", offset1);
       break;
case MOD_UNLOAD:
       //printf("syscall unloaded from %d\n", offset1);
       break;
default:
       error = EINVAL;
       break;
}
return error;
}

SYSCALL_MODULE(setLotteryMode, &offset3, &setLotteryMode_sysent, load3, NULL);

//******************************************** set process tickets

static int setProcessTickets(struct proc *p, void* arg)
{

        int processID = *((int*)arg);
        int tickets = *((int*)arg + 1);	
	struct proc* process = pfind(processID);
	
	if(process == NULL) {
		curthread->td_retval[0] = -1;
		return 0;
	}
	
	process->tickets = tickets; 
	PROC_UNLOCK(process); 
        curthread->td_retval[0] = 1;
	return 0;
}

static struct sysent setProcessTickets_sysent = {2,(sy_call_t*)setProcessTickets};

static int offset4 = NO_SYSCALL;

static int load4 (struct module *module, int cmd, void *arg) {
int error = 0;

switch (cmd) {
case MOD_LOAD:
       //printf("syscall loaded at %d\n", offset1);
       break;
case MOD_UNLOAD:
       //printf("syscall unloaded from %d\n", offset1);
       break;
default:
       error = EINVAL;
       break;
}
return error;
}

SYSCALL_MODULE(setProcessTickets, &offset4, &setProcessTickets_sysent, load4, NULL);

//********************************************end of 4 added syscalls
