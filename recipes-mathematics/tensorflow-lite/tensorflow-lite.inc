
# Handle common things for all of the tensorflow-lite specific recipes.

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=c7e17cca1ef4230861fb7868e96c387e"

# Specify a compatible list for us here...we only support a few cases of
# TARGET_ARCH because Google looks at it that way.
COMPATIBLE_MACHINE = "(aarch64|arm|x86_64)"

# Intelligently handle versioning here...if ${PV} is, "git", handle the
# fetch rules a bit differently...

# Compute branch info from ${PV} as Base PV...if it's "git", it's nonsensical, but
# won't be used by the other expansions that follow...
BPV = "${@'.'.join(d.getVar('PV').split('.')[0:2])}"

# Since they tag off of something resembling ${PV}, use it as needed.  We support
# a "git" rev (And you can specify preferences accorsingly in a config for layer,
# distro, or locally here...) as well as a version.  Version is computed from the
# previous expression and the following.  If it's "git", we just use what's specified
# in "GIT_HASH" here- otherwise we figure out branch and SRCREV off of ${PV}.
#
# If you want a differing version line in the sand for "git" versioning, you specify
# a new GIT_HASH value in a .bbappend and it will fetch that instead.  This includes
# the magic ${AUTOREV} "hash" value.
GIT_HASH ?= "c204a11c7509b18411817c587f6c0a48afe545b8"
SRCREV = "${@bb.utils.contains('PV', 'git', '${GIT_HASH}', 'v${PV}', d)}"
BRANCH = "${@bb.utils.contains('PV', 'git', '', ';branch=r${BPV}', d)}"

SRC_URI = " \
    git://github.com/tensorflow/tensorflow.git;protocol=https;branch=${BRANCH} \
    file://fix-missing-limits-include.patch \
    file://FindTFLite.cmake \
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

