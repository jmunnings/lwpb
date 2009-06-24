/**
 * @file socket_protocol.c
 * 
 * Helper functions for the socket RPC protocol.
 * 
 * Copyright 2009 Simon Kallweit
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *     
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>

#include <lwpb/lwpb.h>

#include "socket_protocol.h"
#include "socket_header_pb2.h"

int send_request(int socket, const struct lwpb_method_desc *method_desc,
                 void *req_buf, size_t req_len)
{
    struct lwpb_encoder encoder;
    uint8_t buf[128];
    size_t len;
    
    lwpb_encoder_init(&encoder);
    lwpb_encoder_start(&encoder, socket_header_Header, buf, sizeof(buf));
    lwpb_encoder_add_enum(&encoder, socket_header_Header_type, SOCKET_HEADER_REQUEST);
    lwpb_encoder_add_string(&encoder, socket_header_Header_service, (char *) method_desc->service->name);
    lwpb_encoder_add_string(&encoder, socket_header_Header_method, (char *) method_desc->name);
    lwpb_encoder_add_uint32(&encoder, socket_header_Header_length, req_len);
    len = lwpb_encoder_finish(&encoder);

    send(socket, buf, len, 0);
    send(socket, req_buf, req_len, 0);
}