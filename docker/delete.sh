#!/bin/bash
echo 'deleting device'

curl --location --request DELETE 'localhost:4041/iot/devices/myDevice' \
--header 'fiware-service: openiot' \
--header 'fiware-servicepath: /airQuality'