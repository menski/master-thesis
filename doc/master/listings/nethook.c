ssize_t
recvmsg(int sockfd, struct msghdr *msg, int flags)
{
  static recvmsg_t libc_recvmsg;
  static struct nethook_context context;
  struct nethook_shared *shared;
  pid_t           pid;
  struct nethook_data *data;
  int             result;
  ssize_t		libc_result;

  /* set shared memory */
  shared = context.shared;

  /* set libc recvmsg */
  if (libc_recvmsg == NULL) {
    /* set libc recvmsg */
    libc_recvmsg = (recvmsg_t) dlsym(RTLD_NEXT, "recvmsg");
    if (libc_recvmsg == NULL) {
      syslog(LOG_ERR, "failed to find libc recvmsg symbol: %s (%s at line %d)", dlerror(), __FILE__, __LINE__);
      return ERROR;
    }
  }

  /* ... */

  /* call libc recvmsg */
  libc_result = libc_recvmsg(sockfd, msg, flags);
  if (libc_result == ERROR) {
    syslog(LOG_ERR, "recvmsg error: %s", strerror(errno));
    return libc_result;
  }

  /* ... */

        /* set current data pointer */
        data = &shared->data[shared->data_count];
        memset(data, 0, sizeof(struct nethook_data));

  /* ... */

        /* set recv size */
        data->recv_size = libc_result;

        /* increment data count */
        shared->data_count++;

  /* ... */

  return libc_result;
}
