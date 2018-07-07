#define IDLE_TO_IMPACT_ACCEL_THRESHOLD 20.0
#define BUFFER_SIZE                    150
#define ACTIVITY_ACCEL_THRESHOLD       20.0
//#define ACTIVITY_THRESHOLD_FRACTION 0.3
//#define ACTIVITY_THRESHOLD_CYCLES   \
//                       (IMPACT_TO_ACTIVITY_THRESHOLD_FRACTION * IMPACT_CYCLES)
#define ACTIVITY_THRESHOLD_CYCLES      50

int run_fall_detector(double x, double y, double z);
