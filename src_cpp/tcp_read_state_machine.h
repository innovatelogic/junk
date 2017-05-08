#pragma once

#include <system_error>
#include <future>
/*
namespace junk
{
namespace tcp_reader_state_machine
{
class tcp_reader
{
    char buf[64 * 1024];
    Tcp::Connection conn;
    std::promise<int> done;
    int total;

    explicit tcp_reader(int total) : total(total) {}

    void OnConnect(std::error_code ec, Tcp::Connection newCon)
    {
        if (ec)
            return OnError(ec);
        conn = std::move(newCon);
        conn.Read(buf, sizeof(buf),
                  [this](std::error_code ec, int bytesRead) {
                    OnRead(ec, bytesRead);
                  });
    }
    void OnRead(std::error_code ec, int bytesRead)
    {
        if (ec)
            return OnError(ec);
        total -= bytesRead;
        if (total <= 0 || bytesRead == 0)
            return OnComplete();
        conn.Read(buf, sizeof(buf),
                  [this](std::error_code ec, int bytesRead) {
                      OnRead(ec, bytesRead);
                  });
    }
    void OnError(std::error_code ec)
    {
        auto cleadMe = std::unique_ptr<tcp_reader>(this);
        done.set_exception(std::make_exception_ptr(std::system_error(ec)));
    }

    void OnComplete()
    {
        auto cleanMe = std::unique_ptr<tcp_reader>(this);
        done.set_value(total);
    }

  public:
    static std::future<int> start(int total)
    {
        auto p = std::make_unique<tcp_reader>(total);
        auto result = p->done.get_future();
        Tcp::Connect("127.0.0.1", 1337,
                     [raw = p.get()](auto ec, auto newConn) {
                         raw->OnConnect(ec, std::move(newConn));
                     });
        p.release();
    }
};
}
}
*/