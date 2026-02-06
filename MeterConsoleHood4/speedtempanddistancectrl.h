#ifndef SPEEDTEMPANDDISTANCECTRL_H
#define SPEEDTEMPANDDISTANCECTRL_H

#include <QObject>
#include <QTimer>

class SpeedTempAndDistanceCtrl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(int fuel READ fuel WRITE setFuel  NOTIFY fuelChanged)
    Q_PROPERTY(float distanceTraveled READ distanceTraveled NOTIFY distanceTraveledChanged)
    Q_PROPERTY(float temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(bool holding READ holding NOTIFY holdingChanged)
    Q_PROPERTY(bool isOverHeating READ isOverHeating  NOTIFY isOverHeatingChanged)

public:
    enum class State
    {
        FUEL_FINISHED,
        ACCELERATION_PRESSED,
        ACCELERATION_RELEASED,
        OVERHEATED
    };
    explicit SpeedTempAndDistanceCtrl(QObject *parent = nullptr);

    int speed() const;

    int fuel() const;

    float distanceTraveled() const;

    float temperature() const;

    bool holding() const;
    void setState(State state);
    State getState() const;

    Q_INVOKABLE void startAcceleration();
    Q_INVOKABLE void stopAcceleration();


    void setFuel(int newFuel);

    bool isOverHeating() const;

signals:
    void speedChanged();

    void fuelChanged();

    void distanceTraveledChanged();

    void temperatureChanged();

    void holdingChanged();

    void isOverHeatingChanged();

private:
    void getFuelleft(int speed);
    void getTemperature(int speed);
    void coolDown(int speed);
    QTimer* m_timer;

    int m_speed;
    int m_fuel;
    float m_distanceTraveled;
    float m_temperature;
    bool m_holding;
    int m_distanceForFuelConsumption;
    int m_distanceForTemp;
    State m_state;
    bool m_onMaxTemp;
    int m_durationCountAfterMaxTemp;
    bool m_isOverHeating;
};

#endif // SPEEDTEMPANDDISTANCECTRL_H
