#include "App.h"


int main(int argc, char const *argv[])
{
  uWS::App().get("/hello", [](auto *res, auto *req) {
        res->end("Hello World!");
        }).listen(9001, [](auto *listenSocket) {
            if (listenSocket) {
              std::cout << "BUONASERA\n\n";
            }
      }).run();
  // us_poll_free(nullptr, nullptr);
  // us_ssl_socket_context_free(nullptr);
  return 0;
}
