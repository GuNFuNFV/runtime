
#include "interval_tree.h"


#include "tiny_json.h"



ACTOR_CONTROL_STATE_INIT(interval_tree_init) {

    DEBUG_PRINT("interval_tree_init\n");
    DEBUG_PRINT("%s\n", config);
    struct interval_tree_state *intervalTreeState = (struct interval_tree_state *) rte_malloc(NULL,
                                                                                              sizeof(struct interval_tree_state),
                                                                                              0);
    intervalTreeState->key_offset = 0;
    intervalTreeState->node_offset = (CONTROL_VARIABLE_OFFSET) sizeof(uint16_t);
    _jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    // parse the config
    json_t const *json = json_createWithPool(config, &spool.pool);
    // check whether contain cuckoo_hash_entry_num
    json_t const *interval_tree_depth = json_getProperty(json, "interval_tree_depth");
    json_t const *interval_tree_dimension = json_getProperty(json, "interval_tree_dimension");

    if (interval_tree_depth == 0 || interval_tree_dimension == 0) {
        DEBUG_PRINT("interval_tree_init: interval_tree_depth or interval_tree_dimension not found\n");
        return NULL;
    }
    intervalTreeState->depth = json_getInteger(interval_tree_depth);
    intervalTreeState->dimension = json_getInteger(interval_tree_dimension);

    json_t const *interval_tree_compare_success = json_getProperty(json, "interval_tree_compare_success");
    json_t const *interval_tree_get_key_done = json_getProperty(json, "interval_tree_get_key_done");
    json_t const *interval_tree_compare_failure = json_getProperty(json, "interval_tree_compare_failure");
    json_t const *interval_tree_load_key_done = json_getProperty(json, "interval_tree_load_key_done");

    if (interval_tree_compare_success != 0) {
        DEBUG_PRINT("interval_tree_compare_success: %d\n", json_getInteger(interval_tree_compare_success));
        intervalTreeState->interval_tree_compare_success = (EVENT) json_getInteger(interval_tree_compare_success);
    }
    if (interval_tree_get_key_done != 0) {
        DEBUG_PRINT("interval_tree_get_key_done: %d\n", json_getInteger(interval_tree_get_key_done));
        intervalTreeState->interval_tree_get_key_done = (EVENT) json_getInteger(interval_tree_get_key_done);
    }
    if (interval_tree_compare_failure != 0) {
        DEBUG_PRINT("interval_tree_compare_failure: %d\n", json_getInteger(interval_tree_compare_failure));
        intervalTreeState->interval_tree_compare_failure = (EVENT) json_getInteger(interval_tree_compare_failure);
    }
    if (interval_tree_load_key_done != 0) {
        DEBUG_PRINT("interval_tree_load_key_done: %d\n", json_getInteger(interval_tree_load_key_done));
        intervalTreeState->interval_tree_load_key_done = (EVENT) json_getInteger(interval_tree_load_key_done);
    }

//    intervalTreeState->interval_tree_compare_failure = (EVENT) json_getInteger(interval_tree_compare_fail);
//    intervalTreeState->interval_tree_get_key_done = (EVENT) json_getInteger(interval_tree_get_key_done);
//    intervalTreeState->interval_tree_compare_failure = (EVENT) json_getInteger(interval_tree_compare_failure);
    return intervalTreeState;
}

struct multi_dimensional_interval_tree_node *
build_tree(struct multi_dimensional_interval_tree_node *nodes, int start, int end, int dimension) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    struct multi_dimensional_interval_tree_node *node = &nodes[mid];
    node->left = build_tree(nodes, start, mid - 1, dimension);
    node->right = build_tree(nodes, mid + 1, end, dimension);
    return node;
}

struct multi_dimensional_interval_tree *init_multi_dimensional_interval_tree(int dimension, int depth) {
    dimension = 1; // fixed for now
    struct multi_dimensional_interval_tree *tree = (struct multi_dimensional_interval_tree *) rte_malloc(NULL,
                                                                                                         sizeof(struct multi_dimensional_interval_tree),
                                                                                                         0);
    int num_nodes = (1 << depth) - 1; // number of nodes in the tree is 2^depth - 1
    struct multi_dimensional_interval_tree_node *nodes = (struct multi_dimensional_interval_tree_node *) rte_malloc(
            NULL, sizeof(struct multi_dimensional_interval_tree_node) * num_nodes, 0);
    // we have num_nodes intervals, each interval we assume has 1000 elements
    int num_intervals = num_nodes;
    int init_value = 0;
    int interval_size = 100;
    // init nodes
    for (int i = 0; i < num_nodes; i++) {
        struct multi_dimensional_interval_tree_node *node = &nodes[i];
        node->dimension = dimension;
        node->multi_dimensional_interval.structinterval[0].start = init_value;
        node->multi_dimensional_interval.structinterval[0].end = init_value + interval_size;
        init_value += interval_size;
        node->dimension = dimension;
        node->offset = i;
    }
    // we init the node in this way, so that the tree is balanced
    // the root is at the middle of the array
    int root_index = num_nodes / 2;
    // build the tree recursively
    struct multi_dimensional_interval_tree_node *root = &nodes[root_index];
    root->left = build_tree(nodes, 0, root_index - 1, dimension);
    root->right = build_tree(nodes, root_index + 1, num_nodes - 1, dimension);
    tree->root = root;
    return tree;
}

void dump_tree(struct multi_dimensional_interval_tree_node *node, int depth) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf(" ");
    }
    printf("%d %d %d\n", node->multi_dimensional_interval.structinterval[0].start,
           node->multi_dimensional_interval.structinterval[0].end, node->dimension);
    dump_tree(node->left, depth + 1);
    dump_tree(node->right, depth + 1);
}

int node_search(struct multi_dimensional_interval_tree_node *node, int point) {
    if (node == NULL) {
        return -1;
    }
    if (node->multi_dimensional_interval.structinterval[0].start <= point &&
        node->multi_dimensional_interval.structinterval[0].end >= point) {
        return node->offset;
    } else if (node->multi_dimensional_interval.structinterval[0].start > point) {
        return node_search(node->left, point);
    } else {
        return node_search(node->right, point);
    }
}

int tree_search(struct multi_dimensional_interval_tree *tree, int point) {
    // return the index of the node that contains the interval
    struct multi_dimensional_interval_tree_node *node = tree->root;
    int num_nodes = (1 << tree->depth) - 1;
    int dimension = DIMENSION;
    int offset = node_search(node, point);
    return offset;
}


AMAC_CLASSIFIER_INIT(interval_tree_classifier) {
    int dimension = 1;// fixed for now
    int depth = ((struct interval_tree_state *) control_state)->depth; // depth for the tree
    struct multi_dimensional_interval_tree *tree = init_multi_dimensional_interval_tree(dimension, depth);
    return tree;
}

