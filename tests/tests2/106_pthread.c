#include <errno.h>
#include <pthread.h>
#include <stdio.h>

int main(void) {
  int ret;
  pthread_condattr_t attr;
  pthread_cond_t condition;

  pthread_condattr_init(&attr);
  pthread_condattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
  printf("%s\n", pthread_cond_init(&condition, &attr) ? "fail" : "ok");
  pthread_condattr_destroy(&attr);
  return 0;
}
