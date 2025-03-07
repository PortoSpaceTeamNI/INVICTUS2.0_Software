/******************************************************************************/
/*                             Start of crcmodel.c                            */
/******************************************************************************/
/*                                                                            */
/* Author : Ross Williams (ross@guest.adelaide.edu.au.).                      */
/* Date   : 3 June 1993.                                                      */
/* Status : Public domain.                                                    */
/*                                                                            */
/* Description : This is the implementation (.c) file for the reference       */
/* implementation of the Rocksoft^tm Model CRC Algorithm. For more            */
/* information on the Rocksoft^tm Model CRC Algorithm, see the document       */
/* titled "A Painless Guide to CRC Error Detection Algorithms" by Ross        */
/* Williams (ross@guest.adelaide.edu.au.). This document is likely to be in   */
/* "ftp.adelaide.edu.au/pub/rocksoft".                                        */
/*                                                                            */
/* Note: Rocksoft is a trademark of Rocksoft Pty Ltd, Adelaide, Australia.    */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* Implementation Notes                                                       */
/* --------------------                                                       */
/* To avoid inconsistencies, the specification of each function is not echoed */
/* here. See the header file for a description of these functions.            */
/* This package is light on checking because I want to keep it short and      */
/* simple and portable (i.e. it would be too messy to distribute my entire    */
/* C culture (e.g. assertions package) with this package.                     */
/*                                                                            */
/******************************************************************************/

#include "CRC.h"

/******************************************************************************/

/* The following definitions make the code more readable. */

#define BITMASK(X) (1L << (X))
#define MASK32 0xFFFFFFFFL
#define LOCAL static

#define INIT 0L
#define XOROT 0L

/*****************************************************************/
/*                                                               */
/* CRC LOOKUP TABLE                                              */
/* ================                                              */
/* The following CRC lookup table was generated automagically    */
/* by the Rocksoft^tm Model CRC Algorithm Table Generation       */
/* Program V1.0 using the following model parameters:            */
/*                                                               */
/*    Width   : 2 bytes.                                         */
/*    Poly    : 0xD175                                           */
/*    Reverse : FALSE.                                           */
/*                                                               */
/* For more information on the Rocksoft^tm Model CRC Algorithm,  */
/* see the document titled "A Painless Guide to CRC Error        */
/* Detection Algorithms" by Ross Williams                        */
/* (ross@guest.adelaide.edu.au.). This document is likely to be  */
/* in the FTP archive "ftp.adelaide.edu.au/pub/rocksoft".        */
/*                                                               */
/*****************************************************************/
unsigned short crctable[256] =
{
 0x0000, 0xD175, 0x739F, 0xA2EA, 0xE73E, 0x364B, 0x94A1, 0x45D4,
 0x1F09, 0xCE7C, 0x6C96, 0xBDE3, 0xF837, 0x2942, 0x8BA8, 0x5ADD,
 0x3E12, 0xEF67, 0x4D8D, 0x9CF8, 0xD92C, 0x0859, 0xAAB3, 0x7BC6,
 0x211B, 0xF06E, 0x5284, 0x83F1, 0xC625, 0x1750, 0xB5BA, 0x64CF,
 0x7C24, 0xAD51, 0x0FBB, 0xDECE, 0x9B1A, 0x4A6F, 0xE885, 0x39F0,
 0x632D, 0xB258, 0x10B2, 0xC1C7, 0x8413, 0x5566, 0xF78C, 0x26F9,
 0x4236, 0x9343, 0x31A9, 0xE0DC, 0xA508, 0x747D, 0xD697, 0x07E2,
 0x5D3F, 0x8C4A, 0x2EA0, 0xFFD5, 0xBA01, 0x6B74, 0xC99E, 0x18EB,
 0xF848, 0x293D, 0x8BD7, 0x5AA2, 0x1F76, 0xCE03, 0x6CE9, 0xBD9C,
 0xE741, 0x3634, 0x94DE, 0x45AB, 0x007F, 0xD10A, 0x73E0, 0xA295,
 0xC65A, 0x172F, 0xB5C5, 0x64B0, 0x2164, 0xF011, 0x52FB, 0x838E,
 0xD953, 0x0826, 0xAACC, 0x7BB9, 0x3E6D, 0xEF18, 0x4DF2, 0x9C87,
 0x846C, 0x5519, 0xF7F3, 0x2686, 0x6352, 0xB227, 0x10CD, 0xC1B8,
 0x9B65, 0x4A10, 0xE8FA, 0x398F, 0x7C5B, 0xAD2E, 0x0FC4, 0xDEB1,
 0xBA7E, 0x6B0B, 0xC9E1, 0x1894, 0x5D40, 0x8C35, 0x2EDF, 0xFFAA,
 0xA577, 0x7402, 0xD6E8, 0x079D, 0x4249, 0x933C, 0x31D6, 0xE0A3,
 0x21E5, 0xF090, 0x527A, 0x830F, 0xC6DB, 0x17AE, 0xB544, 0x6431,
 0x3EEC, 0xEF99, 0x4D73, 0x9C06, 0xD9D2, 0x08A7, 0xAA4D, 0x7B38,
 0x1FF7, 0xCE82, 0x6C68, 0xBD1D, 0xF8C9, 0x29BC, 0x8B56, 0x5A23,
 0x00FE, 0xD18B, 0x7361, 0xA214, 0xE7C0, 0x36B5, 0x945F, 0x452A,
 0x5DC1, 0x8CB4, 0x2E5E, 0xFF2B, 0xBAFF, 0x6B8A, 0xC960, 0x1815,
 0x42C8, 0x93BD, 0x3157, 0xE022, 0xA5F6, 0x7483, 0xD669, 0x071C,
 0x63D3, 0xB2A6, 0x104C, 0xC139, 0x84ED, 0x5598, 0xF772, 0x2607,
 0x7CDA, 0xADAF, 0x0F45, 0xDE30, 0x9BE4, 0x4A91, 0xE87B, 0x390E,
 0xD9AD, 0x08D8, 0xAA32, 0x7B47, 0x3E93, 0xEFE6, 0x4D0C, 0x9C79,
 0xC6A4, 0x17D1, 0xB53B, 0x644E, 0x219A, 0xF0EF, 0x5205, 0x8370,
 0xE7BF, 0x36CA, 0x9420, 0x4555, 0x0081, 0xD1F4, 0x731E, 0xA26B,
 0xF8B6, 0x29C3, 0x8B29, 0x5A5C, 0x1F88, 0xCEFD, 0x6C17, 0xBD62,
 0xA589, 0x74FC, 0xD616, 0x0763, 0x42B7, 0x93C2, 0x3128, 0xE05D,
 0xBA80, 0x6BF5, 0xC91F, 0x186A, 0x5DBE, 0x8CCB, 0x2E21, 0xFF54,
 0x9B9B, 0x4AEE, 0xE804, 0x3971, 0x7CA5, 0xADD0, 0x0F3A, 0xDE4F,
 0x8492, 0x55E7, 0xF70D, 0x2678, 0x63AC, 0xB2D9, 0x1033, 0xC146
};

/******************************************************************************/
unsigned long crc (unsigned char *blk_adr, unsigned long blk_len)
{
    unsigned long crc = INIT;
    while (blk_len--)
        crc = crctable[((crc>>8) ^ *blk_adr++) & 0xFFL] ^ (crc << 8);
    return crc ^ XOROT;
}