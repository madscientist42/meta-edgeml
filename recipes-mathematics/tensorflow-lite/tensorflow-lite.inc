
# Handle common things for all of the tensorflow-lite specific recipes.

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=64a34301f8e355f57ec992c2af3e5157"

# Specify a compatible list for us here...we only support a few cases of
# TARGET_ARCH because Google looks at it that way.
COMPATIBLE_MACHINE = "(aarch64|arm)"

# Intelligently handle versioning here...if ${PV} is, "git", handle the
# fetch rules a bit differently...

# Compute branch info from ${PV} as Base PV...if it's "git", it's nonsensical, but
# won't be used by the other expansions that follow...
BPV = "${@'.'.join(d.getVar('PV').split('.')[0:2])}"

# Since they tag off of something resembling ${PV}, use it as needed.
GIT_HASH = "c09b6df6896ed71fcd5cb26b27ec1c83f80780cf"
SRCREV = "${@bb.utils.contains('PV', 'git', '${GIT_HASH}', 'v${PV}', d)}"
BRANCH = "${@bb.utils.contains('PV', 'git', '', ';branch=r${BPV}', d)}"

SRC_URI = " \
    git://github.com/tensorflow/tensorflow.git${BRANCH} \
    file://001-Change-curl-to-wget-command.patch \
    file://001-TensorFlow-Lite_Makefile.patch \
    file://001-Remove-toolchain-setup-and-pybind11.patch \
    "

S = "${WORKDIR}/git"

DEPENDS += " \
    gzip-native \
    unzip-native \
    zlib \
    python3 \
    python3-native \
    python3-numpy-native \
    python3-pip-native \
    python3-wheel-native \
    python3-pybind11 \
    "

