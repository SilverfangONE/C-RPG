## <code>C-RPG</code>
# @author: SilverfangOne

### Allgemein
- Diese RPG Game engine verwedet Sprites/Tiles mit der groe�e von 16x16 pixeln.
- Nutzt SNES aufl�sung f�r Tiles/Sprites: 256 x 224.
- Die eigentliche Aufl�sung soll dan �bers Game konfiguriert werden.

### Projekt bauen:
Einfach im Projekt Ordner <code>make</code> in der cmd ausf�hren.

### Libs die Verwendet werden:
- JSON: https://github.com/DaveGamble/cJSON/tree/master
- LOGGER: https://github.com/rxi/log.c
- SDL: https://www.libsdl.org/
- Hashmap: https://github.com/tidwall/hashmap.c


### <code>Setup C ENV in Windows:</code>
> 1. download zip mingw64: https://winlibs.com/
> 2. put into C:\ (system drive)
> 3. set env path var to mingw64 bin
> 4. rename ming32-make to make 

## ERRNOS
| Code | Fehlerbezeichnung     | Beschreibung                                 |
|------|-----------------------|----------------------------------------------|
| 1    | EPERM                 | Operation not permitted                      |
| 2    | ENOENT                | No such file or directory                   |
| 3    | ESRCH                 | No such process                              |
| 4    | EINTR                 | Interrupted system call                      |
| 5    | EIO                   | Input/output error                           |
| 6    | ENXIO                 | No such device or address                    |
| 7    | E2BIG                 | Argument list too long                       |
| 8    | ENOEXEC               | Exec format error                            |
| 9    | EBADF                 | Bad file descriptor                          |
| 10   | ECHILD                | No child processes                           |
| 11   | EAGAIN                | Resource temporarily unavailable             |
| 11   | EWOULDBLOCK           | Resource temporarily unavailable             |
| 12   | ENOMEM                | Cannot allocate memory                       |
| 13   | EACCES                | Permission denied                            |
| 14   | EFAULT                | Bad address                                  |
| 15   | ENOTBLK               | Block device required                        |
| 16   | EBUSY                 | Device or resource busy                      |
| 17   | EEXIST                | File exists                                  |
| 18   | EXDEV                 | Invalid cross-device link                    |
| 19   | ENODEV                | No such device                               |
| 20   | ENOTDIR               | Not a directory                              |
| 21   | EISDIR                | Is a directory                               |
| 22   | EINVAL                | Invalid argument                             |
| 23   | ENFILE                | Too many open files in system                |
| 24   | EMFILE                | Too many open files                          |
| 25   | ENOTTY                | Inappropriate ioctl for device               |
| 26   | ETXTBSY               | Text file busy                               |
| 27   | EFBIG                 | File too large                               |
| 28   | ENOSPC                | No space left on device                      |
| 29   | ESPIPE                | Illegal seek                                 |
| 30   | EROFS                 | Read-only file system                        |
| 31   | EMLINK                | Too many links                               |
| 32   | EPIPE                 | Broken pipe                                  |
| 33   | EDOM                  | Numerical argument out of domain             |
| 34   | ERANGE                | Numerical result out of range                |
| 35   | EDEADLK               | Resource deadlock avoided                    |
| 35   | EDEADLOCK             | Resource deadlock avoided                    |
| 36   | ENAMETOOLONG          | File name too long                           |
| 37   | ENOLCK                | No locks available                           |
| 38   | ENOSYS                | Function not implemented                     |
| 39   | ENOTEMPTY             | Directory not empty                          |
| 40   | ELOOP                 | Too many levels of symbolic links            |
| 42   | ENOMSG                | No message of desired type                   |
| 43   | EIDRM                 | Identifier removed                           |
| 44   | ECHRNG                | Channel number out of range                  |
| 45   | EL2NSYNC              | Level 2 not synchronized                     |
| 46   | EL3HLT                | Level 3 halted                               |
| 47   | EL3RST                | Level 3 reset                                |
| 48   | ELNRNG                | Link number out of range                     |
| 49   | EUNATCH               | Protocol driver not attached                 |
| 50   | ENOCSI                | No CSI structure available                   |
| 51   | EL2HLT                | Level 2 halted                               |
| 52   | EBADE                 | Invalid exchange                             |
| 53   | EBADR                 | Invalid request descriptor                   |
| 54   | EXFULL                | Exchange full                                |
| 55   | ENOANO                | No anode                                     |
| 56   | EBADRQC               | Invalid request code                         |
| 57   | EBADSLT               | Invalid slot                                 |
| 59   | EBFONT                | Bad font file format                         |
| 60   | ENOSTR                | Device not a stream                          |
| 61   | ENODATA               | No data available                            |
| 62   | ETIME                 | Timer expired                                |
| 63   | ENOSR                 | Out of streams resources                     |
| 64   | ENONET                | Machine is not on the network                |
| 65   | ENOPKG                | Package not installed                        |
| 66   | EREMOTE               | Object is remote                             |
| 67   | ENOLINK               | Link has been severed                        |
| 68   | EADV                  | Advertise error                              |
| 69   | ESRMNT                | Srmount error                                |
| 70   | ECOMM                 | Communication error on send                  |
| 71   | EPROTO                | Protocol error                               |
| 72   | EMULTIHOP             | Multihop attempted                           |
| 73   | EDOTDOT               | RFS specific error                           |
| 74   | EBADMSG               | Bad message                                  |
| 75   | EOVERFLOW             | Value too large for defined data type        |
| 76   | ENOTUNIQ              | Name not unique on network                   |
| 77   | EBADFD                | File descriptor in bad state                 |
| 78   | EREMCHG               | Remote address changed                       |
| 79   | ELIBACC               | Can not access a needed shared library       |
| 80   | ELIBBAD               | Accessing a corrupted shared library         |
| 81   | ELIBSCN               | .lib section in a.out corrupted              |
| 82   | ELIBMAX               | Attempting to link in too many shared libraries |
| 83   | ELIBEXEC              | Cannot exec a shared library directly        |
| 84   | EILSEQ                | Invalid or incomplete multibyte or wide character |
| 85   | ERESTART              | Interrupted system call should be restarted  |
| 86   | ESTRPIPE              | Streams pipe error                           |
| 87   | EUSERS                | Too many users                               |
| 88   | ENOTSOCK              | Socket operation on non-socket               |
| 89   | EDESTADDRREQ          | Destination address required                 |
| 90   | EMSGSIZE              | Message too long                             |
| 91   | EPROTOTYPE            | Protocol wrong type for socket               |
| 92   | ENOPROTOOPT           | Protocol not available                       |
| 93   | EPROTONOSUPPORT       | Protocol not supported                       |
| 94   | ESOCKTNOSUPPORT       | Socket type not supported                    |
| 95   | ENOTSUP               | Operation not supported                      |
| 95   | EOPNOTSUPP             | Operation not supported                      |
| 96   | EPFNOSUPPORT          | Protocol family not supported                |
| 97   | EAFNOSUPPORT          | Address family not supported by protocol     |
| 98   | EADDRINUSE            | Address already in use                       |
| 99   | EADDRNOTAVAIL         | Cannot assign requested address              |
| 100  | ENETDOWN              | Network is down                              |
| 101  | ENETUNREACH           | Network is unreachable                       |
| 102  | ENETRESET             | Network dropped connection on reset          |
| 103  | ECONNABORTED          | Software caused connection abort             |
| 104  | ECONNRESET            | Connection reset by peer                     |
| 105  | ENOBUFS               | No buffer space available                    |
| 106  | EISCONN               | Transport endpoint is already connected      |
| 107  | ENOTCONN              | Transport endpoint is not connected          |
| 108  | ESHUTDOWN             | Cannot send after transport endpoint shutdown |
| 109  | ETOOMANYREFS          | Too many references: cannot splice           |
| 110  | ETIMEDOUT             | Connection timed out                         |
| 111  | ECONNREFUSED          | Connection refused                            |
| 112  | EHOSTDOWN             | Host is down                                 |
| 113  | EHOSTUNREACH          | No route to host                             |
| 114  | EALREADY              | Operation already in progress                |
| 115  | EINPROGRESS           | Operation now in progress                    |
| 116  | ESTALE                | Stale file handle                            |
| 117  | EUCLEAN               | Structure needs cleaning                     |
| 118  | ENOTNAM               | Not a XENIX named type file                  |
| 119  | ENAVAIL               | No XENIX semaphores available                |
| 120  | EISNAM                | Is a named type file                         |
| 121  | EREMOTEIO             | Remote I/O error                             |
| 122  | EDQUOT                | Disk quota exceeded                          |
| 123  | ENOMEDIUM             | No medium found                              |
| 124  | EMEDIUMTYPE           | Wrong medium type                            |
| 125  | ECANCELED             | Operation canceled                            |
| 126  | ENOKEY                | Required key not available                   |
| 127  | EKEYEXPIRED           | Key has expired                              |
| 128  | EKEYREVOKED           | Key has been revoked                         |
| 129  | EKEYREJECTED          | Key was rejected by service                  |
| 130  | EOWNERDEAD            | Owner died                                   |
| 131  | ENOTRECOVERABLE       | State not recoverable                        |
| 132  | ERFKILL               | Operation not possible due to RF-kill        |
| 133  | EHWPOISON             | Memory page has hardware error               |
