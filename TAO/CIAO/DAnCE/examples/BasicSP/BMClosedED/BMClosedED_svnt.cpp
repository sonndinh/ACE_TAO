// $Id$
//
// ****              Code generated by the                 ****
// ****  Component Integrated ACE ORB (CIAO) CIDL Compiler ****
// CIAO has been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// CIDL Compiler has been developed by:
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about CIAO is available at:
//    http://www.dre.vanderbilt.edu/CIAO

#include "BMClosedED_svnt.h"
#include "Cookies.h"
#include "ciao/Servant_Activator.h"
#include "ciao/Port_Activator_T.h"

namespace BMClosedED_Impl
{
  namespace CIAO_GLUE_BasicSP
  {
    template <typename T>
    ReadData_Servant_T<T>::ReadData_Servant_T (
    ::BasicSP::CCM_ReadData_ptr executor,
    ::Components::CCMContext_ptr c)
    : executor_ (::BasicSP::CCM_ReadData::_duplicate (executor)),
    ctx_ (::Components::CCMContext::_duplicate (c))
    {
    }

    template <typename T>
    ReadData_Servant_T<T>::~ReadData_Servant_T (void)
    {
    }

    template <typename T>
    char *
    ReadData_Servant_T<T>::get_data (
    ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      return this->executor_->get_data (
      ACE_ENV_SINGLE_ARG_PARAMETER);
    }

    template <typename T>
    CORBA::Object_ptr
    ReadData_Servant_T<T>::_get_component (
    ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      ::Components::SessionContext_var sc =
      ::Components::SessionContext::_narrow (
      this->ctx_.in ()
      ACE_ENV_ARG_PARAMETER);
      ACE_CHECK_RETURN (CORBA::Object::_nil ());

      if (! CORBA::is_nil (sc.in ()))
      {
        return sc->get_CCM_object (
        ACE_ENV_SINGLE_ARG_PARAMETER);
      }

      ::Components::EntityContext_var ec =
      ::Components::EntityContext::_narrow (
      this->ctx_.in ()
      ACE_ENV_ARG_PARAMETER);
      ACE_CHECK_RETURN (CORBA::Object::_nil ());

      if (! CORBA::is_nil (ec.in ()))
      {
        return ec->get_CCM_object (
        ACE_ENV_SINGLE_ARG_PARAMETER);
      }

      ACE_THROW_RETURN (CORBA::INTERNAL (), 0);
    }
  }

  namespace CIAO_GLUE_BasicSP
  {
    BMClosedED_Context::BMClosedED_Context (
    ::Components::CCMHome_ptr home,
    ::CIAO::Session_Container *c,
    BMClosedED_Servant *sv)
      : Context_Impl_Base (home, c),
        ctx_svnt_base (home, c, sv)
    {
    }

    BMClosedED_Context::~BMClosedED_Context (void)
    {
    }

    // Operations for BMClosedED receptacles and event sources,
    // defined in ::BasicSP::CCM_BMClosedED_Context.

    ::BasicSP::ReadData_ptr
    BMClosedED_Context::get_connection_datain (
    ACE_ENV_SINGLE_ARG_DECL_NOT_USED)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      return ::BasicSP::ReadData::_duplicate (
      this->ciao_uses_datain_.in ());
    }

    void
    BMClosedED_Context::connect_datain (
    ::BasicSP::ReadData_ptr c
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::AlreadyConnected,
    ::Components::InvalidConnection))
    {
      if (!CORBA::is_nil (this->ciao_uses_datain_.in ()))
      {
        ACE_THROW (::Components::AlreadyConnected ());
      }

      if (CORBA::is_nil (c))
      {
        ACE_THROW (::Components::InvalidConnection ());
      }

      this->ciao_uses_datain_ =
      ::BasicSP::ReadData::_duplicate (c);
    }

    ::BasicSP::ReadData_ptr
    BMClosedED_Context::disconnect_datain (
    ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::NoConnection))
    {
      if (CORBA::is_nil (this->ciao_uses_datain_.in ()))
      {
        ACE_THROW_RETURN (
        ::Components::NoConnection (),
        ::BasicSP::ReadData::_nil ());
      }

      return this->ciao_uses_datain_._retn ();
    }

    void
    BMClosedED_Context::push_out_avail (
    ::BasicSP::DataAvailable *ev
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {

      ACE_CString my_uuid = this->servant_->component_UUID (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;
      my_uuid += "_prepare_capture_publisher";

      this->container_->push_event (ev,
                                    my_uuid.c_str ()
                                    ACE_ENV_ARG_PARAMETER);
      ACE_CHECK;
      /*
      ACE_Active_Map_Manager< 
      ::BasicSP::DataAvailableConsumer_var>::iterator end =
      this->ciao_publishes_out_avail_map_.end ();

      for (ACE_Active_Map_Manager< 
      ::BasicSP::DataAvailableConsumer_var>::iterator iter =
      this->ciao_publishes_out_avail_map_.begin ();
      iter != end;
      ++iter)
      {
        ACE_Active_Map_Manager< 
        ::BasicSP::DataAvailableConsumer_var>::ENTRY &entry = *iter;

        ::BasicSP::DataAvailableConsumer_var c =
        ::BasicSP::DataAvailableConsumer::_narrow (
        entry.int_id_.in ()
        ACE_ENV_ARG_PARAMETER);
        ACE_CHECK;

        entry.int_id_->push_DataAvailable (
        ev
        ACE_ENV_ARG_PARAMETER);
        ACE_CHECK;
      }
      */
    }

    ::Components::Cookie *
    BMClosedED_Context::subscribe_out_avail (
    ::BasicSP::DataAvailableConsumer_ptr c
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::ExceededConnectionLimit))
    {
      if (CORBA::is_nil (c))
      {
        ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
      }

      ::BasicSP::DataAvailableConsumer_var sub =
      ::BasicSP::DataAvailableConsumer::_duplicate (c);

      ACE_Active_Map_Manager_Key key;
      this->ciao_publishes_out_avail_map_.bind (sub.in (), key);
      sub._retn ();

      ::Components::Cookie_var retv = new ::CIAO::Map_Key_Cookie (key);
      return retv._retn ();
    }

    ::BasicSP::DataAvailableConsumer_ptr
    BMClosedED_Context::unsubscribe_out_avail (
    ::Components::Cookie *ck
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::InvalidConnection))
    {
      ::BasicSP::DataAvailableConsumer_var retv;
      ACE_Active_Map_Manager_Key key;

      if (ck == 0 || ::CIAO::Map_Key_Cookie::extract (ck, key) == false)
      {
        ACE_THROW_RETURN (
        ::Components::InvalidConnection (),
        ::BasicSP::DataAvailableConsumer::_nil ());
      }

      if (this->ciao_publishes_out_avail_map_.unbind (key, retv) != 0)
      {
        ACE_THROW_RETURN (
        ::Components::InvalidConnection (),
        ::BasicSP::DataAvailableConsumer::_nil ());
      }

      return retv._retn ();
    }

    // CIAO-specific.

    BMClosedED_Context *
    BMClosedED_Context::_narrow (
    ::Components::SessionContext_ptr p
    ACE_ENV_ARG_DECL_NOT_USED)
    {
      return dynamic_cast<BMClosedED_Context *> (p);
    }
  }

  namespace CIAO_GLUE_BasicSP
  {
    void
    BMClosedED_Servant::component_UUID (
    const char * new_component_UUID
    ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      this->component_UUID_ = new_component_UUID;
    }

    CIAO::CONNECTION_ID
    BMClosedED_Servant::component_UUID (
    ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      return CORBA::string_dup (this->component_UUID_.c_str ());
    }

 
    BMClosedED_Servant::BMClosedED_Servant (
    ::BasicSP::CCM_BMClosedED_ptr exe,
    ::Components::CCMHome_ptr h,
    ::CIAO::Session_Container *c)
      : Servant_Impl_Base (c),
        comp_svnt_base (exe, c)
    {
      this->context_ = new BMClosedED_Context (h, c, this);

      CIAO_REGISTER_OBV_FACTORY (
      ::BasicSP::DataAvailable_init,
      ::BasicSP::DataAvailable);

      ACE_TRY_NEW_ENV
      {
        ::Components::SessionComponent_var scom =
        ::Components::SessionComponent::_narrow (
        exe
        ACE_ENV_ARG_PARAMETER);
        ACE_TRY_CHECK;

        if (! ::CORBA::is_nil (scom.in ()))
        {
          scom->set_session_context (
          this->context_
          ACE_ENV_ARG_PARAMETER);
          ACE_TRY_CHECK;
        }

        this->populate_port_tables (
        ACE_ENV_SINGLE_ARG_PARAMETER);
        ACE_TRY_CHECK;
      }

      ACE_CATCHANY
      {
      }

      ACE_ENDTRY;
    }

    BMClosedED_Servant::~BMClosedED_Servant (void)
    {
    }

    void
    BMClosedED_Servant::set_attributes (
    const ::Components::ConfigValues &descr
    ACE_ENV_ARG_DECL_NOT_USED)
    {
      for (CORBA::ULong i = 0;
       i < descr.length ();
       ++i)
      {
        const char *descr_name = descr[i]->name ();
        ::CORBA::Any &descr_value = descr[i]->value ();

        ACE_UNUSED_ARG (descr_name);
        ACE_UNUSED_ARG (descr_value);
      }
    }

    ::BasicSP::ReadData_ptr
    BMClosedED_Servant::provide_dataout (
    ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      if (! ::CORBA::is_nil (this->provide_dataout_.in ()))
      {
        return ::BasicSP::ReadData::_duplicate (this->provide_dataout_.in ());
      }

      ::CORBA::Object_var obj =
      this->provide_dataout_i (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK_RETURN (::BasicSP::ReadData::_nil ());

      ::BasicSP::ReadData_var fo =
      ::BasicSP::ReadData::_narrow (
      obj.in ()
      ACE_ENV_ARG_PARAMETER);
      ACE_CHECK_RETURN (::BasicSP::ReadData::_nil ());

      this->provide_dataout_ = fo;
      return ::BasicSP::ReadData::_duplicate (this->provide_dataout_.in ());
    }

    ::CORBA::Object_ptr
    BMClosedED_Servant::provide_dataout_i (
    ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      ::CORBA::Object_ptr ret =
      this->lookup_facet ("dataout");

      if (! ::CORBA::is_nil (ret))
      {
        return ret;
      }

      CIAO::Port_Activator_T<
          CIAO_GLUE_BasicSP::ReadData_Servant,
          ::BasicSP::CCM_ReadData,
          ::Components::CCMContext,
          BMClosedED_Servant
        > *tmp = 0;

      typedef CIAO::Port_Activator_T<
          CIAO_GLUE_BasicSP::ReadData_Servant,
          ::BasicSP::CCM_ReadData,
          ::Components::CCMContext,
          BMClosedED_Servant
        >
      MACRO_MADNESS_TYPEDEF;

      ACE_NEW_THROW_EX ( 
      tmp,
      MACRO_MADNESS_TYPEDEF (
      "BasicSP_BMClosedED_dataout",
      "dataout",
      CIAO::Port_Activator::Facet,
      0,
      this->context_,
      this),
      CORBA::NO_MEMORY ());

      CIAO::Servant_Activator *sa = 
      this->container_->ports_servant_activator ();

      if (!sa->register_port_activator (tmp))
      {
        return 0;
      }

      ::CORBA::Object_var obj =
      this->container_->generate_reference (
      "BasicSP_BMClosedED_dataout",
      "IDL:BasicSP/ReadData:1.0",
      CIAO::Container::Facet_Consumer
      ACE_ENV_ARG_PARAMETER);
      ACE_CHECK_RETURN (::BasicSP::ReadData::_nil ());

      this->add_facet (
      "dataout",
      obj.in ());

      return obj._retn ();
    }

    ::Components::Cookie *
    BMClosedED_Servant::subscribe_out_avail (
    ::BasicSP::DataAvailableConsumer_ptr c
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::ExceededConnectionLimit))
    {
      return this->context_->subscribe_out_avail (
      c
      ACE_ENV_ARG_PARAMETER);
    }

    ::BasicSP::DataAvailableConsumer_ptr
    BMClosedED_Servant::unsubscribe_out_avail (
    ::Components::Cookie *ck
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::InvalidConnection))
    {
      return this->context_->unsubscribe_out_avail (
      ck
      ACE_ENV_ARG_PARAMETER);
    }

    BMClosedED_Servant::DataAvailableConsumer_in_avail_Servant::DataAvailableConsumer_in_avail_Servant (
    ::BasicSP::CCM_BMClosedED_ptr executor,
    ::BasicSP::CCM_BMClosedED_Context_ptr c)
    : executor_ (::BasicSP::CCM_BMClosedED::_duplicate (executor)),
    ctx_ (::BasicSP::CCM_BMClosedED_Context::_duplicate (c))
    {
    }

    BMClosedED_Servant::DataAvailableConsumer_in_avail_Servant::~DataAvailableConsumer_in_avail_Servant (void)
    {
    }

    CORBA::Object_ptr
    BMClosedED_Servant::DataAvailableConsumer_in_avail_Servant::_get_component (
    ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      return this->ctx_->get_CCM_object (ACE_ENV_SINGLE_ARG_PARAMETER);
    }

    void
    BMClosedED_Servant::DataAvailableConsumer_in_avail_Servant::push_DataAvailable (
    ::BasicSP::DataAvailable *evt
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      this->executor_->push_in_avail (
      evt
      ACE_ENV_ARG_PARAMETER);
    }

    // Inherited from ::Components::EventConsumerBase.
    void
    BMClosedED_Servant::DataAvailableConsumer_in_avail_Servant::push_event (
    ::Components::EventBase *ev
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::BadEventType))
    {
      ::BasicSP::DataAvailable_var ev_type =
      ::BasicSP::DataAvailable::_downcast (ev);

      if (ev_type != 0)
      {
        this->push_DataAvailable (
        ev_type.in ()
        ACE_ENV_ARG_PARAMETER);

        return;
      }

      ACE_THROW (::Components::BadEventType ());
    }

    ::BasicSP::DataAvailableConsumer_ptr
    BMClosedED_Servant::get_consumer_in_avail (
    ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      if (! ::CORBA::is_nil (this->consumes_in_avail_.in ()))
      {
        return ::BasicSP::DataAvailableConsumer::_duplicate (this->consumes_in_avail_.in ());
      }

      ::Components::EventConsumerBase_var obj =
      this->get_consumer_in_avail_i (
      ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK_RETURN (::BasicSP::DataAvailableConsumer::_nil ());

      ::BasicSP::DataAvailableConsumer_var eco =
      ::BasicSP::DataAvailableConsumer::_narrow (
      obj.in ()
      ACE_ENV_ARG_PARAMETER);
      ACE_CHECK_RETURN (::BasicSP::DataAvailableConsumer::_nil ());

      this->consumes_in_avail_ = eco;
      return ::BasicSP::DataAvailableConsumer::_duplicate (this->consumes_in_avail_.in ());
    }

    ::Components::EventConsumerBase_ptr
    BMClosedED_Servant::get_consumer_in_avail_i (
    ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      ::Components::EventConsumerBase_ptr ret =
      this->lookup_consumer ("in_avail");

      if (! ::CORBA::is_nil (ret))
      {
        return ret;
      }

      CIAO::Port_Activator_T<
      BMClosedED_Servant::DataAvailableConsumer_in_avail_Servant,
      ::BasicSP::CCM_BMClosedED,
      ::BasicSP::CCM_BMClosedED_Context,
      BMClosedED_Servant > *tmp = 0;

      typedef  CIAO::Port_Activator_T<
      BMClosedED_Servant::DataAvailableConsumer_in_avail_Servant,
      ::BasicSP::CCM_BMClosedED,
      ::BasicSP::CCM_BMClosedED_Context, 
      BMClosedED_Servant > 
       MACRO_MADNESS_TYPEDEF;


      ACE_NEW_THROW_EX ( 
        tmp,
        MACRO_MADNESS_TYPEDEF (
      "BasicSP_BMClosedED_in_avail",
      "in_avail",
      CIAO::Port_Activator::Sink,
      this->executor_.in (),
      this->context_,
      this),
      CORBA::NO_MEMORY ());


      CIAO::Servant_Activator *sa = 
      this->container_->ports_servant_activator ();

      if (!sa->register_port_activator (tmp))
      {
        return 0;
      }

      ::CORBA::Object_var obj =
      this->container_->generate_reference (
      "BasicSP_BMClosedED_in_avail",
      "IDL:BasicSP/DataAvailableConsumer:1.0",
      CIAO::Container::Facet_Consumer
      ACE_ENV_ARG_PARAMETER);
      ACE_CHECK_RETURN (::BasicSP::DataAvailableConsumer::_nil ());

      ::Components::EventConsumerBase_var ecb =
      ::Components::EventConsumerBase::_narrow (
      obj.in ()
      ACE_ENV_ARG_PARAMETER);
      ACE_CHECK_RETURN (::BasicSP::DataAvailableConsumer::_nil ());

      this->add_consumer (
      "in_avail",
      ecb.in ());

      return ecb._retn ();
    }

    ::Components::Cookie *
    BMClosedED_Servant::connect (
    const char *name,
    ::CORBA::Object_ptr connection
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::InvalidName,
    ::Components::InvalidConnection,
    ::Components::AlreadyConnected,
    ::Components::ExceededConnectionLimit))
    {
      // If the component has no receptacles, this will be unused.
      ACE_UNUSED_ARG (connection);

      if (name == 0)
      {
        ACE_THROW_RETURN (::Components::InvalidName (), 0);
      }

      if (ACE_OS::strcmp (name, "datain") == 0)
      {
        ::BasicSP::ReadData_var _ciao_conn =
        ::BasicSP::ReadData::_narrow (
        connection
        ACE_ENV_ARG_PARAMETER);
        ACE_CHECK_RETURN (0);

        if (::CORBA::is_nil (_ciao_conn.in ()))
        {
          ACE_THROW_RETURN (::Components::InvalidConnection (), 0);
        }

        // Simplex connect.
        this->connect_datain (
        _ciao_conn.in ()
        ACE_ENV_ARG_PARAMETER);
        ACE_CHECK_RETURN (0);

        return 0;
      }

      ACE_THROW_RETURN (::Components::InvalidName (), 0);
    }

    CORBA::Object_ptr
    BMClosedED_Servant::disconnect (
    const char *name,
    ::Components::Cookie * ck
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::InvalidName,
    ::Components::InvalidConnection,
    ::Components::CookieRequired,
    ::Components::NoConnection))
    {
      if (name == 0)
      {
        ACE_THROW_RETURN (
        ::Components::InvalidName (),
        ::CORBA::Object::_nil ());
      }

      if (ACE_OS::strcmp (name, "datain") == 0)
      {
        // Simplex disconnect.
        return this->disconnect_datain (ACE_ENV_SINGLE_ARG_PARAMETER);
      }

      ACE_THROW_RETURN (
      ::Components::InvalidName (),
      ::CORBA::Object::_nil ());

      ACE_UNUSED_ARG (ck);
    }

    void
    BMClosedED_Servant::connect_datain (
    ::BasicSP::ReadData_ptr c
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::AlreadyConnected,
    ::Components::InvalidConnection))
    {
      this->context_->connect_datain (
      c
      ACE_ENV_ARG_PARAMETER);
    }

    ::BasicSP::ReadData_ptr
    BMClosedED_Servant::disconnect_datain (
    ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::NoConnection))
    {
      return this->context_->disconnect_datain (
      ACE_ENV_SINGLE_ARG_PARAMETER);
    }

    ::BasicSP::ReadData_ptr
    BMClosedED_Servant::get_connection_datain (
    ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      return this->context_->get_connection_datain (
      ACE_ENV_SINGLE_ARG_PARAMETER);
    }

    void
    BMClosedED_Servant::connect_consumer (
    const char * emitter_name,
    ::Components::EventConsumerBase_ptr consumer
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::InvalidName,
    ::Components::AlreadyConnected,
    ::Components::InvalidConnection))
    {
      if (emitter_name == 0)
      {
        ACE_THROW (::CORBA::BAD_PARAM ());
      }

      ACE_UNUSED_ARG (consumer);
      ACE_THROW (::Components::InvalidName ());
    }

    ::Components::Cookie *
    BMClosedED_Servant::subscribe (
    const char *publisher_name,
    ::Components::EventConsumerBase_ptr subscribe
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::InvalidName,
    ::Components::InvalidConnection,
    ::Components::ExceededConnectionLimit))
    {
      // Just in case there are no if blocks
      ACE_UNUSED_ARG (subscribe);

      if (publisher_name == 0)
      {
        ACE_THROW_RETURN (::Components::InvalidName (), 0);
      }

      if (ACE_OS::strcmp (publisher_name, "out_avail") == 0)
      {
        ::BasicSP::DataAvailableConsumer_var _ciao_consumer =
        ::BasicSP::DataAvailableConsumer::_narrow (
        subscribe
        ACE_ENV_ARG_PARAMETER);
        ACE_CHECK_RETURN (0);

        if (::CORBA::is_nil (_ciao_consumer.in ()))
        {
          ACE_THROW_RETURN (::Components::InvalidConnection (), 0);
        }

        return this->subscribe_out_avail (
        _ciao_consumer.in ()
        ACE_ENV_ARG_PARAMETER);
      }

      ACE_THROW_RETURN (::Components::InvalidName (), 0);
    }

    ::Components::EventConsumerBase_ptr
    BMClosedED_Servant::unsubscribe (
    const char *publisher_name,
    ::Components::Cookie *ck
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException,
    ::Components::InvalidName,
    ::Components::InvalidConnection))
    {
      // Just in case there are no if blocks
      ACE_UNUSED_ARG (ck);

      if (publisher_name == 0)
      {
        ACE_THROW_RETURN (
        ::Components::InvalidName (),
        ::Components::EventConsumerBase::_nil ());
      }

      if (ACE_OS::strcmp (publisher_name, "out_avail") == 0)
      {
        return this->unsubscribe_out_avail (
        ck
        ACE_ENV_ARG_PARAMETER);
      }

      ACE_THROW_RETURN (
      ::Components::InvalidName (),
      ::Components::EventConsumerBase::_nil ());
    }

    CORBA::Object_ptr
    BMClosedED_Servant::get_facet_executor (const char *name
    ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((
    ::CORBA::SystemException))
    {
      if (name == 0)
      {
        ACE_THROW_RETURN (
        ::CORBA::BAD_PARAM (),
        ::CORBA::Object::_nil ());
      }

      if (ACE_OS::strcmp (name, "dataout") == 0)
      {
        return this->executor_->get_dataout (ACE_ENV_SINGLE_ARG_PARAMETER);
      }

       return CORBA::Object::_nil ();
    }

    // Supported operations.

    // Component attribute operations.

    // Private method to populate the port tables.
    void
    BMClosedED_Servant::populate_port_tables (
    ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
    {
      ::CORBA::Object_var obj_var;
      ::Components::EventConsumerBase_var ecb_var;

      obj_var =
      this->provide_dataout_i (
      ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;

      ecb_var =
      this->get_consumer_in_avail_i (
      ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;
    }
  }

  namespace CIAO_GLUE_BasicSP
  {
    BMClosedEDHome_Servant::BMClosedEDHome_Servant (
    ::BasicSP::CCM_BMClosedEDHome_ptr exe,
    ::CIAO::Session_Container *c)
      : CIAO::Home_Servant_Impl_Base (c),
        home_svnt_base (exe, c)
    {
    }

    BMClosedEDHome_Servant::~BMClosedEDHome_Servant (void)
    {
    }

    // Home operations.

    // Home supported interface operations.

    // Home factory and finder operations.

    // Home attribute operations.
  }

  extern "C" BMCLOSEDED_SVNT_Export ::PortableServer::Servant
  createBMClosedEDHome_Servant (
  ::Components::HomeExecutorBase_ptr p,
  CIAO::Session_Container *c
  ACE_ENV_ARG_DECL)
  {
    if (p == 0)
    {
      return 0;
    }

    ::BasicSP::CCM_BMClosedEDHome_var x =
    ::BasicSP::CCM_BMClosedEDHome::_narrow (
    p
    ACE_ENV_ARG_PARAMETER);
    ACE_CHECK_RETURN (0);

    if (::CORBA::is_nil (x.in ()))
    {
      return 0;
    }

    return new
    CIAO_GLUE_BasicSP::BMClosedEDHome_Servant (
    x.in (),
    c);
  }
}

