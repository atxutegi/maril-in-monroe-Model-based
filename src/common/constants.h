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


#ifndef COMMON_CONSTANTS_H_
#define COMMON_CONSTANTS_H_

#define MBM_VERSION "0.5"
#define READY       "READY"
#define END         "END"

#define MS_PER_SEC  1000
#define NS_PER_SEC  1000000000

#define MAX_PACKETS_TEST 30000
#define MAX_PACKETS_CWND 30000
#define TEST_BASE_SEC 30
#define TEST_INCR_SEC_PER_MB 15
#define TEST_MAX_SEC 300
#define CWND_BASE_SEC 15
#define CWND_INCR_SEC_PER_MB 5
#define CWND_MAX_SEC 50

#define NUM_PORTS_TO_TRY 3
#define NUM_READY_RETRANS 5
#define DEFAULT_TIMEO_SEC 5
#define DEFAULT_TIMEO_NS 0
#define MIN_TARGET_PIPE_SIZE 1
#define DEFAULT_TYPE_I_ERR 0.05
#define DEFAULT_TYPE_II_ERR 0.05
#define MAX_RECV_BYTES 500000

#endif  // COMMON_CONSTANTS_H_
