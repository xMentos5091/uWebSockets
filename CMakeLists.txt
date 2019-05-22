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

file(GLOB HEADERS src/*.h src/libwshandshake.hpp src/f2/function2.hpp)
install(
    FILES ${HEADERS}
    COMPONENT ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/external/include/uWebSockets
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

add_library(uWS SHARED ${uWebSockets_src})
target_link_libraries(uWS ${ZLIB} ${OPENSSL}) # miss libuv