#!/bin/bash

docker inspect -f '{{.Name}} -> {{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' docker-iotagent-lora1-1 docker-iotagent-lora2-1 docker-iotagent-lora3-1
