
#ifndef NFLAMBDA_RUNTIME_INTERVAL_TREE_H
#define NFLAMBDA_RUNTIME_INTERVAL_TREE_H

#include "fsm_amac_nf_common.h"
#include "common.h"
#include "stdint-gcc.h"
#include "stdbool.h"
#include "stdio.h"

#define DIMENSION 1 // fixed dimension for now
struct interval {
    uint16_t start;
    uint16_t end;
};

struct multi_dimensional_interval {
    struct interval structinterval[DIMENSION];
};

struct multi_dimensional_interval_tree_node {
    struct multi_dimensional_interval_tree_node *left;
    struct multi_dimensional_interval_tree_node *right;
    struct multi_dimensional_interval multi_dimensional_interval;
    uint16_t offset; // stored the offset of the value in the value array
    int dimension;
};


struct multi_dimensional_interval_tree {
    // an array of nodes of indefinite size
    struct multi_dimensional_interval_tree_node *root;
    int dimension;
    int depth;
};


struct interval_tree_state {
    CONTROL_VARIABLE_OFFSET key_offset;
    CONTROL_VARIABLE_OFFSET node_offset;
    char state_name[50];
    int state_id;
    int depth;
    int dimension;
    EVENT interval_tree_get_key_done;
    EVENT interval_tree_load_key_done;
    EVENT interval_tree_compare_success;
    EVENT interval_tree_compare_failure;

};

ACTOR_CONTROL_STATE_INIT(interval_tree_init);

INLINE_ACTOR_ACTION(interval_tree_rtc) {
    DEBUG_PRINT("interval_tree_rtc\n");
    struct interval_tree_state *intervalTreeState = (struct interval_tree_state *) m->control_state;
    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_ipv4_hdr*,
                                                            sizeof(struct rte_ether_hdr));
    struct rte_tcp_hdr *tcp_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_tcp_hdr*,
                                                          sizeof(struct rte_ether_hdr) + sizeof(struct rte_ipv4_hdr));
    uint16_t key = rte_be_to_cpu_16(tcp_hdr->src_port);
    // get the tree from the data state
    struct multi_dimensional_interval_tree *tree = (struct multi_dimensional_interval_tree *) m->data_state;
    struct multi_dimensional_interval_tree_node *node = tree->root;
    bool found = false;
    // search the node with rtc
    while (node != NULL) {
        if (key < node->multi_dimensional_interval.structinterval[0].start) {
            node = node->left;
        } else if (key >= node->multi_dimensional_interval.structinterval[0].end) {
            node = node->right;
        } else {
            // found the node
            int data_block_id = m->datablock_id;
            int offset = node->offset;
            m->local_offset[data_block_id] = offset;
            m->event = intervalTreeState->interval_tree_compare_success;
            found = true;
            break;
        }
    }
    if (!found) {
        m->event = 255;
        rte_pktmbuf_free(m->packet);
        DEBUG_PRINT("interval_tree_compare: not found\n");
    }
}

INLINE_ACTOR_ACTION(interval_tree_get_key) {
//    DEBUG_PRINT("interval_tree_get_key\n");
    struct interval_tree_state *intervalTreeState = (struct interval_tree_state *) m->control_state;
    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_ipv4_hdr*,
                                                            sizeof(struct rte_ether_hdr));
    struct rte_tcp_hdr *tcp_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_tcp_hdr*,
                                                          sizeof(struct rte_ether_hdr) + sizeof(struct rte_ipv4_hdr));
    // prefetch tcp_hdr
    rte_prefetch0(tcp_hdr);
    m->event = intervalTreeState->interval_tree_get_key_done;
}

INLINE_ACTOR_ACTION(interval_tree_load_key) {
//    DEBUG_PRINT("interval_tree_load_key\n");
    struct interval_tree_state *intervalTreeState = (struct interval_tree_state *) m->control_state;
    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_ipv4_hdr*,
                                                            sizeof(struct rte_ether_hdr));
    struct rte_tcp_hdr *tcp_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_tcp_hdr*,
                                                          sizeof(struct rte_ether_hdr) + sizeof(struct rte_ipv4_hdr));
    uint16_t key = rte_be_to_cpu_16(tcp_hdr->src_port); // get the key
    // store the key in the buffer
    uint16_t *key_ptr = (uint16_t *) &m->buffer.data[intervalTreeState->key_offset];
    *key_ptr = key;
    // get the node, which is the root
    struct multi_dimensional_interval_tree *dimensionalIntervalTree = (struct multi_dimensional_interval_tree *) m->data_state;
    // get the root
    struct multi_dimensional_interval_tree_node *root = dimensionalIntervalTree->root;
    // store the root in the buffer
    struct multi_dimensional_interval_tree_node **node = (struct multi_dimensional_interval_tree_node **) &m->buffer.data[intervalTreeState->node_offset];
    *node = root;
    // prefetch the root
    rte_prefetch0(root);
    m->event = intervalTreeState->interval_tree_load_key_done;
}

INLINE_ACTOR_ACTION(interval_tree_compare) {
//    DEBUG_PRINT("interval_tree_compare\n");
    struct interval_tree_state *intervalTreeState = (struct interval_tree_state *) m->control_state;
    struct multi_dimensional_interval_tree_node **node = (struct multi_dimensional_interval_tree_node **) &m->buffer.data[intervalTreeState->node_offset];
    // compare the node and point
    uint16_t *key_ptr = (uint16_t *) &m->buffer.data[intervalTreeState->key_offset];
    uint16_t key = *key_ptr;
    struct multi_dimensional_interval_tree_node *current_node = *node;
    if (current_node == NULL) {
        // not found
        m->event = 255;
        rte_pktmbuf_free(m->packet);
        DEBUG_PRINT("interval_tree_compare: not found\n");
        return;
    }
    // compare the key with the current node
    if (key >= current_node->multi_dimensional_interval.structinterval[0].start &&
        key < current_node->multi_dimensional_interval.structinterval[0].end) {
        // found the node
        int data_block_id = m->datablock_id;
        int offset = current_node->offset;
        m->local_offset[data_block_id] = offset;
        m->event = intervalTreeState->interval_tree_compare_success;
        return;
    } else {
        // not found, go to the next node
        if (key < current_node->multi_dimensional_interval.structinterval[0].start) {
            // go to the left
            *node = current_node->left;
            // prefetch the left node
            rte_prefetch0(current_node->left);
            // this function will be called again
            m->event = intervalTreeState->interval_tree_compare_failure;
            return;
        }
        else if (key >= current_node->multi_dimensional_interval.structinterval[0].end) {
            // go to the right
            *node = current_node->right;
            // prefetch the right node
            rte_prefetch0(current_node->right);
            // this function will be called again
            m->event = intervalTreeState->interval_tree_compare_failure;
            return;
        }
        // not found
        DEBUG_PRINT("interval_tree_compare: not found\n");
        m->event = 255;
        rte_pktmbuf_free(m->packet);
    }
}

AMAC_CLASSIFIER_INIT(interval_tree_classifier);

struct multi_dimensional_interval_tree *init_multi_dimensional_interval_tree(int dimension, int depth);

void dump_tree(struct multi_dimensional_interval_tree_node *node, int depth);

int node_search(struct multi_dimensional_interval_tree_node *node, int point);

int tree_search(struct multi_dimensional_interval_tree *tree, int point);

#endif //NFLAMBDA_RUNTIME_INTERVAL_TREE_H
