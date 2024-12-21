#!/usr/bin/env python
import os
import subprocess
from glob import glob
from pathlib import Path

# Build GekkoNet static library
def build_gekkonet():
    base_dir = "GekkoNet/GekkoLib"
    build_dir = os.path.join(base_dir, "build")
    os.makedirs(build_dir, exist_ok=True)
    
    # Determine the output library path (platform-specific)
    if os.name == "nt":  # Windows
        subprocess.run(["dir"], shell=True)
        output_lib = os.path.join(base_dir, "out", "Release", "GekkoNet_STATIC_NO_ASIO.lib")
    else:  # Unix-like
        subprocess.run(["ls"])
        output_lib = os.path.join(base_dir, "out", "libGekkoNet_STATIC_NO_ASIO.a")

    # Check if rebuild is necessary
    if os.path.exists(output_lib):
        # Gather all relevant source and header files
        source_files = glob(os.path.join(base_dir, "src", "*.cpp")) + \
                       glob(os.path.join(base_dir, "include", "*.h"))
        
        # If the output library is newer than all source files, skip the build
        if all(os.path.getmtime(output_lib) > os.path.getmtime(src) for src in source_files):
            print(f"Skipping build: {output_lib} is up-to-date.")
            return output_lib



    # Run CMake configuration and build
    subprocess.run(["cmake", "..",
                    "-DBUILD_SHARED_LIBS=OFF",
                    "-DNO_ASIO_BUILD=ON",
                    "-DBUILD_DOCS=OFF"],
                   cwd=build_dir, check=True)
    subprocess.run(["cmake", "--build", ".", "--config", "Release"],
                   cwd=build_dir, check=True)
    
    return output_lib

# TODO: Do not copy environment after godot-cpp/test is updated <https://github.com/godotengine/godot-cpp/blob/master/test/SConstruct>.
env = SConscript("godot-cpp/SConstruct")

# Build and add GekkoNet
gekkonet_lib = build_gekkonet()
env.Append(CPPPATH=["GekkoNet/GekkoLib/include"])
env.Append(LIBS=[File(gekkonet_lib)])

# Add source files.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

# Find gdextension path even if the directory or extension is renamed (e.g. project/addons/example/example.gdextension).
(extension_path,) = glob("project/addons/*/*.gdextension")

# Get the addon path (e.g. project/addons/example).
addon_path = Path(extension_path).parent

# Get the project name from the gdextension file (e.g. example).
project_name = Path(extension_path).stem

scons_cache_path = os.environ.get("SCONS_CACHE")
if scons_cache_path != None:
    CacheDir(scons_cache_path)
    print("Scons cache enabled... (path: '" + scons_cache_path + "')")

# Create the library target (e.g. libexample.linux.debug.x86_64.so).
debug_or_release = "release" if env["target"] == "template_release" else "debug"
if env["platform"] == "macos":
    library = env.SharedLibrary(
        "{0}/bin/lib{1}.{2}.{3}.framework/{1}.{2}.{3}".format(
            addon_path,
            project_name,
            env["platform"],
            debug_or_release,
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "{}/bin/lib{}.{}.{}.{}{}".format(
            addon_path,
            project_name,
            env["platform"],
            debug_or_release,
            env["arch"],
            env["SHLIBSUFFIX"],
        ),
        source=sources,
    )

Default(library)
