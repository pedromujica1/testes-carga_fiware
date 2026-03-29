#!/bin/bash

for i in {1..10}; do   curl -s -D- http://localhost:4041/iot/about -o /dev/null | awk -F': ' 'tolower($1)=="x-upstream"{print $2}'; done | sort | uniq -c

