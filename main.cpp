
#include <cassert>
#include <iostream>
#include <locale.h>
#include <poll.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <asm/unistd.h>

#include "metrics_linux.h"


#define DCHECK_EQ(a,b) (assert(a != b))

using namespace std;

const uint16_t cpu_number = 12;

static long
perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
                int cpu, int group_fd, unsigned long flags)
{
  int ret;
  // perf_event_open
  // int syscall(SYS_perf_event_open, struct perf_event_attr *attr,
  //                 pid_t pid, int cpu, int group_fd, unsigned long flags);
  // pid > 0 and cpu == -1 This measures the specified process/thread on any CPU.
  // pid == -1 and cpu >= 0 // This measures all processes/threads on the specified CPU. REQUIRES SPECIAL ADMIN rights.
  ret = syscall(__NR_perf_event_open, hw_event, pid, cpu,
                group_fd, flags);
  return ret;
}

int main(int argc, const char **argv)
{
  struct perf_event_attr pe_inst, pe_clk;
  long long count;
  int fd_exp, fd_trash[cpu_number];
  int timeout = 5000;

  setlocale(LC_ALL, "");

  struct pollfd fds[cpu_number];

  pe_inst = inst_retired_any_u_base;
  pe_clk = cpu_clk_unhalted_thread_u_group;
//  pe_exp = inst_retired_any_u_base;
//  pe_exp = cpu_clk_unhalted_thread_u_base;


  for (int i = 0; i < cpu_number; i++) {
    fd_exp = perf_event_open(&pe_inst, -1, i, -1, 0);
    if (fd_exp == -1) {
      fprintf(stderr, "Error opening leader %llx\n", pe_inst.config);
      exit(EXIT_FAILURE);
    }
//    fd_trash[i] = perf_event_open(&pe_clk, -1, i, fd_exp, 0);
//    if (fd_trash[i] == -1) {
//      fprintf(stderr, "Error opening follower %llx\n", pe_clk.config);
//      exit(EXIT_FAILURE);
///    }
    fds[i].fd = fd_exp;
    fds[i].events = 0;
    fds[i].events |= POLLIN;

    cout << "fds[" << i << "] = " <<  fd_exp  << " and " << fd_trash[i] << endl;
    ioctl(fds[i].fd, PERF_EVENT_IOC_RESET, 0);
    ioctl(fds[i].fd, PERF_EVENT_IOC_ENABLE, 0);
  }

  while(1) {
    int pret = poll(fds, cpu_number, timeout);

    if (pret == 0) {
      cout << "timed out" << endl;
      break;

    } else {
      if (pret == -1)
        cout << "pollerror"<< endl;
      for (int j = 0; j < cpu_number; j++) {
        //read
        if (fds[j].revents & POLLIN) {
          cout << "poll returned for: " << fds[j].fd << endl;
          int ret = read(fds[j].fd, &count, sizeof(count));
          if (ret == -1)
            cout << errno << endl;
        } 
        if (fds[j].revents & POLLHUP) {
          cout << "pollhup for "<< fds[j].fd << endl;
        }
      }
    }
  }

  for (int i = 0; i < cpu_number; i++) {
    close(fds[i].fd);
    close(fd_trash[i]);
  }

  return 0;
}

