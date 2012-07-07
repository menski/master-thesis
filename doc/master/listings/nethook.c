ssize_t
recvmsg(int sockfd, struct msghdr *msg, int flags)
{
  /* ... */
  /* set libc recvmsg */
  if (libc_recvmsg == NULL) {
    /* set libc recvmsg */
    libc_recvmsg = (recvmsg_t) dlsym(RTLD_NEXT, "recvmsg");
    if (libc_recvmsg == NULL) {
      /* ... ERROR */
    }
  }
  /* ... */
  /* call libc recvmsg */
  libc_result = libc_recvmsg(sockfd, msg, flags);
  if (libc_result == ERROR) {
    /* ... ERROR */
  }
  /* ... */
        /* set recv size */
        data->recv_size = libc_result;
  /* ... */
  return libc_result;
}
