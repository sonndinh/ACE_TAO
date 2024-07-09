#include "test_config.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_sys_wait.h"
//#include "ace/Thread.h"
#include "ace/Time_Value.h"
//#include "ace/Thread_Manager.h"
//#include "ace/SOCK_Connector.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Handle_Set.h"

static const char ACE_ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";
const u_short SERVER_PORT = 4321;

void *
server (void *arg)
{
  ACE_UNUSED_ARG (arg);
  ACE_SOCK_Acceptor acceptor;
  ACE_INET_Addr server_addr (SERVER_PORT, "127.0.0.1");
  if (acceptor.open (server_addr) == -1) {
    ACE_ERROR ((LM_ERROR, "(%P|%t) %p\n", "open"));
    return 0;
  }

  ACE_DEBUG ((LM_DEBUG, "(%P|%t) starting server at port %d\n", SERVER_PORT));

  ACE_SOCK_Acceptor* peer_acceptor = &acceptor;
  //if (peer_acceptor->enable (ACE_NONBLOCK) == -1)
  //  ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("enable")));

  // Keep these objects out here to prevent excessive constructor
  // calls...
  ACE_SOCK_Stream new_stream;
  ACE_INET_Addr cli_addr;
  const ACE_Time_Value def_timeout (ACE_DEFAULT_TIMEOUT);
  ACE_Time_Value tv (def_timeout);

  char buf[BUFSIZ];
  const char *t = ACE_ALPHABET;

  //int result = ACE::handle_read_ready (peer_acceptor->get_handle (), &tv);

  //ACE_TEST_ASSERT (tv == def_timeout);

  //if (result == -1)
  //  ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), ACE_TEXT ("handle_read_ready")), 0);

  // Create a new ACE_SOCK_Stream endpoint (note automatic restart
  // if errno == EINTR).

  int result;
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

int
run_main (int, ACE_TCHAR *[])
{
  ACE_START_TEST (ACE_TEXT ("SOCK_Test_Server"));
  server (0);
  ACE_END_TEST;
  return 0;
}
