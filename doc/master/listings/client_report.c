#define UDP_TRUESIZE(X) (((int) (((X) + 63) / 128)) * 128 + 376)

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


switch (network->protocol) {
  case IPPROTO_TCP:
    /* ... */
  case IPPROTO_UDP:
    maximum = (uint32_t) network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].maximum / UDP_TRUESIZE(network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_SIZE].maximum);
    current = (uint32_t) network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_QUEUE].current / UDP_TRUESIZE(network->metrics.udp[CLIENT_METRIC_UDP_RECEIVE_SIZE].history_median);
    break;
}
