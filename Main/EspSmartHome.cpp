#include "EspSmartHome.h"

namespace EspSmartHome_n
{
    EspSmartHome::EspSmartHome(const std::string &deviceName, const WifiConfiguration &configuration) : SmartHomeDevice(deviceName, configuration)
    {
        Serial.begin(115200); 
        WiFi.mode(WIFI_STA);
    }
    
    EspSmartHome::~EspSmartHome()
    {
        disconnectFromServer();
        disconnectFromWiFi();
    }

    std::string EspSmartHome::getMacAddress()
    {
        return std::string(WiFi.macAddress().c_str());
    }

    void EspSmartHome::connectToWiFi(const std::string &ssid, const std::string &password)
    {
        WiFi.begin(ssid.c_str(), password.c_str());
    }
    
    void EspSmartHome::disconnectFromWiFi()
    {
        WiFi.disconnect();
        delay(100);
    }
    
    void EspSmartHome::scanForNetworks(std::function<void(int)> scanCallback)
    {
          scanCallbacks.push_back(scanCallback);
          
          WiFi.disconnect();
          WiFi.scanNetworks(true);
    }
    
    NetworkInfo EspSmartHome::getInfoForNetwork(const byte &networkNumber)
    {
        NetworkInfo netInfo;
        memset(&netInfo, 0, sizeof(netInfo));
        
        strcpy(netInfo.ssid, WiFi.SSID(networkNumber).c_str());
        netInfo.channel = WiFi.channel(networkNumber);
        netInfo.rssi    = WiFi.RSSI(networkNumber);
        netInfo.isOpen  = WiFi.encryptionType(networkNumber) == ENC_TYPE_NONE;
    }
    
    void EspSmartHome::connectToServer(const std::string &host, const unsigned short &port)
    {
        wifiClient.connect(host.c_str(), port);
    }
    
    void EspSmartHome::disconnectFromServer()
    {
        wifiClient.stop();
    }
    
    bool EspSmartHome::dataAvailable()
    {
        return wifiClient.available();
    }
    
    bool EspSmartHome::connectedToServer()
    {
        return wifiClient.connected();
    }
    
    std::string EspSmartHome::readData()
    {
        std::string dataStr;
        
        while (wifiClient.connected() || wifiClient.available())
        {
            if (wifiClient.available())
            {
                String line = wifiClient.readStringUntil('\n');
                dataStr += std::string(line.c_str()) + "\n";
            }
        }

        return dataStr;
    }
    
    void EspSmartHome::sendData(const std::string &textData)
    {
        wifiClient.print(textData.c_str());
    }
    
    WifiStatus::Values EspSmartHome::getWifiStatus()
    {
        switch(WiFi.status())
        {   
            case WL_IDLE_STATUS     : return WifiStatus::IDLE;
            case WL_NO_SSID_AVAIL   : return WifiStatus::NO_SSID_AVAILABLE;
            case WL_SCAN_COMPLETED  : return WifiStatus::SCAN_COMPLETED;
            case WL_CONNECTED       : return WifiStatus::CONNECTED;
            case WL_CONNECT_FAILED  : return WifiStatus::CONNECT_FAILED;
            case WL_CONNECTION_LOST : return WifiStatus::CONNECTION_LOST;
            case WL_DISCONNECTED    : return WifiStatus::DISCONNECTED;

            default                 : return static_cast<WifiStatus::Values>(-1);
        }
    }
    
    unsigned int EspSmartHome::getCurrentTime()
    {
        return millis();
    }
    
    void EspSmartHome::reset()
    {
        static void(*resetFunc)(void) = 0;
        resetFunc();
    }
    
    void EspSmartHome::debugPrint(const std::string &debugMessage)
    {
        Serial.print(debugMessage.c_str());
    }

    void EspSmartHome::run()
    {
        enum WifiScanStatus
        {
            WIFI_SCAN_IDLE = -2,
            WIFI_SCAN_IN_PROGRESS = -1
        };

        static WifiScanStatus scanStatus = WIFI_SCAN_IDLE;
        
        WifiScanStatus newScanStatus = static_cast<WifiScanStatus>(WiFi.scanComplete());

        if (scanStatus != newScanStatus)
        {
            if ( (newScanStatus != WIFI_SCAN_IN_PROGRESS) && (newScanStatus != WIFI_SCAN_IDLE) && (scanStatus >= 0) )
            {
                for (auto scanCallback : scanCallbacks)
                    if (scanCallback != nullptr)
                        scanCallback(static_cast<int>(newScanStatus));
              
                WiFi.scanDelete();

                scanCallbacks.clear();
            }

            scanStatus = newScanStatus;
        }

        SmartHomeDevice::run();
    }
}
