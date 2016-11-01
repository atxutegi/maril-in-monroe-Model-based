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


#include "server/model.h"

#include <stdint.h>

#include <algorithm>

#include "common/constants.h"

namespace mbm {
namespace model {

uint64_t target_pipe_size(int rate_kb_s, int rtt_ms, int mss_bytes) {
  // convert kilobits per second to bytes per milisecond
  uint64_t rate_bytes_ms = rate_kb_s / 8;
  return std::max(rate_bytes_ms * rtt_ms / mss_bytes,
                  static_cast<uint64_t>(MIN_TARGET_PIPE_SIZE));
}

uint64_t target_run_length(int rate_kb_s, int rtt_ms, int mss_bytes) {
  uint64_t pipe_size = target_pipe_size(rate_kb_s, rtt_ms, mss_bytes);
  return 3 * pipe_size * pipe_size;
}

} // namesapce model
} // namespace mbm
