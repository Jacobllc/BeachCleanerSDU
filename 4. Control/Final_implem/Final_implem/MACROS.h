/*
 * MACROS.h
 *
 * Created: 10/2/2019 1:01:38 PM
 *  Author: Red
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#define pb0		B, 0
#define pb1		B, 1
#define pb2		B, 2
#define pb3		B, 3
#define pb4		B, 4
#define pb5		B, 5
#define pb6		B, 6
#define pb7		B, 7

#define pc0		D, 0
#define pc1		D, 1
#define pc2		D, 2
#define pc3		D, 3
#define pc4		D, 4
#define pc5		D, 5
#define pc6		D, 6
#define pc7		D, 7

#define pd0		D, 0
#define pd1		D, 1
#define pd2		D, 2
#define pd3		D, 3
#define pd4		D, 4
#define pd5		D, 5
#define pd6		D, 6
#define pd7		D, 7

//							Pint state input / output
#define PinIO(			  	x, y)	( 		y 			?	_SET(DDR, x)	:	_CLEAR(DDR, x)		)
//							Internal pull up enable / disable
#define PinState(			x, y)	( 		y 			?	_SET(PORT, x)	:	_CLEAR(PORT, x)		)
//							Read pin state high / low
#define PinRead(  	  		x)		(						_GET(PIN, x)							)
//							Toggle DDRnx
#define IOToggle(		x)		(						_TOGGLE(DDR, x)							)
//							Toggle PORTnx
#define Toggle(			x)		(						_TOGGLE(PORT, x)						)

//General use bit manipulating commands
#define BitSet(		x, y)			(	x |=	 (1UL<<y)			)
#define BitClear(	x, y)			(	x &=	(~(1UL<<y))			)
#define BitToggle(	x, y)			(	x ^=	 (1UL<<y)			)
#define BitCheck(	x, y)			(	x &		 (1UL<<y)	? 1 : 0	)

//Access PORT, DDR and PIN
#define PORT(	port)				(_PORT(	port))
#define DDR(	port)				(_DDR(	port))
#define PIN(	port)				(_PIN(	port))

#define _PORT(	port)				(PORT##	port)
#define _DDR(	port)				(DDR##	port)
#define _PIN(	port)				(PIN##	port)

#define _SET(	type, port, bit)	(	BitSet(		(type##port),	bit)	)
#define _CLEAR(	type, port, bit)	(	BitClear(	(type##port),	bit)	)
#define _TOGGLE(type, port, bit)	(	BitToggle(	(type##port),	bit)	)
#define _GET(	type, port, bit)	(	BitCheck(	(type##port),	bit)	)

//Definitions
#define input		0
#define output		!input
#define low			0
#define high		!low
#define false		0
#define true		!false


void IO_init(void);

#endif /* MACROS_H_ */