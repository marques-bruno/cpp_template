from invoke.tasks import task

@task
def clean(c, build_dir='build'):
    """ Cleanup task. removes all files from the build/ folder """
    c.run("rm -rf {}".format(build_dir))

@task
def configure(c, generator='Ninja', build_type='Release', vcpkg_dir='vcpkg', build_dir='build'):
    """ Configure and generate CMake project """
    c.run("cmake -G {} -DCMAKE_BUILD_TYPE={} -DCMAKE_TOOLCHAIN_FILE={}/scripts/buildsystems/vcpkg.cmake -B {} -S .".format(generator, build_type, vcpkg_dir, build_dir))

@task
def build(c, build_dir='build', docs=False):
    c.run("cmake --build {}".format(build_dir))
    if docs:
        c.run("echo 'doxygen not yet supported")
