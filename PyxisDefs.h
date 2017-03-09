/*
 * PyxisDefs.h
 *
 *  Created on: 16 Feb 2017
 *      Author: Matusovsky
 */

#ifndef PYXISDEFS_H_
#define PYXISDEFS_H_


#define JOIN_PKT_TYPE   0
#define REQ_PKT_TYPE    1

typedef enum { BACKOFF_HARMONIC = 0, BACKOFF_RAMPUP, BACKOFF_MIX } backoff_t;

#endif /* PYXISDEFS_H_ */
