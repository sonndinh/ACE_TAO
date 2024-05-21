
//=============================================================================
/**
 *  @file    SOCK_Test.cpp
 *
 *   This is a test of the <ACE_SOCK_Acceptor> and
 *   <ACE_SOCK_Connector> classes. The test forks two processes or
 *   spawns two threads (depending upon the platform) and then
 *   executes client and server allowing them to connect and
 *   exchange data.
 *
 *  @author Prashant Jain <pjain@cs.wustl.edu> and Doug Schmidt <d.schmidt@vanderbilt.edu>
 */
//=============================================================================


#include "test_config.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_sys_wait.h"
#include "ace/Thread.h"
#include "ace/Time_Value.h"
#include "ace/Thread_Manager.h"
#include "ace/SOCK_Connector.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Handle_Set.h"


static const char ACE_ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";

void *
client (void *arg)
{
  ACE_INET_Addr *remote_addr = (ACE_INET_Addr *) arg;
  // NOTE(sonndinh): Name resolution doesn't work properly when running test on INTEGRITY Simulator.
  // As a fix, just use a localhost IP address for now.
  //ACE_INET_Addr server_addr (remote_addr->get_port_number (), ACE_LOCALHOST);
  ACE_INET_Addr server_addr (remote_addr->get_port_number (), "127.0.0.1");
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

void *
server (void *arg)
{
  ACE_SOCK_Acceptor *peer_acceptor = (ACE_SOCK_Acceptor *) arg;

  if (peer_acceptor->enable (ACE_NONBLOCK) == -1)
    ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("enable")));

  // Keep these objects out here to prevent excessive constructor
  // calls...
  ACE_SOCK_Stream new_stream;
  ACE_INET_Addr cli_addr;
  const ACE_Time_Value def_timeout (ACE_DEFAULT_TIMEOUT);
  ACE_Time_Value tv (def_timeout);

  char buf[BUFSIZ];
  const char *t = ACE_ALPHABET;

  int result = ACE::handle_read_ready (peer_acceptor->get_handle (), &tv);

  ACE_TEST_ASSERT (tv == def_timeout);

  if (result == -1)
    ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("handle_read_ready")), 0);

  // Create a new ACE_SOCK_Stream endpoint (note automatic restart
  // if errno == EINTR).

  while ((result = peer_acceptor->accept (new_stream, &cli_addr)) != -1)
    {
      ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%P|%t) client %C connected from %d\n"),
                  cli_addr.get_host_name (), cli_addr.get_port_number ()));

      // Enable non-blocking I/O.
      if (new_stream.enable (ACE_NONBLOCK) == -1)
        ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("enable")), 0);

      // Read data from client (terminate on error).
      for (ssize_t r_bytes; ;)
        {
          if (ACE::handle_read_ready (new_stream.get_handle (), 0) == -1)
            ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("handle_read_ready")), 0);

          while ((r_bytes = new_stream.recv (buf, 1)) > 0)
            {
              ACE_TEST_ASSERT (*t == buf[0]);
              t++;
            }

          if (r_bytes == 0)
            {
              ACE_DEBUG ((LM_DEBUG,
                          ACE_TEXT ("(%P|%t) reached end of input, connection closed by client\n")));

              // Handshake back with client.
              if (new_stream.send_n ("", 1) != 1)
                ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("send_n")));

              // Close endpoint.
              if (new_stream.close () == -1)
                ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("close")));
              return 0;
            }
          else if (r_bytes == -1)
            {
              if (errno == EAGAIN || errno == EWOULDBLOCK)
                ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%P|%t) no input available, going back to reading\n")));
              else
                ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("recv_n")), 0);
            }
        }
    }

  if (result == -1)
    {
      if (errno == EWOULDBLOCK)
        ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%P|%t) no connections available, shutting down\n")));
      else
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("accept")));
    }

  return 0;
}

void
spawn ()
{
  // Acceptor
  ACE_SOCK_Acceptor peer_acceptor;

  // Create a server address.
  ACE_INET_Addr server_addr;

  // Bind listener to any port and then find out what the port was.
  if (peer_acceptor.open (ACE_Addr::sap_any) == -1
      || peer_acceptor.get_local_addr (server_addr) == -1)
    ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("open")));
  else
    {
      ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%P|%t) starting server at port %d\n"),
                  server_addr.get_port_number ()));
      // sonndinh: start
      //char buff[128];
      //if (server_addr.addr_to_string(buff, 128) != 0) {
      //  ACE_DEBUG((LM_DEBUG, "spawn: addr_to_string failed\n"));
      //}
      //buff[127] = '\0';
      //ACE_DEBUG((LM_DEBUG, "spawn: Server address is %C\n", buff));
      // sonndinh: end


#if !defined (ACE_LACKS_FORK)
      switch (ACE_OS::fork (ACE_TEXT ("child")))
        {
        case -1:
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("(%P|%t) %p\n"),
                      ACE_TEXT ("fork failed"),
                      1));
          ACE_OS::abort ();
        case 0:
          client (&server_addr);
          ACE_OS::exit (0);
          /* NOTREACHED */
        default:
          server ((void *) &peer_acceptor);
          ACE_OS::wait ();
        }
#elif defined (ACE_HAS_THREADS)
      if (ACE_Thread_Manager::instance ()->spawn
          (ACE_THR_FUNC (server),
           (void *) &peer_acceptor,
           THR_NEW_LWP | THR_DETACHED) == -1)
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("(%P|%t) %p\n%a"),
                    ACE_TEXT ("thread create failed"),
                    1));

      if (ACE_Thread_Manager::instance ()->spawn
          (ACE_THR_FUNC (client),
           (void *) &server_addr,
           THR_NEW_LWP | THR_DETACHED) == -1)
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("(%P|%t) %p\n%a"),
                    ACE_TEXT ("thread create failed"),
                    1));

      // Wait for the threads to exit.
      ACE_Thread_Manager::instance ()->wait ();
#else
      ACE_ERROR ((LM_INFO,
                  ACE_TEXT ("(%P|%t) ")
                  ACE_TEXT ("only one thread may be run ")
                  ACE_TEXT ("in a process on this platform\n")));
#endif /* ACE_HAS_THREADS */

      peer_acceptor.close ();
    }
}

int
run_main (int, ACE_TCHAR *[])
{
  ACE_START_TEST (ACE_TEXT ("SOCK_Test"));

#ifndef ACE_LACKS_ACCEPT
  spawn ();
#endif

  ACE_END_TEST;

  // sonndinh: start
  // Log messages from spawned client and server thread don't get printed out to stderr.
  // But they can be logged to a log file.
  // This tries to print the contents of the log file for checking.
  /*
#include "ace/streams.h"
#include <string>

  // Try reading from the log file
#if !defined ACE_TEST_LOG_TO_STDERR
  const char* filename = "/SOCK_Test.log";
  ifstream input;
  input.open(filename, ios::in);
  if (!input.good()) {
    ACE_DEBUG((LM_DEBUG, "Failed to open %C to read\n", filename));
  }
  std::string line;
  while (std::getline(input, line)) {
    cout << line << endl;
  }
#endif
  */
  // sonndinh: end

  return 0;
}
