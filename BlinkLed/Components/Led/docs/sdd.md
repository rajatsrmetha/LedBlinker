# Led Component — Software Design Description

**Author:** Rajat Metha

**Email:** [rajatsrmetha@gmail.com](mailto:rajatsrmetha@gmail.com)

## Purpose

The `BlinkLed::Led` active component controls a GPIO-connected LED from an F´ command. It periodically toggles the output from a scheduler port, exposes the interval as a parameter, and reports its behavior through events and telemetry.

## Requirements

| ID | Requirement |
|---|---|
| LED-001 | Provide an asynchronous `BLINKING_ON_OFF` command that enables or disables blinking. |
| LED-002 | Report each accepted blinking-state command through `SetBlinkingState`. |
| LED-003 | Publish the commanded state through `BlinkingState` telemetry. |
| LED-004 | Toggle the GPIO output after the configured number of scheduler ticks while blinking is enabled. |
| LED-005 | Configure the transition interval through the `BLINK_INTERVAL` parameter, with a default of one tick. |
| LED-006 | Report parameter updates through `BlinkIntervalSet`. |
| LED-007 | Count output state transitions since component construction and publish the count through `BlinkTransitions`. |
| LED-008 | Report each logical LED transition through `LedState`. |
| LED-009 | Drive an illuminated LED low and set its logical state to `OFF` after blinking is disabled. |
| LED-010 | Return an `OK` response after processing `BLINKING_ON_OFF`. |

## Interfaces

| Type | Name | Details |
|---|---|---|
| Command | `BLINKING_ON_OFF` | Asynchronous; accepts `Fw.On` |
| Parameter | `BLINK_INTERVAL` | `U32`; defaults to 1 scheduler tick |
| Event | `SetBlinkingState` | `ACTIVITY_HI`; reports the commanded state |
| Event | `BlinkIntervalSet` | `ACTIVITY_HI`; reports a new interval |
| Event | `LedState` | `ACTIVITY_LO`; reports each logical transition |
| Telemetry | `BlinkingState` | `Fw.On`; last commanded blinking state |
| Telemetry | `BlinkTransitions` | `U64`; transitions since startup |
| Input port | `run` | Asynchronous `Svc.Sched` input that advances blinking |
| Output port | `gpioSet` | `Drv.GpioWrite` output that drives the LED |

The component also imports the standard F´ command, event, telemetry, time, and parameter interfaces.

## Design

`Led` stores four pieces of runtime state: the logical LED state, total transition count, tick counter, and whether blinking is enabled.

```text
BLINKING_ON_OFF
       |
       v
Reset tick counter -> update blinking flag
       |
       v
Emit event + telemetry -> return OK

1 Hz run input
       |
       +-- blinking enabled and interval > 0
       |       |
       |       +-- counter is zero -> toggle GPIO, count and report transition
       |       +-- advance counter modulo interval
       |
       +-- blinking disabled -> drive an ON LED low and record OFF state
```

The GPIO output is checked for a connection before it is invoked. With an interval of `N`, transitions occur every `N` calls to `run`; the first transition occurs on the first call after blinking is enabled. An interval of zero suppresses transitions.

The deployed component instance has a queue size of 10, a 64 KiB stack, priority 50, and base ID `0x10006000`. It is scheduled by the 1 Hz rate group. The Linux GPIO driver opens line 13 on `/dev/gpiochip4` as an output.

## Validation

The `Nominal.testBlinking` unit test loads the default parameters, invokes one scheduler cycle with blinking disabled, and verifies that no LED-state event, GPIO output, or transition telemetry is produced.

## Limitations

- The GPIO chip and line are fixed in the deployment source rather than configured at runtime.
- `BLINK_INTERVAL` is expressed in scheduler ticks; the component does not measure wall-clock time.
- An interval of zero disables transitions but is not rejected or reported as an error.
- Transition count and logical state are held only in memory and reset when the application restarts.
- Current automated coverage checks only the default disabled state.
