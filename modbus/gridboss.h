#pragma once

void sync_smart_loads() {
    if (id(smartLoadOnOff).has_state() && id(smartLoadExtraSettings).has_state()) {
        uint16_t oo = id(smartLoadOnOff).state;
        uint16_t es = id(smartLoadExtraSettings).state;
        ESP_LOGD("smart_loads", "smartLoadOnOff has state: 0x%04X, smartLoadExtraSettings: 0x%04X", oo, es);
        id(smartLoad1On).publish_state((oo & 0x0003) == 0x0001 && (es & 0x0011) == 0x0011);
        id(smartLoad2On).publish_state((oo & 0x000C) == 0x0004 && (es & 0x0022) == 0x0022);
        id(smartLoad3On).publish_state((oo & 0x0030) == 0x0010 && (es & 0x0044) == 0x0044);
        id(smartLoad4On).publish_state((oo & 0x00C0) == 0x0040 && (es & 0x0088) == 0x0088);
    }
}

void set_bits(esphome::number::Number *num, uint16_t mask, uint16_t value) {
    if (id(smartLoadOnOff).has_state() && id(smartLoadExtraSettings).has_state()) {
        uint16_t state = num->state;
        uint16_t desired = state & ~mask | value;
        ESP_LOGD("smart_loads", "%s has state: 0x%04X, wanted: 0x%04X", num->get_name(), state, desired);
        if (state != desired) {
            ESP_LOGI("smart_loads", "Updating state of %s to: 0x%04X", num->get_name(), desired);
            auto call = num->make_call();
            call.set_value(desired);
            call.perform();
        }
    }
}
