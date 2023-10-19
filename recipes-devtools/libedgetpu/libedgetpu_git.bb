DESCRIPTION = "libedgetpu Coral AI/Google Edge TPU interface library."
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

DEPENDS = " \
    abseil-cpp \
    libflatbuffers \
    "

SRC_URI = " \
    git://github.com/google-coral/libedgetpu.git;protocol=https;branch=master \
    "

SRCREV = "ddfa7bde33c23afd8c2892182faa3e5b4e6ad94e"
PV = "git+${SRCPV}"
S = "${WORKDIR}/git"

# We're going to drive the simplest edge of this as Bazel's patently STUPID
# for what we (and they...) needed here.  It circumvents the very purpose of
# packaging, etc. in numerous ways.
