#!/bin/bash

while true
do
	docker-compose up --build
	sleep 5m
	docker-compose down
done
