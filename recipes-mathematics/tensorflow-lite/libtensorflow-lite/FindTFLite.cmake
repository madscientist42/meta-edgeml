# - Find TensorFlow-Lite
#
# Find the TensorFlow-Lite includes and .a file
#
#  TFLITE_INCLUDES    - Where to find our desired headers
#  TFLITE_LIBRARIES   - Where to find our desired libraries
#  TFLITE_FOUND       - True if TF-Lite was found.


if (TFLITE_INCLUDES)
  # Already in cache, be silent
  set (TFLITE_FIND_QUIETLY TRUE)
endif (TFLITE_INCLUDES)

find_path (TFLITE_INCLUDES tensorflow/lite/version.h)

find_library (TFLITE_LIB NAMES TFLITE)

set (TFLITE_LIBRARIES "${TFLITE_LIB}")

# handle the QUIETLY and REQUIRED arguments and set TFLITE_FOUND to TRUE if
# all listed variables are TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (TFLITE DEFAULT_MSG TFLITE_LIBRARIES TFLITE_INCLUDES)

mark_as_advanced (TFLITE_LIB TFLITE_INCLUDES)