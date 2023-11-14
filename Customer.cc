// Customer.cc
#include <sstream>
#include <vector>
#include "Customer.hh"

using std::ostringstream;
using std::vector;

std::string Customer::statement()
{
  double totalAmount = 0;
  int frequentRenterPoints = 0;
  std::vector< Rental >::iterator iter = _rentals.begin();
  std::vector< Rental >::iterator iter_end = _rentals.end();
  std::ostringstream result;
  result << "Rental Record for " << getName() << "\n";
  for ( ; iter != iter_end; ++iter ) {
    double thisAmount = 0;
    Rental each = *iter;

    // determine amounts for each line
    thisAmount = each.getCharge();

    // add frequent renter points
    frequentRenterPoints++;
    // add bonus for a two day new release rental
    if ( ( each.getMovie().getPriceCode() == Movie::NEW_RELEASE )
         && each.getDaysRented() > 1 ) frequentRenterPoints++;

    // show figures for this rental
    result << "\t" << each.getMovie().getTitle() << "\t"
           << thisAmount << "\n";
    totalAmount += thisAmount;
  }
  // add footer lines
  result << "Amount owed is " << totalAmount << "\n";
  result << "You earned " << frequentRenterPoints
         << " frequent renter points";
  return result.str();
}

std::string Customer::htmlstatement(){
    std::vector< Rental >::iterator iter = _rentals.begin();
    std::vector< Rental >::iterator iter_end = _rentals.end();
    double totalAmount = 0;
    int frequentRenterPoints = 0;
	std::stringstream ss(statement());
	std::string output = "{\n\"name\": \""+ getName() + "\",\n\"rental\": [\n";
    for ( ; iter != iter_end; ++iter ) {
	    double thisAmount = 0;
	    Rental each = *iter;
	    thisAmount = each.getCharge();
	    frequentRenterPoints++;
        if ( ( each.getMovie().getPriceCode() == Movie::NEW_RELEASE )
             && each.getDaysRented() > 1 ) frequentRenterPoints++;
        output += "{\n";
        output += "\"movie_name\": " + each.getMovie().getTitle() + ",\n";
		output += "\"rent_price\": " + std::to_string(thisAmount) + ",\n";
		output += "},\n";
        totalAmount += thisAmount;
    }
    output += "],\n";
    output += "\"total_price\": " + std::to_string(totalAmount) + ",\n";
    output += "\"frequent_renter_points\": " + std::to_string(frequentRenterPoints) + ",\n";
    output += "},\n";
	return output;
}