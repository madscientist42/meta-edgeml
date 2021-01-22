require tensorflow-lite.inc

DESCRIPTION = "TensorFlow Lite Standalone Pip"

RDEPENDS_{PN} += " \
    python3 \
    python3-numpy \
    python3-pybind11 \
    "

inherit python3native

export PYTHON_BIN_PATH="${PYTHON}"
export PYTHON_LIB_PATH="${STAGING_LIBDIR_NATIVE}/${PYTHON_DIR}/site-packages"

# FIXME - This is a hack that supports the usual suspects for this since
#         Google doesn't support everything under the sun with this like they
#         ought to with this- it's "optimized" in thier take and is limited...
do_compile () {
    echo ${TARGET_ARCH}

    if [ ${TARGET_ARCH} = "aarch64" ]; then
        echo "build aarch64"
        export TENSORFLOW_TARGET=aarch64
        export TARGET=aarch64
    elif [ ${TARGET_ARCH} = "arm" ]; then
        echo "build arm"
        export TENSORFLOW_TARGET=rpi
        export TARGET=rpi
    fi

    ${S}/tensorflow/lite/tools/pip_package/build_pip_package.sh

}

do_install() {
    echo "Generating pip package"
    install -d ${D}/${PYTHON_SITEPACKAGES_DIR}

    ${STAGING_BINDIR_NATIVE}/pip3 install --disable-pip-version-check -v \
        -t ${D}/${PYTHON_SITEPACKAGES_DIR} --no-cache-dir --no-deps \
        ${S}/tensorflow/lite/tools/pip_package/gen/tflite_pip${WORKDIR}/recipe-sysroot-native/usr/bin/python3-native/python3/dist/tflite_runtime-2.4.0-*.whl
}

FILES_${PN}-dev = ""
INSANE_SKIP_${PN} += "dev-so \
                     "
FILES_${PN} += "${libdir}/* ${datadir}/*"
