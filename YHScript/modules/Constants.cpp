#include "Constants.h"

#include <errno.h>
#if !defined(_MSC_VER)
#include <unistd.h>
#endif
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

NS_YHSCRIPT_MODULES_BEGIN

//文件相关的静态值
void defineFileConConstants(JSContext *cx,JSObject *target)
{
    // file access modes
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_RDONLY);
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_WRONLY);
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_RDWR);

  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IFMT);
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IFREG);
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IFDIR);
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IFCHR);
#ifdef S_IFBLK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IFBLK);
#endif

#ifdef S_IFIFO
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IFIFO);
#endif

#ifdef S_IFLNK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IFLNK);
#endif

#ifdef S_IFSOCK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IFSOCK);
#endif

#ifdef O_CREAT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_CREAT);
#endif

#ifdef O_EXCL
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_EXCL);
#endif

#ifdef O_NOCTTY
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_NOCTTY);
#endif

#ifdef O_TRUNC
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_TRUNC);
#endif

#ifdef O_APPEND
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_APPEND);
#endif

#ifdef O_DIRECTORY
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_DIRECTORY);
#endif

#ifdef O_EXCL
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_EXCL);
#endif

#ifdef O_NOFOLLOW
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_NOFOLLOW);
#endif

#ifdef O_SYNC
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_SYNC);
#endif

#ifdef O_SYMLINK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_SYMLINK);
#endif

#ifdef O_DIRECT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, O_DIRECT);
#endif

#ifdef S_IRWXU
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IRWXU);
#endif


#ifdef S_IRUSR
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IRUSR);
#endif

#ifdef S_IWUSR
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IWUSR);
#endif

#ifdef S_IXUSR
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IXUSR);
#endif


#ifdef S_IRWXG
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IRWXG);
#endif


#ifdef S_IRGRP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IRGRP);
#endif

#ifdef S_IWGRP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IWGRP);
#endif

#ifdef S_IXGRP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IXGRP);
#endif


#ifdef S_IRWXO
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IRWXO);
#endif


#ifdef S_IROTH
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IROTH);
#endif

#ifdef S_IWOTH
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IWOTH);
#endif

#ifdef S_IXOTH
  YHSCRIPT_DEFINE_CONSTANT(cx,target, S_IXOTH);
#endif

#ifdef E2BIG
  YHSCRIPT_DEFINE_CONSTANT(cx,target, E2BIG);
#endif

#ifdef EACCES
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EACCES);
#endif

#ifdef EADDRINUSE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EADDRINUSE);
#endif

#ifdef EADDRNOTAVAIL
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EADDRNOTAVAIL);
#endif

#ifdef EAFNOSUPPORT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EAFNOSUPPORT);
#endif

#ifdef EAGAIN
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EAGAIN);
#endif

#ifdef EALREADY
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EALREADY);
#endif

#ifdef EBADF
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EBADF);
#endif

#ifdef EBADMSG
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EBADMSG);
#endif

#ifdef EBUSY
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EBUSY);
#endif

#ifdef ECANCELED
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ECANCELED);
#endif

#ifdef ECHILD
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ECHILD);
#endif

#ifdef ECONNABORTED
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ECONNABORTED);
#endif

#ifdef ECONNREFUSED
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ECONNREFUSED);
#endif

#ifdef ECONNRESET
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ECONNRESET);
#endif

#ifdef EDEADLK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EDEADLK);
#endif

#ifdef EDESTADDRREQ
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EDESTADDRREQ);
#endif

#ifdef EDOM
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EDOM);
#endif

#ifdef EDQUOT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EDQUOT);
#endif

#ifdef EEXIST
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EEXIST);
#endif

#ifdef EFAULT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EFAULT);
#endif

#ifdef EFBIG
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EFBIG);
#endif

#ifdef EHOSTUNREACH
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EHOSTUNREACH);
#endif

#ifdef EIDRM
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EIDRM);
#endif

#ifdef EILSEQ
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EILSEQ);
#endif

#ifdef EINPROGRESS
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EINPROGRESS);
#endif

#ifdef EINTR
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EINTR);
#endif

#ifdef EINVAL
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EINVAL);
#endif

#ifdef EIO
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EIO);
#endif

#ifdef EISCONN
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EISCONN);
#endif

#ifdef EISDIR
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EISDIR);
#endif

#ifdef ELOOP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ELOOP);
#endif

#ifdef EMFILE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EMFILE);
#endif

#ifdef EMLINK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EMLINK);
#endif

#ifdef EMSGSIZE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EMSGSIZE);
#endif

#ifdef EMULTIHOP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EMULTIHOP);
#endif

#ifdef ENAMETOOLONG
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENAMETOOLONG);
#endif

#ifdef ENETDOWN
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENETDOWN);
#endif

#ifdef ENETRESET
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENETRESET);
#endif

#ifdef ENETUNREACH
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENETUNREACH);
#endif

#ifdef ENFILE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENFILE);
#endif

#ifdef ENOBUFS
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOBUFS);
#endif

#ifdef ENODATA
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENODATA);
#endif

#ifdef ENODEV
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENODEV);
#endif

#ifdef ENOENT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOENT);
#endif

#ifdef ENOEXEC
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOEXEC);
#endif

#ifdef ENOLCK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOLCK);
#endif

#ifdef ENOLINK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOLINK);
#endif

#ifdef ENOMEM
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOMEM);
#endif

#ifdef ENOMSG
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOMSG);
#endif

#ifdef ENOPROTOOPT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOPROTOOPT);
#endif

#ifdef ENOSPC
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOSPC);
#endif

#ifdef ENOSR
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOSR);
#endif

#ifdef ENOSTR
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOSTR);
#endif

#ifdef ENOSYS
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOSYS);
#endif

#ifdef ENOTCONN
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOTCONN);
#endif

#ifdef ENOTDIR
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOTDIR);
#endif

#ifdef ENOTEMPTY
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOTEMPTY);
#endif

#ifdef ENOTSOCK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOTSOCK);
#endif

#ifdef ENOTSUP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOTSUP);
#endif

#ifdef ENOTTY
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENOTTY);
#endif

#ifdef ENXIO
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ENXIO);
#endif

#ifdef EOPNOTSUPP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EOPNOTSUPP);
#endif

#ifdef EOVERFLOW
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EOVERFLOW);
#endif

#ifdef EPERM
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EPERM);
#endif

#ifdef EPIPE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EPIPE);
#endif

#ifdef EPROTO
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EPROTO);
#endif

#ifdef EPROTONOSUPPORT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EPROTONOSUPPORT);
#endif

#ifdef EPROTOTYPE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EPROTOTYPE);
#endif

#ifdef ERANGE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ERANGE);
#endif

#ifdef EROFS
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EROFS);
#endif

#ifdef ESPIPE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ESPIPE);
#endif

#ifdef ESRCH
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ESRCH);
#endif

#ifdef ESTALE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ESTALE);
#endif

#ifdef ETIME
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ETIME);
#endif

#ifdef ETIMEDOUT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ETIMEDOUT);
#endif

#ifdef ETXTBSY
  YHSCRIPT_DEFINE_CONSTANT(cx,target, ETXTBSY);
#endif

#ifdef EWOULDBLOCK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EWOULDBLOCK);
#endif

#ifdef EXDEV
  YHSCRIPT_DEFINE_CONSTANT(cx,target, EXDEV);
#endif

#ifdef WSAEINTR
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEINTR);
#endif

#ifdef WSAEBADF
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEBADF);
#endif

#ifdef WSAEACCES
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEACCES);
#endif

#ifdef WSAEFAULT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEFAULT);
#endif

#ifdef WSAEINVAL
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEINVAL);
#endif

#ifdef WSAEMFILE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEMFILE);
#endif

#ifdef WSAEWOULDBLOCK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEWOULDBLOCK);
#endif

#ifdef WSAEINPROGRESS
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEINPROGRESS);
#endif

#ifdef WSAEALREADY
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEALREADY);
#endif

#ifdef WSAENOTSOCK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAENOTSOCK);
#endif

#ifdef WSAEDESTADDRREQ
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEDESTADDRREQ);
#endif

#ifdef WSAEMSGSIZE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEMSGSIZE);
#endif

#ifdef WSAEPROTOTYPE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEPROTOTYPE);
#endif

#ifdef WSAENOPROTOOPT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAENOPROTOOPT);
#endif

#ifdef WSAEPROTONOSUPPORT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEPROTONOSUPPORT);
#endif

#ifdef WSAESOCKTNOSUPPORT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAESOCKTNOSUPPORT);
#endif

#ifdef WSAEOPNOTSUPP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEOPNOTSUPP);
#endif

#ifdef WSAEPFNOSUPPORT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEPFNOSUPPORT);
#endif

#ifdef WSAEAFNOSUPPORT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEAFNOSUPPORT);
#endif

#ifdef WSAEADDRINUSE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEADDRINUSE);
#endif

#ifdef WSAEADDRNOTAVAIL
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEADDRNOTAVAIL);
#endif

#ifdef WSAENETDOWN
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAENETDOWN);
#endif

#ifdef WSAENETUNREACH
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAENETUNREACH);
#endif

#ifdef WSAENETRESET
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAENETRESET);
#endif

#ifdef WSAECONNABORTED
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAECONNABORTED);
#endif

#ifdef WSAECONNRESET
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAECONNRESET);
#endif

#ifdef WSAENOBUFS
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAENOBUFS);
#endif

#ifdef WSAEISCONN
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEISCONN);
#endif

#ifdef WSAENOTCONN
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAENOTCONN);
#endif

#ifdef WSAESHUTDOWN
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAESHUTDOWN);
#endif

#ifdef WSAETOOMANYREFS
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAETOOMANYREFS);
#endif

#ifdef WSAETIMEDOUT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAETIMEDOUT);
#endif

#ifdef WSAECONNREFUSED
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAECONNREFUSED);
#endif

#ifdef WSAELOOP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAELOOP);
#endif

#ifdef WSAENAMETOOLONG
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAENAMETOOLONG);
#endif

#ifdef WSAEHOSTDOWN
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEHOSTDOWN);
#endif

#ifdef WSAEHOSTUNREACH
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEHOSTUNREACH);
#endif

#ifdef WSAENOTEMPTY
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAENOTEMPTY);
#endif

#ifdef WSAEPROCLIM
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEPROCLIM);
#endif

#ifdef WSAEUSERS
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEUSERS);
#endif

#ifdef WSAEDQUOT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEDQUOT);
#endif

#ifdef WSAESTALE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAESTALE);
#endif

#ifdef WSAEREMOTE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEREMOTE);
#endif

#ifdef WSASYSNOTREADY
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSASYSNOTREADY);
#endif

#ifdef WSAVERNOTSUPPORTED
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAVERNOTSUPPORTED);
#endif

#ifdef WSANOTINITIALISED
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSANOTINITIALISED);
#endif

#ifdef WSAEDISCON
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEDISCON);
#endif

#ifdef WSAENOMORE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAENOMORE);
#endif

#ifdef WSAECANCELLED
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAECANCELLED);
#endif

#ifdef WSAEINVALIDPROCTABLE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEINVALIDPROCTABLE);
#endif

#ifdef WSAEINVALIDPROVIDER
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEINVALIDPROVIDER);
#endif

#ifdef WSAEPROVIDERFAILEDINIT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEPROVIDERFAILEDINIT);
#endif

#ifdef WSASYSCALLFAILURE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSASYSCALLFAILURE);
#endif

#ifdef WSASERVICE_NOT_FOUND
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSASERVICE_NOT_FOUND);
#endif

#ifdef WSATYPE_NOT_FOUND
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSATYPE_NOT_FOUND);
#endif

#ifdef WSA_E_NO_MORE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSA_E_NO_MORE);
#endif

#ifdef WSA_E_CANCELLED
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSA_E_CANCELLED);
#endif

#ifdef WSAEREFUSED
  YHSCRIPT_DEFINE_CONSTANT(cx,target, WSAEREFUSED);
#endif

#ifdef SIGHUP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGHUP);
#endif

#ifdef SIGINT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGINT);
#endif

#ifdef SIGQUIT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGQUIT);
#endif

#ifdef SIGILL
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGILL);
#endif

#ifdef SIGTRAP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGTRAP);
#endif

#ifdef SIGABRT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGABRT);
#endif

#ifdef SIGIOT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGIOT);
#endif

#ifdef SIGBUS
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGBUS);
#endif

#ifdef SIGFPE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGFPE);
#endif

#ifdef SIGKILL
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGKILL);
#endif

#ifdef SIGUSR1
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGUSR1);
#endif

#ifdef SIGSEGV
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGSEGV);
#endif

#ifdef SIGUSR2
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGUSR2);
#endif

#ifdef SIGPIPE
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGPIPE);
#endif

#ifdef SIGALRM
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGALRM);
#endif

  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGTERM);

#ifdef SIGCHLD
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGCHLD);
#endif

#ifdef SIGSTKFLT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGSTKFLT);
#endif


#ifdef SIGCONT
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGCONT);
#endif

#ifdef SIGSTOP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGSTOP);
#endif

#ifdef SIGTSTP
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGTSTP);
#endif

#ifdef SIGBREAK
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGBREAK);
#endif

#ifdef SIGTTIN
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGTTIN);
#endif

#ifdef SIGTTOU
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGTTOU);
#endif

#ifdef SIGURG
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGURG);
#endif

#ifdef SIGXCPU
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGXCPU);
#endif

#ifdef SIGXFSZ
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGXFSZ);
#endif

#ifdef SIGVTALRM
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGVTALRM);
#endif

#ifdef SIGPROF
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGPROF);
#endif

#ifdef SIGWINCH
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGWINCH);
#endif

#ifdef SIGIO
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGIO);
#endif

#ifdef SIGPOLL
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGPOLL);
#endif

#ifdef SIGLOST
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGLOST);
#endif

#ifdef SIGPWR
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGPWR);
#endif

#ifdef SIGSYS
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGSYS);
#endif

#ifdef SIGUNUSED
  YHSCRIPT_DEFINE_CONSTANT(cx,target, SIGUNUSED);
#endif
}

Module Constants::s_moduleData=YHSCRIPT_MODULE_DATA(constants,Constants::registerModule);

void Constants::registerModule(JSContext *cx,JSObject *module)
{
    defineFileConConstants(cx,module);
}

NS_YHSCRIPT_MODULES_END