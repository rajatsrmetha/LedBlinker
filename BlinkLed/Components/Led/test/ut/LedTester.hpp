// ======================================================================
// \title  LedTester.hpp
// \author space
// \brief  hpp file for Led component test harness implementation class
// ======================================================================

#ifndef BlinkLed_LedTester_HPP
#define BlinkLed_LedTester_HPP

#include "BlinkLed/Components/Led/Led.hpp"
#include "BlinkLed/Components/Led/LedGTestBase.hpp"

namespace BlinkLed {

class LedTester final : public LedGTestBase {
  public:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    // Maximum size of histories storing events, telemetry, and port outputs
    static const FwSizeType MAX_HISTORY_SIZE = 10;

    // Instance ID supplied to the component instance under test
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;

    // Queue depth supplied to the component instance under test
    static const FwSizeType TEST_INSTANCE_QUEUE_DEPTH = 10;

  public:
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct object LedTester
    LedTester();

    //! Destroy object LedTester
    ~LedTester();

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! To do
    void testBlinking();
    
  private:
    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Connect ports
    void connectPorts();

    //! Initialize components
    void initComponents();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    Led component;
};

}  // namespace BlinkLed

#endif
