/* nethook data */
struct nethook_data {
  enum nethook_hooks hook;
  int32_t         protocol;
  struct sockaddr_storage address;
  socklen_t       address_size;
  ssize_t         recv_size;
};
