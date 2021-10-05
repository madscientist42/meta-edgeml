DESCRIPTION = "Coral Edge TPU Python3 Libraries and Executables"
HOMEPAGE = "https://coral.ai/"
LICENSE = "Apache2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5="

DEPENDS = " \
    python3 \
    python3-native \
    python3-pip-native \
    python3-wheel-native \
    "

RDEPENDS:${PN} += " \
    python3 \
    "

SRC_URI = " \
    git://github.com/google-coral/edgetpu.git;protocol=https \
    "
SRCREV = "${PV}"

S = "${WORKDIR}/git"

do_compile() {
}
