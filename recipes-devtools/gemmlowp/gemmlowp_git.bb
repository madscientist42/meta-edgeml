DESCRIPTION = "A small self-contained low-precision GEMM library from Google"
HOMEPAGE = "https://github.com/google/gemmlowp"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = " \
    git://github.com/google/gemmlowp.git;protocol=https;branch=master \
    "

SRCREV = "13d57703abca3005d97b19df1f2db731607a7dc2"
S = "${WORKDIR}/git"

do_compile[noexec] = "1"
do_install() {
    install -d ${D}/usr/include/gemmlowp
    rsync -a --prune-empty-dirs --include '*/' --include '*.h' --exclude '*' ${S} ${D}/usr/include/gemmlowp
}