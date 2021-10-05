DESCRIPTION = "Moblile Neural Net (MNN) neural net inferrence engine"
HOMEPAGE = "http://www.mnn.zone/"
LICENSE = "Apache-2.0"

LIC_FILES_CHKSUM = "file://README.md;md5=692d64646daeb35b7c4ea4293840cc18"

SRC_URI = " \
    git://github.com/alibaba/MNN.git;protocol=https;branch=master \
    file://fix-Expr-c-snprintf-call.patch \
    "

SRCREV = "${PV}"

S = "${WORKDIR}/git"

inherit cmake cuda

DEPENDS = " \
    python3 \
    python3-native \
    protobuf \
    protobuf-native \
    "

# We need this turned on globally for the build here...
export CXXFLAGS += "-flax-vector-conversions"

# Build out the tools.  We're going to skip the codegen pieces for now...
# (Requires more work with LLVM than I have time for right now...)
EXTRA_OECMAKE = " \
    -DMNN_BUILD_TOOLS=on \
    -DMNN_BUILD_TRAIN=on \
    -DMNN_BUILD_QUANTOOLS=on \
    -DMNN_EVALUATION=on \
    -DMNN_BUILD_CONVERTER=on \
    -DMNN_SUPPORT_TFLITE_QUAN=on \
    -DMNN_WITH_PLUGIN=on \
    "

# We're going to go out on a limb and say we always support HW FP- it does
# little good to try to do NN Inferrence without that on ARM...
EXTRA_OECMAKE:append_arm = " \
    -DMNN_BUILD_HARD=on \
    "

# We currently support the OpenCL and Vulkan accelerator backends.  Eventually,
# this recipe will support the OpenGLES (They call it OpenGL, but don't seem to
# understand the distinction there...) and the CUDA ones.  Wanted to get this
# up enough that it'd work for most of the potential targets out of box.
PACKAGECONFIG ??= "vulkan opencl"

# Handle Vulkan optimization/backend support...
PACKAGECONFIG[vulkan] = " \
    -DMNN_VULKAN=on, \
    -DMNN_VULKAN=off, \
    vulkan-headers vulkan-loader, \
    mnn-vulkan \
    "

# Handle OpenCL optimization/backend support...
PACKAGECONFIG[opencl] = " \
    -DMNN_OPENCL=on, \
    -DMNN_OPENCL=off, \
    ocl-icd opencl-clhpp opencl-headers, \
    mnn-opencl \
    "

# Handle all the .out files and pour them into /usr/bin for the tools.
# Also go scrounge out the OTHER .so's that the tools use so they can
# be packaged (They don't install the tools or their .so's- annoying...)
do_install_append() {
    mkdir -p ${D}/usr/bin
    find ${B} -name "*.out" -exec cp {} ${D}/usr/bin \; || true
    rm -f ${D}/usr/bin/a*
    find ${D} -name "*.out" -exec rename 's/\e.out$//' {} \; || true
    find ${B} -name "*.so" -exec cp {} ${D}/usr/lib \; || true
}


PACKAGES += "${PN}-tools ${PN}-opencl ${PN}-vulkan"

# The tools explicitly require the library...
RDEPENDS:${PN}-tools = "${PN}"

FILES:${PN} = " \
    /usr/lib/libMNN.so \
    "


FILES:${PN}-opencl = " \
    /usr/lib/libMNN_CL.so \
    "

FILES:${PN}-vulkan = " \
    /usr/lib/libMNN_Vulkan.so \
    "

FILES:${PN}-dev = " \
    /usr/include \
    "

FILES:${PN}-tools = " \
    /usr/lib/libMNNTrain.so \
    /usr/lib/libMNN_Express.so \
    /usr/lib/libMNNConvertDeps.so \
    /usr/bin \
    "

BBCLASSEXTEND = "native nativesdk"