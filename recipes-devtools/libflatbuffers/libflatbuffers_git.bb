DESCRIPTION = "A cross platform serialization library architected for maximum memory efficiency"
HOMEPAGE = "https://flatbuffers.dev/"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

DEPENDS = " \
    libflatbuffers-native \
    "

SRC_URI = " \
    git://github.com/google/flatbuffers.git;protocol=https;branch=master \
    "

SRCREV = "48da2389205ca5fbd0d1f40ad52d9c0b8685a076"
S = "${WORKDIR}/git"

inherit cmake

EXTRA_OECMAKE = " \
    -DFLATBUFFERS_BUILD_TESTS=off \
    "

BBCLASSEXTEND = "native nativesdk"