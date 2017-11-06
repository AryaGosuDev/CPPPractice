/*
 * This file contains code from "C++ Primer, Fifth Edition", by Stanley B.
 * Lippman, Josee Lajoie, and Barbara E. Moo, and is covered under the
 * copyright and warranty notices given in that book:
 *
 * "Copyright (c) 2013 by Objectwrite, Inc., Josee Lajoie, and Barbara E. Moo."
 *
 *
 * "The authors and publisher have taken care in the preparation of this book,
 * but make no expressed or implied warranty of any kind and assume no
 * responsibility for errors or omissions. No liability is assumed for
 * incidental or consequential damages in connection with or arising out of the
 * use of the information or programs contained herein."
 *
 * Permission is granted for this code to be used for educational purposes in
 * association with the book, given proper citation if and when posted or
 * reproduced.Any commercial use of this code requires the explicit written
 * permission of the publisher, Addison-Wesley Professional, a division of
 * Pearson Education, Inc. Send your request for permission, stating clearly
 * what code you would like to use, and in what specific way, to the following
 * address:
 *
 * 	Pearson Education, Inc.
 * 	Rights and Permissions Department
 * 	One Lake Street
 * 	Upper Saddle River, NJ  07458
 * 	Fax: (201) 236-3290
*/

#ifndef _SALES_DATA_H
#define _SALES_DATA_H

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Sales_data {

	friend Sales_data add ( const Sales_data &, const Sales_data &);
	friend std::istream & read (std::istream &, Sales_data & );
	friend std::ostream & print ( std::ostream &, const Sales_data & );

public :

	Sales_data() = default ;
	Sales_data( std::istream & is = std::cin, std::string thisStr = "defStr" );
	Sales_data( int inI) : Sales_data ( std::cin ) { std::cout << "Run int const" << std::endl;}

	std::string isbn() const { return bookNo;}

	Sales_data & combine ( const Sales_data& rhs){
		units_sold += rhs.units_sold;
		revenue += rhs.revenue;
		return *this;
	}

private :

	inline double avg_price() const {
		if ( units_sold)
			return revenue / units_sold;
		else
			return 0;
	}

	std::string bookNo;
	unsigned units_sold = 0;
	double price = 0 ;
	double revenue = 0.0;
};

std::istream &read ( std::istream &is, Sales_data &item){
	is >> item.bookNo >> item.units_sold >> item.price ;
	item.revenue = item.price * item.units_sold ;
	return is;
}

std::ostream & print ( std::ostream &os, const Sales_data & item){
	os << item.isbn() << " " << item.units_sold << " " << item.price <<
	 " " << item.revenue << " " << item.avg_price() << std::endl ;
	 return os;
}

Sales_data add ( const Sales_data & lhs, const Sales_data & rhs){
	Sales_data sum = lhs;
	sum.combine( rhs );
	return sum;
}

Sales_data::Sales_data ( std::istream & is, std::string thisStr )
{
	std::cout << " Delegating constructor executed : " << thisStr << std::endl;
	read ( is, *this );
}

#endif
