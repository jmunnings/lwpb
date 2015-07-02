# Introduction #

lwpb (short for lightweight protocol buffers) is an implementation of Google's protocol buffers (in short protobuf) in C for systems with limited resources.

For more information about protocol buffers in general, see:

http://code.google.com/p/protobuf/

# Forks #

I stopped development work on lwpb quite some time ago, but the project has been cloned and further improved and is available on https://github.com/acg/lwpb.git

Also, another interesting implementation of lightweight protocol buffers for C is available on https://github.com/haberman/upb, but note that this project is completely independent of lwpb.

# Design #

Most protobuf implementations represent messages as hierarchies of objects during runtime, which can be encoded/decoded to/from binary data streams. lwpb in contrast, encodes and decodes messages on the fly, much like a SAX parser does with XML. Encoding is done by calling encoder functions for each message and field to be encoded. Decoding uses callback functions to notify about messages and fields. Type information used for encoding and decoding is gathered from the compiled protobuf schema, generated with the protoc compiler using the lwpb output module.

# Limitations #

There are a few inherent limitations in lwpb, due to the simplicity of it's design:

  * The decoder does not warn the client when 'required' fields are missing
  * The decoder does not warn the client when 'required' or 'optional' fields have multiple occurances
  * The encoder does not implicitly encode 'required' fields with their default values, when the client does not manually encode them

# Usage #

The following shows a few examples of how to use lwpb. We use the following protobuf definitions:

```
package test;

message Info {
    required int32 result = 1;
    required string msg = 2;
}

message TestMessage {
    required int32 count = 1;
    required Info info = 2;
}
```

## Encoder ##

The following example will encode a simple message of the type 'TestMessage':

```
void encode_example(void)
{
    struct lwpb_encoder encoder;
    unsigned char buf[128];
    size_t len;
    
    // Initialize the encoder
    lwpb_encoder_init(&encoder);

    // Start encoding a message of type 'test.TestMessage' into buf
    lwpb_encoder_start(&encoder, test_TestMessage, buf, sizeof(buf));

    // Encode a 55 to the field 'count'
    lwpb_encoder_add_int32(&encoder, test_TestMessage_count, 55);

    // Start encoding the nested message of type 'test.Info' in field 'info'
    lwpb_encoder_nested_start(&encoder, test_TestMessage_info);

    // Encode a -1 to the field 'result'
    lwpb_encoder_add_int32(&encoder, test_Info_result, -1);

    // Encode a "Unknown" to the field 'msg'
    lwpb_encoder_add_string(&encoder, test_Info_msg, "Unknown");

    // Finish encoding the nested message of type 'test.Info'
    lwpb_encoder_nested_end(&encoder);

    // Finish encoding the message of type 'test.TestMessage'
    len = lwpb_encoder_finish(&encoder);

    // buf now holds the encoded message which is len bytes long
}
```

## Decoder ##

The following example will decode a simple message of the type 'TestMessage':

```
// Structure to decode into
struct TestMessage {
    int32 count;
    struct {
        int32 result;
        char msg[32];
    } info;
}

void msg_start_handler(struct lwpb_decoder *decoder,
                       const struct lwpb_msg_desc *msg_desc, void *arg)
{
    // We don't use the message start handler
}

void msg_end_handler(struct lwpb_decoder *decoder,
                     const struct lwpb_msg_desc *msg_desc, void *arg)
{
    // We don't use the message end handler
}

void field_handler(struct lwpb_decoder *decoder,
                   const struct lwpb_msg_desc *msg_desc,
                   const struct lwpb_field_desc *field_desc,
                   union lwpb_value *value, void *arg)
{
    struct TestMessage *msg = arg;
    
    // Copy fields into local structure
    if (msg_desc == test_TestMessage) {
        if (field_desc == test_TestMessage_count)
            msg->count = value->int32;
    } else if (msg_desc == test_Info) {
        if (field_desc == test_Info_result)
            msg->info.result = value->int32;
        if (field_desc == test_Info_msg)
            strncpy(msg->info.msg, sizeof(msg->info.msg), value->string.str);
    }
}

void decode_example(void)
{
    struct lwpb_decoder decoder;
    unsigned char buf[128];
    size_t len;
    struct TestMessage msg;
    
    // Initialize the decoder
    lwpb_decoder_init(&decoder);

    // Register a pointer to our local structure we want to decode into as
    // the argument for the decoder event handlers
    lwpb_decoder_arg(&decoder, &msg);

    // Register event handlers
    lwpb_decoder_msg_handler(&decoder, msg_start_handler, msg_end_handler);
    lwpb_decoder_field_handler(&decoder, field_handler);

    // Decode the binary buffer from the encode example
    lwpb_decoder_decode(&decoder, test_TestMessage, buf, len, NULL);

    // The local structure 'msg' will now hold the decoded values
}
```

## Struct map ##

TBD