/* -*- C++ -*- */

// ============================================================================
// $Id$
//
// = LIBRARY
//    Admin
// 
// = FILENAME
//    Admin.cpp
//
// = AUTHOR
//    Marina Spivak <marina@cs.wustl.edu>
//    Seth Widoff <sbw1@cs.wustl.edu>
// 
// ============================================================================

#if !defined (TAO_ADMIN_C)
#define TAO_ADMIN_C

#include "Admin.h"

template <class TRADER>
const char* TAO_Admin<TRADER>::NAME = "Trader: Admin";

template <class TRADER>  
TAO_Admin<TRADER>::TAO_Admin (TRADER &trader)
  : trader_ (trader),
    TAO_Trader_Components <POA_CosTrading::Admin> (trader.trading_components ()),
    TAO_Import_Attributes <POA_CosTrading::Admin> (trader.import_attributes ()),
    TAO_Support_Attributes <POA_CosTrading::Admin> (trader.support_attributes ()),
    TAO_Link_Attributes <POA_CosTrading::Admin> (trader.link_attributes ())
{
}

template <class TRADER>
TAO_Admin<TRADER>::~TAO_Admin (void)
{
}

template <class TRADER> CosTrading::Admin::OctetSeq * 
TAO_Admin<TRADER>::request_id_stem (CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  return 0;
}

template <class TRADER> CORBA::ULong 
TAO_Admin<TRADER>::set_def_search_card (CORBA::ULong value,
					CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException)) 
{
  CORBA::ULong return_value =
    this->trader_.import_attributes ().def_search_card ();

  this->trader_.import_attributes ().def_search_card (value);
  return return_value;
}

template <class TRADER> CORBA::ULong 
TAO_Admin<TRADER>::set_max_search_card (CORBA::ULong value,
					CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CORBA::ULong return_value =
    this->trader_.import_attributes ().max_search_card ();

  this->trader_.import_attributes ().max_search_card (value);
  return return_value;
}

template <class TRADER> CORBA::ULong 
TAO_Admin<TRADER>::set_def_match_card (CORBA::ULong value,
				       CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CORBA::ULong return_value =
    this->trader_.import_attributes ().def_match_card ();

  this->trader_.import_attributes ().def_match_card (value);
  return return_value;
}

template <class TRADER> CORBA::ULong 
TAO_Admin<TRADER>::set_max_match_card (CORBA::ULong value,
				       CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CORBA::ULong return_value =
    this->trader_.import_attributes ().max_match_card ();

  this->trader_.import_attributes ().max_match_card (value);
  return return_value;
}

template <class TRADER> CORBA::ULong 
TAO_Admin<TRADER>::set_def_return_card (CORBA::ULong value,
					CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CORBA::ULong return_value =
    this->trader_.import_attributes ().def_return_card ();
  
  this->trader_.import_attributes ().def_return_card (value);
  return return_value;
}

template <class TRADER> CORBA::ULong 
TAO_Admin<TRADER>::set_max_return_card (CORBA::ULong value,
					CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CORBA::ULong return_value =
    this->trader_.import_attributes ().max_return_card ();
  
  this->trader_.import_attributes ().max_return_card (value);
  return return_value;
}

template <class TRADER> CORBA::ULong 
TAO_Admin<TRADER>::set_max_list (CORBA::ULong value,
				 CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CORBA::ULong return_value =
    this->trader_.import_attributes ().max_list ();
  
  this->trader_.import_attributes ().max_list (value);
  return return_value;
}

template <class TRADER> CORBA::Boolean 
TAO_Admin<TRADER>::
set_supports_modifiable_properties (CORBA::Boolean value,
				    CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CORBA::Boolean return_value =
    this->trader_.support_attributes ().supports_modifiable_properties ();
  
  this->trader_.support_attributes ().supports_modifiable_properties (value);
  return return_value;
}

template <class TRADER> CORBA::Boolean 
TAO_Admin<TRADER>::
set_supports_dynamic_properties (CORBA::Boolean value,
				 CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CORBA::Boolean return_value =
    this->trader_.support_attributes ().supports_dynamic_properties ();
  
  this->trader_.support_attributes ().supports_dynamic_properties (value);
  return return_value;
}

template <class TRADER> CORBA::Boolean 
TAO_Admin<TRADER>::set_supports_proxy_offers (CORBA::Boolean value,      
					      CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CORBA::Boolean return_value =
    this->trader_.support_attributes ().supports_proxy_offers ();
  
  this->trader_.support_attributes ().supports_proxy_offers (value);
  return return_value;
}

template <class TRADER> CORBA::ULong 
TAO_Admin<TRADER>::set_def_hop_count (CORBA::ULong value,
				      CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CORBA::ULong return_value =
    this->trader_.import_attributes ().def_hop_count ();
  
  this->trader_.import_attributes ().def_hop_count (value);
  return return_value;
}

template <class TRADER> CORBA::ULong 
TAO_Admin<TRADER>::set_max_hop_count (CORBA::ULong value,
				      CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CORBA::ULong return_value =
    this->trader_.import_attributes ().max_hop_count ();
    
  this->trader_.import_attributes ().max_hop_count (value);
  return return_value;
}

template <class TRADER> CosTrading::FollowOption 
TAO_Admin<TRADER>::set_def_follow_policy (CosTrading::FollowOption policy,
					  CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CosTrading::FollowOption return_value =
    this->trader_.import_attributes ().def_follow_policy ();
    
  this->trader_.import_attributes ().def_follow_policy (policy);
  return return_value;
}

template <class TRADER> CosTrading::FollowOption 
TAO_Admin<TRADER>::set_max_follow_policy (CosTrading::FollowOption policy,
					  CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CosTrading::FollowOption return_value =
    this->trader_.import_attributes ().max_follow_policy ();
    
  this->trader_.import_attributes ().max_follow_policy (policy);
  return return_value;
}

template <class TRADER> CosTrading::FollowOption 
TAO_Admin<TRADER>::
set_max_link_follow_policy (CosTrading::FollowOption policy,
			    CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CosTrading::FollowOption return_value =
    this->trader_.link_attributes ().max_link_follow_policy ();
  
  this->trader_.link_attributes ().max_link_follow_policy (policy);
  return return_value;
}

template <class TRADER> CosTrading::TypeRepository_ptr 
TAO_Admin<TRADER>::
set_type_repos (CosTrading::TypeRepository_ptr repository,
		CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  CosTrading::TypeRepository_ptr return_value =
    this->trader_.support_attributes ().type_repos ();
  
  this->trader_.support_attributes ().type_repos (repository);
  return return_value;
}

template <class TRADER> CosTrading::Admin::OctetSeq* 
TAO_Admin<TRADER>::set_request_id_stem (const CosTrading::Admin::OctetSeq& stem,
					CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException))
{
  return 0;
}

template <class TRADER> void 
TAO_Admin<TRADER>::list_offers (CORBA::ULong how_many, 
				CosTrading::OfferIdSeq_out ids, 
				CosTrading::OfferIdIterator_out id_itr,
				CORBA::Environment& _env)
  TAO_THROW_SPEC ((CORBA::SystemException,) 
		  CosTrading::NotImplemented)
{
  // This method only applies when the register interface is implemented
  if (CORBA::is_nil(this->trader_.trading_components().register_if()))
    TAO_THROW (CosTrading::NotImplemented());

  TRADER::SERVICE_TYPE_MAP& type_map = this->trader_.service_type_map();

  CosTrading::OfferIdIterator_ptr oi =
    type_map.retrieve_all_offer_ids ()->_this (_env);
  TAO_CHECK_ENV_RETURN (_env,);
      
  id_itr = CosTrading::OfferIdIterator::_nil ();
  if (how_many > 0)
    {      
      if (oi->next_n (how_many, ids, _env) == (CORBA::Boolean)0)
	{
	  // No more items left in the iterator.
	  oi->destroy (_env);
	  oi = CosTrading::OfferIdIterator::_nil ();
	}       
    }
  else
    ids = new CosTrading::OfferIdSeq(0);
}

template <class TRADER> void 
TAO_Admin<TRADER>::list_proxies (CORBA::ULong how_many, 
				 CosTrading::OfferIdSeq_out ids, 
				 CosTrading::OfferIdIterator_out id_itr,
				 CORBA::Environment& _env) 
  TAO_THROW_SPEC ((CORBA::SystemException,
		  CosTrading::NotImplemented))
{
  TAO_THROW (CosTrading::NotImplemented ());
}

#endif /* TAO_ADMIN_C */
