#include "TutorialServo.h"
#include "mbed.h"

TutorialServo::TutorialServo(PinName servoPin, float servoRangeInDegrees, float minPulsewidthInMs, float maxPulsewidthInMs) :
    m_servoPwmOut(servoPin), 
    m_servoRangeInDegrees(servoRangeInDegrees),
    m_minPulsewidthInMs(minPulsewidthInMs),
    m_maxPulsewidthInMs(maxPulsewidthInMs)
    { m_servoPwmOut.period_ms(20); }

void TutorialServo::setPositionInDegrees(const float degrees) {
    m_servoPwmOut.pulsewidth((1 + degrees/this->m_servoRangeInDegrees) / 1000);
}

float TutorialServo::getServoRangeInDegrees() const {
    return m_servoRangeInDegrees;
}

float TutorialServo::getMinPulseWidthInMs() const{
    return m_minPulsewidthInMs;
}

float TutorialServo::getMaxPulseWidthInMs() const {
    return m_maxPulsewidthInMs;
}