#pragma once
using namespace std;

void HandleResponseData(const vector<uint8_t>& data) {
  if (data.size() < 42) {
    if (data.size() >=2) {
      if (data[0] == 0x01 && data[1] == 0x06) {
        // write operations (0106...) have a shorter return value than we care about here
      }
      else {
        ESP_LOGW("mppt", "Received data too short: %d", data.size());
      }
    }
    return;
  }

  // Parse the data based on the format from your data streams
  // Example format: 0103260064008f05c900d31bff008f000200000321036804ba0000800400000003000017e000000000a884

  if (data[0] != 0x01 || data[1] != 0x03) {
    ESP_LOGW("mppt", "Invalid header");
    return;
  }

  // Extract values based on our understanding of the data format
  // Convert the raw bytes to actual values

  // Battery data
  uint16_t raw_batt_voltage = (data[5] << 8) | data[6];
  id(battery_voltage).publish_state(raw_batt_voltage * 0.1f);

  uint16_t raw_batt_current = (data[7] << 8) | data[8];
  id(battery_current).publish_state(raw_batt_current * 0.01f);

  uint16_t raw_batt_power = (data[9] << 8) | data[10];
  id(battery_power).publish_state(raw_batt_power);

  // Controller temperature
  id(controller_temp).publish_state(data[11]);

  // data[12] == 'ff' - spacer?
  
  // Load data (if enabled)
  uint16_t raw_load_voltage = (data[13] << 8) | data[14];
  id(load_voltage).publish_state(raw_load_voltage * 0.1f);

  uint16_t raw_load_current = (data[15] << 8) | data[16];
  id(load_current).publish_state(raw_load_current * 0.01f);

  uint16_t raw_load_power = (data[17] << 8) | data[18];
  id(load_power).publish_state(raw_load_power);

  // PV input
  uint16_t raw_pv_voltage = (data[19] << 8) | data[20];
  id(pv_voltage).publish_state(raw_pv_voltage * 0.1f);

  // Daily max power
  uint16_t raw_max_power = (data[21] << 8) | data[22];
  id(max_charge_power).publish_state(raw_max_power);

  // Energy charged today
  uint16_t raw_energy_today = (data[23] << 8) | data[24];
  id(energy_today).publish_state(raw_energy_today);

  // Controller mode
  //todo: convert
  // id(controller_mode).publish_state(data[26]);

  // Running days
  uint16_t raw_days = (data[31] << 8) | data[32];
  id(running_days).publish_state(raw_days);

  // Total energy charged
  uint16_t raw_total_energy = (data[35] << 8) | data[36];
  id(total_energy).publish_state(raw_total_energy);

  ESP_LOGI("mppt", "Data parsed successfully: Battery %.1fV, %.2fA, %dW",
          raw_batt_voltage * 0.1f, raw_batt_current * 0.1f, raw_batt_power);
}
