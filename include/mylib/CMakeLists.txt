set(BOOST_ROOT /home/king/Documents/boost/boost_1_81_0) # укажите путь к папке с библиотекой Boost
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

find_package (Boost REQUIRED system thread COMPONENTS REQUIRED)

include_directories (SYSTEM ${Boost_INCLUDE_DIR}) # подключаем заголовочные файлы

target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES}) # подключаем библиотеку