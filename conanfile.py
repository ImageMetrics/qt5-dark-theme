import os
from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain, CMakeDeps

class Qt5DarkThemeLocal(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    
    def requirements(self):
        self.requires("qt/5.15.9")
        
    def configure(self):
        # Configure Qt dependency options
        self.options["qt"].with_libjpeg = "libjpeg-turbo"
        self.options["qt"].with_libpng = True
        self.options["qt"].qtsvg = True
    
    def layout(self):
        cmake_layout(self)
        
    def generate(self):
        tc = CMakeToolchain(self)
        # Remove the "conan-" prefix to get preset names like "default", "debug", "release"
        tc.presets_prefix = ""
        tc.generate()
        
        deps = CMakeDeps(self)
        deps.generate()