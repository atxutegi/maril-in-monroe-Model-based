/**
 * *****************************************************************************
 * Code adaptation and development based on
 * https://github.com/m-lab/mbm
 *
 * This code includes an adaptation and simplication of the software developed at:
 * M-Lab (http://www.measurementlab.net),
 * gflags library  (google-gflags@googlegroups.com),
 * gtest (http://code.google.com/p/googletest/)
 * and pthreads-win32 (LGPL).
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************
 */


#include "common/time.h"

#include <time.h>
#include <assert.h>

#include <iostream>
#include <sstream>
#include <cerrno>

#include "common/constants.h"

namespace mbm {

uint64_t GetTimeNS() {
  struct timespec time;
#if defined(OS_FREEBSD)
  clock_gettime(CLOCK_MONOTONIC_PRECISE, &time);
#else
  clock_gettime(CLOCK_MONOTONIC_RAW, &time);
#endif
  return static_cast<uint64_t>(time.tv_sec) * NS_PER_SEC + time.tv_nsec;
}

void NanoSleepX(uint64_t sec, uint64_t ns) {
  struct timespec sleep_req = {(__time_t)sec, (long)ns};
  struct timespec sleep_rem;
  int slept = nanosleep(&sleep_req, &sleep_rem);
  while (slept == -1) {
    assert(errno == EINTR);  
    slept = nanosleep(&sleep_rem, &sleep_rem);
  }
}

} // namespace mbm
