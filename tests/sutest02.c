/*
 * sutest02.c
 *
 * Copyright (C) 2015-2017 Kristofer Berggren
 * All rights reserved.
 * 
 * stackusage is distributed under the BSD 3-Clause license, see LICENSE for details.
 *
 */

/* ----------- Includes ------------------------------------------ */
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/* ----------- Defines ------------------------------------------- */
/* Temporary pthread limits, to be removed */
#ifndef PTHREAD_KEYS_MAX
#define PTHREAD_KEYS_MAX 128
#endif

#ifndef PTHREAD_STACK_MIN
#define PTHREAD_STACK_MIN 16384
#endif

#define NUM_THREADS  (PTHREAD_KEYS_MAX + 1)


/* ----------- Local Function Prototypes ------------------------- */
static pthread_t spawn_thread(void);
static void *thread_start(void *arg);


/* ----------- Global Functions ---------------------------------- */
int main()
{
  pthread_t tid[NUM_THREADS];
  int i = 0;

  /* Spawn threads */
  for(i = 0; i < NUM_THREADS; i++)
  {
    tid[i] = spawn_thread();
  }

  /* Wait for threads to complete */
  for(i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(tid[i], NULL);
  }
  
  return 0;
}


/* ----------- Local Functions ----------------------------------- */
static pthread_t spawn_thread(void)
{
  pthread_t tid;
  pthread_attr_t attr;

  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
  pthread_create(&tid, &attr, &thread_start, NULL);
  pthread_attr_destroy(&attr);

  return tid;
}


static void *thread_start(void *arg)
{
  /* Sleep 1 ms */
  usleep(1000);

  return arg;
}

