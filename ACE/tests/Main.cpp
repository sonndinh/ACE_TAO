
//=============================================================================
/**
 *  @file    Main.cpp
 *
 *   This is a wrapper for the test programs.  It obviates the test cpp's
 *   from having to always include OS.h.
 *
 *  @author Don Hinton <dhinton@dresystems.com>
 */
//=============================================================================

#include "ace/OS_main.h"
#include "ace/Log_Msg.h"

extern "C" {
  char *shm_area_name = "Example_Area";
  char *shm_area_password = "******";
}

int run_main (int argc, ACE_TCHAR *argv[]);

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  return run_main (argc, argv);
}
