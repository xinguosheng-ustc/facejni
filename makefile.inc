# Copyright (c) 2015-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD+Patents license found in the
# LICENSE file in the root directory of this source tree.

CXX          = g++ -std=c++11
CXXCPP       = g++ -std=c++11 -E
# TODO: Investigate the LAPACKE wrapper for LAPACK, which defines the correct
#   type for FORTRAN integers.
CPPFLAGS     = -DFINTEGER=int 
CXXFLAGS     = -fPIC -fopenmp -m64 -Wno-sign-compare -g -O3 -Wall -Wextra
CPUFLAGS     = -msse4 -mpopcnt
LDFLAGS      = -fopenmp 
LIBS         = -lopenblas -llapack 
PYTHONCFLAGS = -I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/python2.7 -I/home/hrg/anaconda3/lib/python3.6/site-packages/numpy/core/include

NVCC         = /usr/local/cuda/bin/nvcc
NVCCLDFLAGS  = -L/usr/local/cuda/lib64 
NVCCLIBS     = -lcudart -lcublas -lcuda 
CUDAROOT     = /usr/local/cuda
CUDACFLAGS   = -I/usr/local/cuda/include 
NVCCFLAGS    = -I $(CUDAROOT)/targets/x86_64-linux/include/ \
-Xcompiler -fPIC \
-Xcudafe --diag_suppress=unrecognized_attribute \
-gencode arch=compute_35,code="compute_35" \
-gencode arch=compute_52,code="compute_52" \
-gencode arch=compute_60,code="compute_60" \
-gencode arch=compute_61,code="compute_61" \
-lineinfo \
-ccbin $(CXX) -DFAISS_USE_FLOAT16

OS = $(shell uname -s)

SHAREDEXT   = so
SHAREDFLAGS = -shared

ifeq ($(OS),Darwin)
	SHAREDEXT   = dylib
	SHAREDFLAGS = -dynamiclib -undefined dynamic_lookup
endif

MKDIR_P      = /bin/mkdir -p
PYTHON       = python
SWIG         = swig

prefix      ?= /usr/local
exec_prefix ?= ${prefix}
libdir       = ${exec_prefix}/lib
includedir   = ${prefix}/include
