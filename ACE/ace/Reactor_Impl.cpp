#include "ace/Reactor_Impl.h"

#if defined (ghs)
# include "ace/Malloc_Base.h"
#endif

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_ALLOC_HOOK_DEFINE (ACE_Reactor_Impl)

ACE_Reactor_Impl::~ACE_Reactor_Impl ()
{
}

ACE_END_VERSIONED_NAMESPACE_DECL
