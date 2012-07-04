/*
 * update metrics and credits
 */
  static int
client_report_update(struct client_context * context, struct client_network * network)
{
  int  result;
  int  packet_median;

  /* update metrics */
  result = client_metric_update(context, network);
  if (result == ERROR) {
    syslog(LOG_ERR, "could not update metrics (%s at line %d)", __FILE__, __LINE__);
    return ERROR;
  }

  /* calculate credits from metrics */
  switch (network->protocol) {
    case IPPROTO_TCP:
      /* ... */
      break;
    case IPPROTO_UDP:
      packet_median = UDP_TRUESIZE(network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_SIZE].history_median);
      if (network->metrics.udp[CLIENT_METRIC_UDP_DROP].history[1] > 0 &&
          network->metrics.udp[CLIENT_METRIC_UDP_DROP].current - network->metrics.udp[CLIENT_METRIC_UDP_DROP].history[1] > 0) {
        network->credits.hard = 0;
        network->credits.soft = 0;
      }
      else {
        network->credits.hard = (uint32_t) ((network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].maximum - network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].current) / packet_median); 
        network->credits.soft = (uint32_t) ((network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].maximum - network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].history_median) / packet_median); 
      }
      break;
  }

  return SUCCESS;
}

/* calculate maximum and current */
switch (network->protocol) {
  case IPPROTO_TCP:
    maximum = network->metrics.tcp[CLIENT_METRIC_TCP_SYN_RECEIVED].maximum + network->metrics.tcp[CLIENT_METRIC_TCP_ACKNOWLEDGED].maximum;
    current = network->metrics.tcp[CLIENT_METRIC_TCP_SYN_RECEIVED].current + network->metrics.tcp[CLIENT_METRIC_TCP_ACKNOWLEDGED].current;
    break;
  case IPPROTO_UDP:
    maximum = (uint32_t) network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].maximum / UDP_TRUESIZE(network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_SIZE].maximum);
    current = (uint32_t) network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].current / UDP_TRUESIZE(network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_SIZE].history_median);
    break;
}
