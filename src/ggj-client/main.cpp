#include "../galder-game-jam-library/GalderGameJamLibrary.h"
#include "di.hpp"
#include "fmt/color.h"
#include "raylib-cpp.hpp"
#include <stdio.h>

auto buildInjectorForNetworking(ggj::ILogger &logger)
{
    auto injector = boost::di::make_injector(
            boost::di::bind<ggj::IIpAddressResolver>().to<ggj::IpAddressResolver>(),
            boost::di::bind<ggj::IExecutableInfo>().to<ggj::ExecutableInfo>(),
            boost::di::bind<ggj::IServer<ggj::ServerNetworkData, ggj::PlayerNetworkData>>().to<ggj::GalderServer>(),
            boost::di::bind<ggj::IClient<ggj::PlayerNetworkData, ggj::ServerNetworkData>>().to<ggj::GalderClient>(),
            boost::di::bind<ggj::ILogger>().to(logger)
    );
    
    return injector;
}

struct App
{
    ggj::ILogger &logger;
    ggj::IExecutableInfo &executableInfo;
    ggj::IIpAddressResolver &ipResolver;
    ggj::IClient<ggj::PlayerNetworkData, ggj::ServerNetworkData> &client;
    ggj::IServer<ggj::ServerNetworkData, ggj::PlayerNetworkData> &server;
    
    bool initialize()
    {
        return true;
    }
};

int testNetworking()
{
    ggj::ConsoleLogger l = ggj::ConsoleLogger(ggj::LogLevel::Debug);
    
    //Handle dependency injection
    auto injector = buildInjectorForNetworking(l);
    App app = injector.create<App>();
    ggj::ILogger &logger = app.logger;
    
    //logger.information(fmt::format("Content path: {0}", app.executableInfo.getContentRootDirectory().string()));
    //Initialize everything
    if(!app.initialize())
        app.logger.critical("App initialization failed!");
    
    app.client.initialize();
    app.client.connect(13337, "127.0.0.1");
    
    return 0;
}

int main(int argc, char **argv)
{
    int result = testNetworking();
    return result;
}

