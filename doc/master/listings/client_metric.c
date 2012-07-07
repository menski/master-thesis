file_stream = fopen("/proc/net/udp", "r");
if (file_stream == NULL) {
  /* ... ERROR */
}
/* skip headline */
result = fscanf(file_stream, "%*[^\n]\n");
if (ferror(file_stream) || result != 0) {
  /* ... ERROR */
}
/* iterate over proc udp and parse lines */
while (!feof(file_stream)) {
  /* parse relevant values from single line */
  result = fscanf(file_stream, "%*d: %8x:%4hx %*x:%*x %x %*x:%lx %*[^\n]\n", &ipv4_address.s_addr, &port, &state, &receive_queue);
  if (ferror(file_stream) || result != 4) {
    /* ... ERROR */
  }
  /* set source address to address storage */
  result = address_storage(AF_INET, (void *) &ipv4_address, htons(port), &source_address);
  if (result == ERROR) {
    /* ... ERROR */
  }
  /* compare source address and network address */
  if (state == UDP_LISTEN &&
      address_inet_compare(&source_address, &network->address) == 0) {
    network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].current = receive_queue;
    ipv4_found = SUCCESS;
    break;
  }
}


if (network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].maximum == 0) {
  file_stream = fopen("/proc/sys/net/core/rmem_default", "r");
  if (file_stream == NULL) {
    /* ... ERROR */
  }
  /* parse udp receive maximum from proc file */
  result = fscanf(file_stream, "%u", &network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].maximum);
  if (ferror(file_stream) || result != 1) {
    /* ... ERROR */
  }
  /* ... */
}


file_stream = fopen("/proc/net/snmp", "r");
if (file_stream == NULL) {
  /* ... ERROR */
}
while (!feof(file_stream)) {
  /* parse relevant values from single line */
  result = fscanf(file_stream, "Udp: %*d %*d %u %*[^\n]\n", &network->metrics.udp[CLIENT_METRIC_UDP_DROP].current);
  if (ferror(file_stream)) {
    /* ... ERROR */
  }
  if (result == 1) {
    /* increase drop count to distinguish from zero */
    network->metrics.udp[CLIENT_METRIC_UDP_DROP].current++;
    break;
  }
  /* ... skip line */
}
