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
 * $FreeBSD: src/share/examples/kld/syscall/test/call.c,v 1.3.56.1.2.1 2009/10/25 01:10:29 kensmith Exp $
 */

#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/module.h>
#include "call.h"

int setProcessTickets(int pid,int tickets)
{
	int output;

	char *endptr;
	int syscall_num;
	struct module_stat stat;

	stat.version = sizeof(stat);
	modstat(modfind("setProcessTickets"), &stat);
	syscall_num = stat.data.intval;
	output= syscall (syscall_num,pid,tickets);
	if(output==-1)
		printf("process ID does not exist! \n");
	else if(output==1)
		printf("Process tickets is set! \n");
	return 0;
}
int getProcessTickets(int pid){
	int output;
	char *endptr;
	int syscall_num;
	struct module_stat stat;

	stat.version = sizeof(stat);
	modstat(modfind("getProcessTickets"), &stat);
	syscall_num = stat.data.intval;
	output= syscall (syscall_num,pid);

	if(output== -1)
		printf("process ID doesn't exist! \n");
	else 
		printf("process ticket is: %d \n",output);

	return 0;
}
int setLotteryMode(int mode){
	int output;
	char *endptr;
	int syscall_num;
	struct module_stat stat;

	stat.version = sizeof(stat);
	modstat(modfind("setLotteryMode"), &stat);
	syscall_num = stat.data.intval;
	if(syscall (syscall_num,mode)==1)
		printf("Lottery mode is set. \n");
}
int getLotteryMode(void){
	int output;
	char *endptr;
	int syscall_num;
	struct module_stat stat;

	stat.version = sizeof(stat);
	modstat(modfind("getLotteryMode"), &stat);
	syscall_num = stat.data.intval;
	output=syscall (syscall_num);
	printf("lottery mode is: %d \n", output);
	return 0;
}

