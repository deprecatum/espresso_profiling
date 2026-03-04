#define ENABLE_DEBUG false

// temperature safety margins
#define STANDBY_TEMPERATURE 90.0F
#define MAX_TEMPERATURE_ESPRESSO 95.0F
#define OUTPUT_STEAM_PRESSURE 110.0F
#define MAX_TEMPERATURE_STEAM 130.0F

// pressure safety margins
#define MAX_BAR 12.0F
#define MARGIN 0.25F
#define TOP_MARGIN MARGIN
#define BOTTOM_MARGIN MARGIN

enum class StatusCode : int {
    fail  = 0L,
    success  = 1L,
    standby = 2L,
    failedOnSet = 100L,
    failedOnRead = 1000L,
  };