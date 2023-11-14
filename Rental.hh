// Rental.hh
#ifndef RENTAL_HH
#define RENTAL_HH
#include "Movie.hh"

class Rental {
public:
  Rental( const Movie& movie, int daysRented );

  int getDaysRented() const;
  const Movie& getMovie() const;
  double getCharge() const;

private:
  Movie _movie;
  int _daysRented;
};

inline Rental::Rental( const Movie& movie, int daysRented ):
  _movie( movie ),
  _daysRented( daysRented ) {}

inline int Rental::getDaysRented() const { return _daysRented; }

inline const Movie& Rental::getMovie() const { return _movie; }

inline double Rental::getCharge() const{
	// determine amounts for each line
	float thisAmount = 0;
    switch ( _movie.getPriceCode() ) {
        case Movie::REGULAR:
            thisAmount += 2;
            if ( _daysRented > 2 )
                thisAmount += ( _daysRented - 2 ) * 1.5 ;
            break;
        case Movie::NEW_RELEASE:
            thisAmount += _daysRented * 3;
            break;
        case Movie::CHILDRENS:
            thisAmount += 1.5;
            if ( _daysRented > 3 )
                thisAmount += ( _daysRented - 3 ) * 1.5;
            break;
    }
	return thisAmount;
}	

#endif // RENTAL_HH
