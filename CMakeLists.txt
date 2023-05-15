cmake_minimum_required(VERSION 3.1.14)
project(Server VERSION 0.1.0 LANGUAGES CXX)

option(MYLIB_TESTING "Turn on testing" ON)
option(MYLIB_COVERAGE "Turn on code coverage measurement with tests" OFF)

add_compile_options(  #compilation option
    -Werror 

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_library(mylib INTERFACE) #lib

target_include_directories(mylib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(mylib INTERFACE cxx_std_20)


add_library(Mylib::mylib ALIAS mylib)

install(DIRECTORY include/mylib DESTINATION include) # Установка наших заголовков в систему. Тут всё просто. Говорим, что папка со всеми заголовками должна попасть в директорию include относительно места установки.

install(TARGETS mylib EXPORT MylibConfig) # Далее сообщаем системе сборки о том, что мы хотим иметь возможность в сторонних проектах звать команду find_package(Mylib) и получать цель Mylib::mylib
install(EXPORT MylibConfig NAMESPACE Mylib:: DESTINATION share/Mylib/cmake)

include(CMakePackageConfigHelpers) # Следующее заклинание нужно понимать так. Когда в стороннем проекте мы вызовем команду find_package(Mylib 1.2.3 REQUIRED), и при этом реальная версия установленной библиотеки окажется несовместимой с версией 1.2.3, CMake автоматически сгенерирует ошибку. То есть не нужно будет следить за версиями вручную.
write_basic_package_version_file("${PROJECT_BINARY_DIR}/MylibConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/MylibConfigVersion.cmake" DESTINATION share/Mylib/cmake)

include(CTest)
enable_testing()

if(NOT MYLIB_TESTING)
    message(STATUS "Testing of the Mylib project is off")
elseif(IS_SUBPROJECT)
    message(STATUS "Mylib is not tested in submodule mode")
else()
    add_subdirectory(tests)
endif()

include_directories(rapidjson)


# include(CTest)
# enable_testing()

# add_executable(Server main.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
