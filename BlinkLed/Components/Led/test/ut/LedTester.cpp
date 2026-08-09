// ======================================================================
// \title  LedTester.cpp
// \author space
// \brief  cpp file for Led component test harness implementation class
// ======================================================================

#include "LedTester.hpp"

namespace BlinkLed {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

LedTester ::LedTester() : LedGTestBase("LedTester", LedTester::MAX_HISTORY_SIZE), component("Led") {
    this->initComponents();
    this->connectPorts();
}

LedTester ::~LedTester() {
    this->component.deinit();
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void LedTester ::testBlinking() {
    // This test will make use of parameters. So need to load them.
    this->component.loadParameters();

    // Ensure LED stays off when blinking is disabled
    // The Led component defaults to blinking off
    this->invoke_to_run(0, 0);     // invoke the 'run' port to simulate running one cycle
    this->component.doDispatch();  // Trigger execution of async port

    ASSERT_EVENTS_LedState_SIZE(0);  // ensure no LedState change events we emitted

    ASSERT_from_gpioSet_SIZE(0);  // ensure gpio LED wasn't set

    ASSERT_TLM_BlinkTransitions_SIZE(0);  // ensure no LedTransitions were recorded
}

}  // namespace BlinkLed
