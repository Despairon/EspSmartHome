#include "EspSmartHome.h"

namespace EspSmartHome_n
{
    EspSmartHome::EspSmartHome(const std::string &deviceName, const WifiConfiguration &configuration) : SmartHomeDevice(deviceName, configuration)
    {
        // TODO: not implemented  
    }
    
    EspSmartHome::~EspSmartHome()
    {
        // TODO: not implemented
    }

    void EspSmartHome::connectToWiFi(const std::string &ssid, const std::string &password)
    {
      
    }
    
    void EspSmartHome::disconnectFromWiFi()
    {
      
    }
    
    void EspSmartHome::scanForNetworks(std::function<void(int)> scanCallback)
    {
        // TODO: not implemented
    }
    
    NetworkInfo EspSmartHome::getInfoForNetwork(const byte &networkNumber)
    {
        // TODO: not implemented
    }
    
    void EspSmartHome::connectToServer(const std::string &host, const unsigned short &port)
    {
        // TODO: not implemented
    }
    
    void EspSmartHome::disconnectFromServer()
    {
        // TODO: not implemented
    }
    
    bool EspSmartHome::dataAvailable()
    {
        // TODO: not implemented
    }
    
    bool EspSmartHome::connectedToServer()
    {
        // TODO: not implemented
    }
    
    std::string EspSmartHome::readData()
    {
        // TODO: not implemented
    }
    
    void EspSmartHome::sendData(const std::string &textData)
    {
        // TODO: not implemented
    }
    
    WifiStatus::Values EspSmartHome::getWifiStatus()
    {
        // TODO: not implemented
    }
    
    unsigned int EspSmartHome::getCurrentTime()
    {
        // TODO: not implemented
    }
    
    void EspSmartHome::reset()
    {
        // TODO: not implemented
    }
    
    void EspSmartHome::debugPrint(const std::string &debugMessage)
    {
        // TODO: not implemented
    }
    
}
