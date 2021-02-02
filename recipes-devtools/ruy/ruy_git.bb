DESCRIPTION = "The ruy matrix multiplication library"
HOMEPAGE = "https://github.com/google/ruy"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = " \
    gitsm://github.com/google/ruy.git;protocol=https \
    "

SRCREV = "2887692065c38ef6617f423feafc6b69dd0a0681"
S = "${WORKDIR}/git"

inherit cmake

