git clone --recursive https://github.com/boostorg/boost.git
cd boost
git checkout boost-1.65.0
git submodule update

call bootstrap.bat
b2.exe headers
b2 --stagedir=stage --toolset=msvc-14.0 address-model=64 stage --with-atomic --with-system --with-chrono --with-container --with-context --with-coroutine --with-coroutine2 --with-date_time --with-exception --with-fiber --with-filesystem --with-locale --with-log --with-math --with-metaparse --with-mpi --with-program_options --with-python --with-random --with-regex --with-serialization --with-signals --with-system  --with-thread --with-timer variant=debug,release link=static