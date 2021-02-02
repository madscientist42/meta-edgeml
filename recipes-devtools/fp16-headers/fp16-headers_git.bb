DESCRIPTION = "Header-only library for conversion to/from half-precision floating point formats"
HOMEPAGE = "https://github.com/Maratyszcza/FP16"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=998fb0b16ad8a4fb8bd41bf3faf2d21c"


SRC_URI = " \
    git://github.com/Maratyszcza/FP16.git;protocol=https \
    "

SRCREV = "4dfe081cf6bcd15db339cf2680b9281b8451eeb3"
S = "${WORKDIR}/git"

do_compile[noexec] = "1"
do_install() {
    install -d ${D}/usr/include
    rsync -a --prune-empty-dirs --include '*/' --include '*.h' --exclude '*' ${S}/include ${D}/usr/include
}

