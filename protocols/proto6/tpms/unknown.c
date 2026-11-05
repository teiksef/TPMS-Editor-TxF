/* Made just for saving unknown data
 * ID is random
 */

#include <furi_hal_random.h>
#include "../proto6_core.h"
#include "tpms_build.h"
#include "../../../tpms_save.h"

static bool decode(uint8_t *bits, uint32_t numbytes, uint32_t numbits, ProtoViewMsgInfo *info) {

    if(!tpms_cfg_is_debugunknown_enabled()) return false;	// only if this feature is enabled

    if (numbits < 20 || numbits > 1024) return false;	// do not react on very long streams
    FURI_LOG_E(TAG, "Unknown data, got %lu bits, %lu bytes from C1101", numbits, numbytes);

    info->start_off = 0;

    // Keep original bit length info in kpa, pulses count are capped anyway. Then limit if needed
    float kpa = (float)numbits;
    info->pulses_count = numbits;
    if(numbits > TPMS_RAWBITS_BUF) numbits = TPMS_RAWBITS_BUF;

    uint32_t id = furi_hal_random_get();
    uint8_t realbytes = (numbits+7U)/8U; // rounding up to bytes
    fieldset_add_bytes(info->fieldset,"Tire ID",(const uint8_t *)&id,4*2);
    fieldset_add_float(info->fieldset,"Pressure kpa",kpa,2);
    fieldset_add_bytes(info->fieldset, "Raw payload", (const uint8_t *)bits, (uint32_t)(realbytes * 2U));
//    fieldset_add_bytes(info->fieldset, "Raw payload", (const uint8_t *)bits, 64U*2U);
    fieldset_add_uint(info->fieldset, "Raw payload bits", numbits, 8U);
    return true;
}


static void get_fields(ProtoViewFieldSet* fieldset) {
    const uint8_t default_id[4] = {0x12, 0x34, 0x56, 0x78};
    fieldset_add_bytes(fieldset, "Tire ID", default_id, 8);
    fieldset_add_float(fieldset, "Pressure psi", 32.0f, 2);
}

static void build_message(RawSamplesBuffer* samples, ProtoViewFieldSet* fieldset) {
    const uint32_t te = 52U;
    uint8_t data[TPMS_RAWBITS_BUF/8] = {0};

    size_t raw_payload_size = tpms_build_load_raw_payload(fieldset, data, sizeof(data), NULL);
    // resend raw data
    if(raw_payload_size != 0U) {
        tpms_add_data(samples, data, raw_payload_size, te);

    }
}

ProtoViewDecoder UnknownDataDecoder = {
    .name = "Unknown Data",
    .decode = decode,
    .get_fields = get_fields,
    .build_message = build_message
};
