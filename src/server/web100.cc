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


#ifdef USE_WEB100

#include "server/web100.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
extern "C" {
#include <web100/web100.h>
}

#include <string>
#include <iostream>

#include "common/constants.h"
#include "mlab/socket.h"

namespace web100 {

Agent::Agent() {
  agent_ = web100_attach(WEB100_AGENT_TYPE_LOCAL, NULL);
  if (agent_ == NULL) {
    web100_perror("web100");
    perror("sys");
    assert(false);
  }
}

Agent::~Agent() {
  web100_detach(agent_);
}

web100_agent* Agent::get() {
  return agent_;
}


class Connection::Var {
 public:
  explicit Var(const std::string& name, web100_connection* connection,
               web100_agent* agent)
      : var_(NULL),
        group_(NULL),
        before_(NULL),
        after_(NULL),
        started(false),
        stopped(false) {
    assert(agent != NULL);
    assert(connection != NULL);

    if (web100_agent_find_var_and_group(agent, name.c_str(), &group_, &var_) !=
        WEB100_ERR_SUCCESS) {
      web100_perror("web100");
      perror("sys");
      assert(false);
    }

    before_ = web100_snapshot_alloc(group_, connection);
    assert(before_ != NULL);

    after_ = web100_snapshot_alloc(group_, connection);
    assert(after_ != NULL);
  }

  ~Var() {
    web100_snapshot_free(after_);
    web100_snapshot_free(before_);
  }

  void start() {
    assert(!started);
    assert(!stopped);
    if (web100_snap(before_) != WEB100_ERR_SUCCESS) {
      web100_perror("web100");
      perror("sys");
      assert(false);
    }
    started = true;
  }

  void stop() {
    // allow multiple snapshots for after_ in the course of testing
    // assert(!stopped);
    if (web100_snap(after_) != WEB100_ERR_SUCCESS) {
      web100_perror("web100");
      perror("sys");
      assert(false);
    }
    stopped = true;
  }

  // TODO(dominic): assume counter32 or gauge32 types. should be more general.
  uint32_t delta() const {
    assert(started && stopped);
    uint32_t delta;
    if (web100_delta_any(var_, after_, before_, &delta) != WEB100_ERR_SUCCESS) {
      web100_perror("web100");
      perror("sys");
      assert(false);
    }
    return delta;
  }

  uint32_t get() const {
    assert(stopped);
    uint32_t result;
    if (web100_snap_read(var_, after_, &result) != WEB100_ERR_SUCCESS) {
      web100_perror("web100");
      perror("sys");
      assert(false);
    }
    return result;
  }

 private:
  web100_var* var_;
  web100_group* group_;
  web100_snapshot* before_;
  web100_snapshot* after_;

  bool started;
  bool stopped;

};


Connection::Connection(const mlab::Socket* socket, web100_agent* agent):
    socket_(socket){
  if (socket_->type() == SOCKETTYPE_TCP) {
    //web100_connection* connection =
    connection = web100_connection_from_socket(agent, socket->raw());
    if (connection == NULL) {
      web100_perror("web100");
      perror("sys");
      assert(false);
    }

    pktsretrans = new Var("PktsRetrans", connection, agent);
    curretxqueue = new Var("CurRetxQueue", connection, agent);
    curappwqueue = new Var("CurAppWQueue", connection, agent);
    samplertt = new Var("SampleRTT", connection, agent);
    curcwnd = new Var("CurCwnd", connection, agent);
    snduna = new Var("SndUna", connection, agent);
    sndnxt = new Var("SndNxt", connection, agent);
  }
}

Connection::~Connection(){
  if (socket_->type() == SOCKETTYPE_TCP) {
    delete pktsretrans;
    delete curretxqueue;
    delete curappwqueue;
    delete samplertt;
    delete curcwnd;
    delete snduna;
    delete sndnxt;
  }
}

void Connection::Start() {
  pktsretrans->start();
}

void Connection::Stop() {
  pktsretrans->stop();
  curretxqueue->stop();
  curappwqueue->stop();
  samplertt->stop();
  curcwnd->stop();
  snduna->stop();
  sndnxt->stop();
}

uint32_t Connection::PacketRetransCount() {
  return pktsretrans->delta();
}

uint32_t Connection::RetransmitQueueSize() {
  return curretxqueue->get();
}

uint32_t Connection::ApplicationWriteQueueSize() {
  return curappwqueue->get();
}

uint32_t Connection::SampleRTT() {
  return samplertt->get();
}

uint32_t Connection::CurCwnd() {
  return curcwnd->get();
}

uint32_t Connection::SndUna() {
  return snduna->get();
}

uint32_t Connection::SndNxt() {
  return sndnxt->get();
}

}  // namespace web100

#endif  // USE_WEB100
