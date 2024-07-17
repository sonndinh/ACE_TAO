#include "Hello.h"
#include "ace/Get_Opt.h"
#include "ace/OS_NS_stdio.h"

#if !defined (ACE_USES_GHS_ISIMPPC)
const ACE_TCHAR *ior_output_file = ACE_TEXT ("test.ior");
#endif

int
parse_args (int argc, ACE_TCHAR *argv[])
{
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("o:"));
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'o':
        ior_output_file = get_opts.opt_arg ();
        break;

      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage:  %s "
                           "-o <iorfile>"
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
      CORBA::ORB_var orb =
        CORBA::ORB_init (argc, argv);
      ACE_DEBUG((LM_DEBUG, "(%P|%t) server: ORB init done\n"));

      CORBA::Object_var poa_object =
        orb->resolve_initial_references("RootPOA");
      ACE_DEBUG((LM_DEBUG, "(%P|%t) server: resolve_initial_references done\n"));

      PortableServer::POA_var root_poa =
        PortableServer::POA::_narrow (poa_object.in ());

      if (CORBA::is_nil (root_poa.in ()))
        ACE_ERROR_RETURN ((LM_ERROR,
                           " (%P|%t) Panic: nil RootPOA\n"),
                          1);

      PortableServer::POAManager_var poa_manager = root_poa->the_POAManager ();
      ACE_DEBUG((LM_DEBUG, "(%P|%t) server: the_POAManager done\n"));

      if (parse_args (argc, argv) != 0)
        return 1;

      Hello *hello_impl = 0;
      ACE_NEW_RETURN (hello_impl,
                      Hello (orb.in ()),
                      1);
      PortableServer::ServantBase_var owner_transfer(hello_impl);
      ACE_DEBUG((LM_DEBUG, "(%P|%t) server: Create ServantBase_var done\n"));

      PortableServer::ObjectId_var id =
        root_poa->activate_object (hello_impl);
      ACE_DEBUG((LM_DEBUG, "(%P|%t) server: activate_object done\n"));

      CORBA::Object_var object = root_poa->id_to_reference (id.in ());

      Test::Hello_var hello = Test::Hello::_narrow (object.in ());

      CORBA::String_var ior = orb->object_to_string (hello.in ());
      ACE_DEBUG((LM_DEBUG, "(%P|%t) server: IOR string: %C\n", ior.in()));

#if !defined (ACE_USES_GHS_ISIMPPC)
      // Output the IOR to the <ior_output_file>
      FILE *output_file= ACE_OS::fopen (ior_output_file, "w");
      if (output_file == 0)
        ACE_ERROR_RETURN ((LM_ERROR,
                           "Cannot open output file for writing IOR: %s\n",
                           ior_output_file),
                           1);

      ACE_OS::fprintf (output_file, "%s", ior.in ());
      ACE_OS::fclose (output_file);
#endif

      ACE_DEBUG((LM_DEBUG, "(%P|%t) server: Activating POA Manager\n"));
      poa_manager->activate ();

      ACE_DEBUG((LM_DEBUG, "(%P|%t) server: Running ORB...\n"));
      orb->run ();

      ACE_DEBUG ((LM_DEBUG, "(%P|%t) server - event loop finished\n"));

      root_poa->destroy (true, true);

      orb->destroy ();
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Exception caught:");
      return 1;
    }

  return 0;
}
