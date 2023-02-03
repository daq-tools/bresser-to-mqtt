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

Acquire sources::

    git clone https://github.com/daq-tools/bresser-to-mqtt
    cd bresser-to-mqtt

Build firmware image::

    python3 -m venv .venv
    source .venv/bin/activate
    pip install --upgrade --requirement=requirements.txt
    pio run

More targets::

    pio run --list-targets
    pio run --target clean
    pio run --target upload


.. _BresserWeatherSensorReceiver: https://github.com/matthias-bs/BresserWeatherSensorReceiver
