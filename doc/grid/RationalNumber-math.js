//
// Programmer:	 Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Fri Dec 26 09:26:18 PST 2014
// Last Modified: Fri Jan  2 14:42:25 PST 2015
// Filename:		RationalNumber-math.js
// Syntax:			JavaScript 1.8.5/ECMAScript 5.1
// vim:				ts=3
//
// Description:	Mathematical operations for the RationalNumber object.
//

'use strict';

// If using node, load the constructor for RationalNumber:
if (typeof module !== 'undefined' && module.hasOwnProperty('exports')) {
	var RationalNumber = require('./RationalNumber-base.js');
}


//////////////////////////////
//
// RationalNumber.prototype.abs -- Return a new RationalNumber which is
//   the non-negative version of the calling object.
//

RationalNumber.prototype.abs = function () {
	return this.clone().setSign('+');
}



//////////////////////////////
//
// RationalNumber.prototype.invert -- Switch the numerator and denominator
//   in the calling object.
//

RationalNumber.prototype.invert = function () {
   var temp = this._n;
   this._n = this._d;
   this._d = temp;
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype.inversion -- Alias for getInversion().
// RationalNumber.prototype.getInversion -- Return the reciproical of
//    the RationalNumber object.  Returns a new RationalNumber and does 
//    not modify the calling object.
//

RationalNumber.prototype.getInversion = function () {
	var n = this.getNumerator();
	var d = this.getDenominator();
	return new RationalNumber(d, n);
}


RationalNumber.prototype.inversion = RationalNumber.prototype.getInversion;



//////////////////////////////
//
// RationalNumber.prototype.negate -- Make positive values negative and
//    negative values positive.
//

RationalNumber.prototype.negate = function () {
	this._s = -this._s;
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype.negation -- Alias of getNegation().
// RationalNumber.prototype.getNegation -- Return a copy of the object, with
//    the sign reversed.
//

RationalNumber.prototype.getNegation = function () {
	return this.clone().negate();
}



//////////////////////////////
//
// RationalNumber.prototype.addTo -- To this RationalNumber, add additional
//		RationalNumbers or integers.  If an input parameter is a string, then
//		parse as an integer, or as a fraction if '/' is found in the string.
//		The value of this object will be changed to the sum.

RationalNumber.prototype.addTo = function () {
	var a, ai, ao;
	var b, bi, bo;
	if ((arguments.length === 1) && (arguments[0] instanceof Array)) {
		this.addTo.apply(this, arguments[0]);
		return this;
	}
	for (var i=0; i<arguments.length; i++) {
		a = this.getNumerator();
		b = this.getDenominator();
		if (typeof arguments[i] === 'string') {
			var matches = arguments[i].match(/([+-]?\d+)[-+ _](\d+)\/(\d+)/);
			if (matches) {
				ai = parseInt(matches[2]);
				bi = parseInt(matches[3]);
				ai += bi * parseInt(matches[1]);
			} else {
				matches = arguments[i].match(/(-?\d+)\/(\d+)/);
				if (matches) {
					ai = parseInt(matches[1]);
					bi = parseInt(matches[2]);
				} else {
					ai = parseInt(arguments[i]) || 0;
					bi = 1;
  				}
			}
		} else if (typeof arguments[i] === 'number') {
			ai = arguments[i] ? parseInt(arguments[i]) : 0;
			bi = 1;
		} else if ((typeof arguments[i] === 'object') &&
			(this instanceof RationalNumber)) {
			ai = arguments[i].getNumerator();
			bi = arguments[i].getDenominator();
		} else {
			// Don't know what the object is, so skip it.
			continue;
		}

		if ((b === 0) && (bi === 0) && (a < 0) && (ai > 0)) {
			return this.setValue(0,0);
		}
		if ((b === 0) && (bi === 0) && (a > 0) && (ai < 0)) {
			return this.setValue(0,0);
		}
		if ((b  === 0) && (a  === 0)) { return this.setValue(0, 0) }
		if ((bi === 0) && (ai === 0)) { return this.setValue(0, 0) }
		if ((b  === 0) || (bi === 0)) { return this.setValue(1, 0) }

		// deal with infnities and NaNs here.
		ao = a * bi + b * ai;
		bo = b * bi;
		this.setValue(ao, bo);
	}
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype.add -- Similar to addTo(), but will not
//    alter the calling object and instead returns a new RationalNumber
//    which is the sum of the rational numbers.

RationalNumber.prototype.add = function () {
	return RationalNumber.prototype.addTo.apply(this.clone(), arguments);
}



//////////////////////////////
//
// RationalNumber.prototype.subtractTo -- To this RationalNumber, subtract
//		a RationalNumber or integer.  If an input parameter is a string, then
//		parse as an integer, or as a fraction if '/' is found in the string.
//		The value of this object will be changed to the difference value.
//    All arguments will be negated and the added to the initial value
//    of the object.

RationalNumber.prototype.subtractTo = function () {
	var a, ai, ao;
	var b, bi, bo;
	if ((arguments.length === 1) && (arguments[0] instanceof Array)) {
		this.subtractTo.apply(this, arguments[0]);
		return this;
	}
	for (var i=0; i<arguments.length; i++) {
		a = this.getNumerator();
		b = this.getDenominator();
		if (typeof arguments[i] === 'string') {
			var matches = arguments[i].match(/([+-]?\d+)[-+ _](\d+)\/(\d+)/);
			if (matches) {
				ai = parseInt(matches[2]);
				bi = parseInt(matches[3]);
				ai += bi * parseInt(matches[1]);
			} else {
				matches = arguments[i].match(/(-?\d+)\/(\d+)/);
				if (matches) {
					ai = parseInt(matches[1]);
					bi = parseInt(matches[2]);
				} else {
					ai = parseInt(arguments[i]) || 0;
					bi = 1;
  				}
			}
		} else if (typeof arguments[i] === 'number') {
			ai = arguments[i] ? parseInt(arguments[i]) : 0;
			bi = 1;
		} else if ((typeof arguments[i] === 'object') &&
			(this instanceof RationalNumber)) {
			ai = arguments[i].getNumerator();
			bi = arguments[i].getDenominator();
		} else {
			// Don't know what the object is, so skip it.
			continue;
		}

		if ((b === 0) && (bi === 0) && (a < 0) && (ai < 0)) {
			return this.setValue(0,0);
		}
		if ((b === 0) && (bi === 0) && (a > 0) && (ai > 0)) {
			return this.setValue(0,0);
		}
		if ((b  === 0) && (a  === 0)) { return this.setValue(0, 0) }
		if ((bi === 0) && (ai === 0)) { return this.setValue(0, 0) }
		if ((b  === 0) || (bi === 0)) { return this.setValue(1, 0) }

		ao = a * bi - b * ai;
		bo = b * bi;
		this.setValue(ao, bo);
	}
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype.subtract -- Similar to subtractTo(), but will not
//    alter the calling object and instead returns a new RationalNumber
//    which is the sum of the first numbers and the negation of the other
//    numbers.

RationalNumber.prototype.subtract = function () {
	return RationalNumber.prototype.subtractTo.apply(this.clone(), arguments);
}



//////////////////////////////
//
// RationalNumber.prototype.multiplyTo -- To this RationalNumber, multiply
//    additional RationalNumbers or integers.  If an input parameter is a
//    string, then parse as an integer, or as a fraction if '/' is found
//    in the string.  The value of this object will be changed to the sum.

RationalNumber.prototype.multiplyTo = function () {
	var a, ai, ao;
	var b, bi, bo;
	if ((arguments.length === 1) && (arguments[0] instanceof Array)) {
		this.multiplyTo.apply(this, arguments[0]);
		return this;
	}
	for (var i=0; i<arguments.length; i++) {
		a = this.getNumerator();
		b = this.getDenominator();
		if (typeof arguments[i] === 'string') {

			var matches = arguments[i].match(/([+-]?\d+)[-+ _](\d+)\/(\d+)/);
			if (matches) {
				ai = parseInt(matches[2]);
				bi = parseInt(matches[3]);
				ai += bi * parseInt(matches[1]);
			} else {
				matches = arguments[i].match(/(-?\d+)\/(\d+)/);
				if (matches) {
					ai = parseInt(matches[1]);
					bi = parseInt(matches[2]);
				} else {
					ai = parseInt(arguments[i]) || 0;
					bi = 1;
  				}
			}

		} else if (typeof arguments[i] === 'number') {
			ai = arguments[i] ? parseInt(arguments[i]) : 0;
			bi = 1;
		} else if ((typeof arguments[i] === 'object') &&
			(this instanceof RationalNumber)) {
			ai = arguments[i].getNumerator();
			bi = arguments[i].getDenominator();
		} else {
			// Don't know what the object is, so skip it.
			continue;
		}

      if (((a === 0) || (ai === 0)) && ((b === 0) || (bi === 0))) {
			return this.setValue(0,0);
		} else if ((b  === 0) || (bi === 0)) { 
			if ((a < 0) && (ai < 0)) {
				return this.setValue(1, 0) 
			} else if ((a >= 0) && (ai >= 0)) {
				return this.setValue(1, 0) 
			} else {
				return this.setValue(-1, 0) 
			}
		}

		ao = a * ai;
		bo = b * bi;
		this.setValue(ao, bo);
	}
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype.multiply -- Similar to multiplyTo(), but will not
//    alter the calling object and instead returns a new RationalNumber
//    which is the product of the rational numbers.

RationalNumber.prototype.multiply = function () {
	return RationalNumber.prototype.multiplyTo.apply(this.clone(), arguments);
}



//////////////////////////////
//
// RationalNumber.prototype.divideTo -- To this RationalNumber, divide
//    additional RationalNumbers or integers.  If an input parameter is a
//    string, then parse as an integer, or as a fraction if '/' is found
//    in the string.  The value of this object will be changed.

RationalNumber.prototype.divideTo = function () {
	var a, ai, ao;
	var b, bi, bo;
	if ((arguments.length === 1) && (arguments[0] instanceof Array)) {
		this.divideTo.apply(this, arguments[0]);
		return this;
	}
	for (var i=0; i<arguments.length; i++) {
		a = this.getNumerator();
		b = this.getDenominator();
		if (typeof arguments[i] === 'string') {

			var matches = arguments[i].match(/([+-]?\d+)[-+ _](\d+)\/(\d+)/);
			if (matches) {
				ai = parseInt(matches[2]);
				bi = parseInt(matches[3]);
				ai += bi * parseInt(matches[1]);
			} else {
				matches = arguments[i].match(/(-?\d+)\/(\d+)/);
				if (matches) {
					ai = parseInt(matches[1]);
					bi = parseInt(matches[2]);
				} else {
					ai = parseInt(arguments[i]) || 0;
					bi = 1;
  				}
			}

		} else if (typeof arguments[i] === 'number') {
			ai = arguments[i] ? parseInt(arguments[i]) : 0;
			bi = 1;
		} else if ((typeof arguments[i] === 'object') &&
			(this instanceof RationalNumber)) {
			ai = arguments[i].getNumerator();
			bi = arguments[i].getDenominator();
		} else {
			// Don't know what the object is, so skip it.
			continue;
		}

		if ((b  === 0) && (a  === 0)) { return this.setValue(0, 0) }
		if ((bi === 0) && (ai === 0)) { return this.setValue(0, 0) }
		if ((b  === 0) && (ai === 0)) { return this.setValue(0, 0) }
		if ((a  === 0) && (bi === 0)) { return this.setValue(0, 0) }

		ao = a * bi;
		bo = b * ai;
		this.setValue(ao, bo);
	}
	return this;
}



//////////////////////////////
//
// RationalNumber.prototype.divide -- Similar to divideTo(), but will not
//    alter the calling object and instead returns a new RationalNumber
//    which is the division of the rational numbers in the argument list.

RationalNumber.prototype.divide = function () {
	return RationalNumber.prototype.divideTo.apply(this.clone(), arguments);
}


///////////////////////////////////////////////////////////////////////////
//
// Export RationalNumber constructor if running in node:
//

if (typeof module !== 'undefined' && module.hasOwnProperty('exports')) {
	module.exports = RationalNumber;
}


