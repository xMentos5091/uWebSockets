cmake_minimum_required(VERSION 3.10)
project(uWebSockets VERSION 0.15.6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lz -lssl -lcrypto")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/external/lib)
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

file(GLOB UWS_HEADERS src/*.h src/libwshandshake.hpp src/f2/function2.hpp)
file(COPY ${UWS_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/external/include/uWebSockets)


file(GLOB USOCKETS_HEADERS
  uSockets/src/*.h
  uSockets/src/internal/*.h
  uSockets/src/internal/eventing/*.h
  uSockets/src/internal/networking/*.h
  uSocket/src/interfaces/*.h
)
file(COPY ${USOCKETS_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/external/include/uWebSockets/uSockets)

include_directories(${CMAKE_INSTALL_PREFIX}/external/include/uWebSockets)
include_directories(${CMAKE_INSTALL_PREFIX}/external/include/uWebSockets/uSockets)

add_library(uWS SHARED ${uWebSockets_src})
target_link_libraries(uWS ${ZLIB_LIBRARIES} ${OPENSSL_LIBRARIES}) # miss libuv