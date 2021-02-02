DESCRIPTION = "A C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms."
HOMEPAGE = "https://gitlab.com/libeigen/eigen"
LICENSE = "MPL2+Apache-2.0+LGPL+BSD"
LIC_FILES_CHKSUM = " \
    file://COPYING.README;md5=856ad513819c1eff6b536f939c1bf803 \
    file://COPYING.MPL2;md5=815ca599c9df247a0c7f619bab123dad \
    file://COPYING.APACHE;md5=8de23b8e93c63005353056b2475e9aa5 \
    file://COPYING.LGPL;md5=4fbd65380cdd255951079008b364516c \
    file://COPYING.BSD;md5=2dd0510ee95e59ca28834b875bc96596 \
    "

SRC_URI = " \
    git://gitlab.com/libeigen/eigen.git;protocol=https \
    "

SRCREV = "56c8b14d875ae42a52d0da52916fac1e29305ca7"
S = "${WORKDIR}/git"

inherit cmake

# Handle proper packaging of the convenient CMake find_package helpers.
FILES_${PN}-dev += " \
    /usr/share/eigen3 \
    "
