#include "SmartHomeDevice.h"
#include <arduino.h>
#include <ESP8266WiFi.h>
#include <list>

using namespace SmartHomeDevice_n;

namespace EspSmartHome_n
{
    class EspSmartHome : public SmartHomeDevice
    {
    private:
        WiFiClient wifiClient;
        std::list<std::function<void(int)>> scanCallbacks;
    protected:
        std::string         getMacAddress() override;
        void                connectToWiFi(const std::string &ssid, const std::string &password) override;
        void                disconnectFromWiFi() override;
        void                scanForNetworks(std::function<void(int)> scanCallback) override;
        NetworkInfo         getInfoForNetwork(const byte &networkNumber) override;
        void                connectToServer(const std::string &host, const unsigned short &port) override;
        void                disconnectFromServer() override;
        bool                dataAvailable() override;
        bool                connectedToServer() override;
        std::string         readData() override;
        void                sendData(const std::string &textData) override;
        WifiStatus::Values  getWifiStatus() override;
        unsigned int        getCurrentTime() override;
        void                reset() override;
        void                debugPrint(const std::string &debugMessage) override;
    public:
        EspSmartHome(const std::string &deviceName, const WifiConfiguration &configuration);
        virtual ~EspSmartHome();

        void run() override;
    };
}
