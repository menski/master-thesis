/* open proc udp */
file_stream = fopen("/proc/net/udp", "r");
if (file_stream == NULL) {
  syslog(LOG_ERR, "could not open udp proc file stream: %m (%s at line %d)", __FILE__, __LINE__);
  return ERROR;
}
/* skip headline */
result = fscanf(file_stream, "%*[^\n]\n");
if (ferror(file_stream) || result != 0) {
  syslog(LOG_ERR, "could not skip headline of udp proc file stream: %m (%s at line %d)", __FILE__, __LINE__);
  fclose(file_stream);
  return ERROR;
}
/* iterate over proc udp and parse lines */
while (!feof(file_stream)) {
  /* parse relevant values from single line */
  result = fscanf(file_stream, "%*d: %8x:%4hx %*x:%*x %x %*x:%lx %*[^\n]\n", &ipv4_address.s_addr, &port, &state, &receive_queue);
  if (ferror(file_stream) || result != 4) {
    syslog(LOG_ERR, "could not parse udp proc file line: %m (%s at line %d)", __FILE__, __LINE__);
    fclose(file_stream);
    return ERROR;
  }
  /* set source address to address storage */
  result = address_storage(AF_INET, (void *) &ipv4_address, htons(port), &source_address);
  if (result == ERROR) {
    syslog(LOG_ERR, "failed to set udp source address to address storage (%s at line %d)", __FILE__, __LINE__);
    fclose(file_stream);
    return ERROR;
  }
  /* compare source address and network address */
  if (state == UDP_LISTEN &&
      address_inet_compare(&source_address, &network->address) == 0) {
    network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].current = receive_queue;
    ipv4_found = SUCCESS;
    break;
  }
}
/* close proc udp */
result = fclose(file_stream);


/* maximum value from proc */
if (network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].maximum == 0) {
  file_stream = fopen("/proc/sys/net/core/rmem_default", "r");
  if (file_stream == NULL) {
    syslog(LOG_ERR, "could not open rmem_default proc file stream: %m (%s at line %d)", __FILE__, __LINE__);
    return ERROR;
  }
  /* parse udp receive maximum from proc file */
  result = fscanf(file_stream, "%u", &network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].maximum);
  if (ferror(file_stream) || result != 1) {
    syslog(LOG_ERR, "could not parse value for receive queue maximum from proc file: %m (%s at line %d)", __FILE__, __LINE__);
    return ERROR;
  }
  result = fclose(file_stream);
  if (result == ERROR) {
    syslog(LOG_ERR, "could not close proc file stream: %m (%s at line %d)", __FILE__, __LINE__);
    return ERROR;
  }
}


/* gather drops for udp */
file_stream = fopen("/proc/net/snmp", "r");
if (file_stream == NULL) {
  syslog(LOG_ERR, "could not open snmp proc file stream: %m (%s at line %d)", __FILE__, __LINE__);
  return ERROR;
}
while (!feof(file_stream)) {
  /* parse relevant values from single line */
  result = fscanf(file_stream, "Udp: %*d %*d %u %*[^\n]\n", &network->metrics.udp[CLIENT_METRIC_UDP_DROP].current);
  if (ferror(file_stream)) {
    fclose(file_stream);
    syslog(LOG_ERR, "could not parse value for udp drops from proc file: %m (%s at line %d)", __FILE__, __LINE__);
    return ERROR;
  }
  if (result == 1) {
    /* increase drop count to distinguish from zero */
    network->metrics.udp[CLIENT_METRIC_UDP_DROP].current++;
    break;
  }

  /* skip line */
  result = fscanf(file_stream, "%*[^\n]\n");
  if (ferror(file_stream) || result != 0) {
    fclose(file_stream);
    syslog(LOG_ERR, "could not parse value for udp drops from proc file: %m (%s at line %d)", __FILE__, __LINE__);
    return ERROR;
  }
}
/* close proc snmp */
result = fclose(file_stream);
if (result == -1) {
  syslog(LOG_ERR, "could not close snmp proc file stream: %m (%s at line %d)", __FILE__, __LINE__);
  return ERROR;
}
