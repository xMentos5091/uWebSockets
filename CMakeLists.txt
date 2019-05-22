cmake_minimum_required(VERSION 3.10)
project(uWebSockets VERSION 0.15.6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLIBUS_USE_LIBUV -DLIBUS_USE_OPENSSL -luv -lssl -lcrypto -lz -flto -O3")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)

include_directories(${CMAKE_INSTALL_PREFIX}/include/uWebSockets)
include_directories(${CMAKE_INSTALL_PREFIX}/include/uWebSockets/uSockets)
include_directories(uSockets/src)
set(uWebSockets_src
  uSockets/src/ssl.c
  uSockets/src/socket.c
  uSockets/src/loop.c
  uSockets/src/context.c
  uSockets/src/eventing/epoll.c
  uSockets/src/eventing/libuv.c
  src/App.h
  src/AsyncSocket.h
  src/AsyncSocketData.h
  src/HttpContext.h
  src/HttpContextData.h
  src/HttpParser.h
  src/HttpResponse.h
  src/HttpResponseData.h
  src/HttpRouter.h
  src/Loop.h
  src/LoopData.h
  src/PerMessageDeflate.h
  src/TopicTree.h
  src/Utilities.h
  src/WebSocket.h
  src/WebSocketContext.h
  src/WebSocketContextData.h
  src/WebSocketData.h
  src/WebSocketExtensions.h
  src/WebSocketProtocol.h
  src/libwshandshake.hpp
  src/f2/function2.hpp
)

include(FindOpenSSL)
message("OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
message("OpenSSL libraries: ${OPENSSL_LIBRARIES}")
include_directories(${OPENSSL_INCLUDE_DIR})
link_directories(${OPENSSL_LIBRARIES})
list(APPEND LIB_LIST ${OPENSSL_LIBRARIES})

include(FindZLIB)
message("ZLIB include dir: ${ZLIB_INCLUDE_DIR}")
message("ZLIB libraries: ${ZLIB_LIBRARIES}")
include_directories(${ZLIB_INCLUDE_DIR})
link_directories(${ZLIB_LIBRARIES})
list(APPEND LIB_LIST ${ZLIB_LIBRARIES})

file(GLOB USOCK_INTERF
  uSockets/src/interfaces/*.h
)
install(
  FILES ${USOCK_INTERF}
  COMPONENT ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/uWebSockets/uSockets/interfaces
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

file(GLOB USOCK_INT_NETWORK
  uSockets/src/internal/networking/*.h
)
install(
  FILES ${USOCK_INT_NETWORK}
  COMPONENT ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/uWebSockets/uSockets/internal/networking
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

file(GLOB USOCK_INT_EVENTING
  uSockets/src/internal/eventing/*.h
)
install(
  FILES ${USOCK_INT_EVENTING}
  COMPONENT ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/uWebSockets/uSockets/internal/eventing
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

file(GLOB USOCK_INT
  uSockets/src/internal/*.h
)
install(
  FILES ${USOCK_INT}
  COMPONENT ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/uWebSockets/uSockets/internal
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

file(GLOB USOCKETS
  uSockets/src/*.h
)
install(
  FILES ${USOCKETS}
  COMPONENT ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/uWebSockets/uSockets
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

file(GLOB UWS_HEADERS
  src/*.h
  src/libwshandshake.hpp
)
install(
  FILES ${UWS_HEADERS}
  COMPONENT ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/uWebSockets
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

file(GLOB F_2 src/f2/function2.hpp)
install(
  FILES ${F_2}
  COMPONENT ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/uWebSockets/f2
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)
add_library(uWS SHARED ${uWebSockets_src})
target_link_libraries(uWS uv ${ZLIB_LIBRARIES} ${OPENSSL_LIBRARIES})