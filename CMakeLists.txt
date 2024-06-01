cmake_minimum_required(VERSION 3.14)
project(bmstu_cpp_work)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.0
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 23)
set(TEST_NAME ${PROJECT_NAME}_tests)

# Добавляем все домашки
file(GLOB SOURCES_HW "hw_*/*.h" "hw_*/*.cpp")

## Добавляем древние знания
#file(GLOB SOURCES_ANCIENT "ancient_knowledge/*")

# Объединяем все списки исходных файлов
set(ALL_SOURCES ${SOURCES_LET} ${SOURCES_HW} ${SOURCES_ANCIENT})

# Удаляем то, что нужно удалить
list(REMOVE_ITEM ALL_SOURCES ${REMOVE_SOURCES})

add_executable(${TEST_NAME} ${ALL_SOURCES})
target_link_libraries(${TEST_NAME} gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})

# Добавляем субдиректории


# Не забыть исключить лишнее (добавить в REMOVE_SOURCES)
