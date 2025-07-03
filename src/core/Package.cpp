#include "Package.h"
#include <ctime>
#include <stdexcept>

Package::Package(const std::string& trackingNumber, 
                 const std::string& ownerPhone,
                 const std::string& shelfNumber,
                 bool isUrgent)
    : trackingNumber(trackingNumber),
      ownerPhone(ownerPhone),
      shelfNumber(shelfNumber),
      urgent(isUrgent),
      arrivalTime(std::time(nullptr)),
      pickupTime(0) {
    if (trackingNumber.empty() || ownerPhone.empty()) {
        throw std::invalid_argument("Tracking number and owner phone cannot be empty");
    }
}

std::string Package::getTrackingNumber() const { return trackingNumber; }
std::string Package::getOwnerPhone() const { return ownerPhone; }
std::string Package::getShelfNumber() const { return shelfNumber; }
bool Package::isUrgent() const { return urgent; }
time_t Package::getArrivalTime() const { return arrivalTime; }
time_t Package::getPickupTime() const { return pickupTime; }

void Package::setShelfNumber(const std::string& newShelfNumber) {
    shelfNumber = newShelfNumber;
}

void Package::setUrgent(bool urgent) {
    this->urgent = urgent;
}

void Package::setPickupTime(time_t time) {
    pickupTime = time;
}

bool Package::operator<(const Package& other) const {
    return trackingNumber < other.trackingNumber;
}

bool Package::operator==(const Package& other) const {
    return trackingNumber == other.trackingNumber;
}