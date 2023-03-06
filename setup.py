from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

import numpy

ext_modules = [
    Extension("kernel", language="c++", include_dirs=[numpy.get_include()],
              sources=["kernel2.pyx","kernel1.cpp"])
]

setup(name="kernel",
      cmdclass={"build_ext": build_ext},
      ext_modules=ext_modules)
      
