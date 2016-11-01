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


#ifndef COMMON_WEB100_H
#define COMMON_WEB100_H

#ifndef USE_WEB100
#error USE_WEB100 should be defined if you expect this to work.
#endif  // !USE_WEB100

#include <stdint.h>
extern "C" {
#include <web100/web100.h>
}

namespace mlab {
class Socket;
}  // namespace mlab

namespace web100 {

class Agent {
  public: 
    Agent();
    ~Agent();
    web100_agent* get();

  private:
    web100_agent* agent_;
};

class Connection {
  public:
    Connection() {};
    Connection(const mlab::Socket* socket, web100_agent* agent);
    uint32_t PacketRetransCount();
    uint32_t RetransmitQueueSize();
    uint32_t ApplicationWriteQueueSize();
    uint32_t SampleRTT();
    uint32_t CurCwnd();
    uint32_t SndUna();
    uint32_t SndNxt();
    int id();
    void Start();
    void Stop();
    ~Connection();

  private:
    class Var;
    const mlab::Socket* socket_;
    web100_connection* connection;
    Var* pktsretrans;
    Var* curretxqueue;
    Var* curappwqueue;
    Var* samplertt;
    Var* curcwnd;
    Var* snduna;
    Var* sndnxt;
};


}  // namespace web100

#endif  // COMMON_WEB100_H
