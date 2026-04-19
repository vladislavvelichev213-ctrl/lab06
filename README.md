# Laboratory work 5: Google Test
[![Coverage Status](https://coveralls.io/repos/github/vladislavvelichev213-ctrl/lab05/badge.svg?branch=main)](https://coveralls.io/github/vladislavvelichev213-ctrl/lab05?branch=main)
## Author
**Vladislav Velichev** (vladislavvelichev213-ctrl)

## CI/CD Status
- **GitHub Actions:** ✅ Passing
- **Coveralls.io:** ✅ 100% coverage

## Build and Test

```bash
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
cmake --build .
ctest
```

## Project Structure

- `banking/` - Banking library (Account, Transaction)
- `tests/` - Unit tests using GTest
- `third-party/gtest/` - Google Test framework

## Coverage

Coverage report: https://coveralls.io/github/vladislavvelichev213-ctrl/lab05

## Repository

https://github.com/vladislavvelichev213-ctrl/lab05
```

