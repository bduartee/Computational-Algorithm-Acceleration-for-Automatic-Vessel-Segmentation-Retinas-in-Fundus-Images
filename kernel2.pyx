# distutils: sources = kernel1.cpp
import numpy as np
cimport numpy as np

cdef extern from "kernel1.h":
    cdef cppclass KERNEL:
        KERNEL() except +
        void inversao(double *data, int pn_lins, int pn_cols)
        void calcula(double *data, double *data_mask, double *data_S, double *data_So, int n_lins, int n_cols)
       
cdef class kernelpython:
    cdef KERNEL c_kernel

    def __cinit__(self):
        self.c_kernel= KERNEL()
    
    def inversao(self, np.ndarray[np.float64_t, ndim=2] image):
        self.c_kernel.inversao(<double*> image.data, image.shape[0], image.shape[1])

    def calcula(self, np.ndarray[np.float64_t, ndim=2] image, np.ndarray[np.float64_t, ndim=2] image1,np.ndarray[np.float64_t, ndim=2] image2,np.ndarray[np.float64_t, ndim=2] image3):
        self.c_kernel.calcula(<double*> image.data,<double*> image1.data,<double*> image2.data,<double*> image3.data, image.shape[0], image.shape[1])
 
