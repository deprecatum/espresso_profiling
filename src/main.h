#define ENABLE_DEBUG false

enum class StatusCode : int {
    fail  = 0L,
    success  = 1L,
    standby = 2L,
    failedOnSet = 100L,
    failedOnRead = 1000L,
  };
