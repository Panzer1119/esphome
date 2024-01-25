#pragma once

#include "esphome/core/log.h"
#include "esphome/core/automation.h"
#include "ikea_ansluta.h"

namespace esphome {
namespace ikea_ansluta {

class OnRemoteClickTrigger : public Trigger<uint16_t, uint8_t> {
 public:
  OnRemoteClickTrigger(IkeaAnsluta *parent) {
    parent->add_on_remote_click_callback(
        [this](uint16_t address, uint8_t command) {
          if (this->debounce_.has_value() && millis() < (this->last_trigger_ + this->debounce_.value())) {
            return;
          }

          if (!this->address_.has_value() || address == this->address_.value()) {
            this->trigger(address, command);
            this->last_trigger_ = millis();
          }
        });
  }
  void set_address(uint16_t address) { this->address_ = address; }
  void set_debounce(uint16_t delay) { this->debounce_ = delay; }
 protected:
  optional<uint16_t> address_{};
  optional<uint16_t> debounce_{};
  uint32_t last_trigger_{0};
};

}  // namespace ikea_ansluta
}  // namespace esphome
