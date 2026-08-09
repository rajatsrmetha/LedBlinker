# LedBlinker

**Author:** Rajat Metha

**Email:** [rajatsrmetha@gmail.com](mailto:rajatsrmetha@gmail.com)

LedBlinker is an LED-control application built with [F´ (F Prime)](https://fprime.jpl.nasa.gov/) 4.2.2. It demonstrates command, event, telemetry, parameter, rate-group, and Linux GPIO integration in a custom F´ component.

## What it does

The `Led` component accepts the `BLINKING_ON_OFF` command from the F´ Ground Data System (GDS):

- `ON` enables periodic LED toggling.
- `OFF` disables blinking and drives an illuminated LED low on the next scheduled cycle.

The `BLINK_INTERVAL` parameter controls the number of 1 Hz rate-group ticks between transitions. The component reports the requested blinking state and interval as events, emits an event for every LED transition, and publishes the configured blinking state and total transition count as telemetry.

The Linux deployment drives GPIO line 13 on `/dev/gpiochip4`.

## F´ modules used

The project uses standard F´ modules together with the custom `Led` component:

- `CdhCore` handles commands, events, telemetry, and health monitoring.
- `ComCcsds` provides CCSDS communication with the GDS.
- `FileHandling` provides file transfer and parameter storage.
- `DataProducts` provides data-product storage services.
- `Svc.CmdSequencer` runs stored command sequences.
- `Drv.TcpClient` connects the application to the GDS.
- `Drv.LinuxGpioDriver` controls the physical GPIO line.
- F´ rate groups schedule the component and framework services.

## Project structure

| Path | Description |
|---|---|
| `BlinkLed/Components/Led` | LED control component and unit tests |
| `BlinkLed/Components/Led/docs/sdd.md` | Component requirements and design |
| `BlinkLed/LED` | Runnable Linux deployment |
| `BlinkLed/LED/Top` | Component instances, connections, and GPIO setup |
| `lib/fprime` | F´ framework submodule |

See the [Led component SDD](BlinkLed/Components/Led/docs/sdd.md) for component details. Build, run, and GDS usage instructions are in the [LED deployment README](BlinkLed/LED/README.md).
