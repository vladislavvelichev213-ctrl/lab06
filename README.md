# Laboratory work 6: CPack

## Author
Vladislav Velichev

## CI/CD Status
- GitHub Actions: ✅ Passing
- Coveralls.io: ✅ 100% coverage

## Build and Package

mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
cmake --build .
ctest
cpack -G "TGZ"
cpack -G "DEB"
cpack -G "RPM"

## Repository
https://github.com/vladislavvelichev213-ctrl/lab06

## Release
https://github.com/vladislavvelichev213-ctrl/lab06/releases
