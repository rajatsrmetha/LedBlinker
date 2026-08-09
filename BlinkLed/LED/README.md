# LED Deployment

**Author:** Rajat Metha

**Email:** [rajatsrmetha@gmail.com](mailto:rajatsrmetha@gmail.com)

`LED` is the runnable Linux deployment for LedBlinker. It connects `LedCmpInstance` to the standard F´ command, event, telemetry, communication, file-handling, and data-product services, and connects its GPIO output to `Drv.LinuxGpioDriver`.

For a project overview, see the [project README](../../README.md). For requirements and design, see the [Led component SDD](../Components/Led/docs/sdd.md).

## Hardware configuration

The deployment opens GPIO line 13 on `/dev/gpiochip4` as an output. Confirm that this chip and line match the target board and that the user running the application has permission to access the GPIO device. If initialization fails, the application logs `Failed to open GPIO pin`.

## Build

Initialize the submodule if necessary, activate the project environment, and build from the project root:

```bash
git submodule update --init --recursive
source fprime-venv/bin/activate
fprime-util generate
fprime-util build
```

## Run with the GDS

From this directory, run:

```bash
fprime-gds
```

This starts both the GDS and the `LED` application. In the GDS, send `BlinkLed.LedCmpInstance.BLINKING_ON_OFF` with `ON` to start blinking or `OFF` to stop it. Use the parameter interface to update `BlinkLed.LedCmpInstance.BLINK_INTERVAL`; the value is measured in 1 Hz rate-group ticks and must be greater than zero for blinking to occur.

## Run separately

Start only the GDS:

```bash
fprime-gds --no-app
```

Then start the application from the project root using the host and port displayed by the GDS:

```bash
./build-fprime-automatic-native/bin/LED -a 127.0.0.1 -p 50000
```

Both `-a` and `-p` are required for a GDS connection. Use `-h` to display command-line help.

## Runtime design

- A TCP client connects the application to the GDS.
- A 1 Hz Linux timer drives rate groups running at 1 Hz, 1/2 Hz, and 1/4 Hz.
- `LedCmpInstance` runs in the 1 Hz rate group.
- `CdhCore` handles commands, events, telemetry, and health monitoring.
- `ComCcsds` handles CCSDS uplink and downlink data.
- `FileHandling` provides file transfer and parameter storage.
- `DataProducts` provides data-product storage services.
- `Svc.CmdSequencer` runs stored command sequences.

Press `Ctrl-C` to stop the deployment cleanly.

## Unit tests

Run the component tests from the project root:

```bash
fprime-util check
```

The current test verifies that the LED remains off and produces no transition output while blinking is disabled.
