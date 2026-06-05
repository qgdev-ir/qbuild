//
// Qson is a json serializer/deserializer based on RFC 8259
//

#ifndef _qson_qson_h_
#define _qson_qson_h_
#ifdef __cplusplus
extern "C" {
#endif

#define QSON_BEGIN_ARRAY	'['
#define QSON_END_ARRAY		']'
#define QSON_BEGIN_OBJECT	'{'
#define QSON_END_OBJECT		'}'
#define QSON_NAME_SEPARATOR	':'
#define QSON_VALUE_SEPARATOR	','
#define QSON_QUOTATION_MARK	'"'
const char QSON_WHITESPACES[5] = {'\n', '\r', '\t', ' '};

#ifdef __cplusplus
}
#endif
#endif

