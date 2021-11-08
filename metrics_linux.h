#include <vector>
#include <linux/perf_event.h>
#include <stdlib.h>

const perf_event_attr inst_retired_any_u_base
{
  .type = PERF_TYPE_RAW,
  .size = sizeof(perf_event_attr),
  .config = 0xc0,
  .sample_type = PERF_SAMPLE_IDENTIFIER,
  .read_format = PERF_FORMAT_TOTAL_TIME_ENABLED|
                 PERF_FORMAT_TOTAL_TIME_RUNNING,
  .disabled = 1,
  .inherit = 1,
  .exclude_kernel = 1,
  .exclude_hv = 1,
  .wakeup_events = 5,
};

const perf_event_attr inst_retired_any_u_group
{
  .type = PERF_TYPE_RAW,
  .size = sizeof(perf_event_attr),
  .config = 0xc0,
  .sample_type = PERF_SAMPLE_IDENTIFIER,
  .read_format = PERF_FORMAT_TOTAL_TIME_ENABLED|
                 PERF_FORMAT_TOTAL_TIME_RUNNING|
                 PERF_FORMAT_ID|
                 PERF_FORMAT_GROUP,
  .disabled = 1,
  .inherit = 1,
  .exclude_kernel = 1,
  .exclude_hv = 1,
  .wakeup_events = 5,
};

const perf_event_attr cpu_clk_unhalted_thread_u_base
{
  .type = PERF_TYPE_RAW,
  .size = sizeof(perf_event_attr),
  .config = 0x3c,
  .sample_type = PERF_SAMPLE_IDENTIFIER,
  .read_format = PERF_FORMAT_TOTAL_TIME_ENABLED|
                 PERF_FORMAT_TOTAL_TIME_RUNNING,
  .disabled = 1,
  .inherit = 1,
  .exclude_kernel = 1,
  .exclude_hv = 1,
};

const perf_event_attr cpu_clk_unhalted_thread_u_group
{
  .type = PERF_TYPE_RAW,
  .size = sizeof(perf_event_attr),
  .config = 0x3c,
  .sample_type = PERF_SAMPLE_IDENTIFIER,
  .read_format = PERF_FORMAT_TOTAL_TIME_ENABLED|
                 PERF_FORMAT_TOTAL_TIME_RUNNING|
                 PERF_FORMAT_ID|
                 PERF_FORMAT_GROUP,
  .disabled = 1,
  .inherit = 1,
  .exclude_kernel = 1,
  .exclude_hv = 1,
};


const perf_event_attr i915_rcs0_busy_base
{
  .type = 18, //TODO: TO CHECK!
  .size = sizeof(perf_event_attr),
  .sample_type = PERF_SAMPLE_IDENTIFIER,
  .read_format = PERF_FORMAT_TOTAL_TIME_ENABLED|
                 PERF_FORMAT_TOTAL_TIME_RUNNING,
  .disabled = 1,
  .inherit = 1,
  .exclude_guest = 1,
};

