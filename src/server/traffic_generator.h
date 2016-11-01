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


#ifndef SERVER_TRAFFIC_GENERATOR
#define SERVER_TRAFFIC_GENERATOR

#include <vector>

#include "mlab/accepted_socket.h"

namespace mbm {

class TrafficGenerator {  
  public:
    TrafficGenerator(const mlab::AcceptedSocket *test_socket,
                     uint32_t bytes_per_chunk, uint32_t max_pkt);
    bool Send(uint32_t num_chunks, ssize_t& num_bytes);
    bool Send(uint32_t num_chunks);
    uint32_t packets_sent();
    uint64_t total_bytes_sent();
    uint32_t bytes_per_chunk();
    const std::vector<uint32_t>& nonce();
    const std::vector<uint64_t>& timestamps();

  private:
    const mlab::AcceptedSocket *test_socket_;
    uint32_t max_packets_;
    uint32_t bytes_per_chunk_;
    uint64_t total_bytes_sent_;
    uint32_t packets_sent_;
    uint32_t last_percent_;
    std::vector<char> buffer_;
    std::vector<uint32_t> nonce_;
    std::vector<uint64_t> timestamps_;
    
};

} // namespace mbm

#endif // SERVER_TRAFFIC_GENERATOR 
