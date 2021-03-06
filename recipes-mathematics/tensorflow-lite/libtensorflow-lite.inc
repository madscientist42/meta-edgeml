# Dogsbody for the C++ library build with GPU delegate suppot.  This handles
# the actual operations for the recipes themselves let us specify version or
# "git" for preferred recipes.  "git" lets us go to the tip of TensorFlow
# or as close to it as we dare...

DESCRIPTION = "TensorFlow Lite C++ library with GPU delegate support"

PROVIDES = "libtensorflow-lite"

# Our dependencies expand a smidge...some of this is a generic requirement (Like OpenCL,
# OpenGL, and Vulkan), some of this is a requirement because the headers, etc. we need
# are handled in the 2.5.x pre-release git versions, but not in prior versions.  While
# this takes some of the control out of our hands for build/packaging, etc. we'll live
# with it for now.  It should be an option on their CMake and we're going to suggest
# this to them so everyone wins here.
DEPENDS = " \
    opencl-headers \
    mesa \
    "

# This is built with a CMake builder instead of the other.  Kind of experimental and all.
# Until at least r2.5, this beastie is a, "...as close to the tip as we dare..." thing.
inherit cmake

OECMAKE_SOURCEPATH = "${S}/tensorflow/lite"
OECMAKE_COREPATH = "${S}/tensorflow/core"

# Make this act as close to the makefile solution as we can, but add GPU
# delegate support.
EXTRA_OECMAKE += " \
    -DTFLITE_ENABLE_XNNPACK=OFF \
    -DTFLITE_ENABLE_GPU=ON \
    "

# Add fPIC flag
CXXFLAGS += " -fPIC "

# Unfortunately, like pretty much everything in TF, it's not QUITE done right for us.
# We have to install this manually- the CMake build doesn't handle installs (Go figure...).
do_install() {
    install -d ${D}/usr/lib
    install -d ${D}/usr/include
    install -d ${D}/usr/include/tensorflow
    install -d ${D}/usr/share/cmake/Modules
    install -m 0644 ${B}/libtensorflow-lite.a ${D}/usr/lib
    # We're isolating header files into a proper place (i.e. tensorflow/lite/<foo> for #includes, etc.)
    rsync -a --prune-empty-dirs --include '*/' --include '*.h' --exclude '*' ${OECMAKE_SOURCEPATH} ${D}/usr/include/tensorflow
    rsync -a --prune-empty-dirs --include '*/' --include '*.h' --exclude '*' ${OECMAKE_COREPATH} ${D}/usr/include/tensorflow
    # Clean up a few tidbits.  For example we don't want testing, python bindings, etc...
    rm -rf ${D}/usr/include/tensorflow/lite/python
    rm -rf ${D}/usr/include/tensorflow/lite/testing
    rm -rf ${D}/usr/include/tensorflow/lite/examples
    # Now, drop the CMake helper into something resembling the right place...
    install ${WORKDIR}/FindTFLite.cmake ${D}/usr/share/cmake/Modules
}

# Kind of override files for packaging.  We're going to make the package BE a -dev
# without saying it so we can make it play nicely with Yocto.  It wants the package
# to RDEPEND on ${PN} so, we're going to give it that- if we ever move to a dynamic
# library, we'll want to re-work this.
FILES_${PN} = " \
    /usr/include \
    "

FILES_${PN}-dev = " \
    /usr/share \
    "

FILES_${PN}-staticdev = " \
    /usr/lib \
    "
