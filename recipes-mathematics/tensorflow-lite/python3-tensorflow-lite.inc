# Dogsbody for the Python pip packahing build.  This handles the actual operations.
# the recipes themselves let us specify version or "git" for preferred
# or as close to the tip of master as we dare.

DESCRIPTION = "TensorFlow Lite Standalone Pip"

RDEPENDS:{PN} += " \
    python3 \
    python3-numpy \
    python3-pybind11 \
    "

inherit python3native

export PYTHON_BIN_PATH="${PYTHON}"
export PYTHON_LIB_PATH="${STAGING_LIBDIR_NATIVE}/${PYTHON_DIR}/site-packages"

# Normally, you don't do a configure step that does download of
# sources, but Google's got their OWN notions of things.  They
# download critical dependencies and then _*STATICALLY*_ link them
# with TensorFlow anything.  It's worse in the full TensorFlow, mind.
do_configure(){
	${S}/tensorflow/lite/tools/make/download_dependencies.sh
}

# FIXME - This is a hack that supports the usual suspects for this since
#         Google doesn't support everything under the sun with this like they
#         ought to with this- it's "optimized" in thier take and is limited...
do_compile () {
    echo build ${TARGET_ARCH}

    case "${TARGET_ARCH}" in
        aarch64)
            export TENSORFLOW_TARGET=aarch64
            export TARGET=aarch64
            ;;

        arm)
            export TENSORFLOW_TARGET=rpi
            export TARGET=rpi
            ;;

        x86_64)
            export TENSORFLOW_TARGET=linux
            export TARGET=linux
            ;;
    esac

    ${S}/tensorflow/lite/tools/pip_package/build_pip_package.sh

}

do_install() {
    echo "Generating pip package"
    install -d ${D}/${PYTHON_SITEPACKAGES_DIR}

    ${STAGING_BINDIR_NATIVE}/pip3 install --disable-pip-version-check -v \
        -t ${D}/${PYTHON_SITEPACKAGES_DIR} --no-cache-dir --no-deps \
        ${S}/tensorflow/lite/tools/pip_package/gen/tflite_pip${WORKDIR}/recipe-sysroot-native/usr/bin/python3-native/python3/dist/tflite_runtime-2.4.0-*.whl
}

FILES:${PN}-dev = ""
INSANE_SKIP:${PN} += "dev-so \
                     "
FILES:${PN} += "${libdir}/* ${datadir}/*"

BBCLASSEXTEND += "native nativesdk"