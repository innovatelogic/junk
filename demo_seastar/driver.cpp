
#include <seastar/core/app-template.hh>
#include <seastar/core/condition-variable.hh>
#include <seastar/core/signal.hh>
#include <seastar/core/coroutine.hh>
#include <seastar/core/sleep.hh>
#include <seastar/http/httpd.hh>
#include <seastar/http/function_handlers.hh>
#include <seastar/net/api.hh>

#include <iostream>

auto logger = seastar::logger("http_server");

using reply = std::unique_ptr<seastar::http::reply>;
using request = std::unique_ptr<seastar::http::request>;

using namespace std::chrono_literals;

seastar::future<> coroutine_main()
{
    namespace h = seastar::httpd;
    h::http_server_control server;

    co_await server.start();

    auto handle_main = new h::function_handler(
        [](h::const_req req) {
            logger.info("Hellow World!");
            return "Hello World";
        });


    auto handle_sleep = new h::function_handler(
        [](request req, reply rep)
        -> seastar::future<reply> {
            auto it = req->query_parameters.find("seconds");
            auto seconds = it != req->query_parameters.end() ? std::stoi(it->second) : 1;

            logger.info("Sleep for {} seconds", seconds);

            co_await seastar::sleep(seconds * 1s);

            rep->_content = fmt::format("Hellow World! Slept for {} seconds", seconds);

            logger.info("Done sleeping for {} seconds", seconds);

            co_return std::move(rep);
        }, "text/plain");


        co_await server.set_routes([&](auto &r){

            r.add(
                h::operation_type::GET,
                h::url("/"),
                handle_main
            );

            r.add(
                h::operation_type::GET,
                h::url("/sleep"),
                handle_sleep
            );
        });
    

    static std::atomic<bool> stop = false;
    seastar::condition_variable cv;

    seastar::handle_signal(SIGINT, [&] {
        stop.store(true);
        cv.broadcast();
    });

    co_await server.listen(
        seastar::ipv4_addr("0.0.0.0", 31337)
    );

    co_await cv.wait([&] { return stop.load(); });

    co_await server.stop();

    co_return;
}

int main(int argc, char ** argv)
{
    seastar::app_template app;

    seastar::global_logger_registry().set_all_loggers_level(seastar::log_level::debug);

    return app.run(argc, argv, coroutine_main);
}