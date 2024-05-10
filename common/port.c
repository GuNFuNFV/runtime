

#include "port.h"

extern struct Runtime_state *c;

#define ETH_RSS_E1000_IGB (    \
    ETH_RSS_IPV4 |             \
    ETH_RSS_NONFRAG_IPV4_TCP | \
    ETH_RSS_NONFRAG_IPV4_UDP | \
    ETH_RSS_IPV6 |             \
    ETH_RSS_NONFRAG_IPV6_TCP | \
    ETH_RSS_NONFRAG_IPV6_UDP | \
    ETH_RSS_IPV6_EX |          \
    ETH_RSS_IPV6_TCP_EX |      \
    ETH_RSS_IPV6_UDP_EX)

static uint8_t rss_intel_key[40] = {0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x5B, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A,
                                    0x5B, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x5B, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A,
                                    0x6D, 0x5A, 0x5B, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x5B, 0x5A};

#define VMXNET3_RSS_OFFLOAD_ALL ( \
      ETH_RSS_IPV4 | \
      ETH_RSS_NONFRAG_IPV4_TCP | \
      ETH_RSS_IPV6 | \
      ETH_RSS_NONFRAG_IPV6_TCP)


static const struct rte_eth_conf port_conf_default = {.rxmode = {
     .mq_mode = RTE_ETH_MQ_RX_NONE,}, .txmode = {},};


// memory poolc
// number of cores
// port number

int port_init(struct port_parameter *portParameter) {
//    printf("port init started\n");
    struct rte_eth_conf port_conf = port_conf_default;
    struct rte_eth_txconf txconf;
    struct rte_eth_dev_info dev_info;
    const uint16_t rx_rings = portParameter->n_queue, tx_rings = portParameter->n_queue;

    int nb_ports = rte_eth_dev_count_avail();
    if (nb_ports == 0)
        rte_exit(EXIT_FAILURE, "No Ethernet ports - bye\n");

    int retval;
    uint16_t q;

    rte_eth_dev_info_get(portParameter->port, &dev_info);
//    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_MBUF_FAST_FREE)
//        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_MBUF_FAST_FREE;

    if (!rte_eth_dev_is_valid_port(portParameter->port)) {
        printf("error 1\n");
        return retval;
    }

    /* Configure the Ethernet device. */
    retval = rte_eth_dev_configure(portParameter->port, rx_rings, tx_rings, &port_conf);
    if (retval != 0) {
        printf("error 2\n");
        return retval;
    }

    retval = rte_eth_dev_adjust_nb_rx_tx_desc(portParameter->port, &(portParameter->nb_rxd), &(portParameter->nb_txd));

    if (retval != 0) {
        printf("error 3\n");
        return retval;
    }

    for (q = 0; q < rx_rings; q++) {
        retval = rte_eth_rx_queue_setup(portParameter->port, q, portParameter->nb_rxd,
                                        rte_eth_dev_socket_id(portParameter->port), NULL, portParameter->mempool);
        if (retval < 0) {
            printf("error 4\n");
            return retval;
        }
    }

    txconf = dev_info.default_txconf;
    txconf.offloads = port_conf.txmode.offloads;
    for (q = 0; q < tx_rings; q++) {
        retval = rte_eth_tx_queue_setup(portParameter->port, q, portParameter->nb_txd,
                                        rte_eth_dev_socket_id(portParameter->port), &txconf);
        if (retval < 0) {
            printf("error 5\n");
            return retval;
        }
    }
//    rte_eth_dev_set_mtu(portParameter->port, 3000);
    retval = rte_eth_dev_start(portParameter->port);
    if (retval < 0) {
        printf("error 6\n");
        return retval;
    }

    for (int i = 0; i < portParameter->n_queue; i++) {
        // 0 to core 2
        // 1 to core 4
        // 2 to core 6
        // etc.
        uint16_t core_id = 2 + 2 * i;
        create_flow_rule((uint16_t) i, core_id, portParameter->port);
    }
    /* Display the port MAC address. */
    struct rte_ether_addr addr;
    rte_eth_macaddr_get(portParameter->port, &addr);
    printf("Port %u MAC: %02" PRIx8
           " %02" PRIx8
           " %02" PRIx8
           " %02" PRIx8
           " %02" PRIx8
           " %02" PRIx8
           "\n", portParameter->port, addr.addr_bytes[0], addr.addr_bytes[1], addr.addr_bytes[2], addr.addr_bytes[3],
           addr.addr_bytes[4], addr.addr_bytes[5]);
    /* Enable RX in promiscuous mode for the Ethernet device. */
    rte_eth_promiscuous_enable(portParameter->port);
//    printf("port init done\n");
    return 1;
}

struct rte_flow *create_flow_rule(uint16_t queue_id, uint16_t core_id, uint16_t port_id) {
    struct rte_flow_error error;
    struct rte_flow_attr attr;
    struct rte_flow_item pattern[4];
    struct rte_flow_action action[2];
    struct rte_flow *flow;
    struct rte_flow_action_queue queue;
    struct rte_flow_item_ipv4 ip_spec;
    struct rte_flow_item_ipv4 ip_mask;
    struct rte_flow_item_tcp tcp_spec;
    struct rte_flow_item_tcp tcp_mask;
    queue.index = queue_id;

    printf("install flow rule\n");
    int res;

    flow = NULL;
    memset(pattern, 0, sizeof(pattern));
    memset(action, 0, sizeof(action));

    memset(&attr, 0, sizeof(struct rte_flow_attr));
    attr.ingress = 1;

    action[0].type = RTE_FLOW_ACTION_TYPE_QUEUE;
    action[0].conf = &queue;
    action[1].type = RTE_FLOW_ACTION_TYPE_END;
    ip_spec.hdr.src_addr = rte_cpu_to_be_32(0);
    ip_mask.hdr.src_addr = 0x00000000;
    ip_spec.hdr.dst_addr = rte_cpu_to_be_32(core_id);
    ip_mask.hdr.dst_addr = 0xffffffff;

//    tcp_spec.hdr.src_port = rte_cpu_to_be_16(0);
//    tcp_mask.hdr.src_port = 0x00;
//    tcp_spec.hdr.dst_port = rte_cpu_to_be_16(0);
//    tcp_mask.hdr.dst_port = 0x00;

//    pattern[0].type = RTE_FLOW_ITEM_TYPE_ETH;
    pattern[0].type = RTE_FLOW_ITEM_TYPE_IPV4;
    pattern[0].spec = &ip_spec;
    pattern[0].mask = &ip_mask;
//    pattern[2].type = RTE_FLOW_ITEM_TYPE_TCP;
//    pattern[2].spec = &tcp_spec;
//    pattern[2].mask = &tcp_mask;
    /* the final datablock_id must be always type end */
    pattern[1].type = RTE_FLOW_ITEM_TYPE_END;

    res = rte_flow_validate(port_id, &attr, pattern, action, &error);
    if (!res) {
        flow = rte_flow_create(port_id, &attr, pattern, action, &error);
    }

    if (!flow) {
        printf("Flow can't be created %d message: %s\n", error.type,
               error.message ? error.message : "(no stated reason)");
        rte_exit(EXIT_FAILURE, "error in creating flow");
    }
}