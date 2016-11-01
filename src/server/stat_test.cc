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


#include <server/stat_test.h>

#include <math.h>

#include <iostream>

#include "common/constants.h"

namespace mbm {

StatTest::StatTest(uint64_t target_run_length) {
  init(target_run_length, DEFAULT_TYPE_I_ERR, DEFAULT_TYPE_II_ERR);
}

StatTest::StatTest(uint64_t target_run_length, double alpha, double beta) {
  init(target_run_length, alpha, beta);
}

void StatTest::init(uint64_t target_run_length, double alpha, double beta) {
  double p0 = 1.0 / target_run_length;
  double p1 = std::min(1.0 / (target_run_length / 4.0), 0.99);
  double k = log(p1 * (1 - p0) / (p0 * (1 - p1)));
  s = log((1-p0) / (1-p1)) / k;
  h1 = log((1-alpha) / beta) / k;
  h2 = log((1-beta) / alpha) / k;
}

Result StatTest::test_result(uint32_t n, uint32_t loss) {
  double xa = -h1 + s * n;
  double xb = h2 + s * n;
  std::cout << "Deciding test result n="<< n <<" loss="<< loss << " s="<< s << " h1=" << h1 << " h2=" << h2 << " xa=" << xa << " xb=" << xb << std::endl;
  if (loss <= xa) return RESULT_PASS;
  if (loss >= xb) return RESULT_FAIL;
  return RESULT_INCONCLUSIVE;
}

} // namespace mbm
