# Air Quality Monitoring System

## Overview

This repository contains a C program for monitoring and analyzing real-time air quality data using the OpenWeatherMap API. The program fetches air quality information, stores it in JSON and text files, performs comparisons against predefined ranges, generates reports, and sends real-time email alerts for anomalies. The system utilizes popular C libraries such as libcurl for API requests and cJSON for JSON parsing.

## Features

- *Data Retrieval:* Fetches real-time air quality data from the OpenWeatherMap API.
- *Data Storage:* Saves fetched data in JSON (output.json) and text (output.txt) files.
- *Data Process and Analysis:* Compares air quality components (SO2, NO, O3) against specified ranges.
- *Optimization and Effeciency:* Utilize the dynamic memory allocation in C program to optimize data mnipulation and ehance effeciency.
- *Reporting System:* Generates a report (air_currentdata.txt) with computed results and additional information.
- *Anomaly Detection:* Checks for anomalies and creates an anomaly.txt file with safety measures if detected.
- *Real-time Alerts:* Sends email alerts using Mutt for detected anomalies
   
## Dependencies

- *libcurl:* Used for making HTTP requests to the OpenWeatherMap API.
- *cJSON:* A lightweight JSON parser for handling JSON data.
- *Mutt:* A simple and powerful text-based mail client for sending real-time email alerts.

## Configuration

- Open main.c and update the OpenWeatherMap API URL with your own latitude, longitude, and API key.

## Usage

- Run the compiled program to fetch and analyze real-time air quality data.
- Check the generated files (output.json, output.txt, air_currentdata.txt, anomaly.txt) for historical records and reports.
- Receive real-time email alerts for anomalies.

## Acknowledgments

- Thanks to the creators of libcurl and cJSON for providing powerful libraries.
- Inspired by the need for a simple yet effective air quality monitoring solution.

Feel free to contribute, report issues, or suggest improvements!
