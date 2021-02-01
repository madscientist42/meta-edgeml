# Dogsbody for the C++ library build.  This handles the actual operations.
# the recipes themselves let us specify version or "git" for preferred
# or as close to the tip of master as we dare.

DESCRIPTION = "TensorFlow Lite C++ library"

BUILD_TOPLEVEL = "${S}/tensorflow/lite/tools/make"

# Normally, you don't do a configure step that does download of
# sources, but Google's got their OWN notions of things.  They
# download critical dependencies and then _*STATICALLY*_ link them
# with TensorFlow anything.  It's worse in the full TensorFlow, mind.
do_configure(){
	${S}/tensorflow/lite/tools/make/download_dependencies.sh
}

# FIXME - This is a hack that supports the usual suspects for this since
#         Google doesn't support everything under the sun with this like they
#         ought to with this- it's "optimized" in thier take and is limited.
do_compile () {
    echo build ${TARGET_ARCH}

    case "${TARGET_ARCH}" in
        aarch64)
            ${BUILD_TOPLEVEL}/build_aarch64_lib.sh
            ;;

        arm)
            # Blindly presume a 32-bit RPi other than Pi Classic or PiZero, which are
            # ARMv6 class machines...
            ${BUILD_TOPLEVEL}/build_rpi_lib.sh
            ;;
    esac

}

# Unfortunately, like pretty much everything in TF, it's not QUITE done right for us.
# We have to install this manually- the CMake build doesn't handle installs (Go figure...).
do_install() {
    install -d ${D}/usr/lib
    install -d ${D}/usr/include
    install -d ${D}/usr/share/cmake/Modules
    install -m 0644 ${BUILD_TOPLEVEL}/gen/${TARGET_OS}_${TARGET_ARCH}/lib/libtensorflow-lite.a ${D}/usr/lib
    # We're isolating header files into a proper place (i.e. tflite/<foo> for #includes, etc.)
    rsync -a --prune-empty-dirs --include '*/' --include '*.h' --exclude '*' ${OECMAKE_SOURCEPATH} ${D}/usr/include
    # Clean up a few tidbits.  For example we don't want testing, python bindings, etc...
    mv ${D}/usr/include/lite ${D}/usr/include/tflite
    rm -rf ${D}/usr/include/tflite/python
    rm -rf ${D}/usr/include/tflite/testing
    rm -rf ${D}/usr/include/tflite/examples
    # Now, drop the CMake helper into something resembling the right place...
    install ${WORKDIR}/FindTFLite.cmake ${D}/usr/share/cmake/Modules
}

