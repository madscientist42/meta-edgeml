# Dogsbody for the Python pip packahing build.  This handles the actual operations.
# the recipes themselves let us specify version or "git" for preferred
# or as close to the tip of master as we dare.

DESCRIPTION = "TensorFlow Lite Standalone Pip Package..."

DEPENDS = " \
    python3 \
    python3-native \
    python3-numpy \
    python3-numpy-native \
    python3-pybind11 \
    python3-pybind11-native \
    "

RDEPENDS:{PN} += " \
    python3 \
    python3-numpy \
    python3-pybind11 \
    "

inherit python3native


export PYTHON_BIN_PATH = "${PYTHON}"
export PYTHON_LIB_PATH += "${STAGING_LIBDIR}/${PYTHON_DIR}/site-packages"


# FIXME - This is a hack that supports the usual suspects for this since
#         Google doesn't support everything under the sun with this like they
#         ought to with this- it's "optimized" in thier take and is limited...
do_compile () {
    bbplain "Building TF-Lite Python for ${TARGET_ARCH}"

    case "${TARGET_ARCH}" in
        aarch64 | armv8 | armv8a )
            BUILD_TGT="aarch64"
            ;;

        arm)
            BUILD_TGT="armhf"
            ;;

        x86_64)
            BUILD_TGT="native"
            ;;
    esac

    ${S}/tensorflow/lite/tools/pip_package/build_pip_package_with_cmake.sh $BUILD_TGT
}

do_install() {
    bbplain "Generating/installing pip package"
    install -d ${D}/${PYTHON_SITEPACKAGES_DIR}

    ${STAGING_BINDIR_NATIVE}/pip3 install --disable-pip-version-check -v \
        -t ${D}/${PYTHON_SITEPACKAGES_DIR} --no-cache-dir --no-deps \
        ${S}/tensorflow/lite/tools/pip_package/gen/tflite_pip${WORKDIR}/recipe-sysroot-native/usr/bin/python3-native/python3/dist/tflite_runtime-${PV}-*.whl
}

FILES:${PN}-dev = ""
INSANE_SKIP:${PN} += "dev-so \
                     "
FILES:${PN} += "${libdir}/* ${datadir}/*"

BBCLASSEXTEND += "native nativesdk"