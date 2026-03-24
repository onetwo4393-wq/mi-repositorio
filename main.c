#include <esp_log.h>
#include <esp_gap_ble_api.h>

void app_main() {
  // Configura la plataforma BLE
  esp_err_t err;
  err = esp_gap_ble_adv_params_init();
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Error iniciando plataforma BLE: %d", err);
    return;
  }

  // Simulación de conexión inestable
  for (int i = 0; i < 10; i++) {
    char uuid[18];
    sprintf(uuid, "%08x", i); // UUID incorrecto

    err = esp_gap_ble_set_advertise_data(uuid);
    if (err != ESP_OK) {
      ESP_LOGE(TAG, "Error enviando paquete de advertencia: %d", err);
    }
  }

  // Manipulación de la tasa de transmisión
  esp_gap_ble_adv_params_t adv_params = {
    .adv_type = ADV_TYPE_IND,
    .own_addr_type = LE_PUBLIC_ADDRESS,
    .primary_phy = PHY_CODE_1M,
    .secondary_phy = 0x00,
    .min_interval = 100, // Tasa de transmisión alta
    .max_interval = 500
  };

  err = esp_gap_ble_set_advertise_params(&adv_params);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Error configurando parámetros de advertencia: %d", err);
  }
}
