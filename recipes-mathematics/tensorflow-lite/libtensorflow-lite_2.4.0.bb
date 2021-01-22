require tensorflow-lite.inc

DESCRIPTION = "TensorFlow Lite C++ library"


# FIXME - This is a hack that supports the usual suspects for this since
#         Google doesn't support everything under the sun with this like they
#         ought to with this- it's "optimized" in thier take and is limited.
do_compile () {
    echo ${TARGET_ARCH}

    if [ ${TARGET_ARCH} = "aarch64" ]; then
        echo "build aarch64"
        ${S}/tensorflow/lite/tools/make/build_aarch64_lib.sh
    elif [ ${TARGET_ARCH} = "arm" ]; then
        echo "build arm"
        # Blindly presume a 32-bit RPi other than Pi Classic or PiZero, which are
        # ARMv6 class machines...
        ${S}/tensorflow/lite/tools/make/build_rpi_lib.sh
    fi
}


do_install() {
    install -d ${D}/usr/lib
    install -d ${D}/usr/include
}

