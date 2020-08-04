from distutils.core import setup, Extension, DEBUG

calcroots_module = Extension('calcrootsmodule', 
                    language="c++",
                    include_dirs = ['C:\\Users\\Robert\\source\\repos\\Polynomial\\Polynomial.Core\\'],
                    sources = ['Polynomial.cpp'])

setup(name = 'calcrootsmodule', version = '1.0',
    description = 'Python Package with calcrootsmodule C++ extension',
    ext_modules = [calcroots_module]
    )