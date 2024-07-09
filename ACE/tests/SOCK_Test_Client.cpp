#include "test_config.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_sys_wait.h"
//#include "ace/Thread.h"
#include "ace/Time_Value.h"
//#include "ace/Thread_Manager.h"
#include "ace/SOCK_Connector.h"
//#include "ace/SOCK_Acceptor.h"
#include "ace/Handle_Set.h"

static const char ACE_ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";
const u_short SERVER_PORT = 4321;

void *
client (void *arg)
{
  ACE_UNUSED_ARG (arg);
  // NOTE(sonndinh): Name resolution doesn't work properly when running test on INTEGRITY Simulator.
  // As a fix, just use a localhost IP address for now.
  
  ACE_INET_Addr server_addr (SERVER_PORT, "127.0.0.1");
  ACE_SOCK_Stream cli_stream;
  ACE_SOCK_Connector con;

  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%P|%t) starting non-blocking connect\n")));
  // Initiate timed, non-blocking connection with server.

  // Attempt a non-blocking connect to the server.
  if (con.connect (cli_stream, server_addr,
                   (ACE_Time_Value *) &ACE_Time_Value::zero) == -1)
    {
      if (errno != EWOULDBLOCK)
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("connection failed")));

      ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%P|%t) starting timed connect\n")));

      // Check if non-blocking connection is in progress,
      // and wait up to ACE_DEFAULT_TIMEOUT seconds for it to complete.
      ACE_Time_Value tv (ACE_DEFAULT_TIMEOUT);

      if (con.complete (cli_stream, &server_addr, &tv) == -1)
        ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("connection failed")), 0);
      else
        ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%P|%t) connected to %C\n"),
                    server_addr.get_host_name ()));
    }

  if (cli_stream.disable (ACE_NONBLOCK) == -1)
    ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("disable")));

  // Test Bug 3606
  const ACE_Time_Value def_timeout (ACE_DEFAULT_TIMEOUT);
  ACE_Time_Value tv (def_timeout);
  int result = ACE::handle_ready (cli_stream.get_handle (), &tv,
                                  true, // read_ready
                                  true, // write_ready
                                  false);
  // we expect the handle to be at least write_ready since it is freshly connected.
  if (result == -1)
    ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("ACE::handle_ready")), 0);

  // Send data to server (correctly handles "incomplete writes").
  for (const char *c = ACE_ALPHABET; *c != '\0'; c++)
    if (cli_stream.send_n (c, 1) == -1)
      ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("send_n")));

  // Explicitly close the writer-side of the connection.
  if (cli_stream.close_writer () == -1)
    ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("close_writer")));

  char buf[1];

  // Wait for handshake with server.
  if (cli_stream.recv_n (buf, 1) != 1)
    ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("recv_n")));

  // Close the connection completely.
  if (cli_stream.close () == -1)
    ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("close")));

  return 0;
}

int run_main (int, ACE_TCHAR *[])
{
  ACE_START_TEST (ACE_TEXT ("SOCK_Test_Client"));
  client (0);
  ACE_END_TEST;
  return 0;
}
