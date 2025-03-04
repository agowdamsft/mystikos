FROM python:3.7-alpine3.12

RUN echo "|--> Updating" \
    && apk update && apk upgrade \
    && echo "|--> Install basics pre-requisites" \
    && apk add --no-cache \
        curl ca-certificates py3-numpy py3-numpy-f2py \
        freetype jpeg libpng libstdc++ libgomp graphviz font-noto \
    && echo "|--> Install build dependencies" \
    && apk add --no-cache --virtual=.build-deps \
        build-base linux-headers python3-dev git cmake jpeg-dev bash \
        libffi-dev gfortran py3-numpy-dev freetype-dev libpng-dev \
    && echo "|--> Install Python packages" \
    && pip install -U --no-cache-dir pyyaml cffi requests pillow

# 1) PyTorch is not officially supported on Alpine.
# See https://discuss.pytorch.org/t/compiling-master-from-source-on-alpine-fails-with-undefined-reference-to-backtrace/64676.
# By defining __EMSCRIPTEN__ the build disables certain features like backtrace support.
# This is a work-around.

# 2) Using OpenBLAS caused a segfault. Not installing libopenblas-dev causes PyTorch
# to fall-back to Eigen. Setting BLAS=Eigen does not work due to a bug in the CMake
# script.

# 3) By default, PyTorch uses OpenMP, however due to https://github.com/lsds/sgx-lkl-oe/issues/264
# we need to disable that. Using USE_OPENMP=0 is broken as PyTorch still uses OMP symbols
# but now doesn't link against OpenMP, caused symbol errors.
# Adding ATEN_THREADING=NATIVE and USE_MKLDNN=0 seems to work around the issue.

# 4) For now Sys_fork is not supported in mystikos. Will use a patched version (using spawn)

RUN echo "|--> Install PyTorch" \
    && git clone https://github.com/bodzhang/pytorch.git --branch v1.4.1-patch --single-branch \
    && cd pytorch \
    && git checkout v1.4.1-patch \
    && git submodule update --init --recursive \
    && DEBUG=0 USE_CUDA=0 USE_MKLDNN=0 USE_OPENMP=0 ATEN_THREADING=NATIVE BUILD_BINARY=0 \
       CFLAGS="-D__EMSCRIPTEN__" \
       python setup.py install \
    && cd .. \
    && rm -rf pytorch

RUN rm -rf /app;mkdir -p /app
WORKDIR /app
# ADD torch_nn.py /app
ADD torch_polynomial_nn.py /app

CMD ["/bin/bash"]
# CMD ["/usr/bin/python3", "/app/torch_nn.py"]
