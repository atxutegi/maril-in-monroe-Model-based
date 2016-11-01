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


#include "common/traffic_data.h"

#include <arpa/inet.h>

#include <iostream>

#include "common/constants.h"

namespace mbm {


// static
TrafficData TrafficData::ntoh(const TrafficData& data) {
  return TrafficData(
           ntohl(data.seq_no_), ntohl(data.nonce_),
           ntohl(data.sec_), ntohl(data.rem_));
}

// static
TrafficData TrafficData::hton(const TrafficData& data) {
  return TrafficData(
           htonl(data.seq_no_), htonl(data.nonce_),
           htonl(data.sec_), htonl(data.rem_));
}

TrafficData::TrafficData()
  : seq_no_(0), nonce_(0), sec_(0), rem_(0) {
}

TrafficData::TrafficData(uint32_t seq_no, uint32_t nonce, uint64_t timestamp)
  : seq_no_(seq_no), nonce_(nonce) {
  sec_ = timestamp / NS_PER_SEC;
  rem_ = timestamp % NS_PER_SEC;
}

TrafficData::TrafficData(uint32_t seq_no, uint32_t nonce,
                         uint32_t sec, uint32_t rem)
  : seq_no_(seq_no), nonce_(nonce), sec_(sec), rem_(rem) {
}

uint64_t TrafficData::timestamp() const {
  return static_cast<uint64_t>(sec_) * NS_PER_SEC + static_cast<uint64_t>(rem_);
}


} // namespace mbm
