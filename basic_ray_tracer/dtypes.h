/*
 * dtypes.h
 *
 *  Created on: Dec 12, 2015
 *      Author: Adrizcorp
 */

#ifndef DTYPES_H_
#define DTYPES_H_

#define NIOS 1

#if NIOS==1
	typedef unsigned long long uint64;
	typedef long long int64;
#else// PC version
	typedef unsigned long uint64;
	typedef long int  int64;
#endif



#endif /* DTYPES_H_ */
