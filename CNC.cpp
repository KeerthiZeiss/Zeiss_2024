#include <iostream>

using namespace std;

class CNCAlertConverter {
public:
    virtual void convertTemperatureAlert(double temperature) = 0;
    virtual void convertDimensionAlert(double variation) = 0;
    virtual void convertDurationAlert(int duration) = 0;
    virtual void convertSelfTestAlert(int statusCode) = 0;
};

class ConsoleAlertConverter : public CNCAlertConverter {
public:
    void convertTemperatureAlert(double temperature) override {
        cout << "Alert: Temperature around the CNC machine is too high. Current temperature: " << temperature << " degrees Celsius." << endl;
    }

    void convertDimensionAlert(double variation) override {
        cout << "Alert: Part-dimension variation in the CNC machine. Current variation: " << variation << " mm." << endl;
    }

    void convertDurationAlert(int duration) override {
        cout << "Alert: Continuous operation duration exceeds 6 hours. Current duration: " << duration << " minutes." << endl;
    }

    void convertSelfTestAlert(int statusCode) override {
        switch (statusCode) {
            case 0xFF:
                cout << "Self-Test: All OK." << endl;
                break;
            case 0x00:
                cout << "Self-Test: No data (examples: no power, no connection to the data-collector)." << endl;
                break;
            case 0x01:
                cout << "Self-Test: Controller board in the machine is not OK." << endl;
                break;
            case 0x02:
                cout << "Self-Test: Configuration data in the machine is corrupted." << endl;
                break;
            default:
                cout << "Self-Test: Unknown status code: 0x" << hex << statusCode << "." << endl;
        }
    }
};

class CNCData {
protected:
    int machineId;

public:
    CNCData(int machineId) : machineId(machineId) {}

    virtual void analyze(CNCAlertConverter& converter) = 0;
};

class TempEvent : public CNCData {
private:
    double temperature;

public:
    TempEvent(int machineId, double temperature) : CNCData(machineId), temperature(temperature) {}

    void analyze(CNCAlertConverter& converter) override {
        if (temperature > 35.0) {
            converter.convertTemperatureAlert(temperature);
        }
    }
};

class DimensionEvent : public CNCData {
private:
    double variation;

public:
    DimensionEvent(int machineId, double variation) : CNCData(machineId), variation(variation) {}

    void analyze(CNCAlertConverter& converter) override {
        if (variation > 0.05) {
            converter.convertDimensionAlert(variation);
        }
    }
};

class DurationEvent : public CNCData {
private:
    int duration;

public:
    DurationEvent(int machineId, int duration) : CNCData(machineId), duration(duration) {}

    void analyze(CNCAlertConverter& converter) override {
        if (duration > 360) {  // 6 hours in minutes
            converter.convertDurationAlert(duration);
        }
    }
};

class SelfTestEvent : public CNCData {
private:
    int statusCode;

public:
    SelfTestEvent(int machineId, int statusCode) : CNCData(machineId), statusCode(statusCode) {}

    void analyze(CNCAlertConverter& converter) override {
        if (statusCode != 0xFF) {
            converter.convertSelfTestAlert(statusCode);
        }
    }
};

int main() {
    ConsoleAlertConverter consoleAlertConverter;

    TempEvent tempAlert(1, 36.5);
    tempAlert.analyze(consoleAlertConverter);

    DimensionEvent dimensionAlert(2, 0.07);
    dimensionAlert.analyze(consoleAlertConverter);

    DurationEvent durationAlert(3, 400);
    durationAlert.analyze(consoleAlertConverter);

    SelfTestEvent selfTestAlert(4, 0x01);
    selfTestAlert.analyze(consoleAlertConverter);

    return 0;
}
