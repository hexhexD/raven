#include "raven.h"
#include <iostream>

using asio::ip::tcp;

int main() {
  asio::io_context ctx;
  tcp::endpoint end(asio::ip::make_address_v4("18.182.57.240"),6900);
  tcp::socket socket(ctx);
  asio::error_code e;

  auto tmp = raven::hexStringToBytes<std::vector<raven::u8>>("7c020a000000726167626c756555497a50524f000000c20a0000c20a000062333439613133616662643534386136386634636464393863363261306631626637646332663262000a0000c00a0000c00a000003018defcb8eca5275048b9dbfbb");
  for (auto e : tmp)
    std::cout << std::hex << e;
  socket.connect(end, e);
  if (!e)
    std::cout << "Connected!\n";

  asio::write(socket, asio::buffer(tmp.data(), tmp.size()));

  socket.wait(socket.wait_read);
  if (socket.available() > 0) {
    std::vector<char> buf(socket.available());
    asio::read(socket, asio::buffer(buf.data(), buf.size()));

    for (auto &e : buf) {
      std::cout << e;
    }
  }
}
