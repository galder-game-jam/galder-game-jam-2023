//
// Created by robin on 04.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_GALDERCLIENT_HPP
#define GALDER_GAME_JAM_2023_PROJECT_GALDERCLIENT_HPP

#include "../../gamedev-base/GameDevBase.h"
#include "../data/PlayerNetworkData.hpp"
#include "../data/ServerNetworkData.hpp"

namespace ggj
{
    
    class GalderClient : public ggj::Client<PlayerNetworkData, ServerNetworkData>
    {
        public:
            GalderClient(ILogger &logger, IIpAddressResolver &ipAddressResolver) :
                    ggj::Client<PlayerNetworkData, ServerNetworkData>(logger, ipAddressResolver)
            {
            
            }
        
        protected:
            void clientProgram() override
            {
                //pollIncomingMessages();
                pollSpecialServerMessages();
                pollConnectionStateChanges();
                pollLocalUserInput();
                sendMessageToServerNowAndThen();
                std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
            }
            
            void sendMessageToServerNowAndThen()
            {
                if(m_messageSendCounter >= m_messageSendTrigger)
                {
                    m_messageSendCounter = 0;
                    sendMessageToServer();
                }
                ++m_messageSendCounter;
            }
            
            void sendMessageToServer()
            {
                PlayerNetworkData data
                {
                    true,
                    raylib::Vector2(1337, 1337),
                    1,
                    2,
                    3
                };
                
                if(!send(data))
                    m_logger.error("Tried to send message to server, but it went to hell!");
                else
                    m_logger.information("Message sent to server!");
            }
            
            void pollSpecialServerMessages()
            {
                while (!m_quit)
                {
                    ServerNetworkData data = receive();
                    if(data.isValid)
                    {
                        m_logger.warning(fmt::format("Server sez: {0}", data.message));
                    }
                }
            }
            
        private:
            uint32_t m_messageSendCounter {0};
            uint32_t m_messageSendTrigger {100};
    };
    
} // ggj

#endif //GALDER_GAME_JAM_2023_PROJECT_GALDERCLIENT_HPP
