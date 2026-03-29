#!/usr/bin/env bash

echo 'sending dummy data to mqtt queue using TTN format'
docker exec -ti mosquitto mosquitto_pub -h mqtt -u admin -P password -t v3/demoTTN/devices/myDevice/up -m '{
  "app_id": "demoTTN",
  "dev_id": "myDevice",
  "hardware_serial": "0102030405060708",
  "port": 1,
  "counter": 1,
  "is_retry": false,
  "confirmed": false,
  "payload_raw": "AHMnSwFnARYCaFADAGQEAQAFAdc="
}'
