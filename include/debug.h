#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef DEBUG_ESP_PORT
//#define DEBUG_CALL(...)
#define DEBUG_CALL(...) DEBUG_ESP_PORT.printf( __VA_ARGS__ )
#define DEBUG_MSG(...) DEBUG_ESP_PORT.printf( __VA_ARGS__ )
#define STRINGIFY_(X) #X
#define STRINGIFY(X) STRINGIFY_(X)
#else
#define DEBUG_CALL(...)
#define DEBUG_MSG(...)
#endif /* DEBUG_ESP_PORT */

#endif /* DEBUG_H_ */