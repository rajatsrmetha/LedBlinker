// ======================================================================
// \title  Led.cpp
// \author space
// \brief  cpp file for Led component implementation class
// ======================================================================

#include "BlinkLed/Components/Led/Led.hpp"

namespace BlinkLed {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Led ::Led(const char* const compName) : LedComponentBase(compName) {}

Led ::~Led() {}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void Led ::BLINKING_ON_OFF_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, Fw::On onOff) {
    this->m_toggleCounter = 0;               // Reset count on any successful command
    this->m_blinking = Fw::On::ON == onOff;  // Update blinking state
    
    this->log_ACTIVITY_HI_SetBlinkingState(onOff);
    
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace BlinkLed
