
# Handle common things...
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=64a34301f8e355f57ec992c2af3e5157"

# Compute branch info from ${PV} as Base PV...
BPV = "${@'.'.join(d.getVar('PV').split('.')[0:2])}"

# Since they tag off of something resembling ${PV}, use it.
SRCREV = "v${PV}"

SRC_URI = " \
    git://github.com/tensorflow/tensorflow.git;branch=r${BPV} \
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

do_unpack(){
	${S}/tensorflow/lite/tools/make/download_dependencies.sh
}

