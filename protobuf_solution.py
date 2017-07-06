#!/usr/bin/env python3

import xml.etree.ElementTree as ET
import os
import subprocess
import fnmatch
import sys

print ('run protobuf_solution.py')

# cmake 환경변수 설정
script_dir = os.getcwd()
os.chdir("./cmake_x64/bin")
bin_cmake_path = os.getcwd()
os.environ["path"] = os.environ["path"] + ';' + bin_cmake_path
os.chdir(script_dir)


def create_vs_solution_batch():
    print ("create_vs_solution_batch")
    target = open("./protobuf-master/cmake/build/solution/create_vs_solution.bat", 'w')
    target.write('cmake -G "Visual Studio 14 2015 Win64" ^ -DCMAKE_INSTALL_PREFIX=../../../../install ^ -Dprotobuf_MSVC_STATIC_RUNTIME=OFF ^ -Dprotobuf_BUILD_TESTS=OFF ^ ../..')
    target.close()

def execute_create_vs_solution_batch():
    print ("execute_create_vs_solution_batch")
    os.chdir("./protobuf-master/cmake/build/solution")
    print (os.getcwd())
    os.system('create_vs_solution.bat')
    os.chdir(script_dir)

build_dir = './protobuf-master/cmake/build'
if not os.path.exists(build_dir):
    os.makedirs(build_dir)

vs_solution_dir = './protobuf-master/cmake/build/solution'
if not os.path.exists(vs_solution_dir):
    os.makedirs(vs_solution_dir)

vs_solution_file = './protobuf-master/cmake/build/solution/protobuf.sln'
if not os.path.isfile(vs_solution_file):
    create_vs_solution_batch()
    execute_create_vs_solution_batch()
