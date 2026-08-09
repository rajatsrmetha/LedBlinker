// ======================================================================
// \title  Led.hpp
// \author space
// \brief  hpp file for Led component implementation class
// ======================================================================

#ifndef BlinkLed_Led_HPP
#define BlinkLed_Led_HPP

#include "BlinkLed/Components/Led/LedComponentAc.hpp"

namespace BlinkLed {

class Led final : public LedComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct Led object
    Led(const char* const compName  //!< The component name
    );

    //! Destroy Led object
    ~Led();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command BLINKING_ON_OFF
    //!
    //! Command to turn on or off the blinking LED
    void BLINKING_ON_OFF_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                    U32 cmdSeq,           //!< The command sequence number
                                    Fw::On onOff) override;
};

}  // namespace BlinkLed

#endif
