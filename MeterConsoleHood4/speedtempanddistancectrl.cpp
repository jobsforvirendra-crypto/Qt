#include "speedtempanddistancectrl.h"
#include <QDebug>
constexpr int MILAGE{36};
SpeedTempAndDistanceCtrl::SpeedTempAndDistanceCtrl(QObject *parent)
    : QObject{parent},
      m_timer{new QTimer(this)},
      m_speed{0},
      m_fuel{100},
      m_distanceTraveled{0},
      m_temperature{0},
      m_holding{false},
      m_distanceForFuelConsumption{0},
      m_distanceForTemp{0},
      m_state{State::ACCELERATION_RELEASED},
      m_onMaxTemp{false},
      m_durationCountAfterMaxTemp{0},
      m_isOverHeating{false}
{
    m_timer->setSingleShot(false);
    connect(m_timer,&QTimer::timeout,this,[this](){
        if(m_fuel == 0)
            setState(State::FUEL_FINISHED);
        switch (m_state)
        {
        case State::ACCELERATION_PRESSED:
            getFuelleft(m_speed);
            getTemperature(m_speed);
            if(m_speed <150 )
                ++m_speed;
            break;
        case State::ACCELERATION_RELEASED:
            if(m_speed >0)
            {
                getFuelleft(m_speed);
                coolDown(m_speed);
                --m_speed;
            }
            break;
        case State::FUEL_FINISHED:
            if(m_speed > 0)
            {
               // getFuelleft(m_speed);
                m_speed -= 10;
            }
            coolDown(m_speed);
            break;
        case State::OVERHEATED:
            if(m_speed > 0)
            {
               // getFuelleft(m_speed);
                m_speed -= 20;
               // qDebug()<<"Over heating ";
                if(m_speed<0)
                {
                    m_speed=0;
                }
            }
            if(m_speed == 0)
                coolDown(m_speed);

        }
        //set speed to zero incase it is negative
        if(m_speed < 0)
            m_speed =0;
        emit speedChanged();
    });
}

int SpeedTempAndDistanceCtrl::speed() const
{
    return m_speed;
}

int SpeedTempAndDistanceCtrl::fuel() const
{
    return m_fuel;
}

float SpeedTempAndDistanceCtrl::distanceTraveled() const
{
    return m_distanceTraveled;
}

float SpeedTempAndDistanceCtrl::temperature() const
{
    return m_temperature;
}

bool SpeedTempAndDistanceCtrl::holding() const
{
    return m_holding;
}

void SpeedTempAndDistanceCtrl::setState(State state)
{
    m_state = state;
}

SpeedTempAndDistanceCtrl::State SpeedTempAndDistanceCtrl::getState() const
{
    return m_state;
}

void SpeedTempAndDistanceCtrl::startAcceleration()
{
    if(m_holding)
        return;
    m_holding = true;
    setState(State::ACCELERATION_PRESSED);
    emit holdingChanged();
    m_timer->setInterval(150);
    m_timer->start();
}

void SpeedTempAndDistanceCtrl::stopAcceleration()
{
    if(!m_holding)
        return;

    m_holding = false;
    setState(State::ACCELERATION_RELEASED);
    emit holdingChanged();
    m_timer->setInterval(300);
    // m_timer->stop();
}

void SpeedTempAndDistanceCtrl::getFuelleft(int speed)
{
    constexpr float intervalSeconds = 0.150f;
    constexpr float secondsInHour = 3600.0f;
    //this coming speed will be last for 150 miliseconds distance traveled in that duration
   // float currentDistance = speed *(intervalSeconds/secondsInHour);
    float currentDistance = speed * 0.150;
    m_distanceTraveled += currentDistance;
    m_distanceForFuelConsumption += currentDistance;
//    qDebug()<<"distance: "<<m_distanceTraveled;
    while(m_distanceForFuelConsumption >= MILAGE)
    {
        if(m_fuel >0)
        --m_fuel;
        if(m_fuel<=0)
            setState(State::FUEL_FINISHED);
        m_distanceForFuelConsumption -= MILAGE;
        emit fuelChanged();

    }
//    qDebug() << "Total Distance:" << m_distanceTraveled;
//    qDebug() << "Fuel:" << m_fuel;
}

void SpeedTempAndDistanceCtrl::getTemperature(int speed)
{
    constexpr float intervalSeconds = 0.150f;
    constexpr float secondsInHour = 3600.0f;
    constexpr int avrageDistanceToRaiseTemp = 10;
    constexpr int timeAllowedONMaxTemp = 100;
    //this coming speed will be last for 150 miliseconds distance traveled in that duration
   // float currentDistance = speed *(intervalSeconds/secondsInHour);
    float currentDistance = speed * 0.150;
    m_distanceTraveled += currentDistance;
    m_distanceForTemp += currentDistance;
    while(m_distanceForTemp >= avrageDistanceToRaiseTemp)
    {
        if(m_temperature <125)
            m_temperature++;
        else
        {
            m_onMaxTemp = true;
            m_durationCountAfterMaxTemp += 15.0;
            if(m_durationCountAfterMaxTemp>= timeAllowedONMaxTemp)
            {
                setState(State::OVERHEATED);
                m_isOverHeating = true;
                emit isOverHeatingChanged();
            }
        }
        emit temperatureChanged();
        m_distanceForTemp -= avrageDistanceToRaiseTemp;
    }
}

void SpeedTempAndDistanceCtrl::coolDown(int speed)
{
    constexpr int dipInTempAtzeroSpeed = 10;
    if(speed > 0)
    {
        if(m_temperature>=0)
        {
            m_temperature -= 1 ;
            if(m_temperature < 0)
                m_temperature=0;
        }
    }
    else
        if(m_temperature>=0 && m_temperature > dipInTempAtzeroSpeed )
            m_temperature -=10 ;
        else
           m_temperature = 0;

    if(m_temperature < 50)
    {
        m_isOverHeating = false;
        emit isOverHeatingChanged();
    }
    emit temperatureChanged();
}

void SpeedTempAndDistanceCtrl::setFuel(int newFuel)
{
    if (m_fuel == newFuel)
        return;

    m_fuel = newFuel;
    if(m_fuel > 100)
        m_fuel = 100;
    emit fuelChanged();
}

bool SpeedTempAndDistanceCtrl::isOverHeating() const
{
    return m_isOverHeating;
}
