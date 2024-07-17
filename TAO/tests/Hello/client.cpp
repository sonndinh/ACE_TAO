#include "TestC.h"
#include "ace/Get_Opt.h"

#if !defined (ACE_USES_GHS_ISIMPPC)
const ACE_TCHAR *ior = ACE_TEXT ("file://test.ior");
#else
// Some Green Hills INTEGRITY environment does not have file system.
// We use this method in such environment.
// Run the server which will print the IOR string to the console.
// Then replace "IOR_string_from_server" with the actual IOR.
// TODO: pass the IOR string as the argument to the client.
const ACE_TCHAR *ior = ACE_TEXT ("IOR_string_from_server");
#endif

//TAO_debug_level = 8;

int
parse_args (int argc, ACE_TCHAR *argv[])
{
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("k:"));
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'k':
        ior = get_opts.opt_arg ();
        break;

      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage:  %s "
                           "-k <ior> "
                           "\n",
                           argv [0]),
                          -1);
      }
  // Indicates successful parsing of the command line
  return 0;
}

#if defined (ghs)
extern "C" {
  char *shm_area_name = const_cast<char*>("Example_Area");
  char *shm_area_password = const_cast<char*>("******");
}
#endif

int
ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
  try
    {
      CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);
      ACE_DEBUG((LM_DEBUG, "(%P|%t) client: ORB_init done\n"));

      if (parse_args (argc, argv) != 0)
        return 1;
      ACE_DEBUG((LM_DEBUG, "(%P|%t) client: parse_args done\n"));

      CORBA::Object_var tmp = orb->string_to_object(ior);
      if (CORBA::is_nil(tmp.in())) {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) client: tmp is nil\n"));
      }
      ACE_DEBUG((LM_DEBUG, "(%P|%t) client: string_to_object done\n"));

      Test::Hello_var hello = Test::Hello::_narrow(tmp.in ());

      if (CORBA::is_nil (hello.in ()))
        {
          ACE_ERROR_RETURN ((LM_DEBUG,
                             "Nil Test::Hello reference <%s>\n",
                             ior),
                            1);
        }

      ACE_DEBUG((LM_DEBUG, "(%P|%t) client: Calling get_string on the Hello object\n"));
      CORBA::String_var the_string = hello->get_string ();

      ACE_DEBUG ((LM_DEBUG, "(%P|%t) - string returned <%C>\n",
                  the_string.in ()));

      ACE_DEBUG((LM_DEBUG, "(%P|%t) client: Calling shutdown on the Hello object\n"));
      hello->shutdown ();

      ACE_DEBUG((LM_DEBUG, "(%P|%t) client: Destroying ORB\n"));
      orb->destroy ();
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Exception caught:");
      return 1;
    }

  return 0;
}
