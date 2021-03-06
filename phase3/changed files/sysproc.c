#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_setPriority(void)
{
  int pid , priority;
  if (argint(0, &pid) < 0)
  {
    return -1;
  }
  if (argint(1, &priority) < 0)
  {
    return -1;
  }
  
  return setpri(pid , priority);
}

int
sys_checkPolicy(void)
{
  
  return checkP();
}

int
sys_setPolicy(void)
{
  int policy;
  argint(0, &policy);
  return setP(policy);
}


int sys_newwait(void) {
  int *retime, *rutime, *stime;
  if (argptr(0, (void*)&retime, sizeof(retime)) < 0)
    return -1;
  if (argptr(1, (void*)&rutime, sizeof(retime)) < 0)
    return -1;
  if (argptr(2, (void*)&stime, sizeof(stime)) < 0)
    return -1;
  return newwait(retime, rutime, stime);
}

int sys_getPerformance(void){
  int pid; 
  int *Btime, *Wtime, *TAtime;

  argint(0, &pid);
  if (argptr(1, (void*)&Btime, sizeof(Btime)) < 0)
    return -1;
  if (argptr(2, (void*)&Wtime, sizeof(Wtime)) < 0)
    return -1;
  if (argptr(3, (void*)&TAtime, sizeof(TAtime)) < 0)
    return -1;
  
  return getPerformance(pid, Btime, Wtime, TAtime);
}

int
sys_iszombie(void)
{
  int pid ;
  argint(0, &pid);
  
  return isZombie(pid);
}

