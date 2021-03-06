//-----------------------------------------------------------------------------
// F36x_CRC.c 
//-----------------------------------------------------------------------------
// Copyright (C) 2013 Silicon Laboratories, Inc.
// http://www.silabs.com
//
//
//
// Target:         C8051F360 
// Tool chain:     Keil C51 9.02 / Keil EVAL C51
// Command Line:   None
//
//
// Release 1.0 / 7May2013 (Mark Ding)
//    -Initial Revision
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <compiler_defs.h>
#include "F36x_CRC.h"

//=============================================================================
// Function Definitions
//=============================================================================

//-----------------------------------------------------------------------------
// Get_Buf_CRC
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Returns a 16-bit CRC of the contents of a buffer.
//
//-----------------------------------------------------------------------------
U16 Get_Buf_CRC(U8 *ptr, U16 numbytes)
{
    U16 i, CRC;

    CRC = 0x0000;

    // Process each byte in the buffer into the running CRC
    for (i = 0; i < numbytes; i++)
    {
        CRC = Update_CRC(CRC, *ptr++);
    }

    return CRC;
}

//-----------------------------------------------------------------------------
// Update_CRC
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// This function accepts a CRC argument and a <newbyte> and returns an
// updated CRC value; Does not use a CRC Lookup Table.
//
//-----------------------------------------------------------------------------
U16 Update_CRC(U16 crc, U8 newbyte)
{
    U8 i; // loop counter

#define POLY 0x8408                 // CRC16-CCITT FCS (X^16+X^12+X^5+1)
    crc = crc ^ newbyte;

    for (i = 0; i < 8; i++)
    {
        if (crc & 0x01)
        {
            crc = crc >> 1;
            crc ^= POLY;
        }
        else
        {
            crc = crc >> 1;
        }
    }
    return crc;
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
