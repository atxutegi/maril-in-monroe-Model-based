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


#ifndef SERVER_MODEL_H
#define SERVER_MODEL_H

#include <stdint.h>

namespace mbm {
namespace model {

uint64_t target_pipe_size(int rate_kb_s, int rtt_ms, int mss_bytes);

uint64_t target_run_length(int rate_kb_s, int rtt_ms, int mss_bytes);
    
} // namespace model
} // namespace mbm
#endif // SERVER_MODEL_H
