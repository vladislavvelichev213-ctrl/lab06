# Laboratory work VI

## Author
Владислав Величев
GitHub: vladislavvelichev213-ctrl

## Tutorial

### Step 1: Clone lab05 → lab06
```bash
$ export GITHUB_USERNAME=vladislavvelichev213-ctrl
$ export GITHUB_EMAIL=vladislav.velichev213@gmail.com
$ export GITHUB_TOKEN=YOUR_TOKEN_HIDDEN
$ alias edit=nano
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
$ git clone https://${GITHUB_TOKEN}@github.com/${GITHUB_USERNAME}/lab05 projects/lab06
$ cd projects/lab06
$ git remote remove origin
$ git remote add origin https://${GITHUB_TOKEN}@github.com/${GITHUB_USERNAME}/lab06
```
Output:
```
bash: cd: vladislavvelichev213-ctrl/workspace: No such file or directory
~/lab05 ~/lab05
bash: scripts/activate: No such file or directory
Cloning into 'projects/lab06'...
remote: Enumerating objects: 225, done.
remote: Counting objects: 100% (225/225), done.
remote: Compressing objects: 100% (145/145), done.
remote: Total 225 (delta 97), reused 184 (delta 56), pack-reused 0 (from 0)
Receiving objects: 100% (225/225), 34.11 KiB | 563.00 KiB/s, done.
Resolving deltas: 100% (97/97), done.
```

### Step 2: Edit CMakeLists.txt
```bash
$ sed -i '/project(print)/a\
set(PRINT_VERSION_MAJOR 0)' CMakeLists.txt
$ sed -i '/project(print)/a\
set(PRINT_VERSION_MINOR 1)' CMakeLists.txt
$ sed -i '/project(print)/a\
set(PRINT_VERSION_PATCH 0)' CMakeLists.txt
$ sed -i '/project(print)/a\
set(PRINT_VERSION_TWEAK 0)' CMakeLists.txt
$ sed -i '/project(print)/a\
set(PRINT_VERSION\
  \${PRINT_VERSION_MAJOR}.\${PRINT_VERSION_MINOR}.\${PRINT_VERSION_PATCH}.\${PRINT_VERSION_TWEAK})' CMakeLists.txt
$ sed -i '/project(print)/a\
set(PRINT_VERSION_STRING "v\${PRINT_VERSION}")' CMakeLists.txt
$ git diff
```

### Step 3: Create DESCRIPTION and ChangeLog.md
```bash
$ touch DESCRIPTION
$ nano DESCRIPTION
$ export DATE="`LANG=en_US date +'%a %b %d %Y'`"
$ cat > ChangeLog.md <<EOF
* ${DATE} ${GITHUB_USERNAME} <${GITHUB_EMAIL}> 0.1.0.0
- Initial RPM release
EOF
```
DESCRIPTION content:
```
static C++ library for printing
```

### Step 4: Create CPackConfig.cmake
```bash
$ cat > CPackConfig.cmake <<EOF
include(InstallRequiredSystemLibraries)
EOF
$ cat >> CPackConfig.cmake <<EOF
set(CPACK_PACKAGE_CONTACT ${GITHUB_EMAIL})
set(CPACK_PACKAGE_VERSION_MAJOR \${PRINT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR \${PRINT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH \${PRINT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK \${PRINT_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION \${PRINT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_FILE \${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "static C++ library for printing")
EOF
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_RESOURCE_FILE_LICENSE \${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README \${CMAKE_CURRENT_SOURCE_DIR}/README.md)
EOF
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_RPM_PACKAGE_NAME "print-devel")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "print")
set(CPACK_RPM_CHANGELOG_FILE \${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md)
set(CPACK_RPM_PACKAGE_RELEASE 1)
EOF
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_DEBIAN_PACKAGE_NAME "libprint-dev")
set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "cmake >= 3.0")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)
EOF
$ cat >> CPackConfig.cmake <<EOF

include(CPack)
EOF
```

### Step 5: Add include to CMakeLists.txt
```bash
$ cat >> CMakeLists.txt <<EOF

include(CPackConfig.cmake)
EOF
```

### Step 6: Update README.md
```bash
$ sed -i 's/lab05/lab06/g' README.md
```

### Step 7: Commit and push
```bash
$ git add .
$ git commit -m "added cpack config"
$ git tag v0.1.0.0
$ git push origin main --tags
```
Output:
```
[main de7eabd] added cpack config
 5 files changed, 30 insertions(+), 1 deletion(-)
 create mode 100644 CPackConfig.cmake
 create mode 100644 ChangeLog.md
 create mode 100644 DESCRIPTION
Enumerating objects: 232, done.
Counting objects: 100% (232/232), done.
Delta compression using up to 2 threads
Compressing objects: 100% (110/110), done.
Writing objects: 100% (232/232), 35.29 KiB | 17.64 MiB/s, done.
Total 232 (delta 100), reused 224 (delta 97), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (100/100), done.
To https://github.com/vladislavvelichev213-ctrl/lab06
 * [new branch]      main -> main
 * [new tag]         v0.1.0.0 -> v0.1.0.0
```

### Step 8: Fix submodule and build
```bash
$ git submodule update --init --recursive
$ touch LICENSE
$ sed -i '/CPACK_RESOURCE_FILE_LICENSE/d' CPackConfig.cmake
```
Output:
```
Submodule 'third-party/gtest' (https://github.com/google/googletest) registered for path 'third-party/gtest'
Cloning into '/home/ubuntu/lab05/projects/lab06/third-party/gtest'...
Submodule path 'third-party/gtest': checked out 'd72f9c8aea6817cdf1ca0ac10887f328de7f3da2'
```

### Step 9: Build and package with CPack
```bash
$ rm -rf _build
$ cmake -H. -B_build
$ cmake --build _build
$ cd _build
$ cpack -G "TGZ"
$ cd ..
$ mkdir -p artifacts
$ mv _build/*.tar.gz artifacts
$ tree artifacts
```
Output:
```
-- The C compiler identification is GNU 15.2.0
-- The CXX compiler identification is GNU 15.2.0
...
[100%] Built target gmock_main
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: lab05
CPack: - Install project: lab05 []
CPack: Create package
CPack: - package: /home/ubuntu/lab05/projects/lab06/_build/lab05-1.16.0-Linux.tar.gz generated.
artifacts
└── lab05-1.16.0-Linux.tar.gz

1 directory, 1 file
```

### Step 10: Final commit
```bash
$ git add .
$ git commit -m "fixed submodule init and LICENSE for CPack"
$ git push origin main
```

## Links
- [CMake CPack Package Generators](https://cmake.org/Wiki/CMake:CPackPackageGenerators)
- [DMG](https://cmake.org/cmake/help/latest/cpack_gen/dmg.html)
- [DEB](https://cmake.org/cmake/help/latest/cpack_gen/deb.html)
- [RPM](https://cmake.org/cmake/help/latest/cpack_gen/rpm.html)
- [NSIS](https://cmake.org/cmake/help/latest/cpack_gen/nsis.html)
