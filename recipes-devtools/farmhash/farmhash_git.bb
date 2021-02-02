DESCRIPTION = "A family of hash functions from Google"
HOMEPAGE = "https://github.com/google/farmhash"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=7dfaa79e2b070897e495fec386e3acfc"

SRC_URI = " \
    git://github.com/google/farmhash.git;protocol=https \
    "

SRCREV = "0d859a811870d10f53a594927d0d0b97573ad06d"
S = "${WORKDIR}/git"

inherit autotools