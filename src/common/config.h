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


#ifndef COMMON_CONFIG_H_
#define COMMON_CONFIG_H_

#include <stdint.h>
#include <string>

#include "mlab/socket_type.h"

namespace mbm {
class Config {
 public:
  Config();
  Config(SocketType socket_type, uint32_t cbr_kb_s,
         uint32_t rtt_ms, uint32_t mss_bytes, uint32_t burst_size);

  SocketType socket_type;
  uint32_t cbr_kb_s;
  uint32_t rtt_ms;
  uint32_t mss_bytes;
  uint32_t burst_size;
};
}  // namespace mbm

#endif  // COMMON_CONFIG_H_
