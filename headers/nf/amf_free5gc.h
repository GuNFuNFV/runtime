#ifndef AMF_FREE5GC_H
#define AMF_FREE5GC_H

#include "control_state/controlstate_amf_free5gc.h"
#include "fsm_amac_nf_common.h"

ACTOR_CONTROL_STATE_INIT(amf_free5gc_init);
INLINE_ACTOR_ACTION(dispatchMain)
{
    //DEBUG_PRINT("dispatchMain called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_handlerUplinkNASTransport_3_security_mode_complete;
            break;
        case 6: m->event = ControlState->E_handlerUplinkNASTransport_6_transport5GSMMessage;
            break;
        case 7: m->event = ControlState->E_handlerPDUSessionResourceSetupResponse_7_pdu_session_resource_setup_response;
            break;
        case 1: m->event = ControlState->E_handlerInitialUEMessage_1_initialue;
            break;
        case 2: m->event = ControlState->E_handlerUplinkNASTransport_2_authentication_response;
            break;
        case 4: m->event = ControlState->E_handlerInitialContextSetupResponse_4_initial_context_response;
            break;
        case 5: m->event = ControlState->E_handlerUplinkNASTransport_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(handlerUplinkNASTransport)
{
    //DEBUG_PRINT("handlerUplinkNASTransport called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_ranUeFind_3_security_mode_complete;
            break;
        case 6: m->event = ControlState->E_ranUeFind_6_transport5GSMMessage;
            break;
        case 2: m->event = ControlState->E_ranUeFind_2_authentication_response;
            break;
        case 5: m->event = ControlState->E_ranUeFind_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(ranUeFind)
{
    //DEBUG_PRINT("ranUeFind called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_RanUeFindByAmfUeNgapID_3_security_mode_complete;
            break;
        case 6: m->event = ControlState->E_RanUeFindByAmfUeNgapID_6_transport5GSMMessage;
            break;
        case 7: m->event = ControlState->E_RanUeFindByAmfUeNgapID_7_pdu_session_resource_setup_response;
            break;
        case 2: m->event = ControlState->E_RanUeFindByAmfUeNgapID_2_authentication_response;
            break;
        case 4: m->event = ControlState->E_RanUeFindByAmfUeNgapID_4_initial_context_response;
            break;
        case 5: m->event = ControlState->E_RanUeFindByAmfUeNgapID_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(RanUeFindByAmfUeNgapID)
{
    //DEBUG_PRINT("RanUeFindByAmfUeNgapID called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_handleUplinkNASTransportMain_3_security_mode_complete;
            break;
        case 6: m->event = ControlState->E_handleUplinkNASTransportMain_6_transport5GSMMessage;
            break;
        case 7: m->event = ControlState->E_handlePDUSessionResourceSetupResponseMain_7_pdu_session_resource_setup_response;
            break;
        case 2: m->event = ControlState->E_handleUplinkNASTransportMain_2_authentication_response;
            break;
        case 4: m->event = ControlState->E_handleInitialContextSetupResponseMain_4_initial_context_response;
            break;
        case 5: m->event = ControlState->E_handleUplinkNASTransportMain_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(handleUplinkNASTransportMain)
{
    //DEBUG_PRINT("handleUplinkNASTransportMain called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // write RanUe_Location_NrLocation_Tai_PlmnId (size 8)
     write_variable(DataState + 1306, 8);
    // write RanUe_Location_NrLocation_Tai_Tac (size 16)
     write_variable(DataState + 1314, 16);
    // write RanUe_Tai (size 24)
     write_variable(DataState + 1158, 24);
    // write RanUe_Location_NrLocation_Ncgi_PlmnId (size 8)
     write_variable(DataState + 1274, 8);
    // write RanUe_Location_NrLocation_Ncgi_NrCellId (size 16)
     write_variable(DataState + 1258, 16);
    // write RanUe_Location_NrLocation_UeLocationTimestamp (size 8)
     write_variable(DataState + 1330, 8);
    // write RanUe_Location_NrLocation_AgeOfLocationInformation (size 4)
     write_variable(DataState + 1254, 4);
    // write AmfUe_LocationChanged (size 1)
     write_variable(DataState + 357, 1);
    // write AmfUe_Location (size 24)
     write_variable(DataState + 309, 24);
    // write AmfUe_Tai (size 24)
     write_variable(DataState + 333, 24);
    // write RanUe_Location_NrLocation_Tai_PlmnId (size 8)
     write_variable(DataState + 1306, 8);
    // write RanUe_Location_NrLocation_Tai_Tac (size 16)
     write_variable(DataState + 1314, 16);
    // write RanUe_Tai (size 24)
     write_variable(DataState + 1158, 24);
    // write RanUe_Location_NrLocation_Ncgi_PlmnId (size 8)
     write_variable(DataState + 1274, 8);
    // write RanUe_Location_NrLocation_Ncgi_NrCellId (size 16)
     write_variable(DataState + 1258, 16);
    // write RanUe_Location_NrLocation_UeLocationTimestamp (size 8)
     write_variable(DataState + 1330, 8);
    // write RanUe_Location_NrLocation_AgeOfLocationInformation (size 4)
     write_variable(DataState + 1254, 4);
    // write AmfUe_LocationChanged (size 1)
     write_variable(DataState + 357, 1);
    // write AmfUe_Location (size 24)
     write_variable(DataState + 309, 24);
    // write AmfUe_Tai (size 24)
     write_variable(DataState + 333, 24);
    // write RanUe_Location_NrLocation_Tai_PlmnId (size 8)
     write_variable(DataState + 1306, 8);
    // write RanUe_Location_NrLocation_Tai_Tac (size 16)
     write_variable(DataState + 1314, 16);
    // write RanUe_Tai (size 24)
     write_variable(DataState + 1158, 24);
    // write RanUe_Location_NrLocation_Ncgi_PlmnId (size 8)
     write_variable(DataState + 1274, 8);
    // write RanUe_Location_NrLocation_Ncgi_NrCellId (size 16)
     write_variable(DataState + 1258, 16);
    // write RanUe_Location_NrLocation_UeLocationTimestamp (size 8)
     write_variable(DataState + 1330, 8);
    // write RanUe_Location_NrLocation_AgeOfLocationInformation (size 4)
     write_variable(DataState + 1254, 4);
    // write AmfUe_LocationChanged (size 1)
     write_variable(DataState + 357, 1);
    // write AmfUe_Location (size 24)
     write_variable(DataState + 309, 24);
    // write AmfUe_Tai (size 24)
     write_variable(DataState + 333, 24);
    // write RanUe_Location_NrLocation_Tai_PlmnId (size 8)
     write_variable(DataState + 1306, 8);
    // write RanUe_Location_NrLocation_Tai_Tac (size 16)
     write_variable(DataState + 1314, 16);
    // write RanUe_Tai (size 24)
     write_variable(DataState + 1158, 24);
    // write RanUe_Location_NrLocation_Ncgi_PlmnId (size 8)
     write_variable(DataState + 1274, 8);
    // write RanUe_Location_NrLocation_Ncgi_NrCellId (size 16)
     write_variable(DataState + 1258, 16);
    // write RanUe_Location_NrLocation_UeLocationTimestamp (size 8)
     write_variable(DataState + 1330, 8);
    // write RanUe_Location_NrLocation_AgeOfLocationInformation (size 4)
     write_variable(DataState + 1254, 4);
    // write AmfUe_LocationChanged (size 1)
     write_variable(DataState + 357, 1);
    // write AmfUe_Location (size 24)
     write_variable(DataState + 309, 24);
    // write AmfUe_Tai (size 24)
     write_variable(DataState + 333, 24);
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_UpdateLocation_3_security_mode_complete;
            break;
        case 6: m->event = ControlState->E_UpdateLocation_6_transport5GSMMessage;
            break;
        case 2: m->event = ControlState->E_UpdateLocation_2_authentication_response;
            break;
        case 5: m->event = ControlState->E_UpdateLocation_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(UpdateLocation)
{
    //DEBUG_PRINT("UpdateLocation called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_HandleNAS_3_security_mode_complete;
            break;
        case 6: m->event = ControlState->E_HandleNAS_6_transport5GSMMessage;
            break;
        case 1: m->event = ControlState->E_HandleNAS_1_initialue;
            break;
        case 2: m->event = ControlState->E_HandleNAS_2_authentication_response;
            break;
        case 5: m->event = ControlState->E_HandleNAS_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(HandleNAS)
{
    //DEBUG_PRINT("HandleNAS called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // read AmfUe_ULCount (size 4)
     read_variable(DataState + 1611, 4);
    // read AmfUe_ULCount (size 4)
     read_variable(DataState + 1611, 4);
    // read AmfUe_SecurityContextAvailable (size 1)
     read_variable(DataState + 1452, 1);
    // read AmfUe_ULCount (size 4)
     read_variable(DataState + 1611, 4);
    // read AmfUe_SecurityContextAvailable (size 1)
     read_variable(DataState + 1452, 1);
    // read AmfUe_IntegrityAlg (size 1)
     read_variable(DataState + 1620, 1);
    // read AmfUe_KnasInt (size 16)
     read_variable(DataState + 1530, 16);
    // read AmfUe_CipheringAlg (size 1)
     read_variable(DataState + 1619, 1);
    // read AmfUe_KnasEnc (size 16)
     read_variable(DataState + 1546, 16);
    // read AmfUe_SecurityContextAvailable (size 1)
     read_variable(DataState + 1452, 1);
    // read AmfUe_ULCount (size 4)
     read_variable(DataState + 1611, 4);
    // read AmfUe_ULCount (size 4)
     read_variable(DataState + 1611, 4);
    // read AmfUe_SecurityContextAvailable (size 1)
     read_variable(DataState + 1452, 1);
    // read AmfUe_IntegrityAlg (size 1)
     read_variable(DataState + 1620, 1);
    // read AmfUe_KnasInt (size 16)
     read_variable(DataState + 1530, 16);
    // read AmfUe_CipheringAlg (size 1)
     read_variable(DataState + 1619, 1);
    // read AmfUe_KnasEnc (size 16)
     read_variable(DataState + 1546, 16);
    // read AmfUe_SecurityContextAvailable (size 1)
     read_variable(DataState + 1452, 1);
    // read AmfUe_ULCount (size 4)
     read_variable(DataState + 1611, 4);
    // read AmfUe_ULCount (size 4)
     read_variable(DataState + 1611, 4);
    // read AmfUe_SecurityContextAvailable (size 1)
     read_variable(DataState + 1452, 1);
    // read AmfUe_IntegrityAlg (size 1)
     read_variable(DataState + 1620, 1);
    // read AmfUe_KnasInt (size 16)
     read_variable(DataState + 1530, 16);
    // read AmfUe_CipheringAlg (size 1)
     read_variable(DataState + 1619, 1);
    // read AmfUe_KnasEnc (size 16)
     read_variable(DataState + 1546, 16);
    // read AmfUe_SecurityContextAvailable (size 1)
     read_variable(DataState + 1452, 1);
    // read AmfUe_ULCount (size 4)
     read_variable(DataState + 1611, 4);
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_Decode_3_security_mode_complete;
            break;
        case 6: m->event = ControlState->E_Decode_6_transport5GSMMessage;
            break;
        case 1: m->event = ControlState->E_NewAmfUe_1_initialue;
            break;
        case 2: m->event = ControlState->E_Decode_2_authentication_response;
            break;
        case 5: m->event = ControlState->E_Decode_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(Decode)
{
    //DEBUG_PRINT("Decode called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_Dispatch_3_security_mode_complete;
            break;
        case 6: m->event = ControlState->E_Dispatch_6_transport5GSMMessage;
            break;
        case 1: m->event = ControlState->E_DeRegistered_1_initialue;
            break;
        case 2: m->event = ControlState->E_Dispatch_2_authentication_response;
            break;
        case 5: m->event = ControlState->E_GetBearerType_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(Dispatch)
{
    //DEBUG_PRINT("Dispatch called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_SecurityMode_3_security_mode_complete;
            break;
        case 6: m->event = ControlState->E_Registered_6_transport5GSMMessage;
            break;
        case 2: m->event = ControlState->E_Authentication_2_authentication_response;
            break;
        case 5: m->event = ControlState->E_ContextSetup_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(SecurityMode)
{
    //DEBUG_PRINT("SecurityMode called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // read AmfUe_SecurityContextAvailable (size 1)
     read_variable(DataState + 1452, 1);
    // read AmfUe_NgKsi_Ksi (size 4)
     read_variable(DataState + 1509, 4);
    // read AmfUe_MacFailed (size 1)
     read_variable(DataState + 1529, 1);
    // write AmfUe_CipheringAlg (size 1)
     write_variable(DataState + 1619, 1);
    // write AmfUe_IntegrityAlg (size 1)
     write_variable(DataState + 1620, 1);
    // write AmfUe_IntegrityAlg (size 1)
     write_variable(DataState + 1620, 1);
    // write AmfUe_CipheringAlg (size 1)
     write_variable(DataState + 1619, 1);
    // read AmfUe_CipheringAlg (size 1)
     read_variable(DataState + 1619, 1);
    // read AmfUe_IntegrityAlg (size 1)
     read_variable(DataState + 1620, 1);
    // write AmfUe_KnasInt (size 16)
     write_variable(DataState + 1530, 16);
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_HandleSecurityModeComplete_3_security_mode_complete;
            break;
        case 2: m->event = ControlState->E_SecurityContextIsValid_2_authentication_response;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(HandleSecurityModeComplete)
{
    //DEBUG_PRINT("HandleSecurityModeComplete called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // write AmfUe_T3560 (size 24)
     write_variable(DataState + 1831, 24);
    // read AmfUe_SecurityContextAvailable (size 1)
     read_variable(DataState + 1452, 1);
    // read AmfUe_NgKsi_Ksi (size 4)
     read_variable(DataState + 1509, 4);
    // read AmfUe_MacFailed (size 1)
     read_variable(DataState + 1529, 1);
    // read AmfUe_Kgnb (size 24)
     read_variable(DataState + 1562, 24);
    // write AmfUe_NCC (size 1)
     write_variable(DataState + 1610, 1);
    m->event = ControlState->E_StopT3560_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(StopT3560)
{
    //DEBUG_PRINT("StopT3560 called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_Stop_3_security_mode_complete;
            break;
        case 2: m->event = ControlState->E_Stop_2_authentication_response;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(Stop)
{
    //DEBUG_PRINT("Stop called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_SecurityContextIsValid_3_security_mode_complete;
            break;
        case 2: m->event = ControlState->E_SendAuth5gAkaConfirmRequest_2_authentication_response;
            break;
        case 5: m->event = ControlState->E_Registered_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(SecurityContextIsValid)
{
    //DEBUG_PRINT("SecurityContextIsValid called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_UpdateSecurityContext_3_security_mode_complete;
            break;
        case 1: m->event = ControlState->E_SendUEAuthenticationAuthenticateRequest_1_initialue;
            break;
        case 2: m->event = ControlState->E_SelectSecurityAlg_2_authentication_response;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(UpdateSecurityContext)
{
    //DEBUG_PRINT("UpdateSecurityContext called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // read AmfUe_ULCount (size 4)
     read_variable(DataState + 1611, 4);
    // read AmfUe_Kamf (size 16)
     read_variable(DataState + 774, 16);
    // read AmfUe_Kamf (size 16)
     read_variable(DataState + 774, 16);
    // write AmfUe_NH (size 24)
     write_variable(DataState + 1586, 24);
    // read AmfUe_ULCount (size 4)
     read_variable(DataState + 1611, 4);
    // read AmfUe_Kamf (size 16)
     read_variable(DataState + 774, 16);
    // read AmfUe_Kamf (size 16)
     read_variable(DataState + 774, 16);
    // write AmfUe_NH (size 24)
     write_variable(DataState + 1586, 24);
    m->event = ControlState->E_DerivateAnKey_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(DerivateAnKey)
{
    //DEBUG_PRINT("DerivateAnKey called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_DerivateNH_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(DerivateNH)
{
    //DEBUG_PRINT("DerivateNH called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_ContextSetup_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(ContextSetup)
{
    //DEBUG_PRINT("ContextSetup called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // read AmfUe_ServingAmfChanged (size 1)
     read_variable(DataState + 98, 1);
    // read AmfUe_Pei (size 16)
     read_variable(DataState + 205, 16);
    // read AmfUe_RegistrationType5GS (size 1)
     read_variable(DataState + 88, 1);
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_HandleInitialRegistration_3_security_mode_complete;
            break;
        case 5: m->event = ControlState->E_HandleRegistrationComplete_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(HandleInitialRegistration)
{
    //DEBUG_PRINT("HandleInitialRegistration called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // read AmfUe_Kgnb (size 24)
     read_variable(DataState + 1562, 24);
    // write AmfUe_NCC (size 1)
     write_variable(DataState + 1610, 1);
    // read AmfUe_NudmSDMUri (size 16)
     read_variable(DataState + 358, 16);
    // read AmfUe_Supi (size 16)
     read_variable(DataState + 172, 16);
    // read AmfUe_PcfUri (size 16)
     read_variable(DataState + 790, 16);
    // read AmfUe_Supi (size 16)
     read_variable(DataState + 172, 16);
    // read AmfUe_Pei (size 16)
     read_variable(DataState + 205, 16);
    // read AmfUe_Gpsi (size 16)
     read_variable(DataState + 189, 16);
    // read AmfUe_PlmnId (size 32)
     read_variable(DataState + 124, 32);
    // read AmfUe_AccessAndMobilitySubscriptionData (size 240)
     read_variable(DataState + 374, 240);
    m->event = ControlState->E_getSubscribedNssai_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(getSubscribedNssai)
{
    //DEBUG_PRINT("getSubscribedNssai called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // read AmfUe_SdmSubscriptionId (size 16)
     read_variable(DataState + 1774, 16);
    // read AmfUe_PlmnId (size 32)
     read_variable(DataState + 124, 32);
    m->event = ControlState->E_SearchUdmSdmInstance_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(SearchUdmSdmInstance)
{
    //DEBUG_PRINT("SearchUdmSdmInstance called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SDMGetSliceSelectionSubscriptionData_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(SDMGetSliceSelectionSubscriptionData)
{
    //DEBUG_PRINT("SDMGetSliceSelectionSubscriptionData called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_handleRequestedNssai_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(handleRequestedNssai)
{
    //DEBUG_PRINT("handleRequestedNssai called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_InSubscribedNssai_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(InSubscribedNssai)
{
    //DEBUG_PRINT("InSubscribedNssai called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_InAllowedNssai_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(InAllowedNssai)
{
    //DEBUG_PRINT("InAllowedNssai called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_storeLastVisitedRegisteredTAI_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(storeLastVisitedRegisteredTAI)
{
    //DEBUG_PRINT("storeLastVisitedRegisteredTAI called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_negotiateDRXParameters_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(negotiateDRXParameters)
{
    //DEBUG_PRINT("negotiateDRXParameters called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_communicateWithUDM_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(communicateWithUDM)
{
    //DEBUG_PRINT("communicateWithUDM called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SendSearchNFInstances_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(SendSearchNFInstances)
{
    //DEBUG_PRINT("SendSearchNFInstances called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_UeCmRegistration_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(UeCmRegistration)
{
    //DEBUG_PRINT("UeCmRegistration called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SDMGetAmData_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(SDMGetAmData)
{
    //DEBUG_PRINT("SDMGetAmData called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SDMGetSmfSelectData_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(SDMGetSmfSelectData)
{
    //DEBUG_PRINT("SDMGetSmfSelectData called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SDMGetUeContextInSmfData_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(SDMGetUeContextInSmfData)
{
    //DEBUG_PRINT("SDMGetUeContextInSmfData called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SDMSubscribe_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(SDMSubscribe)
{
    //DEBUG_PRINT("SDMSubscribe called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_AMPolicyControlCreate_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(AMPolicyControlCreate)
{
    //DEBUG_PRINT("AMPolicyControlCreate called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_GetIPv4Uri_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(GetIPv4Uri)
{
    //DEBUG_PRINT("GetIPv4Uri called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_HTTPAMFStatusChangeSubscribe_3_security_mode_complete;
            break;
        case 6: m->event = ControlState->E_SmfUri_6_transport5GSMMessage;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(HTTPAMFStatusChangeSubscribe)
{
    //DEBUG_PRINT("HTTPAMFStatusChangeSubscribe called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_HandleAMFStatusChangeSubscribeRequest_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(HandleAMFStatusChangeSubscribeRequest)
{
    //DEBUG_PRINT("HandleAMFStatusChangeSubscribeRequest called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_AMFStatusChangeSubscribeProcedure_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(AMFStatusChangeSubscribeProcedure)
{
    //DEBUG_PRINT("AMFStatusChangeSubscribeProcedure called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_NewAMFStatusSubscription_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(NewAMFStatusSubscription)
{
    //DEBUG_PRINT("NewAMFStatusSubscription called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_AllocateRegistrationArea_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(AllocateRegistrationArea)
{
    //DEBUG_PRINT("AllocateRegistrationArea called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_assignLadnInfo_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(assignLadnInfo)
{
    //DEBUG_PRINT("assignLadnInfo called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_AddAmfUeToUePool_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(AddAmfUeToUePool)
{
    //DEBUG_PRINT("AddAmfUeToUePool called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SendRegistrationAccept_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(SendRegistrationAccept)
{
    //DEBUG_PRINT("SendRegistrationAccept called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // read AmfUe_Guti (size 16)
     read_variable(DataState + 221, 16);
    // read AmfUe_LadnInfo (size 40)
     read_variable(DataState + 1669, 40);
    // read AmfUe_NetworkSlicingSubscriptionChanged (size 1)
     read_variable(DataState + 1773, 1);
    // read AmfUe_T3512Value (size 8)
     read_variable(DataState + 1935, 8);
    // read AmfUe_T3512ValueT3502Value (size 8)
     read_variable(DataState + 1927, 8);
    // read AmfUe_UESpecificDRX (size 1)
     read_variable(DataState + 1451, 1);
    // read RanUe_UeContextRequest (size 1)
     read_variable(DataState + 1354, 1);
    m->event = ControlState->E_BuildRegistrationAccept_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(BuildRegistrationAccept)
{
    //DEBUG_PRINT("BuildRegistrationAccept called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_includeConfiguredNssaiCheck_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(includeConfiguredNssaiCheck)
{
    //DEBUG_PRINT("includeConfiguredNssaiCheck called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_GetNasIENetworkFeatureSupport5GS_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(GetNasIENetworkFeatureSupport5GS)
{
    //DEBUG_PRINT("GetNasIENetworkFeatureSupport5GS called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_Encode_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(Encode)
{
    //DEBUG_PRINT("Encode called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_GetBearerType_3_security_mode_complete;
            break;
        case 2: m->event = ControlState->E_GetBearerType_2_authentication_response;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(GetBearerType)
{
    //DEBUG_PRINT("GetBearerType called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_SendN2Message_3_security_mode_complete;
            break;
        case 2: m->event = ControlState->E_SendDownlinkNasTransport_2_authentication_response;
            break;
        case 5: m->event = ControlState->E_Dispatch_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(SendN2Message)
{
    //DEBUG_PRINT("SendN2Message called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SendInitialContextSetupRequest_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(SendInitialContextSetupRequest)
{
    //DEBUG_PRINT("SendInitialContextSetupRequest called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_BuildInitialContextSetupRequest_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(BuildInitialContextSetupRequest)
{
    //DEBUG_PRINT("BuildInitialContextSetupRequest called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_GetNgapIEMobilityRestrictionList_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(GetNgapIEMobilityRestrictionList)
{
    //DEBUG_PRINT("GetNgapIEMobilityRestrictionList called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_BuildIEMobilityRestrictionList_3_security_mode_complete;
            break;
        case 1: m->event = ControlState->E_SendToRanUe_1_initialue;
            break;
        case 2: m->event = ControlState->E_SendToRanUe_2_authentication_response;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(BuildIEMobilityRestrictionList)
{
    //DEBUG_PRINT("BuildIEMobilityRestrictionList called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_GetNgapIEMaskedIMEISV_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(GetNgapIEMaskedIMEISV)
{
    //DEBUG_PRINT("GetNgapIEMaskedIMEISV called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_GetNgapIERedirectionVoiceFallback_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(GetNgapIERedirectionVoiceFallback)
{
    //DEBUG_PRINT("GetNgapIERedirectionVoiceFallback called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_NasSendToRan_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(NasSendToRan)
{
    //DEBUG_PRINT("NasSendToRan called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SendToRanUe_3_security_mode_complete;
}

INLINE_ACTOR_ACTION(SendToRanUe)
{
    //DEBUG_PRINT("SendToRanUe called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_SendToRan_3_security_mode_complete;
            break;
        case 1: m->event = ControlState->E_SendToRan_1_initialue;
            break;
        case 2: m->event = ControlState->E_SendToRan_2_authentication_response;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(SendToRan)
{
    //DEBUG_PRINT("SendToRan called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->E_NewTimer_3_security_mode_complete;
            break;
        case 1: m->event = ControlState->E_NewTimer_1_initialue;
            break;
        case 2: m->event = ControlState->E_NewTimer_2_authentication_response;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(NewTimer)
{
    //DEBUG_PRINT("NewTimer called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 3: m->event = ControlState->packet;
            break;
        case 1: m->event = ControlState->packet;
            break;
        case 2: m->event = ControlState->packet;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(Registered)
{
    //DEBUG_PRINT("Registered called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // write AmfUe_RegistrationRequest (size 8)
     write_variable(DataState + 90, 8);
    // write AmfUe_RegistrationType5GS (size 1)
     write_variable(DataState + 88, 1);
    // write AmfUe_IdentityTypeUsedForRegistration (size 1)
     write_variable(DataState + 89, 1);
    // write AmfUe_AuthFailureCauseSynchFailureTimes (size 8)
     write_variable(DataState + 718, 8);
    // write AmfUe_IdentityRequestSendTimes (size 8)
     write_variable(DataState + 726, 8);
    // write AmfUe_ServingAmfChanged (size 1)
     write_variable(DataState + 98, 1);
    // write AmfUe_RegistrationAcceptForNon3GPPAccess (size 24)
     write_variable(DataState + 99, 24);
    // write AmfUe_RetransmissionOfInitialNASMsg (size 1)
     write_variable(DataState + 123, 1);
    // read AmfUe_MacFailed (size 1)
     read_variable(DataState + 1529, 1);
    switch(ControlState->current_cstate){
        case 6: m->event = ControlState->E_HandleULNASTransport_6_transport5GSMMessage;
            break;
        case 5: m->event = ControlState->E_ClearRegistrationRequestData_5_registration_complete;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(HandleULNASTransport)
{
    //DEBUG_PRINT("HandleULNASTransport called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_transport5GSMMessage_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(transport5GSMMessage)
{
    //DEBUG_PRINT("transport5GSMMessage called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SmContextFindByPDUSessionID_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(SmContextFindByPDUSessionID)
{
    //DEBUG_PRINT("SmContextFindByPDUSessionID called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 6: m->event = ControlState->E_CreatePDUSession_6_transport5GSMMessage;
            break;
        case 7: m->event = ControlState->E_SendUpdateSmContextN2Info_7_pdu_session_resource_setup_response;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(CreatePDUSession)
{
    //DEBUG_PRINT("CreatePDUSession called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SelectSmf_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(SelectSmf)
{
    //DEBUG_PRINT("SelectSmf called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_ServingAMF_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(ServingAMF)
{
    //DEBUG_PRINT("ServingAMF called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_GetNsiInformationFromSnssai_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(GetNsiInformationFromSnssai)
{
    //DEBUG_PRINT("GetNsiInformationFromSnssai called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SearchNssfNSSelectionInstance_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(SearchNssfNSSelectionInstance)
{
    //DEBUG_PRINT("SearchNssfNSSelectionInstance called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_NSSelectionGetForPduSession_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(NSSelectionGetForPduSession)
{
    //DEBUG_PRINT("NSSelectionGetForPduSession called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_NewSmContext_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(NewSmContext)
{
    //DEBUG_PRINT("NewSmContext called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SetSnssai_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(SetSnssai)
{
    //DEBUG_PRINT("SetSnssai called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SetDnn_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(SetDnn)
{
    //DEBUG_PRINT("SetDnn called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SetAccessType_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(SetAccessType)
{
    //DEBUG_PRINT("SetAccessType called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SetNsInstance_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(SetNsInstance)
{
    //DEBUG_PRINT("SetNsInstance called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SetSmfID_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(SetSmfID)
{
    //DEBUG_PRINT("SetSmfID called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SetSmfUri_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(SetSmfUri)
{
    //DEBUG_PRINT("SetSmfUri called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SendCreateSmContextRequest_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(SendCreateSmContextRequest)
{
    //DEBUG_PRINT("SendCreateSmContextRequest called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_buildCreateSmContextRequest_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(buildCreateSmContextRequest)
{
    //DEBUG_PRINT("buildCreateSmContextRequest called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_PduSessionID_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(PduSessionID)
{
    //DEBUG_PRINT("PduSessionID called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_Snssai_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(Snssai)
{
    //DEBUG_PRINT("Snssai called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_Dnn_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(Dnn)
{
    //DEBUG_PRINT("Dnn called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_AccessType_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(AccessType)
{
    //DEBUG_PRINT("AccessType called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_GetIPv4Uri_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(SmfUri)
{
    //DEBUG_PRINT("SmfUri called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 6: m->event = ControlState->E_SetSmContextRef_6_transport5GSMMessage;
            break;
        case 7: m->event = ControlState->E_SmContextRef_7_pdu_session_resource_setup_response;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(SetSmContextRef)
{
    //DEBUG_PRINT("SetSmContextRef called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SetUserLocation_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(SetUserLocation)
{
    //DEBUG_PRINT("SetUserLocation called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_StoreSmContext_6_transport5GSMMessage;
}

INLINE_ACTOR_ACTION(StoreSmContext)
{
    //DEBUG_PRINT("StoreSmContext called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->packet;
}

INLINE_ACTOR_ACTION(handlerPDUSessionResourceSetupResponse)
{
    //DEBUG_PRINT("handlerPDUSessionResourceSetupResponse called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_ranUeFind_7_pdu_session_resource_setup_response;
}

INLINE_ACTOR_ACTION(handlePDUSessionResourceSetupResponseMain)
{
    //DEBUG_PRINT("handlePDUSessionResourceSetupResponseMain called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SmContextFindByPDUSessionID_7_pdu_session_resource_setup_response;
}

INLINE_ACTOR_ACTION(SendUpdateSmContextN2Info)
{
    //DEBUG_PRINT("SendUpdateSmContextN2Info called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SendUpdateSmContextRequest_7_pdu_session_resource_setup_response;
}

INLINE_ACTOR_ACTION(SendUpdateSmContextRequest)
{
    //DEBUG_PRINT("SendUpdateSmContextRequest called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SmfUri_7_pdu_session_resource_setup_response;
}

INLINE_ACTOR_ACTION(SmContextRef)
{
    //DEBUG_PRINT("SmContextRef called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->packet;
}

INLINE_ACTOR_ACTION(handlerInitialUEMessage)
{
    //DEBUG_PRINT("handlerInitialUEMessage called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // write RanUe_RRCEstablishmentCause (size 16)
     write_variable(DataState + 1338, 16);
    // write RanUe_InitialUEMessage (size 24)
     write_variable(DataState + 1134, 24);
    m->event = ControlState->E_handleInitialUEMessageMain_1_initialue;
}

INLINE_ACTOR_ACTION(handleInitialUEMessageMain)
{
    //DEBUG_PRINT("handleInitialUEMessageMain called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // write RanUe_Location_NrLocation (size 72)
     write_variable(DataState + 1182, 72);
    // write RanUe_Location_NrLocation_Tai (size 24)
     write_variable(DataState + 1282, 24);
    // write RanUe_Location_NrLocation_Tai_PlmnId (size 8)
     write_variable(DataState + 1306, 8);
    // write RanUe_Location_NrLocation_Tai_Tac (size 16)
     write_variable(DataState + 1314, 16);
    // write RanUe_Tai (size 24)
     write_variable(DataState + 1158, 24);
    // write RanUe_Location_NrLocation_Ncgi_PlmnId (size 8)
     write_variable(DataState + 1274, 8);
    // write RanUe_Location_NrLocation_Ncgi_NrCellId (size 16)
     write_variable(DataState + 1258, 16);
    // write RanUe_Location_NrLocation_UeLocationTimestamp (size 8)
     write_variable(DataState + 1330, 8);
    // write RanUe_Location_NrLocation_AgeOfLocationInformation (size 4)
     write_variable(DataState + 1254, 4);
    m->event = ControlState->E_RanUeFindByRanUeNgapID_1_initialue;
}

INLINE_ACTOR_ACTION(RanUeFindByRanUeNgapID)
{
    //DEBUG_PRINT("RanUeFindByRanUeNgapID called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_NewRanUe_1_initialue;
}

INLINE_ACTOR_ACTION(NewRanUe)
{
    //DEBUG_PRINT("NewRanUe called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_UpdateLocation_1_initialue;
}

INLINE_ACTOR_ACTION(NewAmfUe)
{
    //DEBUG_PRINT("NewAmfUe called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // write AmfUe_servingAMF (size 8)
     write_variable(DataState + 0, 8);
    // write AmfUe_State (size 64)
     write_variable(DataState + 8, 64);
    // write AmfUe_State_models_AccessType__3_GPP_ACCESS_ (size 8)
     write_variable(DataState + 80, 8);
    // write AmfUe_State_models_AccessType_NON_3_GPP_ACCESS_ (size 8)
     write_variable(DataState + 72, 8);
    // write AmfUe_UnauthenticatedSupi (size 1)
     write_variable(DataState + 188, 1);
    // write AmfUe_EventSubscriptionsInfo (size 72)
     write_variable(DataState + 237, 72);
    // write AmfUe_RanUe (size 296)
     write_variable(DataState + 822, 296);
    // write AmfUe_RegistrationArea (size 48)
     write_variable(DataState + 1621, 48);
    // write AmfUe_AllowedNssai (size 64)
     write_variable(DataState + 1709, 64);
    // write AmfUe_N1N2MessageIDGenerator (size 8)
     write_variable(DataState + 806, 8);
    // write AmfUe_N1N2MessageSubscribeIDGenerator (size 8)
     write_variable(DataState + 814, 8);
    // write AmfUe_onGoing (size 48)
     write_variable(DataState + 1355, 48);
    // write AmfUe_onGoing_models_AccessType_NON_3_GPP_ACCESS_ (size 8)
     write_variable(DataState + 1403, 8);
    // write AmfUe_onGoing_models_AccessType_NON_3_GPP_ACCESS__Procedure (size 16)
     write_variable(DataState + 1411, 16);
    // write AmfUe_onGoing_models_AccessType__3_GPP_ACCESS_ (size 8)
     write_variable(DataState + 1427, 8);
    // write AmfUe_onGoing_models_AccessType__3_GPP_ACCESS__Procedure (size 16)
     write_variable(DataState + 1435, 16);
    // write AmfUe_ReleaseCause (size 48)
     write_variable(DataState + 1879, 48);
    // write AmfUe_UeCmRegistered (size 25)
     write_variable(DataState + 1790, 25);
    m->event = ControlState->E_init_1_initialue;
}

INLINE_ACTOR_ACTION(init)
{
    //DEBUG_PRINT("init called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_AllocateGutiToUe_1_initialue;
}

INLINE_ACTOR_ACTION(AllocateGutiToUe)
{
    //DEBUG_PRINT("AllocateGutiToUe called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_TmsiAllocate_1_initialue;
}

INLINE_ACTOR_ACTION(TmsiAllocate)
{
    //DEBUG_PRINT("TmsiAllocate called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_AttachRanUeToAmfUeAndReleaseOldIfAny_1_initialue;
}

INLINE_ACTOR_ACTION(AttachRanUeToAmfUeAndReleaseOldIfAny)
{
    //DEBUG_PRINT("AttachRanUeToAmfUeAndReleaseOldIfAny called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_AttachRanUe_1_initialue;
}

INLINE_ACTOR_ACTION(AttachRanUe)
{
    //DEBUG_PRINT("AttachRanUe called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_Decode_1_initialue;
}

INLINE_ACTOR_ACTION(DeRegistered)
{
    //DEBUG_PRINT("DeRegistered called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // write AmfUe_RetransmissionOfInitialNASMsg (size 1)
     write_variable(DataState + 123, 1);
    // write AmfUe_RegistrationRequest (size 8)
     write_variable(DataState + 90, 8);
    // write AmfUe_RegistrationType5GS (size 1)
     write_variable(DataState + 88, 1);
    // write AmfUe_SecurityContextAvailable (size 1)
     write_variable(DataState + 1452, 1);
    // write AmfUe_IdentityTypeUsedForRegistration (size 1)
     write_variable(DataState + 89, 1);
    // write AmfUe_Suci (size 16)
     write_variable(DataState + 156, 16);
    // write AmfUe_PlmnId (size 32)
     write_variable(DataState + 124, 32);
    // write AmfUe_NgKsi_Tsc (size 16)
     write_variable(DataState + 1513, 16);
    // write AmfUe_NgKsi_Ksi (size 4)
     write_variable(DataState + 1509, 4);
    // write AmfUe_Location (size 24)
     write_variable(DataState + 309, 24);
    // write AmfUe_Tai (size 24)
     write_variable(DataState + 333, 24);
    // write AmfUe_UESecurityCapability (size 32)
     write_variable(DataState + 1453, 32);
    // read AmfUe_ServingAmfChanged (size 1)
     read_variable(DataState + 98, 1);
    m->event = ControlState->E_HandleRegistrationRequest_1_initialue;
}

INLINE_ACTOR_ACTION(HandleRegistrationRequest)
{
    //DEBUG_PRINT("HandleRegistrationRequest called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // read AmfUe_T3513 (size 8)
     read_variable(DataState + 1815, 8);
    // read AmfUe_T3565 (size 8)
     read_variable(DataState + 1823, 8);
    m->event = ControlState->E_SetOnGoing_1_initialue;
}

INLINE_ACTOR_ACTION(SetOnGoing)
{
    //DEBUG_PRINT("SetOnGoing called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_StopT3513_1_initialue;
}

INLINE_ACTOR_ACTION(StopT3513)
{
    //DEBUG_PRINT("StopT3513 called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_StopT3565_1_initialue;
}

INLINE_ACTOR_ACTION(StopT3565)
{
    //DEBUG_PRINT("StopT3565 called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_PlmnIdStringToModels_1_initialue;
}

INLINE_ACTOR_ACTION(PlmnIdStringToModels)
{
    //DEBUG_PRINT("PlmnIdStringToModels called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_InTaiList_1_initialue;
}

INLINE_ACTOR_ACTION(InTaiList)
{
    //DEBUG_PRINT("InTaiList called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_Authentication_1_initialue;
}

INLINE_ACTOR_ACTION(Authentication)
{
    //DEBUG_PRINT("Authentication called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // write AmfUe_AusfId (size 16)
     write_variable(DataState + 614, 16);
    // write AmfUe_AusfUri (size 16)
     write_variable(DataState + 630, 16);
    // write AmfUe_ABBA (size 24)
     write_variable(DataState + 734, 24);
    // read AmfUe_AuthenticationCtx (size 56)
     read_variable(DataState + 646, 56);
    // write AmfUe_UnauthenticatedSupi (size 1)
     write_variable(DataState + 188, 1);
    // write AmfUe_Kseaf (size 16)
     write_variable(DataState + 758, 16);
    // write AmfUe_Supi (size 16)
     write_variable(DataState + 172, 16);
    // write AmfUe_Kamf (size 16)
     write_variable(DataState + 774, 16);
    switch(ControlState->current_cstate){
        case 1: m->event = ControlState->E_AuthenticationProcedure_1_initialue;
            break;
        case 2: m->event = ControlState->E_HandleAuthenticationResponse_2_authentication_response;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(AuthenticationProcedure)
{
    //DEBUG_PRINT("AuthenticationProcedure called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // read AmfUe_Supi (size 16)
     read_variable(DataState + 172, 16);
    // read AmfUe_Suci (size 16)
     read_variable(DataState + 156, 16);
    // read AmfUe_SecurityContextAvailable (size 1)
     read_variable(DataState + 1452, 1);
    // read AmfUe_NgKsi_Ksi (size 4)
     read_variable(DataState + 1509, 4);
    // read AmfUe_MacFailed (size 1)
     read_variable(DataState + 1529, 1);
    m->event = ControlState->E_IdentityVerification_1_initialue;
}

INLINE_ACTOR_ACTION(IdentityVerification)
{
    //DEBUG_PRINT("IdentityVerification called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SecurityContextIsValid_1_initialue;
}

INLINE_ACTOR_ACTION(SendUEAuthenticationAuthenticateRequest)
{
    //DEBUG_PRINT("SendUEAuthenticationAuthenticateRequest called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SendAuthenticationRequest_1_initialue;
}

INLINE_ACTOR_ACTION(SendAuthenticationRequest)
{
    //DEBUG_PRINT("SendAuthenticationRequest called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // read AmfUe_NgKsi (size 24)
     read_variable(DataState + 1485, 24);
    // read AmfUe_ABBA (size 24)
     read_variable(DataState + 734, 24);
    // read AmfUe_AuthenticationCtx_Var5gAuthData (size 16)
     read_variable(DataState + 702, 16);
    m->event = ControlState->E_BuildAuthenticationRequest_1_initialue;
}

INLINE_ACTOR_ACTION(BuildAuthenticationRequest)
{
    //DEBUG_PRINT("BuildAuthenticationRequest called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SendDownlinkNasTransport_1_initialue;
}

INLINE_ACTOR_ACTION(SendDownlinkNasTransport)
{
    //DEBUG_PRINT("SendDownlinkNasTransport called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // read RanUe_AmfUeNgapId (size 8)
     read_variable(DataState + 1126, 8);
    // read RanUe_RanUeNgapId (size 8)
     read_variable(DataState + 1118, 8);
    // read RanUe_AmfUeNgapId (size 8)
     read_variable(DataState + 1126, 8);
    // read RanUe_RanUeNgapId (size 8)
     read_variable(DataState + 1118, 8);
    switch(ControlState->current_cstate){
        case 1: m->event = ControlState->E_BuildDownlinkNasTransport_1_initialue;
            break;
        case 2: m->event = ControlState->E_BuildDownlinkNasTransport_2_authentication_response;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(BuildDownlinkNasTransport)
{
    //DEBUG_PRINT("BuildDownlinkNasTransport called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    switch(ControlState->current_cstate){
        case 1: m->event = ControlState->E_GetNgapIEMobilityRestrictionList_1_initialue;
            break;
        case 2: m->event = ControlState->E_GetNgapIEMobilityRestrictionList_2_authentication_response;
            break;
        default: printf("Error: unknown state\n");exit(1);
    }

}

INLINE_ACTOR_ACTION(HandleAuthenticationResponse)
{
    //DEBUG_PRINT("HandleAuthenticationResponse called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // write AmfUe_T3560 (size 24)
     write_variable(DataState + 1831, 24);
    m->event = ControlState->E_StopT3560_2_authentication_response;
}

INLINE_ACTOR_ACTION(SendAuth5gAkaConfirmRequest)
{
    //DEBUG_PRINT("SendAuth5gAkaConfirmRequest called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_DerivateKamf_2_authentication_response;
}

INLINE_ACTOR_ACTION(DerivateKamf)
{
    //DEBUG_PRINT("DerivateKamf called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SecurityMode_2_authentication_response;
}

INLINE_ACTOR_ACTION(SelectSecurityAlg)
{
    //DEBUG_PRINT("SelectSecurityAlg called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_DerivateAlgKey_2_authentication_response;
}

INLINE_ACTOR_ACTION(DerivateAlgKey)
{
    //DEBUG_PRINT("DerivateAlgKey called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_SendSecurityModeCommand_2_authentication_response;
}

INLINE_ACTOR_ACTION(SendSecurityModeCommand)
{
    //DEBUG_PRINT("SendSecurityModeCommand called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // read AmfUe_CipheringAlg (size 1)
     read_variable(DataState + 1619, 1);
    // read AmfUe_IntegrityAlg (size 1)
     read_variable(DataState + 1620, 1);
    // read AmfUe_NgKsi (size 24)
     read_variable(DataState + 1485, 24);
    // read AmfUe_Pei (size 16)
     read_variable(DataState + 205, 16);
    // read AmfUe_RetransmissionOfInitialNASMsg (size 1)
     read_variable(DataState + 123, 1);
    // read AmfUe_RegistrationType5GS (size 1)
     read_variable(DataState + 88, 1);
    // read AmfUe_ABBA (size 24)
     read_variable(DataState + 734, 24);
    m->event = ControlState->E_BuildSecurityModeCommand_2_authentication_response;
}

INLINE_ACTOR_ACTION(BuildSecurityModeCommand)
{
    //DEBUG_PRINT("BuildSecurityModeCommand called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // write AmfUe_ULCount (size 4)
     write_variable(DataState + 1611, 4);
    // write AmfUe_DLCount (size 4)
     write_variable(DataState + 1615, 4);
    m->event = ControlState->E_Encode_2_authentication_response;
}

INLINE_ACTOR_ACTION(handlerInitialContextSetupResponse)
{
    //DEBUG_PRINT("handlerInitialContextSetupResponse called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_ranUeFind_4_initial_context_response;
}

INLINE_ACTOR_ACTION(handleInitialContextSetupResponseMain)
{
    //DEBUG_PRINT("handleInitialContextSetupResponseMain called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->packet;
}

INLINE_ACTOR_ACTION(HandleRegistrationComplete)
{
    //DEBUG_PRINT("HandleRegistrationComplete called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // write AmfUe_T3550 (size 24)
     write_variable(DataState + 1855, 24);
    m->event = ControlState->E_StopT3550_5_registration_complete;
}

INLINE_ACTOR_ACTION(StopT3550)
{
    //DEBUG_PRINT("StopT3550 called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->E_Stop_5_registration_complete;
}

INLINE_ACTOR_ACTION(ClearRegistrationRequestData)
{
    //DEBUG_PRINT("ClearRegistrationRequestData called\n");
    struct amf_free5gc_control_state *ControlState = (struct amf_free5gc_control_state *)m->control_state;
    void *DataState = (struct amf_free5gc_data_state *)m->data_state;
    // no associated states
    m->event = ControlState->packet;
}

#endif