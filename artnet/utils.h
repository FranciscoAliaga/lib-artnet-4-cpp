#pragma once

#include <array>
#include <cstdint>
#include <netinet/in.h>
#include <pthread.h>
#include <sched.h>
#include <string>

namespace ArtNet {
namespace utils {

// Threads
enum class ThreadPriority { NORMAL, HIGH, REALTIME };

inline bool setThreadPriority(ThreadPriority priority) {
  int policy;
  struct sched_param param{}; // Initialize to zero

  // Get current thread policy
  pthread_getschedparam(pthread_self(), &policy, &param);

  // Handle all enum cases explicitly
  if(priority==ThreadPriority::HIGH){
    policy = SCHED_FIFO;
    param.sched_priority = sched_get_priority_min(policy) + 1;
  } else if(priority== ThreadPriority::REALTIME){
    policy = SCHED_RR;
    param.sched_priority = sched_get_priority_max(policy);
  } else { // (priority == ThreadPriority::NORMAL) or else
    policy = SCHED_OTHER;
    param.sched_priority = 0;
  }

  if (pthread_setschedparam(pthread_self(), policy, &param) != 0) {
    // Return false if setting priority failed
    return false;
  }

  return true;
}

// Networking
std::string formatIP(const std::array<uint8_t, 4> &ip);
std::string formatIP(const uint8_t *data, size_t size);
std::array<uint8_t, 4> parseIP(std::string const &ipString); // added const &
std::string ipAddressToString(sockaddr_in ip);

} // namespace utils
} // namespace ArtNet
