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


#ifndef SERVER_STAT_TEST
#define SERVER_STAT_TEST

#include <stdint.h>

#include "common/result.h"

namespace mbm {
  class StatTest {
    public:
      StatTest(uint64_t target_run_length);
      StatTest(uint64_t target_run_length, double alpha, double beta);
      Result test_result(uint32_t n, uint32_t loss);

    private:
      void init(uint64_t target_run_length, double alpha, double beta);
      double h1;
      double h2;
      double s;

  };
} // namespace mbm

#endif // SERVER_STAT_TEST
