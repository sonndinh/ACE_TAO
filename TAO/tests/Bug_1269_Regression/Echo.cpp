/**
 * @file Echo.cpp
 *
 * @author Carlos O'Ryan <coryan@atdesk.com>
 */
#include "Echo.h"
#include "ace/OS_NS_unistd.h"

Echo::Echo(CORBA::ORB_ptr orb,
           int abort_counter)
  : orb_(CORBA::ORB::_duplicate(orb))
  , abort_counter_(abort_counter)
{
}

void
Echo::echo_payload(Test::Payload const &)
{
  this->abort_counter_--;

  if (this->abort_counter_ == 0)
    {
      ACE_DEBUG ((LM_DEBUG, "(%P|%t) Echo::echo_payload, sleeping\n"));
      // Sleep for 15 seconds, forcing a flow control of some kind.
      ACE_OS::sleep(15);

      // Run the ORB for a while, to generate a short-lived release of
      // the flow control.
      ACE_Time_Value tv(0, 10000);
      this->orb_->run(tv);

      ACE_DEBUG ((LM_DEBUG, "(%P|%t) Echo::echo_payload, aborting\n"));
      // Kill the app
      ACE_OS::abort();
    }
}
