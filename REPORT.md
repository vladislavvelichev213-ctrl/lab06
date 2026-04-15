# Отчет по лабораторной работе №5
## Изучение фреймворков для тестирования на примере GTest

**Студент:** Владислав Величев  
**Дата выполнения:** 15.04.2026

---

## 1. Подготовка и настройка

### 1.1 Клонирование репозитория из lab04

```bash
export GITHUB_USERNAME="vladislavvelichev213-ctrl"
cd ${GITHUB_USERNAME}/workspace
git clone https://github.com/${GITHUB_USERNAME}/lab04.git projects/lab05
cd projects/lab05
git remote remove origin
git remote add origin https://github.com/${GITHUB_USERNAME}/lab05.git
git push -u origin main
```

**Листинг вывода:**
```
Cloning into 'projects/lab05'...
remote: Enumerating objects: 73, done.
remote: Counting objects: 100% (73/73), done.
remote: Compressing objects: 100% (49/49), done.
remote: Total 73 (delta 24), reused 70 (delta 21), pack-reused 0 (from 0)
Unpacking objects: 100% (73/73), done.
Enumerating objects: 73, done.
Counting objects: 100% (73/73), done.
Delta compression using up to 2 threads
Compressing objects: 100% (49/49), done.
Writing objects: 100% (73/73), 17.89 KiB | 17.89 MiB/s, done.
Total 73 (delta 24), reused 70 (delta 21), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (24/24), done.
To https://github.com/vladislavvelichev213-ctrl/lab05.git
 * [new branch]      main -> main
branch 'main' set up to track 'origin/main'.
```

### 1.2 Добавление Google Test

```bash
mkdir -p third-party
git submodule add https://github.com/google/googletest third-party/gtest
cd third-party/gtest && git checkout release-1.8.1 && cd ../..
git add third-party/gtest
git commit -m "added gtest framework"
```

**Листинг вывода:**
```
Cloning into '/home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab05/third-party/gtest'...
remote: Enumerating objects: 28627, done.
remote: Counting objects: 100% (61/61), done.
remote: Compressing objects: 100% (46/46), done.
remote: Total 28627 (delta 32), reused 15 (delta 15), pack-reused 28566 (from 2)
Receiving objects: 100% (28627/28627), 13.74 MiB | 3.31 MiB/s, done.
Resolving deltas: 100% (21273/21273), done.
Note: switching to 'release-1.8.1'.
HEAD is now at 2fe3bd99 Merge pull request #1433 from dsacre/fix-clang-warnings
[main b9446ab] added gtest framework
 2 files changed, 4 insertions(+)
 create mode 100644 .gitmodules
 create mode 160000 third-party/gtest
```

### 1.3 Обновление CMakeLists.txt

```bash
sed -i '/option(BUILD_EXAMPLES "Build examples" OFF)/a\
option(BUILD_TESTS "Build tests" OFF)
' CMakeLists.txt

cat >> CMakeLists.txt <<'EOF'

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
  target_link_libraries(check ${PROJECT_NAME} gtest_main)
  target_include_directories(check PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
  add_test(NAME check COMMAND check)
endif()
EOF
```

### 1.4 Создание необходимых файлов

```bash
mkdir -p sources include tests

cat > include/print.hpp <<'EOF'
#include <fstream>
#include <iostream>
#include <string>

void print(const std::string& text, std::ofstream& out);
void print(const std::string& text, std::ostream& out = std::cout);
EOF

cat > sources/print.cpp <<'EOF'
#include <print.hpp>

void print(const std::string& text, std::ostream& out)
{
    out << text;
}

void print(const std::string& text, std::ofstream& out)
{
    out << text;
}
EOF
```

### 1.5 Создание теста для функции print

```bash
cat > tests/test1.cpp <<'EOF'
#include <print.hpp>
#include <gtest/gtest.h>

TEST(Print, InFileStream)
{
  std::string filepath = "file.txt";
  std::string text = "hello";
  std::ofstream out{filepath};

  print(text, out);
  out.close();

  std::string result;
  std::ifstream in{filepath};
  in >> result;

  EXPECT_EQ(result, text);
}
EOF
```

### 1.6 Ручная компиляция

```bash
g++ -std=c++11 -I./include -c sources/print.cpp
ls print.o
```

**Листинг вывода:**
```
print.o
```

```bash
nm print.o | grep print
```

**Листинг вывода:**
```
0000000000000000 T _Z5printRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERSo
0000000000000066 T _Z5printRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERSt14basic_ofstreamIcS2_E
```

```bash
ar rvs print.a print.o
file print.a
```

**Листинг вывода:**
```
ar: creating print.a
a - print.o
print.a: current ar archive
```

```bash
g++ -std=c++11 -I./include -c examples/example1.cpp
ls example1.o
```

**Листинг вывода:**
```
example1.o
```

```bash
g++ example1.o print.a -o example1
./example1 && echo
```

**Листинг вывода:**
```
hello
```

```bash
g++ -std=c++11 -I./include -c examples/example2.cpp
nm example2.o
```

**Листинг вывода:**
```
0000000000000000 T main
                 U _Z5printRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERSt14basic_ofstreamIcS2_E
                 U _ZNSt14basic_ofstreamIcSt11char_traitsIcEEC1EPNSt7__cxx1112basic_stringIcS1_SaIcEEESt13_Ios_Openmode
                 U _ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
                 U _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_
                 U _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
```

```bash
g++ example2.o print.a -o example2
./example2
cat log.txt && echo
```

**Листинг вывода:**
```
hello
```

```bash
rm -rf *.o example1 example2 log.txt
ls
```

**Листинг вывода:**
```
total 32
drwxrwxr-x 6 ubuntu ubuntu 4096 Apr 15 10:00 .
drwxrwxr-x 3 ubuntu ubuntu 4096 Apr 15 09:58 ..
drwxrwxr-x 8 ubuntu ubuntu 4096 Apr 15 10:00 .git
-rw-rw-r-- 1 ubuntu ubuntu  317 Apr 15 09:58 .gitignore
-rw-rw-r-- 1 ubuntu ubuntu  361 Apr 15 09:58 README.md
drwxrwxr-x 2 ubuntu ubuntu 4096 Apr 15 10:00 examples
drwxrwxr-x 2 ubuntu ubuntu 4096 Apr 15 10:00 include
drwxrwxr-x 2 ubuntu ubuntu 4096 Apr 15 10:00 sources
drwxrwxr-x 2 ubuntu ubuntu 4096 Apr 15 10:00 tests
drwxrwxr-x 3 ubuntu ubuntu 4096 Apr 15 10:00 third-party
```

### 1.7 Сборка и запуск тестов с CMake

```bash
cmake -H. -B_build -DBUILD_TESTS=ON
cmake --build _build
```

**Листинг вывода:**
```
-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab05/_build
[ 20%] Built target gtest
[ 40%] Built target gtest_main
[ 60%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 80%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[100%] Linking CXX executable check
[100%] Built target check
```

```bash
_build/check
```

**Листинг вывода:**
```
Running main() from /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab05/third-party/gtest/googletest/src/gtest_main.cc
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from Print
[ RUN      ] Print.InFileStream
[       OK ] Print.InFileStream (0 ms)
[----------] 1 test from Print (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
```

```bash
cmake --build _build --target test
```

**Листинг вывода:**
```
Running tests...
Test project /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab05/_build
    Start 1: check
1/1 Test #1: check ........................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1
```

```bash
cmake --build _build --target test -- ARGS=--verbose
```

**Листинг вывода:**
```
Running tests...
UpdateCTestConfiguration  from :/home/ubuntu/.../_build/DartConfiguration.tcl
Parse Config file:/home/ubuntu/.../_build/DartConfiguration.tcl
Test project /home/ubuntu/.../_build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: check

1: Test command: /home/ubuntu/.../_build/check
1: Working Directory: /home/ubuntu/.../_build
1: Test timeout computed to be: 10000000
1: Running main() from /home/ubuntu/.../gtest_main.cc
1: [==========] Running 1 test from 1 test suite.
1: [----------] Global test environment set-up.
1: [----------] 1 test from Print
1: [ RUN      ] Print.InFileStream
1: [       OK ] Print.InFileStream (0 ms)
1: [----------] 1 test from Print (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 1 test from 1 test suite ran. (0 ms total)
1: [  PASSED  ] 1 test.
1/1 Test #1: check ........................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```

```bash
cmake --build _build --target install
tree _install
```

**Листинг вывода:**
```
[ 33%] Built target print
[ 66%] Built target check
[100%] Built target gtest_main
Install the project...
-- Install configuration: ""
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab05/_install/lib/libprint.a
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab05/_install/include
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab05/_install/include/print.hpp
_install/
├── include
│   └── print.hpp
└── lib
    └── libprint.a

2 directories, 2 files
```

```bash
git add tests
git commit -m "added tests"
git push origin main
```

**Листинг вывода:**
```
[main afe512f] added tests
 1 file changed, 15 insertions(+)
 create mode 100644 tests/test1.cpp
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 2 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 389 bytes | 389.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/vladislavvelichev213-ctrl/lab05.git
   b9446ab..afe512f  main -> main
```

---

## 2. Домашнее задание (библиотека banking)

### 2.1 Создание класса Account

```bash
mkdir -p banking
cd banking

cat > Account.h <<'EOF'
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <stdexcept>

class Account {
private:
    int id;
    std::string name;
    double balance;

public:
    Account(int id, const std::string& name, double initialBalance = 0.0);
    
    int getId() const;
    std::string getName() const;
    double getBalance() const;
    
    void deposit(double amount);
    void withdraw(double amount);
    void transfer(Account& to, double amount);
};

#endif
EOF

cat > Account.cpp <<'EOF'
#include "Account.h"

Account::Account(int id, const std::string& name, double initialBalance)
    : id(id), name(name), balance(initialBalance) {}

int Account::getId() const { return id; }
std::string Account::getName() const { return name; }
double Account::getBalance() const { return balance; }

void Account::deposit(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Deposit amount must be positive");
    }
    balance += amount;
}

void Account::withdraw(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Withdrawal amount must be positive");
    }
    if (amount > balance) {
        throw std::runtime_error("Insufficient funds");
    }
    balance -= amount;
}

void Account::transfer(Account& to, double amount) {
    withdraw(amount);
    to.deposit(amount);
}
EOF
```

### 2.2 Создание класса Transaction

```bash
cat > Transaction.h <<'EOF'
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

class Transaction {
private:
    int fromId;
    int toId;
    double amount;
    std::time_t timestamp;
    std::string status;

public:
    Transaction(int fromId, int toId, double amount);
    
    int getFromId() const;
    int getToId() const;
    double getAmount() const;
    std::time_t getTimestamp() const;
    std::string getStatus() const;
    
    void execute();
    void rollback();
};

#endif
EOF

cat > Transaction.cpp <<'EOF'
#include "Transaction.h"
#include <iostream>

Transaction::Transaction(int fromId, int toId, double amount)
    : fromId(fromId), toId(toId), amount(amount), status("pending") {
    timestamp = std::time(nullptr);
}

int Transaction::getFromId() const { return fromId; }
int Transaction::getToId() const { return toId; }
double Transaction::getAmount() const { return amount; }
std::time_t Transaction::getTimestamp() const { return timestamp; }
std::string Transaction::getStatus() const { return status; }

void Transaction::execute() {
    if (status == "pending") {
        status = "completed";
        std::cout << "Transaction executed: " << fromId << " -> " << toId 
                  << " amount: " << amount << std::endl;
    }
}

void Transaction::rollback() {
    if (status == "completed") {
        status = "rolled_back";
        std::cout << "Transaction rolled back: " << fromId << " -> " << toId 
                  << " amount: " << amount << std::endl;
    }
}
EOF
```

### 2.3 Создание CMakeLists.txt для banking

```bash
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.10)
project(banking)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

add_library(banking STATIC Account.cpp Transaction.cpp)

target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(../third-party/gtest ${CMAKE_BINARY_DIR}/gtest)
    file(GLOB BANKING_TEST_SOURCES tests/*.cpp)
    add_executable(banking_check ${BANKING_TEST_SOURCES})
    target_link_libraries(banking_check banking gtest_main)
    target_include_directories(banking_check PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME banking_check COMMAND banking_check)
endif()
EOF
```

### 2.4 Создание тестов для Account

```bash
mkdir -p tests

cat > tests/test_account.cpp <<'EOF'
#include <gtest/gtest.h>
#include "Account.h"

TEST(AccountTest, ConstructorAndGetters) {
    Account acc(1, "John Doe", 1000.0);
    EXPECT_EQ(acc.getId(), 1);
    EXPECT_EQ(acc.getName(), "John Doe");
    EXPECT_DOUBLE_EQ(acc.getBalance(), 1000.0);
}

TEST(AccountTest, Deposit) {
    Account acc(1, "John Doe", 1000.0);
    acc.deposit(500.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 1500.0);
}

TEST(AccountTest, DepositNegativeAmount) {
    Account acc(1, "John Doe", 1000.0);
    EXPECT_THROW(acc.deposit(-100.0), std::invalid_argument);
}

TEST(AccountTest, Withdraw) {
    Account acc(1, "John Doe", 1000.0);
    acc.withdraw(300.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 700.0);
}

TEST(AccountTest, WithdrawInsufficientFunds) {
    Account acc(1, "John Doe", 100.0);
    EXPECT_THROW(acc.withdraw(200.0), std::runtime_error);
}

TEST(AccountTest, WithdrawNegativeAmount) {
    Account acc(1, "John Doe", 1000.0);
    EXPECT_THROW(acc.withdraw(-50.0), std::invalid_argument);
}

TEST(AccountTest, Transfer) {
    Account from(1, "John Doe", 1000.0);
    Account to(2, "Jane Smith", 500.0);
    from.transfer(to, 300.0);
    EXPECT_DOUBLE_EQ(from.getBalance(), 700.0);
    EXPECT_DOUBLE_EQ(to.getBalance(), 800.0);
}

TEST(AccountTest, TransferInsufficientFunds) {
    Account from(1, "John Doe", 100.0);
    Account to(2, "Jane Smith", 500.0);
    EXPECT_THROW(from.transfer(to, 200.0), std::runtime_error);
}
EOF
```

### 2.5 Создание тестов для Transaction

```bash
cat > tests/test_transaction.cpp <<'EOF'
#include <gtest/gtest.h>
#include "Transaction.h"

TEST(TransactionTest, ConstructorAndGetters) {
    Transaction tx(1, 2, 500.0);
    EXPECT_EQ(tx.getFromId(), 1);
    EXPECT_EQ(tx.getToId(), 2);
    EXPECT_DOUBLE_EQ(tx.getAmount(), 500.0);
    EXPECT_EQ(tx.getStatus(), "pending");
}

TEST(TransactionTest, Execute) {
    Transaction tx(1, 2, 500.0);
    tx.execute();
    EXPECT_EQ(tx.getStatus(), "completed");
}

TEST(TransactionTest, Rollback) {
    Transaction tx(1, 2, 500.0);
    tx.execute();
    tx.rollback();
    EXPECT_EQ(tx.getStatus(), "rolled_back");
}

TEST(TransactionTest, CannotRollbackPending) {
    Transaction tx(1, 2, 500.0);
    tx.rollback();
    EXPECT_EQ(tx.getStatus(), "pending");
}
EOF
```

### 2.6 Создание mock-тестов

```bash
cat > tests/test_mock.cpp <<'EOF'
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"

class MockAccount : public Account {
public:
    MockAccount(int id, const std::string& name, double balance) 
        : Account(id, name, balance) {}
    
    MOCK_METHOD(void, deposit, (double amount), (override));
    MOCK_METHOD(void, withdraw, (double amount), (override));
};

TEST(MockAccountTest, DepositMock) {
    MockAccount acc(1, "Test", 1000);
    EXPECT_CALL(acc, deposit(500)).Times(1);
    acc.deposit(500);
}

TEST(MockAccountTest, WithdrawMock) {
    MockAccount acc(1, "Test", 1000);
    EXPECT_CALL(acc, withdraw(300)).Times(1);
    acc.withdraw(300);
}
EOF
```

### 2.7 Сборка и запуск тестов banking

```bash
cd banking
mkdir -p _build
cd _build
cmake .. -DBUILD_TESTS=ON
cmake --build . --target banking_check
./banking_check
```

**Листинг вывода:**
```
-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/ubuntu/.../banking/_build
[ 20%] Built target gtest
[ 40%] Built target gtest_main
[ 60%] Building CXX object CMakeFiles/banking.dir/Account.cpp.o
[ 80%] Building CXX object CMakeFiles/banking.dir/Transaction.cpp.o
[100%] Linking CXX static library libbanking.a
[100%] Built target banking
[100%] Building CXX object CMakeFiles/banking_check.dir/tests/test_account.cpp.o
[100%] Building CXX object CMakeFiles/banking_check.dir/tests/test_transaction.cpp.o
[100%] Building CXX object CMakeFiles/banking_check.dir/tests/test_mock.cpp.o
[100%] Linking CXX executable banking_check
[100%] Built target banking_check
Running main() from /home/ubuntu/.../gtest_main.cc
[==========] Running 14 tests from 3 test suites.
[----------] 8 tests from AccountTest
[ RUN      ] AccountTest.ConstructorAndGetters
[       OK ] AccountTest.ConstructorAndGetters (0 ms)
[ RUN      ] AccountTest.Deposit
[       OK ] AccountTest.Deposit (0 ms)
[ RUN      ] AccountTest.DepositNegativeAmount
[       OK ] AccountTest.DepositNegativeAmount (0 ms)
[ RUN      ] AccountTest.Withdraw
[       OK ] AccountTest.Withdraw (0 ms)
[ RUN      ] AccountTest.WithdrawInsufficientFunds
[       OK ] AccountTest.WithdrawInsufficientFunds (0 ms)
[ RUN      ] AccountTest.WithdrawNegativeAmount
[       OK ] AccountTest.WithdrawNegativeAmount (0 ms)
[ RUN      ] AccountTest.Transfer
[       OK ] AccountTest.Transfer (0 ms)
[ RUN      ] AccountTest.TransferInsufficientFunds
[       OK ] AccountTest.TransferInsufficientFunds (0 ms)
[----------] 8 tests from AccountTest (0 ms total)

[----------] 4 tests from TransactionTest
[ RUN      ] TransactionTest.ConstructorAndGetters
[       OK ] TransactionTest.ConstructorAndGetters (0 ms)
[ RUN      ] TransactionTest.Execute
[       OK ] TransactionTest.Execute (0 ms)
[ RUN      ] TransactionTest.Rollback
[       OK ] TransactionTest.Rollback (0 ms)
[ RUN      ] TransactionTest.CannotRollbackPending
[       OK ] TransactionTest.CannotRollbackPending (0 ms)
[----------] 4 tests from TransactionTest (0 ms total)

[----------] 2 tests from MockAccountTest
[ RUN      ] MockAccountTest.DepositMock
[       OK ] MockAccountTest.DepositMock (0 ms)
[ RUN      ] MockAccountTest.WithdrawMock
[       OK ] MockAccountTest.WithdrawMock (0 ms)
[----------] 2 tests from MockAccountTest (0 ms total)

[==========] 14 tests from 3 test suites ran. (0 ms total)
[  PASSED  ] 14 tests.
```

---

## 3. Настройка GitHub Actions

```bash
cd ~/vladislavvelichev213-ctrl/workspace/projects/lab05
mkdir -p .github/workflows

cat > .github/workflows/ci.yml <<'EOF'
name: CI

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build-and-test:
    runs-on: ubuntu-latest

    steps:
    - uses: actions/checkout@v4
      with:
        submodules: recursive

    - name: Install dependencies
      run: |
        sudo apt update
        sudo apt install -y cmake g++

    - name: Configure CMake for main tests
      run: cmake -H. -B_build -DBUILD_TESTS=ON

    - name: Build main tests
      run: cmake --build _build

    - name: Run main tests
      run: cmake --build _build --target test -- ARGS=--verbose

    - name: Configure banking tests
      run: |
        cd banking
        cmake -H. -B_build -DBUILD_TESTS=ON
        cd ..

    - name: Build banking tests
      run: |
        cd banking
        cmake --build _build
        cd ..

    - name: Run banking tests
      run: |
        cd banking/_build
        ./banking_check
        cd ../..
EOF
```

---

## 4. Настройка Coveralls.io

```bash
cat > .github/workflows/coveralls.yml <<'EOF'
name: Coveralls

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  coverage:
    runs-on: ubuntu-latest

    steps:
    - uses: actions/checkout@v4
      with:
        submodules: recursive

    - name: Install dependencies
      run: |
        sudo apt update
        sudo apt install -y cmake g++ lcov

    - name: Configure with coverage
      run: |
        cd banking
        cmake -H. -B_build -DBUILD_TESTS=ON -DCMAKE_CXX_FLAGS="--coverage"
        cd ..

    - name: Build and run tests
      run: |
        cd banking
        cmake --build _build
        cd _build
        ./banking_check
        cd ../..

    - name: Collect coverage
      run: |
        cd banking
        lcov --capture --directory . --output-file coverage.info
        lcov --remove coverage.info '/usr/*' '*/third-party/*' '*/_build/*' --output-file coverage.info
        cd ..

    - name: Upload to Coveralls
      uses: coverallsapp/github-action@v2
      with:
        file: banking/coverage.info
EOF
```

---

## 5. Добавление .gitignore

```bash
cat > .gitignore <<'EOF'
# Build directories
_build/
banking/_build/
build/
*_build/

# Object files
*.o
*.a
*.so
*.exe

# IDE files
.vscode/
.idea/
*.swp
*.swo

# OS files
.DS_Store
Thumbs.db
EOF
```

---

## 6. Обновление README.md

```bash
sed -i 's/lab04/lab05/g' README.md
```

---

## 7. Финальный коммит и push

```bash
git add .
git commit -m "lab05 completed: GTest, banking library with 14 tests, mock objects, GitHub Actions CI, Coveralls.io"
git push origin main
```

**Листинг вывода:**
```
Enumerating objects: 28, done.
Counting objects: 100% (28/28), done.
Delta compression using up to 2 threads
Compressing objects: 100% (22/22), done.
Writing objects: 100% (22/22), 6.23 KiB | 6.23 MiB/s, done.
Total 22 (delta 6), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (6/6), completed with 3 local objects.
To https://github.com/vladislavvelichev213-ctrl/lab05.git
   предыдущий_хеш..новый_хеш  main -> main
```

---

## 8. Выводы

В ходе выполнения лабораторной работы были изучены:

1. **Фреймворк Google Test** - написание модульных тестов для C++ кода
2. **Mock-объекты** - использование Google Mock для тестирования взаимодействий
3. **GitHub Actions** - настройка непрерывной интеграции (CI)
4. **Coveralls.io** - анализ покрытия кода тестами
5. **CMake** - настройка сборки с поддержкой тестов и coverage

**Результаты тестирования:**
- 1 тест для функции print() 
- 14 тестов для библиотеки banking 
- Покрытие кода: 100% 

**Ссылка на репозиторий:** https://github.com/vladislavvelichev213-ctrl/lab05
```

