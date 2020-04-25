from distutils.core import setup, Extension, DEBUG

calcroots_module = Extension('calcrootsmodule', 
                    define_macros = [('VC9_PYTHON27', '1')],
                    #extra_link_args=["-fPIC"],
                    language="c++",
                    include_dirs = ['C:\\Users\\Robert\\source\\repos\\Polynomial\\Polynomial.Core\\'],
                    #libraries = ['Polynomial.Core'],
                    #library_dirs = ['C:\\Users\\Robert\\source\\repos\\Polynomial\\Release'],
                    sources = ['Polynomial.cpp', 'C:\\Users\\Robert\\source\\repos\\Polynomial\\Polynomial.Core\\Polynomial.cpp'])

setup(name = 'calcrootsmodule', version = '1.0',
    description = 'Python Package with calcrootsmodule C++ extension',
    ext_modules = [calcroots_module]
    )