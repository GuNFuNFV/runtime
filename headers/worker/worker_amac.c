#include "worker_amac.h"
#include "worker_amac_context.h"
#include "worker_amac_nflow.h"

#include "tiny_json.h"

typedef struct {
    json_t mem[256];
    unsigned int nextFree;
    jsonPool_t pool;
} jsonStaticPool_t;

//static json_t *poolInit(jsonPool_t *pool) {
//    jsonStaticPool_t *spool = json_containerOf(pool, jsonStaticPool_t, pool);
//    spool->nextFree = 1;
//    return &spool->mem[0];
//}
//
//static json_t *poolAlloc(jsonPool_t *pool) {
//    jsonStaticPool_t *spool = json_containerOf(pool, jsonStaticPool_t, pool);
//    if (spool->nextFree >= sizeof spool->mem / sizeof spool->mem[0]) return 0;
//    return &spool->mem[spool->nextFree++];
//}


// this piece of code is generated by register_actor.py, do not modify it manually
struct runtime_actor_table runtimeActorTable[] = {
{.run = traffic_generator, .name = "traffic_generator"},
	{.run = traffic_generator_sink, .name = "traffic_generator_sink"},
	{.run = passthrough, .name = "passthrough"},
	{.run = ciphering_simulation, .name = "ciphering_simulation"},
	{.run = prefetch_action, .name = "prefetch_action"},
	{.run = first_action, .name = "first_action"},
	{.run = second_action, .name = "second_action"},
	{.run = third_action, .name = "third_action"},
	{.run = fourth_action, .name = "fourth_action"},
	{.run = fifth_action, .name = "fifth_action"},
	{.run = sixth_action, .name = "sixth_action"},
	{.run = amf_dispatcher, .name = "amf_dispatcher"},
	{.run = amf_unregistered_handler, .name = "amf_unregistered_handler"},
	{.run = amf_registered_handler, .name = "amf_registered_handler"},
	{.run = amf_context_setup_handler, .name = "amf_context_setup_handler"},
	{.run = amf_authentication_handler, .name = "amf_authentication_handler"},
	{.run = bess_nat, .name = "bess_nat"},
	{.run = fastclick_lb, .name = "fastclick_lb"},
	{.run = interval_tree_rtc, .name = "interval_tree_rtc"},
	{.run = interval_tree_get_key, .name = "interval_tree_get_key"},
	{.run = interval_tree_load_key, .name = "interval_tree_load_key"},
	{.run = interval_tree_compare, .name = "interval_tree_compare"},
	{.run = cuckoo_hash_rtc, .name = "cuckoo_hash_rtc"},
	{.run = cuckoo_hash_get_key, .name = "cuckoo_hash_get_key"},
	{.run = cuckoo_hash_first_hash, .name = "cuckoo_hash_first_hash"},
	{.run = cuckoo_hash_first_test, .name = "cuckoo_hash_first_test"},
	{.run = cuckoo_hash_second_hash, .name = "cuckoo_hash_second_hash"},
	{.run = cuckoo_hash_second_test, .name = "cuckoo_hash_second_test"},
	{.run = cuckoo_hash_get_key_non_temporal, .name = "cuckoo_hash_get_key_non_temporal"},
	{.run = cuckoo_hash_first_hash_non_temporal, .name = "cuckoo_hash_first_hash_non_temporal"},
	{.run = cuckoo_hash_first_test_non_temporal, .name = "cuckoo_hash_first_test_non_temporal"},
	{.run = cuckoo_hash_second_hash_non_temporal, .name = "cuckoo_hash_second_hash_non_temporal"},
	{.run = cuckoo_hash_second_test_non_temporal, .name = "cuckoo_hash_second_test_non_temporal"},
	{.run = upf_encapsulate, .name = "upf_encapsulate"},
	{.run = dispatchMain, .name = "dispatchMain"},
	{.run = handlerUplinkNASTransport, .name = "handlerUplinkNASTransport"},
	{.run = ranUeFind, .name = "ranUeFind"},
	{.run = RanUeFindByAmfUeNgapID, .name = "RanUeFindByAmfUeNgapID"},
	{.run = handleUplinkNASTransportMain, .name = "handleUplinkNASTransportMain"},
	{.run = UpdateLocation, .name = "UpdateLocation"},
	{.run = HandleNAS, .name = "HandleNAS"},
	{.run = Decode, .name = "Decode"},
	{.run = Dispatch, .name = "Dispatch"},
	{.run = SecurityMode, .name = "SecurityMode"},
	{.run = HandleSecurityModeComplete, .name = "HandleSecurityModeComplete"},
	{.run = StopT3560, .name = "StopT3560"},
	{.run = Stop, .name = "Stop"},
	{.run = SecurityContextIsValid, .name = "SecurityContextIsValid"},
	{.run = UpdateSecurityContext, .name = "UpdateSecurityContext"},
	{.run = DerivateAnKey, .name = "DerivateAnKey"},
	{.run = DerivateNH, .name = "DerivateNH"},
	{.run = ContextSetup, .name = "ContextSetup"},
	{.run = HandleInitialRegistration, .name = "HandleInitialRegistration"},
	{.run = getSubscribedNssai, .name = "getSubscribedNssai"},
	{.run = SearchUdmSdmInstance, .name = "SearchUdmSdmInstance"},
	{.run = SDMGetSliceSelectionSubscriptionData, .name = "SDMGetSliceSelectionSubscriptionData"},
	{.run = handleRequestedNssai, .name = "handleRequestedNssai"},
	{.run = InSubscribedNssai, .name = "InSubscribedNssai"},
	{.run = InAllowedNssai, .name = "InAllowedNssai"},
	{.run = storeLastVisitedRegisteredTAI, .name = "storeLastVisitedRegisteredTAI"},
	{.run = negotiateDRXParameters, .name = "negotiateDRXParameters"},
	{.run = communicateWithUDM, .name = "communicateWithUDM"},
	{.run = SendSearchNFInstances, .name = "SendSearchNFInstances"},
	{.run = UeCmRegistration, .name = "UeCmRegistration"},
	{.run = SDMGetAmData, .name = "SDMGetAmData"},
	{.run = SDMGetSmfSelectData, .name = "SDMGetSmfSelectData"},
	{.run = SDMGetUeContextInSmfData, .name = "SDMGetUeContextInSmfData"},
	{.run = SDMSubscribe, .name = "SDMSubscribe"},
	{.run = AMPolicyControlCreate, .name = "AMPolicyControlCreate"},
	{.run = GetIPv4Uri, .name = "GetIPv4Uri"},
	{.run = HTTPAMFStatusChangeSubscribe, .name = "HTTPAMFStatusChangeSubscribe"},
	{.run = HandleAMFStatusChangeSubscribeRequest, .name = "HandleAMFStatusChangeSubscribeRequest"},
	{.run = AMFStatusChangeSubscribeProcedure, .name = "AMFStatusChangeSubscribeProcedure"},
	{.run = NewAMFStatusSubscription, .name = "NewAMFStatusSubscription"},
	{.run = AllocateRegistrationArea, .name = "AllocateRegistrationArea"},
	{.run = assignLadnInfo, .name = "assignLadnInfo"},
	{.run = AddAmfUeToUePool, .name = "AddAmfUeToUePool"},
	{.run = SendRegistrationAccept, .name = "SendRegistrationAccept"},
	{.run = BuildRegistrationAccept, .name = "BuildRegistrationAccept"},
	{.run = includeConfiguredNssaiCheck, .name = "includeConfiguredNssaiCheck"},
	{.run = GetNasIENetworkFeatureSupport5GS, .name = "GetNasIENetworkFeatureSupport5GS"},
	{.run = Encode, .name = "Encode"},
	{.run = GetBearerType, .name = "GetBearerType"},
	{.run = SendN2Message, .name = "SendN2Message"},
	{.run = SendInitialContextSetupRequest, .name = "SendInitialContextSetupRequest"},
	{.run = BuildInitialContextSetupRequest, .name = "BuildInitialContextSetupRequest"},
	{.run = GetNgapIEMobilityRestrictionList, .name = "GetNgapIEMobilityRestrictionList"},
	{.run = BuildIEMobilityRestrictionList, .name = "BuildIEMobilityRestrictionList"},
	{.run = GetNgapIEMaskedIMEISV, .name = "GetNgapIEMaskedIMEISV"},
	{.run = GetNgapIERedirectionVoiceFallback, .name = "GetNgapIERedirectionVoiceFallback"},
	{.run = NasSendToRan, .name = "NasSendToRan"},
	{.run = SendToRanUe, .name = "SendToRanUe"},
	{.run = SendToRan, .name = "SendToRan"},
	{.run = NewTimer, .name = "NewTimer"},
	{.run = Registered, .name = "Registered"},
	{.run = HandleULNASTransport, .name = "HandleULNASTransport"},
	{.run = transport5GSMMessage, .name = "transport5GSMMessage"},
	{.run = SmContextFindByPDUSessionID, .name = "SmContextFindByPDUSessionID"},
	{.run = CreatePDUSession, .name = "CreatePDUSession"},
	{.run = SelectSmf, .name = "SelectSmf"},
	{.run = ServingAMF, .name = "ServingAMF"},
	{.run = GetNsiInformationFromSnssai, .name = "GetNsiInformationFromSnssai"},
	{.run = SearchNssfNSSelectionInstance, .name = "SearchNssfNSSelectionInstance"},
	{.run = NSSelectionGetForPduSession, .name = "NSSelectionGetForPduSession"},
	{.run = NewSmContext, .name = "NewSmContext"},
	{.run = SetSnssai, .name = "SetSnssai"},
	{.run = SetDnn, .name = "SetDnn"},
	{.run = SetAccessType, .name = "SetAccessType"},
	{.run = SetNsInstance, .name = "SetNsInstance"},
	{.run = SetSmfID, .name = "SetSmfID"},
	{.run = SetSmfUri, .name = "SetSmfUri"},
	{.run = SendCreateSmContextRequest, .name = "SendCreateSmContextRequest"},
	{.run = buildCreateSmContextRequest, .name = "buildCreateSmContextRequest"},
	{.run = PduSessionID, .name = "PduSessionID"},
	{.run = Snssai, .name = "Snssai"},
	{.run = Dnn, .name = "Dnn"},
	{.run = AccessType, .name = "AccessType"},
	{.run = SmfUri, .name = "SmfUri"},
	{.run = SetSmContextRef, .name = "SetSmContextRef"},
	{.run = SetUserLocation, .name = "SetUserLocation"},
	{.run = StoreSmContext, .name = "StoreSmContext"},
	{.run = handlerPDUSessionResourceSetupResponse, .name = "handlerPDUSessionResourceSetupResponse"},
	{.run = handlePDUSessionResourceSetupResponseMain, .name = "handlePDUSessionResourceSetupResponseMain"},
	{.run = SendUpdateSmContextN2Info, .name = "SendUpdateSmContextN2Info"},
	{.run = SendUpdateSmContextRequest, .name = "SendUpdateSmContextRequest"},
	{.run = SmContextRef, .name = "SmContextRef"},
	{.run = handlerInitialUEMessage, .name = "handlerInitialUEMessage"},
	{.run = handleInitialUEMessageMain, .name = "handleInitialUEMessageMain"},
	{.run = RanUeFindByRanUeNgapID, .name = "RanUeFindByRanUeNgapID"},
	{.run = NewRanUe, .name = "NewRanUe"},
	{.run = NewAmfUe, .name = "NewAmfUe"},
	{.run = init, .name = "init"},
	{.run = AllocateGutiToUe, .name = "AllocateGutiToUe"},
	{.run = TmsiAllocate, .name = "TmsiAllocate"},
	{.run = AttachRanUeToAmfUeAndReleaseOldIfAny, .name = "AttachRanUeToAmfUeAndReleaseOldIfAny"},
	{.run = AttachRanUe, .name = "AttachRanUe"},
	{.run = DeRegistered, .name = "DeRegistered"},
	{.run = HandleRegistrationRequest, .name = "HandleRegistrationRequest"},
	{.run = SetOnGoing, .name = "SetOnGoing"},
	{.run = StopT3513, .name = "StopT3513"},
	{.run = StopT3565, .name = "StopT3565"},
	{.run = PlmnIdStringToModels, .name = "PlmnIdStringToModels"},
	{.run = InTaiList, .name = "InTaiList"},
	{.run = Authentication, .name = "Authentication"},
	{.run = AuthenticationProcedure, .name = "AuthenticationProcedure"},
	{.run = IdentityVerification, .name = "IdentityVerification"},
	{.run = SendUEAuthenticationAuthenticateRequest, .name = "SendUEAuthenticationAuthenticateRequest"},
	{.run = SendAuthenticationRequest, .name = "SendAuthenticationRequest"},
	{.run = BuildAuthenticationRequest, .name = "BuildAuthenticationRequest"},
	{.run = SendDownlinkNasTransport, .name = "SendDownlinkNasTransport"},
	{.run = BuildDownlinkNasTransport, .name = "BuildDownlinkNasTransport"},
	{.run = HandleAuthenticationResponse, .name = "HandleAuthenticationResponse"},
	{.run = SendAuth5gAkaConfirmRequest, .name = "SendAuth5gAkaConfirmRequest"},
	{.run = DerivateKamf, .name = "DerivateKamf"},
	{.run = SelectSecurityAlg, .name = "SelectSecurityAlg"},
	{.run = DerivateAlgKey, .name = "DerivateAlgKey"},
	{.run = SendSecurityModeCommand, .name = "SendSecurityModeCommand"},
	{.run = BuildSecurityModeCommand, .name = "BuildSecurityModeCommand"},
	{.run = handlerInitialContextSetupResponse, .name = "handlerInitialContextSetupResponse"},
	{.run = handleInitialContextSetupResponseMain, .name = "handleInitialContextSetupResponseMain"},
	{.run = HandleRegistrationComplete, .name = "HandleRegistrationComplete"},
	{.run = StopT3550, .name = "StopT3550"},
	{.run = ClearRegistrationRequestData, .name = "ClearRegistrationRequestData"},
	{.run = receive_packet, .name = "receive_packet"},
	{.run = send_packet, .name = "send_packet"},
	{.run = drop, .name = "drop"},
	{.run = Exit, .name = "Exit"},
	{.run = generic, .name = "generic"}
};

int actor_table_size = sizeof(runtimeActorTable) / sizeof(struct runtime_actor_table);

AMAC_WORKER_INIT(worker_actor_table_init) {
    char *config = tokens[0];
    DEBUG_PRINT("%s\n", config);
    jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    json_t const *json = json_createWithPool(config, &spool.pool);
    if (!json) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        return NULL;
    }

    jsonType_t const type = json_getType(json);
    if (type != JSON_OBJ && type != JSON_ARRAY) {
        puts("error");
        exit(1);
    }

    json_t const *child;
    for (child = json_getChild(json); child != 0; child = json_getSibling(child)) {

        jsonType_t propertyType = json_getType(child);
        char const *name = json_getName(child);
        char const *value = json_getValue(child);
        // translate name into integer as actor_id
        int64_t actor_id = atoi(name);
        // translate value into string as action name
        char *action_name = value;
        // find the action name in the runtimeActorTable
        for (int i = 0; i < actor_table_size; i++) {
            struct runtime_actor_table *pRuntimeActorTable = &runtimeActorTable[i];
            if (strcmp(action_name, pRuntimeActorTable->name) == 0) {
                pStructworkerAmacContext->actorTable.actor[actor_id].run = pRuntimeActorTable->run;
                DEBUG_PRINT("actor_id: %d, name: %s\n", actor_id, action_name);
            }
        }
    }
    snprintf(out, out_size, "worker_actor_table_init done\n");
}

struct control_state_table controlStateTable[] = {
{.init = traffic_generator_init, .name = "traffic_generator"},
	{.init = traffic_generator_sink_init, .name = "traffic_generator_sink"},
	{.init = passthrough_init, .name = "passthrough"},
	{.init = ciphering_simulation_init, .name = "ciphering_simulation"},
	{.init = sfc_simulation_init, .name = "sfc_simulation"},
	{.init = amf_init, .name = "amf"},
	{.init = bess_nat_init, .name = "bess_nat"},
	{.init = fastclick_lb_init, .name = "fastclick_lb"},
	{.init = interval_tree_init, .name = "interval_tree"},
	{.init = cuckoo_hash_init, .name = "cuckoo_hash"},
	{.init = upf_encapsulation_init, .name = "upf_encapsulation"},
	{.init = amf_free5gc_init, .name = "amf_free5gc"},
	{.init = generic_init, .name = "generic"},
	{.init = cuckoo_hash_init, .name = "cuckoo_hash_rtc"},
	{.init = interval_tree_init, .name = "interval_tree_rtc"},
	
};


AMAC_WORKER_INIT(control_state_init) {
    // nf_name, control_state_id, config
    char *nf = tokens[0];
    int worker_control_state_id = atoi(tokens[1]);
    char *config = tokens[2];
    DEBUG_PRINT("%s\n", nf);
    for (int i = 0; i < sizeof(controlStateTable) / sizeof(controlStateTable[0]); i++) {
        if (strcmp(nf, controlStateTable[i].name) == 0) {
            pStructworkerAmacContext->controlStateTable.control_state[worker_control_state_id].control_state = controlStateTable[i].init(
                    config, pStructworkerAmacContext->core_id, pStructworkerAmacContext->rx_port_id,
                    pStructworkerAmacContext->queue_id, pStructworkerAmacContext);
            if (pStructworkerAmacContext->controlStateTable.control_state[worker_control_state_id].control_state ==
                NULL) {
                snprintf(out, out_size, "control_state_init: failed to init control state %s\n", nf);
                DEBUG_PRINT("%s", out);
                return NULL;
            }
            pStructworkerAmacContext->controlStateTable.num_control_state++;
            DEBUG_PRINT("control_state: %s, state_id: %d\n", controlStateTable[i].name, worker_control_state_id);
            break;
        }
    }
    snprintf(out, out_size, "control_state_init done\n");
}

AMAC_WORKER_INIT(control_state_configure) {
    char *nf = tokens[0];
    int worker_control_state_id = atoi(tokens[1]);
    char *config = tokens[2];
    DEBUG_PRINT("%s\n", nf);
    for (int i = 0; i < sizeof(controlStateTable) / sizeof(controlStateTable[0]); i++) {
        if (strcmp(nf, controlStateTable[i].name) == 0) {
            if (!pStructworkerAmacContext->controlStateTable.control_state[worker_control_state_id].control_state !=
                NULL) {
                exit(1);
            }
            if (!controlStateTable[i].config != NULL) {
                exit(1);
            }
            controlStateTable[i].config(
                    pStructworkerAmacContext->controlStateTable.control_state[worker_control_state_id].control_state,
                    config);
            break;
        }
    }
    snprintf(out, out_size, "control_state_configure done\n");
}


AMAC_WORKER_INIT(actor_control_state_association) {
    DEBUG_PRINT("actor_control_state_association\n");
    char *config = tokens[0];
    DEBUG_PRINT("%s\n", config);
    // parse config
    jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    json_t const *json = json_createWithPool(config, &spool.pool);
    if (!json) {
        DEBUG_PRINT("json_createWithPool failed\n");
        return NULL;
    }
    // first option
    json_t const *first_option = json_getChild(json);
    if (!first_option) {
        DEBUG_PRINT("json_getChild failed\n");
        return NULL;
    }
    // get the name of the first option
    char const *name = json_getName(first_option);
    if (!name) {
        DEBUG_PRINT("json_getName failed\n");
        return NULL;
    }
    int actor_id = atoi(name);
    // get the value of the first option
    int control_state_id = json_getInteger(first_option);
    pStructworkerAmacContext->actorTable.actor[actor_id].control_state_id = control_state_id;
    DEBUG_PRINT("actor_id: %d, control_state_id: %d\n", actor_id, control_state_id);
    while (json_getSibling(first_option)) {
        json_t const *next_option = json_getSibling(first_option);
        if (!next_option) {
            DEBUG_PRINT("json_getSibling failed\n");
            break;
        }
        // get the name of the next option
        char const *name = json_getName(next_option);
        if (!name) {
            DEBUG_PRINT("json_getName failed\n");
            return NULL;
        }
        int actor_id = atoi(name);
        // get the value of the next option
        int control_state_id = json_getInteger(next_option);
        pStructworkerAmacContext->actorTable.actor[actor_id].control_state_id = control_state_id;
        pStructworkerAmacContext->actorTable.actor[actor_id].control_state = pStructworkerAmacContext->controlStateTable.control_state[control_state_id].control_state;
        if (control_state_id == 0) {
            pStructworkerAmacContext->actorTable.actor[actor_id].control_state = pStructworkerAmacContext;
        }
        first_option = next_option;
        DEBUG_PRINT("actor_id: %d, control_state_id: %d\n", actor_id, control_state_id);
    }

    snprintf(out, out_size, "actor_control_state_association done\n");
    return NULL;
}


AMAC_WORKER_INIT(worker_fsm_amac_run) {
    DEBUG_PRINT("worker_fsm_amac_run\n");
    rte_eal_remote_launch((int (*)(void *)) worker_fsm_amac_thread, pStructworkerAmacContext,
                          pStructworkerAmacContext->core_id);
    printf("worker on core %d is running\n", pStructworkerAmacContext->core_id);
    fflush(stdout);
    pStructworkerAmacContext->running = true;
    snprintf(out, out_size, "worker_fsm_amac_run done\n");
}

struct nflow_variable_setup nflowVariableSetup[] = {{.name = "generic_variable", .value = &generic_variable}};


AMAC_WORKER_INIT(worker_fsm_amac_total_packet) {
    DEBUG_PRINT("worker_fsm_amac_total_packet\n");
    snprintf(out, out_size, "%d", pStructworkerAmacContext->total_packet);
}

AMAC_WORKER_INIT(actor_datablock_association) {
    DEBUG_PRINT("install actor_datablock_association\n");
    char *config = tokens[0];
    DEBUG_PRINT("%s\n", config);
    // parse the config
    jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    json_t const *json = json_createWithPool(config, &spool.pool);
    if (!json) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        return NULL;
    }

    json_t const *child;
    for (child = json_getChild(json); child != 0; child = json_getSibling(child)) {

        jsonType_t propertyType = json_getType(child);
        char const *name = json_getName(child);
        json_t const *datablock_config = json_getProperty(json, name);
        // translate name into integer as actor_id
        int64_t actor_id = atoi(name);
        // datablock_config is another json object
        char const *datablock_id_json = json_getPropertyValue(datablock_config, "datablock_id");
        int64_t datablock_id = atoi(datablock_id_json);
        // get the datablock offset
        char const *datablock_offset_json = json_getPropertyValue(datablock_config, "datablock_offset");
        int64_t datablock_offset = atoi(datablock_offset_json);
        struct actor *temp_actor = &pStructworkerAmacContext->actorTable.actor[actor_id];
        temp_actor->datablock_id = datablock_id;
        temp_actor->datablock_offset = datablock_offset;
        DEBUG_PRINT("actor_id: %d, datablock_id: %d, datablock_offset: %d\n", actor_id, datablock_id, datablock_offset);
    }

    snprintf(out, out_size, "actor_datablock_association done\n");
}


struct data_block_options_init dataBlockOptionsInit[] = {{.name = "cuckoo_hash", .init = cuckoo_hash_classifier, .size = sizeof(struct rte_hash *)},
                                                         {.name = "cuckoo_hash_rtc", .init = cuckoo_hash_classifier, .size = sizeof(struct rte_hash *)},
                                                         {.name = "cuckoo_hash_non_temporal", .init = cuckoo_hash_classifier, .size = sizeof(struct rte_hash *)},
                                                         {.name = "interval_tree", .init = interval_tree_classifier, .size = sizeof(struct multi_dimensional_interval_tree *)},
                                                         {.name = "interval_tree_rtc", .init = interval_tree_classifier, .size = sizeof(struct multi_dimensional_interval_tree *)},
                                                         {.name = "per_flow_state", .init = NULL, .size = 64 *
                                                                                                          8} // the size of per-flow state of generic nf
};

size_t power_2(size_t n) {
    if (n == 0) {
        return 1;
    }
    size_t p = 2;
    int i = 0;
    while (i < n - 1) {
        p *= 2;
        i++;
    }
    return p;
}

AMAC_WORKER_INIT(init_datablock) {
    DEBUG_PRINT("init_datablock\n");
    char *config = tokens[0];
    // parse the config
    jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    json_t const *json = json_createWithPool(config, &spool.pool);

    // get the property named "nf_name"
    char const *nf_name = json_getPropertyValue(json, "type");
    // get the property named "data_block_id"
    char const *datablock_id = json_getPropertyValue(json, "datablock_id");
    // to int nf_name
    int data_block_id = atoi(datablock_id);
    // get the property named "control_state_id"
    char const *control_state_id_json = json_getPropertyValue(json, "control_state_id");
    // to int nf_name
    int control_state_id = atoi(control_state_id_json);
    // get the property named "num_flow_differentiated_per_entry"
    char const *num_flow_differentiated_per_entry_json = json_getPropertyValue(json,
                                                                               "num_flow_differentiated_per_entry");
    int num_flow_differentiated_per_entry_power = atoi(num_flow_differentiated_per_entry_json);
    // get the property named "num_entry"
    char const *num_entry_json = json_getPropertyValue(json, "entry_num");
    int num_entry_power = atoi(num_entry_json);

    size_t num_flow_differentiated_per_entry = power_2(num_flow_differentiated_per_entry_power);
    size_t num_entry = power_2(num_entry_power);
    DEBUG_PRINT("num_flow_differentiated_per_entry: %d, num_entry: %d\n", num_flow_differentiated_per_entry, num_entry);
    DEBUG_PRINT("data_block_id: %d, control_state_id: %d\n", data_block_id, control_state_id);
    DEBUG_PRINT("nf_name: %s\n", nf_name);

    int dataBlockOptionsInit_size = sizeof(dataBlockOptionsInit) / sizeof(dataBlockOptionsInit[0]);
    bool found = false;
    for (int i = 0; i < dataBlockOptionsInit_size; i++) {
        if (strcmp(nf_name, dataBlockOptionsInit[i].name) == 0) {
            found = true;
            pStructworkerAmacContext->total_entries_n[data_block_id] = num_entry;
            pStructworkerAmacContext->num_flow_differentiated_per_entry[data_block_id] = num_flow_differentiated_per_entry;
            void *control_state = pStructworkerAmacContext->controlStateTable.control_state[control_state_id].control_state;
            DEBUG_PRINT("init datablock %d with %s\n", data_block_id, dataBlockOptionsInit[i].name);
            if (dataBlockOptionsInit[i].init != NULL) {
                // for each bucket, we need a pointer
                pStructworkerAmacContext->datablock[data_block_id] = rte_malloc(NULL, num_entry *
                                                                                      dataBlockOptionsInit[i].size,
                                                                                RTE_CACHE_LINE_SIZE);
                pStructworkerAmacContext->entry_size[data_block_id] = dataBlockOptionsInit[i].size;
                void **addr = pStructworkerAmacContext->datablock[data_block_id];
                // call the init function
                for (int j = 0; j < num_entry; j++) {
                    DEBUG_PRINT("init for bucket %d\n", j);
                    *addr = dataBlockOptionsInit[i].init(control_state, 0, pStructworkerAmacContext->core_id,
                                                         data_block_id);
                    addr++;
                }
                break;
            } else {
                pStructworkerAmacContext->datablock[data_block_id] = rte_malloc(NULL, num_entry *
                                                                                      dataBlockOptionsInit[i].size,
                                                                                RTE_CACHE_LINE_SIZE);
                assert(pStructworkerAmacContext->datablock[data_block_id] != NULL);
                pStructworkerAmacContext->entry_size[data_block_id] = dataBlockOptionsInit[i].size;
                DEBUG_PRINT("init per-flow state done using rte_malloc. size: %d\n", num_entry *
                        dataBlockOptionsInit[i].size);
                DEBUG_PRINT("entry_size: %d\n", pStructworkerAmacContext->entry_size[data_block_id]);
                break;
            }
        }
    }
    if (!found) {
        DEBUG_PRINT("nf_name: %s not found\n", nf_name);
        exit(1);
    }
    snprintf(out, out_size, "init_datablock done\n");
}


AMAC_WORKER_INIT(worker_actor_entry_event) {
    DEBUG_PRINT("worker_actor_entry_event\n");
    char *config = tokens[0];
    // parse the config
    jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    json_t const *json = json_createWithPool(config, &spool.pool);
    if (!json) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        return NULL;
    }
    // first option it is the actor id
    json_t const *first_option = json_getChild(json);
    if (!first_option) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        return NULL;
    }
    // get the name of the first option
    char const *first_option_name = json_getName(first_option);
    if (!first_option_name) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        return NULL;
    }
    // get the value of the first option
    int64_t first_option_value = json_getInteger(first_option);
    if (!first_option_value) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        return NULL;
    }
    int64_t actor_id = atoi(first_option_name);
    int actor_entry_event = first_option_value;
    pStructworkerAmacContext->actorTable.actor[actor_id].entry_event = actor_entry_event;
    DEBUG_PRINT("actor_id: %d, actor_entry_event: %d\n", actor_id, actor_entry_event);
    while (json_getSibling(first_option)) {
        json_t const *next_option = json_getSibling(first_option);
        if (!next_option) {
            DEBUG_PRINT("json_getSibling failed\n");
            break;
        }
        char const *next_option_name = json_getName(next_option);
        if (!next_option_name) {
            DEBUG_PRINT("json_getName failed\n");
            return NULL;
        }
        int64_t next_option_value = json_getInteger(next_option);
        int64_t actor_id = atoi(next_option_name);
        int64_t actor_entry_event = next_option_value;
        pStructworkerAmacContext->actorTable.actor[actor_id].entry_event = actor_entry_event;
        first_option = next_option;
        DEBUG_PRINT("actor_id: %d, actor_entry_event: %d\n", actor_id, actor_entry_event);
    }

    snprintf(out, out_size, "worker_actor_entry_event done\n");
    return NULL;
}