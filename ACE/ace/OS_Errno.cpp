// -*- C++ -*-
#include "ace/OS_Errno.h"

// Inlining this class on debug builds with gcc on Solaris can cause
// deadlocks during static initialization. On non debug builds it
// causes compilation errors.
#if !defined (ACE_HAS_INLINED_OSCALLS) || \
    (defined (__GNUG__) && defined (__sun__))
# if defined (ACE_INLINE)
#  undef ACE_INLINE
# endif /* ACE_INLINE */
# define ACE_INLINE
# include "ace/OS_Errno.inl"
#endif /* ACE_HAS_INLINED_OSCALLS */

