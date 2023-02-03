###############
bresser-to-mqtt
###############


*****
About
*****

A PlatformIO-compatible build environment for the excellent `BresserWeatherSensorReceiver`_.


*****
Usage
*****

Baseline::

    python3 -m venv .venv
    source .venv/bin/activate
    pip install platformio
    pio run

More targets::

    pio run --list-targets
    pio run --target clean
    pio run --target upload


.. _BresserWeatherSensorReceiver: https://github.com/matthias-bs/BresserWeatherSensorReceiver
