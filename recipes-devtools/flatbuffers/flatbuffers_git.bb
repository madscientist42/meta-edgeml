DESCRIPTION = "A cross platform serialization library architected for maximum memory efficiency"
HOMEPAGE = "https://google.github.io/flatbuffers/"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=3b83ef96387f14655fc854ddc3c6bd57"

DEPENDS = " \
    flatbuffers-native \
    "

SRC_URI = " \
    git://github.com/google/flatbuffers.git;protocol=https \
    "

SRCREV = "76e7a0ff55f8f3d622a2fdf4a0e91ba6213862a2"
S = "${WORKDIR}/git"

inherit cmake

EXTRA_OECMAKE = " \
    -DFLATBUFFERS_BUILD_TESTS=off \
    "

BBCLASSEXTEND = "native nativesdk"