# Dogsbody for the C++ library build with GPU delegate suppot.  This handles
# the actual operations for the recipes themselves let us specify version or
# "git" for preferred recipes.  "git" lets us go to the tip of TensorFlow
# or as close to it as we dare...

DESCRIPTION = "TensorFlow Lite C++ library with GPU delegate support"

PROVIDES = "libtensorflow-lite"

# Our dependencies expand a smidge...
DEPENDS = " \
    opencl-headers \
    mesa \
    "

# This is built with a CMake builder instead of the other.  Kind of experimental and all.
# Until at least r2.5, this beastie is a, "...as close to the tip as we dare..." thing.
inherit cmake

OECMAKE_SOURCEPATH = "${S}/tensorflow/lite"

# Make this act as close to the makefile solution as we can, but add GPU
# delegate support.
EXTRA_OECMAKE += " \
    -DTFLITE_ENABLE_XNNPACK=OFF \
    -DTFLITE_ENABLE_GPU=ON \
    "

# Unfortunately, like pretty much everything in TF, it's not QUITE done right for us.
# We have to install this manually- the CMake build doesn't handle installs (Go figure...).
do_install() {
    install -d ${D}/usr/lib
    install -d ${D}/usr/include
    install -d ${D}/usr/share/cmake/Modules
    install -m 0644 ${B}/libtensorflow-lite.a ${D}/usr/lib
    # We're isolating header files into a proper place (i.e. tflite/<foo> for #includes, etc.)
    rsync -a --prune-empty-dirs --include '*/' --include '*.h' --exclude '*' ${OECMAKE_SOURCEPATH} ${D}/usr/include
    # Clean up a few tidbits.  For example we don't want testing, python bindings, etc...
    mv ${D}/usr/include/lite ${D}/usr/include/tflite
    rm -rf ${D}/usr/include/tflite/python
    rm -rf ${D}/usr/include/tflite/testing
    rm -rf ${D}/usr/include/tflite/examples
    # Now, drop the CMake helper into something resembling the right place...
    install ${WORKDIR}/FindTFLite.cmake ${D}/usr/share/cmake/Modules
}