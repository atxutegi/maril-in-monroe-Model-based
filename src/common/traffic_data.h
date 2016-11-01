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


#ifndef COMMON_TRAFFIC_DATA_H_
#define COMMON_TRAFFIC_DATA_H_

#include <stdint.h>

namespace mbm {
class TrafficData {
  public:
    static TrafficData ntoh(const TrafficData &data);
    static TrafficData hton(const TrafficData &data);
    TrafficData(uint32_t seq_no, uint32_t nonce, uint64_t timestamp);
    TrafficData();
    uint32_t seq_no() const { return seq_no_; };
    uint32_t nonce() const { return nonce_; };
    uint64_t timestamp() const;

  private:
    TrafficData(uint32_t seq_no, uint32_t nonce, uint32_t sec, uint32_t rem);
    uint32_t seq_no_;
    uint32_t nonce_;
    uint32_t sec_;
    uint32_t rem_;
};
}  // namespace mbm

#endif  // COMMON_TRAFFIC_DATA_H
