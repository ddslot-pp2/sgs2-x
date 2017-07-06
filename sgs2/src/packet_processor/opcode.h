#ifndef __OPCODE_H
#define __OPCODE_H

  enum class opcode : unsigned short
  {
		CS_LOG_IN = 1000,
		SC_LOG_IN = 1001,
		CS_PING = 2000,
		SC_PING = 2001,
  };
#endif
