//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Fri Dec 26 09:26:18 PST 2014
// Last Modified: Thu Jan  8 21:39:35 PST 2015
// Filename:      RationalNumber-base.js
// Syntax:        JavaScript 1.8.5/ECMAScript 5.1
// vim:           ts=3
//
// Description:   RationalNumber object for handling fractions.  Additional
//                prototype methods for arithmetic processing of rational
//                numbers are defined in RationalNumber-math.js.
//
// Constructor:
//    * RationalNumber
//
// Basic RationalNumber methods:
//    * RationalNumber.prototype.getSign
//    * RationalNumber.prototype.setSign
//    * RationalNumber.prototype.getNumerator
//    * RationalNumber.prototype.getNumeratorAbsoluteValue
//    * RationalNumber.prototype.setNumerator
//    * RationalNumber.prototype.setNumeratorNoReduce
//    * RationalNumber.prototype.setNumeratorAbsoluteValueNoReduce
//    * RationalNumber.prototype.getDenominator
//    * RationalNumber.prototype.setDenominatorAbsoluteValue
//    * RationalNumber.prototype.setDenominatorAbsoluteValueNoReduce
//    * RationalNumber.prototype.setValue
//    * RationalNumber.prototype.setValueNoReduce
//    * RationalNumber.prototype.reduce
//
// RationalNumber methods for checking validity:
//    * RationalNumber.prototype.isSafe
//    * RationalNumber.prototype.checkOverflowOn
//    * RationalNumber.prototype.checkOverflowOff
//    * RationalNumber.prototype.checkOverflow
//    * RationalNumber.prototype.isValid
//    * RationalNumber.prototype.isNaN
//    * RationalNumber.prototype.isInfinite
//
// RationalNumber import/export methods:
//    * RationalNumber.prototype.valueOf/toFloat/toNumber
//    * RationalNumber.prototype.toString
//    * RationalNumber.prototype.toStringMixed
//    * RationalNumber.prototype.toJSON
//    * RationalNumber.prototype.toFloatJSON
//    * RationalNumber.prototype.toFloatArray
//
// RationalNumber import methods:
//    * RationalNumber.prototype.parseString
//    * RationalNumber.prototype.fromString
//    * RationalNumber.prototype.fromStringNoReduce
//    * RationalNumber.prototype.copy
//    * RationalNumber.prototype.clone
//
// Internal RationalNumber helper methods:
//    * RationalNumber.prototype.gcdIterative
//    * RationalNumber.prototype.gcdRecursive
//
// Boolean and comparison methods:
//    * RationalNumber.prototype.isEqual
//    * RationalNumber.prototype.isPositive
//    * RationalNumber.prototype.isNegative
//    * RationalNumber.prototype.isInteger
//
// Arithmetic processing methods (found in RationalNumber-math.js):
//    * RationalNumber.prototype.invert
//    * RationalNumber.prototype.inversion/getInversion
//    * RationalNumber.prototype.negate
//    * RationalNumber.prototype.negation
//    * RationalNumber.prototype.addTo
//    * RationalNumber.prototype.add
//    * RationalNumber.prototype.subtractTo
//    * RationalNumber.prototype.subtract
//    * RationalNumber.prototype.multiplyTo
//    * RationalNumber.prototype.multiply
//    * RationalNumber.prototype.divideTo
//    * RationalNumber.prototype.divide
//

'use strict';

//////////////////////////////
//
// RationalNumber constructor -- The RationalNumber object is used to manage
//    fractions.  It is implemented as two integers which store the
//    numerator and denominator as well as a variable to keep track of the
//    sign of the rational number.  These values can be set with
//    setNumerator / setDenominatorAbsoluteValue methods which will
//    automatically reduce the fraction, or with setNumeratorNoReduce /
//    setDenominatorAbsoluteValueNoReduce which will not check for
//    reducing the fraction after the values have been updated.  The sign
//    of the fraction is expected to be attached to the numerator only.
//    Any sign on the denominator will be ignored.  Another RationalNumber
//    can be used to initialize the contents of the object instead of two
//    integers.
//
//    Four types of inputs are allowed:
//       (1) One or two numbers representing the numerator and denominator.
//       (2) One RationalNumber object to be copied.
//       (3) One string object representing a fraction or a mixed fraction,
//           such as "5/4" or "-1-1/2" or "1+4/5" or "1 4/5".
//       (4) No inputs, in which case the value will be set to +0/1.
//

function RationalNumber(topnum, botnum) {
	// pseudo-private variables -- The _n, _d, and _s variables should not
	// be set directly, instead use the accessor methods:
	//    getNumerator, setNumerator, setNumeratorNoReduce
	//    getDenominator, setDenominatorAbsoluteValue,
	//    setDenominatorAbsoluteValueNoReduce, getSign, setSign
	// If these variables are actually made private (including privileged
	// accessor methods), then the code will run 30x slower (in node 0.10.35).
	// Directly setting either value to a non-integer is not supported.
	// The input numerator should be in the range from -(2^53-1) to (2^53-1),
	// and the denominator should be in the range from 0 to (2^53-1).
	if (!arguments.length) {
		// The default value if no arguments is +0/1 = 0.
		this._n = 0;  // default value for the numerator
		this._d = 1;  // default value for the denominator
		this._s = 1;  // default value for the sign (1=positive, -1=negative)
	} else if (arguments[0] instanceof RationalNumber) {
		this._n = arguments[0]._n;
		this._d = arguments[0]._d;
		this._s = arguments[0]._s;
	} else if ((arguments.length === 1) && (typeof arguments[0] === 'string')) {
		this.fromString(arguments[0]);
	} else if (arguments.length === 2) {
		this.setValue(topnum, botnum);
   } else if (arguments.length === 1) {
		this.setNumeratorNoReduce(topnum);
		this._d = 1;
	}
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype._overflowCheck -- Internal state variable for
//    checking that a RationalNumber represents a valid number.  In other
//    words, the values of the numerator and denominator are in the range from
//    0 to (2^53-1).  Use checkOverflowOn(), checkOverflowOff() to toggle
//    the checking.  The default state is off.
//

RationalNumber.prototype._overflowCheck = false;


///////////////////////////////////////////////////////////////////////////
//
// Core RationalNumber methods --
//

//////////////////////////////
//
// RationalNumber.prototype.setSign -- Set the sign to positive or negative.
//    Usually the sign is taken from the numerator value, but it can be
//    set separately wth this method.
//

RationalNumber.prototype.setSign = function (sign) {
	if (typeof sign === 'number') {
		this._s = (sign < 0) ? -1 : +1;
	} else if (typeof sign === 'string') {
		this._s = ((sign === '-') || (sign === 'negative') || 
			(sign === 'minus')) ? -1 : +1;
	} else if (sign instanceof RationalNumber) {
		this._s = sign._s;
	} else {
		this._s = +1;
	}
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype.getSign -- returns +1 if positive,
//    or -1 if negative.  The value 0 will return +1.
//

RationalNumber.prototype.getSign = function () {
	return this._s < 0 ? -1 : +1;
}



//////////////////////////////
//
// RationalNumber.prototype.getNumerator -- Return the top integer in
//    the rational-number fraction.
//

RationalNumber.prototype.getNumerator= function () {
	if (this._s >= 0) {
		return this._n;
	} else {
		return -this._n;
	}
}



//////////////////////////////
//
// RationalNumber.prototype.getNumeratorAbsoluteValue -- Return the
//    absolute value of the top integer in the rational-number fraction,
//

RationalNumber.prototype.getNumeratorAbsoluteValue = function () {
	return this._n;
}



//////////////////////////////
//
// RationalNumber.prototype.getDenominator -- Return the bottom integer in
//    the rational-number fraction.  Should always be non-negative.
//

RationalNumber.prototype.getDenominator = function () {
	return this._d;
}



//////////////////////////////
//
// RationalNumber.prototype.setNumeratorNoReduce -- Set the numerator,
//    but do not try to reduce the fraction.  The sign of the input
//    number will be used to set the sign of the rational number.
//

RationalNumber.prototype.setNumeratorNoReduce = function (topval) {
	this._n = parseInt(topval) || 0;
	if (this._n < 0) {
		this._s = -1;
		this._n = -this._n;
	} else {
		this._s = 1;
	}
	if (this._overflowCheck) { this.checkOverflow(); }
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype.setNumerator -- Set the numerator of the
//    fraction, and reduce the fraction if needed.
//

RationalNumber.prototype.setNumerator = function (input) {
	this.setNumeratorNoReduce(input);
	this.reduce();
	return this;
};



//////////////////////////////
//
// RationalNumber.prototype.setNumeratorAbsoluteValueNoReduce -- Set
//    the numerator, ignoring the sign of the number and not trying to
//    reduce the fraction.
//

RationalNumber.prototype.setNumeratorAbsoluteValueNoReduce = function (topval) {
	this._n = Math.abs(parseInt(topval) || 0);
	if (this._overflowCheck) { this.checkOverflow(); }
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype.setDenominatorAbsoluteValue -- Set the denominator
//    of the fraction, and reduce the fraction if needed.  Absolute values
//    of negative values will be used.  There is no setDenominator() function,
//    use setValue() if you really need to set a negative denominator for some
//    reason.
//

RationalNumber.prototype.setDenominatorAbsoluteValue = function (input) {
	this.setDenominatorAbsoluteValueNoReduce(input);
	this.reduce();
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype.setDenominatorAbsoluveValueNoReduce -- Set
//    the denominator, but do not try to reduce the fraction.  If the
//    value is an invalid string or falsy, then set the denominator to 1
//    rather than 0 or NaN.  The denominator cannot be used to set a negative
//    value; so the absolute value of negative numbers will be used instead.
//

RationalNumber.prototype.setDenominatorAbsoluteValueNoReduce =
	function (botval) {
		if (typeof botval === 'undefined') {
			botval = 1;
		} else {
			botval = parseInt(botval) || 0;
		}
		this._d = Math.abs(botval);
		if (this._overflowCheck) { this.checkOverflow(); }
		return this;
	}




//////////////////////////////
//
// RationalNumber.prototype.reduce -- Reduce the fraction by
//    dividing the numerator and denominator values by their
//    greatest common divisor/factor.
//

RationalNumber.prototype.reduce = function() {
	var topval = this._n;
	var botval = this._d;
	if ((topval === 1 || botval === 1)) {
		// Can't be reduced further, so don't try.
		return this;
	}
	if (topval === 0) {
		// 0/x will be converted into 0/1 (zero).
		if (botval !== 0) {
			this._d = 1;
		}
		return this;
	} else if (botval === 0) {
		// x/0 will be converted into 1/0 (Infinity).
		if (topval !== 0) {
			this._n = 1;
		}
		return this;
	}
	var gcdval = this.gcdIterative(topval, botval);
	if (gcdval > 1) {
		this._n /= gcdval;
		this._d /= gcdval;
		if (this._overflowCheck) { this.checkOverflow(); }
	}
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype.setValue -- Set the numerator and denominator
//    at the same time, including reducing the fraction after both have been
//    set.  This method is typically better than using setNumerator and
//    setDenominatorAbsoluteValue separately since they will try to reduce
//    the fraction independently.  Either or both of the numerator
//    and denominator can be negative.  If both are negative, then the
//    final number will be positive.
//

RationalNumber.prototype.setValue = function (topval, botval) {
	return RationalNumber.prototype.setValueNoReduce.apply(this, arguments)
		.reduce();
}



//////////////////////////////
//
// RationalNumber.prototype.setValueNoReduce -- Set the numerator and
//    denominator at the same time, but do not try to reduce fraction.
//    Either or both of the numerator and denominator can be negative.
//    If both are negative, then the final number will be positive.
//    Also, another RationalNumber can be used to set the value of
//    the object.
//

RationalNumber.prototype.setValueNoReduce = function (topval, botval) {
	if ((arguments.length == 1)) {
		if (arguments[0] instanceof RationalNumber) {
			this._n = arguments[0]._n;
			this._d = arguments[0]._d;
			this._s = arguments[0]._s;
			return this;
		} else if (typeof arguments[0] === 'string') {
			this.fromStringNoReduce(arguments[0]);
			return this;
		}
	}
	topval = parseInt(topval) || 0;
	if ((typeof botval === 'undefined') || 
			((typeof botval === 'string') && (botval === ''))) {
		botval = 1;
	} else {
		botval = parseInt(botval) || 0;
	}
	if (botval < 0) {
		botval = -botval;
		topval = -topval;
	}
	this.setNumeratorNoReduce(topval);
	this.setDenominatorAbsoluteValueNoReduce(botval);
	return this;
}




///////////////////////////////////////////////////////////////////////////
//
// RationalNumber methods for checking validity:
//

//////////////////////////////
//
// RationalNumber.prototype.isSafe -- Fractions can only be represented
//    in the RationalNumber class properly when the numerator is in the
//    range from -(2^53-1) to (2^53-1) and the denominator in the range
//    from 0 to (2^53-1).  If the numbers are out of that range, then the
//    fraction cannot be expected to be valid.  When doing arithmetic
//    with RationalNumbers, you should check if the RationalNumbers are
//    safe after each operation if you want to guarantee that the final
//    result is valid; otherwise, it is possible that the final result is
//    safe but an intermediate value was not, so the final result will be
//    garbage.
//
//    The RationalNumber object is not intended to be used with very large
//    numerators or denominators, so the arithmetic methods do not check
//    safeness when processing numbers by default.  See the checkOverflowOn()
//    function for monitoring overflows in the numerator or denominator values.
//
//    There is no reason for the denominator to be negative so its sign is
//    always ignored when setting it.  Setting the denominator
//    to zero will cause an Infinite number which is considered "safe",
//    but see isValid() which does not like Infinities or NaNs generated
//    by safe integers.  Note that Infinity = 1/0, -Infinity = -1/0,
//    and NaN = 0/0 are safe numbers since they can be represented by the
//    integers 0 and 1.  Use isNaN() and isInfinite() to check those
//    specific values, or isValid() to check that the number is safe, and
//    not infinite and not NaN.
//
//    Internally the numerator is always stored as a non-negative number,
//    so the safety check only check that its range is from 0 to 2^53-1.
//    If you set this._n to any negative number, then it is your fault,
//    and the RationalNumber is identified as "unsafe".
//

RationalNumber.prototype.isSafe = function () {
	var n;
	var d;

	if (arguments.length > 0) {
		if (typeof arguments[0] === 'number') {
			n = Math.abs(parseInt(arguments[0]));
			d = Math.abs(parseInt(arguments[1] || 0));
		} else if (arguments[0] instanceof RationalNumber) {
			n = arguments[0].getNumeratorAbsoluteValue();
			d = arguments[0].getDenominator();
		} else if (typeof arguments[0] === 'string') {
			var temp = new RationalNumber(arguments[0]);
			n = temp.getNumerator();
			d = temp.getDenominator();
		}
	} else {
		n = this.getNumeratorAbsoluteValue();
		d = this.getDenominator();
	}

	// ECMAScript 5 compatibility:
	// (Math.pow(2, 53) - 1) = 9007199254740991
	var maxval = Number.MAX_SAFE_INTEGER || 9007199254740991;

	if ((n<0) || (n>maxval) || (d<0) || (d>maxval)) {
		return false;
	} else {
		return true;
	}
}



//////////////////////////////
//
// RationalNumber.prototype.isNaN -- Returns true if both numerator
//    and denominator are zero.
//

RationalNumber.prototype.isNaN = function () {
	if ((this._d === 0) && (this._n === 0)) {
		return true;
	} else {
		return false;
	}
}



//////////////////////////////
//
// RationalNumber.prototype.isInfinite -- Returns true if numerator
//    is not zero but denominator is zero.  Both -Infinity and Infinity
//    values will return true.
//

RationalNumber.prototype.isInfinite = function () {
	if ((this._d === 0) && (this._n > 0)) {
		return true;
	} else {
		return false;
	}
}



//////////////////////////////
//
// RationalNumber.prototype.isValid -- returns true if safe, not infinite,
//   and not NaN.
//

RationalNumber.prototype.isValid = function () {
	return this.isSafe() && (!this.isNaN()) && (!this.isInfinite());
}



//////////////////////////////
//
// RationalNumber.prototype.checkOverflow -- Same as isSafe(), but
//   throws an error if the number is not safe.
//

RationalNumber.prototype.checkOverflow = function () {
	if (!this.isSafe()) {
		throw new Error('RationalNumber is not safe: ' + String(this));
		return true;
	}
	return false;
}



//////////////////////////////
//
// RationalNumber.prototype.checkOverflowOn -- Force validity check for every
//    operation which may cause the numerator or denominator to overflow
//    the maximum representable integer (2^53-1).  All RationalNumbers will
//    be checked if this method is called from any RationalNumber object.
//

RationalNumber.prototype.checkOverflowOn = function () {
	RationalNumber.prototype._overflowCheck = true;
}



//////////////////////////////
//
// RationalNumber.prototype.checkOverflowOff -- Suppress validity check
//    for every operation which may cause the numerator or denominator
//    to overflow the maximum representable integer (2^53-1).  All
//    RationalNumbers will no longer be automatically checked if this
//    method is called from any RationalNumber object.
//

RationalNumber.prototype.checkOverflowOff = function () {
	RationalNumber.prototype._overflowCheck = false;
}



//////////////////////////////
//
// RationalNumber.prototype.toFloat -- Alias for valueOf.
// RationalNumber.prototype.toNumber -- Alias for valueOf.
// RationalNumber.prototype.valueOf -- Return the floating-point version
//     of the rational number.
//

RationalNumber.prototype.valueOf = function() {
	return this.getNumerator() / this.getDenominator();
}


RationalNumber.prototype.toFloat = RationalNumber.prototype.valueOf;
RationalNumber.prototype.toNumber = RationalNumber.prototype.valueOf;



//////////////////////////////
//
// RationalNumber.prototype.toString -- Return a string in the form of
//  %d/%d representing the fractional form of the number.  If the denominator
//  is 1, then don't print it (or the preceding slash).
//
// For Infinity or -Infinity, toString() will print 1/0 and -1/0 which
// is the internal representations for these numbers.  NaN will be printed
// as 0/0.  The toStringMixed() will instead output Infinity, -Infinity, and
// NaN.
//

RationalNumber.prototype.toString = function() {
	if (this.getDenominator() === 1) {
		return this.getNumerator().toString();
	} else {
		return this.getNumerator() + '/' + this.getDenominator();
	}
}



//////////////////////////////
//
// RationalNumber.prototype.toStringMixed -- Return a string as a mixed
//    fraction in the form %d+%d/%d or -%d-%d/%d.  Optional parameters:
//       0th: separator between integer and fractional part when the
//            value is positive;
//       1st: separator between integer and fractional part when the
//            value is negative;
//       2nd: string to place before integer part.
//       3rd: string to place after fractional part.
//    Examples:
//       21/2 =  10+1/2
//      -21/2 = -10-1/2
//    Using toStringMixed(' '):
//       21/2 =  10 1/2
//      -21/2 = -10 1/2
//    Using toStringMixed(', ', ', -', '(', ')'):
//       21/2 = (10, 1/2)
//      -21/2 = (-10, -1/2)
//

RationalNumber.prototype.toStringMixed = function () {
	var n = this.getNumerator();
	var d = this.getDenominator();

	var positive = '+';
	var negative = '-';
	var prefix   = '';
	var postfix  = '';
	switch (arguments.length) {
		case 0:
			break;
		case 1:
			positive = String(arguments[0]);
			negative = positive;
			break;
		case 2:
			positive = String(arguments[0]);
			negative = String(arguments[1]);
		case 3:
			positive = String(arguments[0]);
			negative = String(arguments[1]);
			prefix   = String(arguments[2]);
		case 4:
		default:
			positive = String(arguments[0]);
			negative = String(arguments[1]);
			prefix   = String(arguments[2]);
			postfix  = String(arguments[3]);
			break;
	}

	if (d === 1) {
		return this.getNumerator().toString();
	} else if (d === 0) {
	   if (n === 0) {
			return prefix + NaN + postfix;
		} else {
			return prefix + (this._s < 0 ? '-' : '')  + Infinity + postfix;
		}
	}

	var intval = Math.floor(Math.abs(n/d));
	if (intval === 0) {
		return prefix + n + '/' + d + postfix;
	} else if (n > 0) {
		n -= intval * d;
		return prefix + intval + positive + n + '/' + d + postfix;
	} else {
		n += intval * d;
		return prefix + -intval + negative + Math.abs(n) + '/' + d + postfix;
	}
}



//////////////////////////////
//
// RationalNumber.prototype.toJSON -- return a JSON string in the form:
//    { "n":#, "d":#}
// where "n" is the numerator and "d" is the denominator.  If the
// denominator is 1, then it is not included.  The "n" and "d" property
// names can be changed with the optional parameters.
//

RationalNumber.prototype.toJSON = function (ntag, dtag) {
	if (typeof ntag === 'undefined') { ntag = 'n' };
	if (typeof dtag === 'undefined') { dtag = 'd' };
	ntag = '"' + ntag + '":';
	dtag = '"' + dtag + '":';
	var n = this.getNumeratorAbsoluteValue();
	var d = this.getDenominator();
	var s = this._s < 0 ? '-' : '';
	return '{' + ntag + s + n + (d === 1 ? '' : ', ' + dtag + d) + '}';
}



//////////////////////////////
//
// RationalNumber.prototype.toFloatJSON -- return a JSON string in the form:
//         { "f":#, "n":#, "d":#}
//    where "f" is the floating-point version of the RationalNumber (or
//    +/-Infinity or NaN, "n" is the numerator of the mixed fraction
//    numerator, and "d" is the denominator of the mixed fraction
//    denominator.  In other words, the "n" and "d" values are the
//    RationalNumber equivalent to the fractional part of "f".  If the
//    floating-point value is an integer, which means that the mixed
//    fraction numerator is 0 (and denominator is 1), then they are not
//    included.  The "f", "n", and "d" property names can be changed with
//    the optional parameters.
//
// Examples:
//     7/2 =>   {"f":3.5, "n":1, "d":2}
//     4/3 =>   {"f":1.33333333333, "n":1, "d":3}
//   -11/5 =>   {"f":-2.2, "n":1, "d":5}
//     100 =>   {"f":100}
//

RationalNumber.prototype.toFloatJSON = function (ftag, ntag, dtag) {
	if (typeof ftag === 'undefined') { ftag = 'f' };
	if (typeof ntag === 'undefined') { ntag = 'n' };
	if (typeof dtag === 'undefined') { dtag = 'd' };
	ftag = '"' + ftag + '":';
	ntag = '"' + ntag + '":';
	dtag = '"' + dtag + '":';
	var n = this.getNumeratorAbsoluteValue();
	var d = this.getDenominator();
	var f = this.valueOf();
	if (isNaN(f) || (f === Infinity) || (f === -Infinity)) {
		f = '"' + f + '"';
		n = 0;
	} else {
		n = n - Math.abs(parseInt(f)) * d;
	}
	return '{'+ftag+f+ (n===0 ? '' : ', ' + ntag + n + ', ' + dtag + d) + '}';
}



//////////////////////////////
//
// RationalNumber.prototype.toFloatArray -- Similar toFloatJSON, but
//   values are stored in an Array.  The first value is always the
//   floating-point representation of the RationalNumber.  The input
//   parameter "expanded" is a boolean, with "true" meaning to include
//   the mixed-fraction numerator and denominator even if they are
//   0 and 1 respectively.
//
// Examples:
//            expanded->falsey          expanded->truthy
//    7/2 =>  [3.5, 1, 2]	             [3.5, 1, 2]
//    4/3 =>  [1.33333333333, 1, 3]     [1.33333333333, 1, 3]
//  -11/5 =>  [-2.2, 1, 5]              [-2.2, 1, 5]
//    100 =>  [100]                     [100, 0, 1]
//
//

RationalNumber.prototype.toFloatArray = function (expanded) {
   var output = new Array;
   var n = this.getNumeratorAbsoluteValue();
   var d = this.getDenominator();
   var f = this.valueOf();
	if (isNaN(f) || (f === Infinity) || (f === -Infinity)) {
		n = 0;
		d = 1;
	} else {
		n = n - Math.abs(parseInt(f)) * d;
	}
	output.push(f);
	if (!!expanded || (n !== 0)) {
		output.push(n);
		output.push(d);
	}
	return output;
}



//////////////////////////////
//
// RationalNumber.prototype.fromString -- Set the rational number from a
//    string and then reduce the fraction if necessary.
//

RationalNumber.prototype.fromString = function (number) {
	return RationalNumber.prototype.fromStringNoReduce.apply(this, arguments)
		.reduce();
}



//////////////////////////////
//
// RationalNumber.prototype.fromStringNoReduce -- Set the rational number
//    from a string, but don't try to reduce the fraction.
//    Understandable string formats are:
//       * Integers, such as: 1, 45, -53, 0.
//       * Two integers separated by a slash:  1/4, -52/54 (fractional
//          portions of numbers are ignored; no spaces around slash).
//       * 5/-6 is equivalent to -5/6.
//       * Mixed fraction:   1+1/2, -1-1/2, "1 1/2", "-1 1/2".
//          "-1+1/2" will be treated as "-1-1/2" which is equal to -1.5.
//       * 2+5/-6 is not a proper input, since the sign of mixed fractions
//          is taken only from initial integer.  In this case the string
//          will be treated as "2+5/6".
//
//    Note that fractional values of numbers will be ignored.
//

RationalNumber.prototype.fromStringNoReduce = function (number) {
	var n;
	var d;
	if (typeof number !== 'string') {
		number = String(number);
	} else {
		if (number === 'NaN') {
			this.setValueNoReduce(0, 0);
			return this;
		} else if (number === 'Infinity') {
			this.setValueNoReduce(1, 0);
			return this;
		} else if (number === '-Infinity') {
			this.setValueNoReduce(-1, 0);
			return this;
		}
   }
	var matches = number.match(/([+-]?\d+)[-+ _](\d+)(\.\d*)?\/(\d+)(\.\d*)?/);
	if (matches) {
		n = parseInt(matches[2]);
		d = parseInt(matches[4]);
		var int = parseInt(matches[1]);
		if (int < 0) {
			n = -n + (d*int);
		} else {
			n += d * int;
		}
		this.setValueNoReduce(n, d);
	} else {
		matches = number.match(/([-+]?\d+)(\.\d*)?\/([-+]?\d+)(\.\d*)?/);
		if (matches) {
			n = parseInt(matches[1]);
			d = parseInt(matches[3]);
		} else {
			n = parseInt(number) || 0;
			d = 1;
		}
		this.setValueNoReduce(n, d);
	}
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype.parseString -- same as fromString(), but returns
//    a new RationalNumber rather than assigning to the object.  The
//    RationalNumber contructor will handle the parsing rather than
//    fromString(), so technically can import another RationalNumber
//    or integers.  The original object will not be modified.
//

RationalNumber.prototype.parseString = function (number) {
	return new RationalNumber(number);
}



//////////////////////////////
//
// RationalNumber.prototype.clone -- Make a new copy of the given
//   RationalNumber.  The original object is not modified.
//

RationalNumber.prototype.clone = function () {
	return new RationalNumber(this);
}



//////////////////////////////
//
// RationalNumber.prototype.copy -- Copy internal contents from
//    another RationalNumber given as the argument.
//

RationalNumber.prototype.copy = function (rn) {
	if (rn instanceof RationalNumber) {
		this._n = rn._n;
		this._d = rn._d;
		this._s = rn._s;
	} else {
		throw new Error ("Input to RationalNumber.prototype.copy is invalid");
	}
	return this;
}


///////////////////////////////////////////////////////////////////////////
//
// pseudo-private prototype methods:
//
// Greatest Common Divisor/Factor between two numbers, used to simplify
// fractions in the reduce method.  Two versions: one which is
// recursive and the other which is iterative (swap each in reduce()
// to test the most efficient for your application).  In node 0.10.35,
// gcdIterative runs 11% faster on average than gcdRecursive.
//

RationalNumber.prototype.gcdRecursive = function (a, b) {
	if (!b) {
		return Math.abs(a);
	} else {
		return this.gcdRecursive(b, a % b);
	}
}


RationalNumber.prototype.gcdIterative = function (a, b) {
	a = Math.abs(a);
	b = Math.abs(b);
	if (!a) { return b; }
	if (!b) { return a; }
	if (b > a) {var temp = a; a = b; b = temp;}
	while (true) {
		a %= b;
		if (!a) { return b; }
		b %= a;
		if (!b) { return a; }
	}
}


///////////////////////////////////////////////////////////////////////////
//
// Boolean and comparison methods:
//

//////////////////////////////
//
//  RationalNumber.prototype.isEqual -- returns true if the sign, numerator
//    and denominator are equal.  If one number is reduced and the other is
//    not, then false will be returned.  Cast to Numbers if you want to
//    also consider different unreduced versions of rational numbers.
//

RationalNumber.prototype.isEqual = function (number) {
	if (typeof number === 'undefined') { return false }
	if (!(number instanceof RationalNumber)) {
		number = new RationalNumber(number);
	}
	if ((this._n === number._n) && (this._d === number._d) 
			&& (this._s === number._s)) {
		return true;
	} else {
		return false;
	}
}



//////////////////////////////
//
//  RationalNumber.prototype.isPositive -- returns true if larger than 0.
//

RationalNumber.prototype.isPositive = function () {
	return (this._s > 0) && (this._n > 0);
}



//////////////////////////////
//
//  RationalNumber.prototype.isNegative -- returns true if smaller than 0.
//

RationalNumber.prototype.isNegative = function () {
	return (this._s < 0) && (this._n > 0);
}



//////////////////////////////
//
//  RationalNumber.prototype.isInteger -- returns true if denominator is 1.
//

RationalNumber.prototype.isInteger = function () {
	return this._d === 1;
}


///////////////////////////////////////////////////////////////////////////
//
// Export RationalNumber constructor if running in node:
//

if (typeof module !== 'undefined' && module.hasOwnProperty('exports')) {
	module.exports = RationalNumber;
}



