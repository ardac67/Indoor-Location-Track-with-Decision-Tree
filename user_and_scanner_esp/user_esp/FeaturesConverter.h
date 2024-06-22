
#pragma once

namespace eloq {
  const static String id = "1";
    namespace rtls {
        class FeaturesConverter {
        public:
            float features[10];
            FeaturesConverter(Eloquent::RTLS::Scanner& scanner,WiFiClient* client) :
                _scanner(&scanner),
                _verbose(false),
                 _client(client) {
                memset(features, 0, 10);
            }
            void verbose(bool enabled = true) {
                _verbose = enabled;
            }
            String predict() {
                memset(features, 0, 10);
                _scanner->scan();

                /* build features */
                while (_scanner->hasNext()) {
                    _scanner->next();

                    if (!_scanner->isValid())
                        continue;

                    String identifier = _scanner->identifier();
                    const int16_t rssi = _scanner->rssi();

                    if (identifier == "A1") features[0] = rssi;
                    if (identifier == "A2") features[1] = rssi;
                    if (identifier == "A3") features[2] = rssi;
                    if (identifier == "A4") features[3] = rssi;
                    if (identifier == "A5") features[4] = rssi;
                    if (identifier == "A6") features[5] = rssi;
                    if (identifier == "A7") features[6] = rssi;
                    if (identifier == "A8") features[7] = rssi;
                    if (identifier == "B1") features[8] = rssi;
                    if (identifier == "B2") features[9] = rssi;
                    
                }

                dump();

              return "AA";
            }


        void dump() {
                if (!_verbose)
                    return;
                StaticJsonDocument<256> doc;
                doc["requestType"] = "RSSI";
                doc["id"] = id;
                JsonArray data = doc.createNestedArray("RSSI");
                for(int i = 0 ; i < 10 ;i++){
                 data.add(features[i]);
                }

                String serJson;
                serializeJson(doc, serJson);
                _client->print(serJson);
            }

        protected:
            bool _verbose;
            Eloquent::RTLS::Scanner *_scanner;
            WiFiClient * _client;
        };
    }
}
