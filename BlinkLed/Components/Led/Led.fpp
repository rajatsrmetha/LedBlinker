module BlinkLed {
    @ Component for F Prime FSW framework.
    active component Led {

        @ Command to turn on or off the blinking LED
        async command BLINKING_ON_OFF(
            onOff: Fw.On 
        )
        
        @ Reports the state we set to blinking.
        event SetBlinkingState($state: Fw.On) \
            severity activity high \
            format "Set blinking state to {}."

        event BlinkIntervalSet(interval: U32) \
            severity activity high \
            format "LED blink interval set to {}"
        
        event LedState(onOff: Fw.On) \
            severity activity low \
            format "LED is {}"
        
        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}